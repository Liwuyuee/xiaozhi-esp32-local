/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/queue.h>

#include "esp_log.h"
#include "esp_check.h"
#include "esp_system.h"

#include "usb/usb_host.h"
#include "usb/uvc_host.h"
#include "uvc_control.h"
#include "uvc_stream.h"
#include "uvc_esp_video.h"
#include "uvc_types_priv.h"
#include "uvc_frame_priv.h"
#include "uvc_descriptors_priv.h"
#include "uvc_check_priv.h"
#include "uvc_critical_priv.h"
#include "uvc_idf_version_priv.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

static const char *TAG = "uvc";

// UVC spinlock
portMUX_TYPE uvc_lock = portMUX_INITIALIZER_UNLOCKED;

// UVC driver status
#define UVC_STARTED           BIT0 // UVC driver events handling started
#define UVC_TEARDOWN          BIT1 // UVC is being uninstalled
#define UVC_TEARDOWN_COMPLETE BIT2 // UVC uninstall finished

// Transfer callbacks
static void ctrl_xfer_cb(usb_transfer_t *transfer);
void isoc_transfer_callback(usb_transfer_t *transfer);
void bulk_transfer_callback(usb_transfer_t *transfer);

// UVC driver object
typedef struct {
    usb_host_client_handle_t usb_client_hdl;    /*!< USB Host handle reused for all UVC devices in the system */
    SemaphoreHandle_t open_close_mutex;         /*!< Protects list of opened devices from concurrent access */
    EventGroupHandle_t driver_status;           /*!< Holds status of the driver */
    usb_transfer_t *ctrl_transfer;              /*!< CTRL (endpoint 0) transfer */
    SemaphoreHandle_t ctrl_mutex;               /*!< CTRL mutex */
    uvc_host_driver_event_callback_t user_cb;   /*!< Callback function to handle events */
    void *user_ctx;
    SLIST_HEAD(list_dev, uvc_host_stream_s) uvc_stream_list;   /*!< List of open streams */
} uvc_host_driver_t;

static uvc_host_driver_t *p_uvc_host_driver = NULL;

static esp_err_t uvc_host_interface_check(uint8_t addr, const usb_config_desc_t *config_desc)
{
    assert(config_desc);
    size_t total_length = config_desc->wTotalLength;
    int iface_offset = 0;
    bool is_uvc_interface = false;
    uint8_t uvc_stream_index = 0;

    // Get first Interface descriptor
    // Check every uac stream interface
    const usb_standard_desc_t *current_desc = (const usb_standard_desc_t *)config_desc;
    while ((current_desc = usb_parse_next_descriptor_of_type((const usb_standard_desc_t *)current_desc, total_length, USB_B_DESCRIPTOR_TYPE_INTERFACE, &iface_offset))) {
        const usb_intf_desc_t *iface_desc = (const usb_intf_desc_t *)current_desc;
        if (USB_CLASS_VIDEO == iface_desc->bInterfaceClass && UVC_SC_VIDEOCONTROL == iface_desc->bInterfaceSubClass) {
            // notify user about the connected Interfaces
            is_uvc_interface = true;

            if (p_uvc_host_driver->user_cb) {
                size_t frame_info_num = 0;
                if (uvc_desc_get_frame_list(config_desc, uvc_stream_index, NULL, &frame_info_num) != ESP_OK) {
                    ESP_LOGE(TAG, "Failed to get frame list for uvc_stream_index %d", uvc_stream_index);
                    return ESP_FAIL;
                }

                const uvc_host_driver_event_data_t conn_event = {
                    .type = UVC_HOST_DRIVER_EVENT_DEVICE_CONNECTED,
                    .device_connected.dev_addr = addr,
                    .device_connected.uvc_stream_index = uvc_stream_index,
                    .device_connected.frame_info_num = frame_info_num
                };
                p_uvc_host_driver->user_cb(&conn_event, p_uvc_host_driver->user_ctx);
            }
            uvc_stream_index++;
        }
    }

    return is_uvc_interface ? ESP_OK : ESP_ERR_NOT_FOUND;
}

/**
 * @brief Handler for USB device connected event
 *
 * @param[in] addr   USB device physical address
 * @return esp_err_t
 */
static esp_err_t uvc_host_device_connected(uint8_t addr)
{
    bool is_uvc_device = false;
    usb_device_handle_t dev_hdl;
    const usb_config_desc_t *config_desc = NULL;

    if (usb_host_device_open(p_uvc_host_driver->usb_client_hdl, addr, &dev_hdl) == ESP_OK) {
        if (usb_host_get_active_config_descriptor(dev_hdl, &config_desc) == ESP_OK) {
            is_uvc_device = uvc_desc_is_uvc_device(config_desc);
        }
        ESP_RETURN_ON_ERROR(usb_host_device_close(p_uvc_host_driver->usb_client_hdl, dev_hdl), TAG, "Unable to close USB device");
    }

    // Create UAC interfaces list in RAM, connected to the particular USB dev
    if (is_uvc_device) {
#ifdef CONFIG_UVC_PRINTF_CONFIGURATION_DESCRIPTOR
        usb_print_config_descriptor(config_desc, &uvc_print_desc);
#endif // CONFIG_UVC_PRINTF_CONFIGURATION_DESCRIPTOR
        // Create Interfaces list for a possibility to claim Interface
        ESP_RETURN_ON_ERROR(uvc_host_interface_check(addr, config_desc), TAG, "uvc stream interface not found");
    } else {
        ESP_LOGW(TAG, "USB device with addr(%d) is not UVC device", addr);
    }

    return is_uvc_device ? ESP_OK : ESP_ERR_NOT_FOUND;
}

/**
 * @brief USB Host Client event callback
 *
 * Handling of USB device connection/disconnection to/from USB device tree.
 *
 * @param[in] event_msg Event message type
 * @param[in] arg Caller's argument (not used in this driver)
 */
static void usb_event_cb(const usb_host_client_event_msg_t *event_msg, void *arg)
{
    switch (event_msg->event) {
    case USB_HOST_CLIENT_EVENT_NEW_DEV:
        ESP_LOGD(TAG, "New device connected");
        uvc_host_device_connected(event_msg->new_dev.address);
        break;
    case USB_HOST_CLIENT_EVENT_DEV_GONE: {
        ESP_LOGD(TAG, "Device suddenly disconnected");
        // Find UVC pseudo-devices associated with this USB device and close them
        uvc_stream_t *uvc_stream;
        uvc_stream_t *tusb_stream;
        // We are using 'SAFE' version of 'SLIST_FOREACH' which enables user to close the disconnected device in the callback
        SLIST_FOREACH_SAFE(uvc_stream, &p_uvc_host_driver->uvc_stream_list, list_entry, tusb_stream) {
            if (uvc_stream->constant.dev_hdl == event_msg->dev_gone.dev_hdl) {
                // The suddenly disconnected device was opened by this driver: pause the stream and inform user about this
                ESP_ERROR_CHECK(uvc_host_stream_pause(uvc_stream)); // This should never fail
                if (uvc_stream->constant.stream_cb) {
                    const uvc_host_stream_event_data_t disconn_event = {
                        .type = UVC_HOST_DEVICE_DISCONNECTED,
                        .device_disconnected.stream_hdl = (uvc_host_stream_hdl_t) uvc_stream,
                    };
                    uvc_stream->constant.stream_cb(&disconn_event, uvc_stream->constant.cb_arg);
                }
            }
        }
        break;
    }
    default:
        assert(false);
        break;
    }
}

esp_err_t uvc_host_handle_events(unsigned long timeout)
{
    uvc_host_driver_t *uvc_obj = UVC_ATOMIC_LOAD(p_uvc_host_driver); // Make local copy of the driver's handle
    UVC_CHECK(uvc_obj, ESP_ERR_INVALID_STATE);

    ESP_LOGV(TAG, "USB UVC handling");
    esp_err_t ret = usb_host_client_handle_events(uvc_obj->usb_client_hdl, timeout);

    // Get driver status
    const EventBits_t events = xEventGroupGetBits(uvc_obj->driver_status);

    // If this is the first call to this function, we need to set the UVC_STARTED bit
    if ((events & UVC_STARTED) == 0) {
        xEventGroupSetBits(uvc_obj->driver_status, UVC_STARTED);
    }

    // We return ESP_FAIL to signal that the driver is being uninstalled
    // and we should stop handling events
    if (events & UVC_TEARDOWN) {
        xEventGroupSetBits(uvc_obj->driver_status, UVC_TEARDOWN_COMPLETE);
        ret = ESP_FAIL;
    }
    return ret;
}

/**
 * @brief UVC driver handling task
 *
 * @param[in] arg User's argument. Handle of a task that started this task.
 */
static void uvc_client_task(void *arg)
{
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    ESP_LOGD(TAG, "USB UVC handling start");
    // Start handling client's events
    while (uvc_host_handle_events(portMAX_DELAY) != ESP_FAIL) {
    }
    ESP_LOGD(TAG, "USB UVC handling stop");
    vTaskDelete(NULL);
}

/**
 * @brief Free USB transfers used by this device
 *
 * @note There can be no transfers in flight, at the moment of calling this function.
 * @param[in] uvc_stream Pointer to UVC stream
 */
static void uvc_transfers_free(uvc_stream_t *uvc_stream)
{
    assert(uvc_stream);
    for (unsigned i = 0; i < uvc_stream->constant.num_of_xfers; i++) {
        usb_host_transfer_free(uvc_stream->constant.xfers[i]);
    }
    free(uvc_stream->constant.xfers);
}

/**
 * @brief Allocate UVC transfers
 *
 * This function can allocate more memory than the caller requested.
 * The requested size is rounded up to integer multiple of MPS.
 *
 * @param[in] uvc_stream       Pointer to UVC stream
 * @param[in] num_of_transfers Number of USB transfers allocated for this stream
 * @param[in] transfer_size    Size of 1 USB transfer in bytes
 * @param[in] ep_desc          Descriptor of the streaming endpoint
 * @return
 *     - ESP_OK:              Success
 *     - ESP_ERR_NO_MEM:      Not enough memory for transfers allocation
 *     - ESP_ERR_INVALID_ARG: Max packet size is invalid or ep_desc is NULL
 */
static esp_err_t uvc_transfers_allocate(uvc_stream_t *uvc_stream, unsigned num_of_transfers, size_t transfer_size, const usb_ep_desc_t *ep_desc)
{
    esp_err_t ret = ESP_OK;
    UVC_CHECK(ep_desc, ESP_ERR_INVALID_ARG);
    unsigned num_isoc_packets = 0;
    const bool is_isoc = (USB_EP_DESC_GET_XFERTYPE(ep_desc) == USB_BM_ATTRIBUTES_XFER_ISOC);
    uint16_t max_packet_size = USB_EP_DESC_GET_MPS(ep_desc);
    UVC_CHECK(max_packet_size > 0, ESP_ERR_INVALID_ARG);

    if (is_isoc) {
        // Multiply MPS by number of transactions in microframe: This is the minimum size we can request in IN transfer
        max_packet_size *= (USB_EP_DESC_GET_MULT(ep_desc) + 1);
        // Divide the transfer data buffer into ISOC packets
        num_isoc_packets = usb_round_up_to_mps(transfer_size, max_packet_size) / max_packet_size;
    }

    // Make sure that we allocate size integer multiple of MPS buffer: This is required for all IN transfers
    transfer_size = usb_round_up_to_mps(transfer_size, max_packet_size);

    ESP_LOGD(TAG, "Allocating %d USB transfers. Each: %zu bytes, %d ISOC packets, %d MPS",
             num_of_transfers, transfer_size, num_isoc_packets, max_packet_size);

    // Allocate array of transfers
    uvc_stream->constant.xfers = malloc(num_of_transfers * sizeof(usb_transfer_t *));
    UVC_CHECK(uvc_stream->constant.xfers, ESP_ERR_NO_MEM);

    // Allocate and init all the transfers
    for (unsigned i = 0; i < num_of_transfers; i++) {
        ESP_GOTO_ON_ERROR(
            usb_host_transfer_alloc(transfer_size, num_isoc_packets, &uvc_stream->constant.xfers[i]),
            err, TAG, "Could not allocate USB transfers");

        uvc_stream->constant.num_of_xfers++;
        usb_transfer_t *this_transfer = uvc_stream->constant.xfers[i];
        this_transfer->device_handle = uvc_stream->constant.dev_hdl;
        this_transfer->context = uvc_stream;
        this_transfer->timeout_ms = 1000;
        this_transfer->bEndpointAddress = ep_desc->bEndpointAddress;

        if (is_isoc) {
            this_transfer->callback = isoc_transfer_callback;
            this_transfer->num_bytes = num_isoc_packets * max_packet_size;
            for (unsigned j = 0; j < num_isoc_packets; j++) {
                this_transfer->isoc_packet_desc[j].num_bytes = max_packet_size;
            }
        } else {
            this_transfer->callback = bulk_transfer_callback;
            this_transfer->num_bytes = transfer_size;
        }
    }
    return ESP_OK;

err:
    uvc_transfers_free(uvc_stream);
    return ret;
}

/**
 * @brief Helper function that releases resources claimed by UVC device
 *
 * Close underlying USB device, free device driver memory
 *
 * @note All interfaces claimed by this device must be release before calling this function
 * @param uvc_stream UVC stream handle to be removed
 */
static void uvc_device_remove(uvc_stream_t *uvc_stream)
{
    assert(uvc_stream);
    uvc_transfers_free(uvc_stream);
    uvc_frame_free(uvc_stream);
    // We don't check the error code of usb_host_device_close, as the close might fail, if someone else is still using the device (not all interfaces are released)
    usb_host_device_close(p_uvc_host_driver->usb_client_hdl, uvc_stream->constant.dev_hdl); // Gracefully continue on error
    free(uvc_stream);
}

/**
 * @brief Open USB device with requested VID/PID
 *
 * This function has two regular return paths:
 * 1. USB device with matching VID/PID/dev_addr is already opened by this driver: allocate new UVC device on top of the already opened USB device.
 * 2. USB device with matching VID/PID/dev_addr is NOT opened by this driver yet: poll USB connected devices until it is found.
 *
 * @note This function will block for timeout_ticks, if the device is not enumerated at the moment of calling this function.
 * @param[in]  dev_addr      Device address
 * @param[in]  vid           Vendor ID
 * @param[in]  pid           Product ID
 * @param[in]  timeout_ticks Connection timeout in FreeRTOS ticks
 * @param[out] dev           UVC device
 * @return
 *     - ESP_OK: Success - device opened
 *     - ESP_ERR_NOT_FOUND: Device not found in given timeout
 */
static esp_err_t uvc_find_and_open_usb_device(uint8_t dev_addr, uint16_t vid, uint16_t pid, TickType_t timeout_ticks, uvc_stream_t **dev)
{
    assert(p_uvc_host_driver);
    assert(dev);

    *dev = calloc(1, sizeof(uvc_stream_t));
    if (*dev == NULL) {
        return ESP_ERR_NO_MEM;
    }

    // First, check list of already opened UVC devices
    ESP_LOGD(TAG, "Checking list of opened USB devices");
    uvc_stream_t *uvc_stream;
    SLIST_FOREACH(uvc_stream, &p_uvc_host_driver->uvc_stream_list, list_entry) {
        const usb_device_desc_t *device_desc;
        usb_device_info_t dev_info;
        ESP_ERROR_CHECK(usb_host_device_info(uvc_stream->constant.dev_hdl, &dev_info));
        ESP_ERROR_CHECK(usb_host_get_device_descriptor(uvc_stream->constant.dev_hdl, &device_desc));
        if ((vid == device_desc->idVendor || vid == UVC_HOST_ANY_VID) &&
                (pid == device_desc->idProduct || pid == UVC_HOST_ANY_PID) &&
                (dev_addr == dev_info.dev_addr || dev_addr == UVC_HOST_ANY_DEV_ADDR)) {
            // Return path 1: t
            (*dev)->constant.dev_hdl = uvc_stream->constant.dev_hdl;
            return ESP_OK;
        }
    }

    // Second, poll connected devices until new device is connected or timeout
    TickType_t timeout = timeout_ticks;
    TimeOut_t connection_timeout;
    vTaskSetTimeOutState(&connection_timeout);

    ESP_LOGD(TAG, "Checking list of connected USB devices");
    do {
        uint8_t dev_addr_list[10];
        int num_of_devices;
        ESP_ERROR_CHECK(usb_host_device_addr_list_fill(sizeof(dev_addr_list), dev_addr_list, &num_of_devices));

        // Go through device address list and find the one we are looking for
        for (int i = 0; i < num_of_devices; i++) {
            usb_device_handle_t current_device;
            bool is_uvc_device = false;
            const usb_config_desc_t *config_desc = NULL;

            // Open USB device
            if (usb_host_device_open(p_uvc_host_driver->usb_client_hdl, dev_addr_list[i], &current_device) != ESP_OK) {
                continue; // In case we failed to open this device, continue with next one in the list
            }
            // Skip non-UVC devices
            if (usb_host_get_active_config_descriptor(current_device, &config_desc) == ESP_OK) {
                is_uvc_device = uvc_desc_is_uvc_device(config_desc);
            }
            if (is_uvc_device) {
                assert(current_device);
                const usb_device_desc_t *device_desc;
                ESP_ERROR_CHECK(usb_host_get_device_descriptor(current_device, &device_desc));
                if ((vid == device_desc->idVendor || vid == UVC_HOST_ANY_VID) &&
                        (pid == device_desc->idProduct || pid == UVC_HOST_ANY_PID) &&
                        (dev_addr == dev_addr_list[i] || dev_addr == UVC_HOST_ANY_DEV_ADDR)) {
                    // Return path 2:
                    (*dev)->constant.dev_hdl = current_device;
                    return ESP_OK;
                }
            }
            usb_host_device_close(p_uvc_host_driver->usb_client_hdl, current_device);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    } while (xTaskCheckForTimeOut(&connection_timeout, &timeout) == pdFALSE);

    // Timeout was reached, clean-up
    free(*dev);
    *dev = NULL;
    return ESP_ERR_NOT_FOUND;
}

/**
 * @brief Send SetInterface USB command to the camera
 *
 * @note Only for ISOC streams
 * @param[in] stream_hdl UVC stream handle
 * @param[in] stream_on  true: Set streaming alternate interface. false: Set alternative setting to 0
 * @return
 *     - ESP_OK: Success
 *     - Other:  CTRL transfer error
 */
static inline esp_err_t uvc_set_interface(uvc_host_stream_hdl_t stream_hdl, bool stream_on)
{
    return uvc_host_usb_ctrl(
               stream_hdl,
               USB_BM_REQUEST_TYPE_DIR_OUT | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_INTERFACE,
               USB_B_REQUEST_SET_INTERFACE,
               stream_on ? stream_hdl->constant.bAlternateSetting : 0,
               stream_hdl->constant.bInterfaceNumber,
               0,
               NULL);
}

/**
 * @brief Find and claim interface for selected frame format
 *
 * @param[in]  uvc_stream  Pointer to UVC stream
 * @param[in]  uvc_index   Index of UVC function you want to use
 * @param[in]  vs_format   Desired frame format
 * @param[out] ep_desc_ret EP descriptor for this stream
 * @return
 *     - ESP_OK:              Success, interface found and claimed
 *     - ESP_ERR_INVALID_ARG: Input parameter is NULL
 *     - ESP_ERR_NOT_FOUND:   Selected format was not found
 *     - Other:               Error during interface claim
 */
static esp_err_t uvc_claim_interface(uvc_stream_t *uvc_stream, uint8_t uvc_index, const uvc_host_stream_format_t *vs_format, const usb_ep_desc_t **ep_desc_ret)
{
    UVC_CHECK(uvc_stream && vs_format && ep_desc_ret, ESP_ERR_INVALID_ARG);

    const usb_config_desc_t *cfg_desc;
    const usb_intf_desc_t *intf_desc;
    const usb_ep_desc_t *ep_desc;
    ESP_ERROR_CHECK(usb_host_get_active_config_descriptor(uvc_stream->constant.dev_hdl, &cfg_desc));

    // Find UVC USB function with desired index
    uint16_t bcdUVC = 0;
    uint8_t bInterfaceNumber = 0;

    ESP_RETURN_ON_ERROR(
        uvc_desc_get_streaming_interface_num(cfg_desc, uvc_index, vs_format, &bcdUVC, &bInterfaceNumber),
        TAG, "Could not find frame format %dx%d@%2.1fFPS",
        vs_format->h_res, vs_format->v_res, vs_format->fps);

    ESP_RETURN_ON_ERROR(
        uvc_desc_get_streaming_intf_and_ep(cfg_desc, bInterfaceNumber, MAX_MPS_IN, &intf_desc, &ep_desc),
        TAG, "Could not find Streaming interface %d", bInterfaceNumber);

    // Save all constant information about the UVC stream
    uvc_stream->constant.bInterfaceNumber  = bInterfaceNumber;
    uvc_stream->constant.bcdUVC            = bcdUVC;
    uvc_stream->constant.bAlternateSetting = intf_desc->bAlternateSetting;
    uvc_stream->constant.bEndpointAddress  = ep_desc->bEndpointAddress;
    *ep_desc_ret                           = ep_desc;

    // Claim the interface in USB Host Lib
    return usb_host_interface_claim(
               p_uvc_host_driver->usb_client_hdl,
               uvc_stream->constant.dev_hdl,
               intf_desc->bInterfaceNumber,
               intf_desc->bAlternateSetting);
}

esp_err_t uvc_host_install(const uvc_host_driver_config_t *driver_config)
{
    UVC_CHECK(!UVC_ATOMIC_LOAD(p_uvc_host_driver), ESP_ERR_INVALID_STATE);

    // In case user did not provide driver_config, use default settings
    const uvc_host_driver_config_t default_driver_config = {
        .driver_task_stack_size = 5 * 1024,
        .driver_task_priority = 5,
        .xCoreID = tskNO_AFFINITY,
        .create_background_task = true,
    };
    if (driver_config == NULL) {
        driver_config = &default_driver_config;
    }

    // Allocate all we need for this driver
    esp_err_t ret;
    uvc_host_driver_t *uvc_obj = heap_caps_calloc(1, sizeof(uvc_host_driver_t), MALLOC_CAP_DEFAULT);
    EventGroupHandle_t driver_status = xEventGroupCreate();
    SemaphoreHandle_t mutex = xSemaphoreCreateMutex();
    SemaphoreHandle_t ctrl_mutex = xSemaphoreCreateMutex();
    SemaphoreHandle_t ctrl_sem = xSemaphoreCreateBinary();
    usb_transfer_t *ctrl_xfer = NULL;
    usb_host_transfer_alloc(64, 0, &ctrl_xfer); // Worst case HS MPS
    TaskHandle_t driver_task_h = NULL;

    if (driver_config->create_background_task) {
        xTaskCreatePinnedToCore(
            uvc_client_task, "USB-UVC", driver_config->driver_task_stack_size, NULL,
            driver_config->driver_task_priority, &driver_task_h, driver_config->xCoreID);
    }

    if (uvc_obj == NULL || (driver_task_h == NULL && driver_config->create_background_task) || driver_status == NULL ||
            mutex == NULL || ctrl_mutex == NULL || ctrl_xfer == NULL || ctrl_sem == NULL) {
        ret = ESP_ERR_NO_MEM;
        goto err;
    }

    // Register USB Host client
    usb_host_client_handle_t usb_client = NULL;
    const usb_host_client_config_t client_config = {
        .is_synchronous = false,
        .max_num_event_msg = 3,
        .async.client_event_callback = usb_event_cb,
        .async.callback_arg = NULL
    };
    ESP_GOTO_ON_ERROR(usb_host_client_register(&client_config, &usb_client), err, TAG, "Failed to register USB host client");

    // Initialize UVC driver structure
    SLIST_INIT(&(uvc_obj->uvc_stream_list));
    uvc_obj->driver_status = driver_status;
    uvc_obj->open_close_mutex = mutex;
    uvc_obj->usb_client_hdl = usb_client;
    uvc_obj->ctrl_mutex = ctrl_mutex;
    uvc_obj->ctrl_transfer = ctrl_xfer;
    uvc_obj->ctrl_transfer->context = ctrl_sem;
    uvc_obj->ctrl_transfer->bEndpointAddress = 0;
    uvc_obj->ctrl_transfer->timeout_ms = 5000;
    uvc_obj->ctrl_transfer->callback = ctrl_xfer_cb;
    uvc_obj->user_cb = driver_config->event_cb;
    uvc_obj->user_ctx = driver_config->user_ctx;

    // Between 1st call of this function and following section, another task might try to install this driver:
    // Make sure that there is only one instance of this driver in the system
    if (!UVC_ATOMIC_SET_IF_NULL(p_uvc_host_driver, uvc_obj)) {
        ret = ESP_ERR_INVALID_STATE;
        goto client_err;
    }

    // Everything OK: Start UVC-Driver task and return
    if (driver_task_h) {
        xTaskNotifyGive(driver_task_h);
    }
    return ESP_OK;

client_err:
    usb_host_client_deregister(usb_client);
err: // Clean-up
    free(uvc_obj);
    if (driver_status) {
        vEventGroupDelete(driver_status);
    }
    if (driver_task_h) {
        vTaskDelete(driver_task_h);
    }
    if (mutex) {
        vSemaphoreDelete(mutex);
    }
    if (ctrl_mutex) {
        vSemaphoreDelete(ctrl_mutex);
    }
    if (ctrl_xfer) {
        usb_host_transfer_free(ctrl_xfer);
    }
    if (ctrl_sem) {
        vSemaphoreDelete(ctrl_sem);
    }
    return ret;
}

esp_err_t uvc_host_uninstall()
{
    esp_err_t ret;
    uvc_host_driver_t *uvc_obj = UVC_ATOMIC_LOAD(p_uvc_host_driver); // Save Driver's handle to temporary handle
    UVC_CHECK(uvc_obj, ESP_ERR_INVALID_STATE);

    xSemaphoreTake(uvc_obj->open_close_mutex, portMAX_DELAY); // Wait for all open/close calls to finish
    xSemaphoreTake(uvc_obj->ctrl_mutex, portMAX_DELAY); // Wait for all CTRL transfers to finish

    UVC_ENTER_CRITICAL();
    if (SLIST_EMPTY(&uvc_obj->uvc_stream_list)) { // Check that device list is empty (all devices closed)
        p_uvc_host_driver = NULL; // NULL static driver pointer: No open/close calls form this point
    } else {
        ret = ESP_ERR_INVALID_STATE;
        UVC_EXIT_CRITICAL();
        goto unblock;
    }
    UVC_EXIT_CRITICAL();

    // Signal to UVC task to stop, unblock it and wait for its deletion
    xEventGroupSetBits(uvc_obj->driver_status, UVC_TEARDOWN);
    usb_host_client_unblock(uvc_obj->usb_client_hdl);
    taskYIELD(); // Give the now unblocked UVC handling task a chance to run

    EventBits_t driver_status = xEventGroupGetBits(uvc_obj->driver_status);
    if (driver_status & UVC_STARTED) {
        ESP_GOTO_ON_FALSE(
            xEventGroupWaitBits(uvc_obj->driver_status, UVC_TEARDOWN_COMPLETE, pdFALSE, pdFALSE, pdMS_TO_TICKS(100)),
            ESP_ERR_NOT_FINISHED, unblock, TAG,);
    }

    ESP_LOGD(TAG, "Deregistering client");
    ESP_ERROR_CHECK(usb_host_client_deregister(uvc_obj->usb_client_hdl));

    // Free remaining resources and return
    vEventGroupDelete(uvc_obj->driver_status);
    xSemaphoreGive(uvc_obj->open_close_mutex);
    vSemaphoreDelete(uvc_obj->open_close_mutex);
    xSemaphoreGive(uvc_obj->ctrl_mutex);
    vSemaphoreDelete(uvc_obj->ctrl_mutex);
    vSemaphoreDelete(uvc_obj->ctrl_transfer->context);
    usb_host_transfer_free(uvc_obj->ctrl_transfer);
    free(uvc_obj);
    return ESP_OK;

unblock:
    xSemaphoreGive(uvc_obj->open_close_mutex);
    xSemaphoreGive(uvc_obj->ctrl_mutex);
    return ret;
}

/**
 * @brief Saves format to stream handle and all its frame buffers
 *
 * @param[in] uvc_stream Stream handle
 * @param[in] vs_format  Format to save
 * @param[in] dwMaxVideoFrameSize Maximum video frame size of this format
 */
static void uvc_format_save(uvc_stream_t *uvc_stream, const uvc_host_stream_format_t *vs_format, uint32_t dwMaxVideoFrameSize)
{
    assert(uvc_stream && vs_format);

    UVC_ENTER_CRITICAL();
    // Save to video format to this stream
    memcpy((uvc_host_stream_format_t *)&uvc_stream->dynamic.vs_format, vs_format, sizeof(uvc_host_stream_format_t));
    uvc_stream->dynamic.dwMaxVideoFrameSize = dwMaxVideoFrameSize;
    UVC_EXIT_CRITICAL();

    // Save to all frame buffers
    assert(uvc_frame_are_all_returned(uvc_stream));
    uvc_frame_format_update(uvc_stream, vs_format);
}
esp_err_t uvc_host_stream_open(const uvc_host_stream_config_t *stream_config, int timeout, uvc_host_stream_hdl_t *stream_hdl_ret)
{
    esp_err_t ret;
    UVC_CHECK(UVC_ATOMIC_LOAD(p_uvc_host_driver), ESP_ERR_INVALID_STATE);
    UVC_CHECK(stream_config, ESP_ERR_INVALID_ARG);
    UVC_CHECK(stream_hdl_ret, ESP_ERR_INVALID_ARG);

    uvc_stream_t *uvc_stream;
    xSemaphoreTake(p_uvc_host_driver->open_close_mutex, portMAX_DELAY);

    // Find underlying USB device
    ret = uvc_find_and_open_usb_device(stream_config->usb.dev_addr, stream_config->usb.vid, stream_config->usb.pid, timeout, &uvc_stream);
    if (ESP_OK != ret) {
        goto not_found;
    }

    // Find the streaming interface and endpoint and claim it
    const usb_ep_desc_t *ep_desc;
    ESP_GOTO_ON_ERROR(
        uvc_claim_interface(uvc_stream, stream_config->usb.uvc_stream_index, &stream_config->vs_format, &ep_desc),
        claim_err, TAG, "Could not find/claim streaming interface");
    ESP_LOGD(TAG, "Claimed interface index %d with MPS %d", uvc_stream->constant.bInterfaceNumber, USB_EP_DESC_GET_MPS(ep_desc));

    /*
    * Although not strictly required by the UVC specification, some UVC ISOC
    * cameras require explicitly entering the NOT STREAMING state by setting
    * the interface's Alternate Setting to 0.
    */
    if (uvc_stream->constant.bAlternateSetting != 0) {
        // We do not check return code here on purpose. We can silently continue
        uvc_set_interface(uvc_stream, false);
    }

    // Allocate USB transfers
    ESP_GOTO_ON_ERROR(
        uvc_transfers_allocate(uvc_stream, stream_config->advanced.number_of_urbs, stream_config->advanced.urb_size, ep_desc),
        err, TAG,);

    // Note: The maximum frame size (dwMaxVideoFrameSize) is not provided in the device descriptors.
    // Instead, it is retrieved via a negotiation process that involves:
    //   1. Setting the desired video format on the camera.
    //   2. Receiving the negotiation result, which includes the maximum supported frame size (dwMaxVideoFrameSize).
    //
    // Important: This negotiation only computes the potential maximum frame size.
    // The selected video frame format is not committed until uvc_host_stream_start() is executed.
    // Negotiate the frame format
    uvc_vs_ctrl_t vs_result;
    uvc_host_stream_format_t real_format;
    memcpy(&real_format, &stream_config->vs_format, sizeof(uvc_host_stream_format_t)); // Memcpy to avoid overwriting the original format
    ESP_GOTO_ON_ERROR(
        uvc_host_stream_control_probe(uvc_stream, &real_format, &vs_result),
        err, TAG, "Failed to negotiate requested Video Stream format");

    // Allocate Frame buffers
    ESP_GOTO_ON_ERROR(
        uvc_frame_allocate(
            uvc_stream,
            stream_config->advanced.number_of_frame_buffers,
            stream_config->advanced.frame_size ? stream_config->advanced.frame_size : vs_result.dwMaxVideoFrameSize,
            stream_config->advanced.frame_heap_caps),
        err, TAG,);

    // Save info
    uvc_format_save(uvc_stream, &real_format, vs_result.dwMaxVideoFrameSize);
    uvc_stream->constant.stream_cb = stream_config->event_cb;
    uvc_stream->constant.frame_cb = stream_config->frame_cb;
    uvc_stream->constant.cb_arg = stream_config->user_ctx;

    // Everything OK, add the device into list
    UVC_ENTER_CRITICAL();
    SLIST_INSERT_HEAD(&p_uvc_host_driver->uvc_stream_list, uvc_stream, list_entry);
    UVC_EXIT_CRITICAL();
    *stream_hdl_ret = (uvc_host_stream_hdl_t)uvc_stream;
    xSemaphoreGive(p_uvc_host_driver->open_close_mutex);
    return ESP_OK;

err:
    usb_host_interface_release(p_uvc_host_driver->usb_client_hdl, uvc_stream->constant.dev_hdl, uvc_stream->constant.bInterfaceNumber);
claim_err:
    uvc_device_remove(uvc_stream); // Including transfers and frames free
not_found:
    xSemaphoreGive(p_uvc_host_driver->open_close_mutex);
    *stream_hdl_ret = NULL;
    return ret;
}

esp_err_t uvc_host_stream_close(uvc_host_stream_hdl_t stream_hdl)
{
    UVC_CHECK(UVC_ATOMIC_LOAD(p_uvc_host_driver), ESP_ERR_INVALID_STATE);
    UVC_CHECK(stream_hdl, ESP_ERR_INVALID_ARG);

    esp_err_t ret = ESP_OK;
    xSemaphoreTake(p_uvc_host_driver->open_close_mutex, portMAX_DELAY);

    // Make sure that the device is in the devices list (that it is not already closed)
    uvc_stream_t *uvc_stream;
    bool device_found = false;
    UVC_ENTER_CRITICAL();
    SLIST_FOREACH(uvc_stream, &p_uvc_host_driver->uvc_stream_list, list_entry) {
        if (uvc_stream == (uvc_stream_t *)stream_hdl) {
            device_found = true;
            break;
        }
    }
    UVC_EXIT_CRITICAL();

    // Device was not found in the uvc_stream_list; it was already closed, return OK
    if (!device_found) {
        ret = ESP_OK;
        goto exit;
    }

    if (UVC_ATOMIC_LOAD(uvc_stream->dynamic.streaming)) {
        uvc_host_stream_stop(stream_hdl);
    }

    if (!uvc_frame_are_all_returned(uvc_stream)) {
        vTaskDelay(pdMS_TO_TICKS(70)); // Wait 70ms so the user can return all frames
        if (!uvc_frame_are_all_returned(uvc_stream)) {
            ESP_LOGW(TAG, "Not all frames are returned, cannot close!");
            ret = ESP_ERR_INVALID_STATE;
            goto exit;
        }
    }

    // Release all interfaces
    ESP_ERROR_CHECK(usb_host_interface_release(p_uvc_host_driver->usb_client_hdl, uvc_stream->constant.dev_hdl, uvc_stream->constant.bInterfaceNumber));

    UVC_ENTER_CRITICAL();
    SLIST_REMOVE(&p_uvc_host_driver->uvc_stream_list, uvc_stream, uvc_host_stream_s, list_entry);
    UVC_EXIT_CRITICAL();

    uvc_device_remove(uvc_stream);

exit:
    xSemaphoreGive(p_uvc_host_driver->open_close_mutex);
    return ret;
}

static esp_err_t uvc_clear_endpoint_feature(uvc_host_stream_hdl_t stream_hdl)
{
    usb_host_endpoint_halt(stream_hdl->constant.dev_hdl, stream_hdl->constant.bEndpointAddress);
    usb_host_endpoint_flush(stream_hdl->constant.dev_hdl, stream_hdl->constant.bEndpointAddress);
    usb_host_endpoint_clear(stream_hdl->constant.dev_hdl, stream_hdl->constant.bEndpointAddress);
    return uvc_host_usb_ctrl(
               stream_hdl,
               USB_BM_REQUEST_TYPE_DIR_OUT | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_ENDPOINT,
               USB_B_REQUEST_CLEAR_FEATURE,
               0, // 0 means HALT
               stream_hdl->constant.bEndpointAddress,
               0,
               NULL);
}

esp_err_t uvc_host_stream_start(uvc_host_stream_hdl_t stream_hdl)
{
    UVC_CHECK(stream_hdl, ESP_ERR_INVALID_ARG);
    UVC_ENTER_CRITICAL();
    UVC_CHECK_FROM_CRIT(stream_hdl->dynamic.streaming == false, ESP_ERR_INVALID_STATE);
    const uvc_host_stream_format_t format = stream_hdl->dynamic.vs_format;
    UVC_EXIT_CRITICAL();

    // 1. Negotiate and commit the frame format
    // @see USB UVC specification ver 1.5, figure 4-1
    ESP_RETURN_ON_ERROR(
        uvc_host_stream_control_commit(stream_hdl, &format),
        TAG, "Failed to negotiate requested Video Stream format");
    vTaskDelay(pdMS_TO_TICKS(10)); // Some cameras need delay between format Commit and SetInterface

    // 2. Send command to the camera to start streaming: ISOC only
    if (stream_hdl->constant.bAlternateSetting != 0) {
        ESP_RETURN_ON_ERROR(
            uvc_set_interface(stream_hdl, true),
            TAG, "Could not Set Interface %d-%d", stream_hdl->constant.bInterfaceNumber, stream_hdl->constant.bAlternateSetting);
    }

    // 3. Unpause: Submit all URBs
    ESP_RETURN_ON_ERROR(
        uvc_host_stream_unpause(stream_hdl),
        TAG, "Could not unpause the stream");

    return ESP_OK;
}

esp_err_t uvc_host_stream_format_select(uvc_host_stream_hdl_t stream_hdl, uvc_host_stream_format_t *format)
{
    esp_err_t ret = ESP_OK;
    UVC_CHECK(stream_hdl && format, ESP_ERR_INVALID_ARG);

    // In case the stream is streaming when format change is requested,
    // we must stop the stream, reconfigure it and restart again
    const bool restart_required = UVC_ATOMIC_LOAD(stream_hdl->dynamic.streaming);
    if (restart_required) {
        ret = uvc_host_stream_stop(stream_hdl);
        if (ret != ESP_OK) {
            return ret;
        }
    }

    // Allow partial format change
    // If the user does not provide resolution/format, we use the **current one**
    // If the user does not provide FPS, we use the **default one**
    if (format->h_res == 0 || format->v_res == 0) {
        UVC_ENTER_CRITICAL();
        format->h_res = stream_hdl->dynamic.vs_format.h_res;
        format->v_res = stream_hdl->dynamic.vs_format.v_res;
        UVC_EXIT_CRITICAL();
    }

    if (format->format == UVC_VS_FORMAT_DEFAULT) {
        format->format = UVC_ATOMIC_LOAD(stream_hdl->dynamic.vs_format.format);
    }

    uvc_vs_ctrl_t vs_result;
    ESP_GOTO_ON_ERROR(
        uvc_host_stream_control_probe(stream_hdl, format, &vs_result),
        bailout, TAG, "Failed to negotiate requested Video Stream format");
    uvc_format_save(stream_hdl, format, vs_result.dwMaxVideoFrameSize);

bailout:
    if (restart_required) {
        ret |= uvc_host_stream_start(stream_hdl);
    }
    return ret;
}

esp_err_t uvc_host_stream_format_get(uvc_host_stream_hdl_t stream_hdl, uvc_host_stream_format_t *format)
{
    UVC_CHECK(stream_hdl && format, ESP_ERR_INVALID_ARG);
    UVC_ENTER_CRITICAL();
    memcpy(format, &stream_hdl->dynamic.vs_format, sizeof(uvc_host_stream_format_t));
    UVC_EXIT_CRITICAL();
    return ESP_OK;
}

esp_err_t uvc_host_buf_info_get(uvc_host_stream_hdl_t stream_hdl, uvc_host_buf_info_t *buf_info)
{
    UVC_CHECK(stream_hdl && buf_info, ESP_ERR_INVALID_ARG);
    buf_info->dwMaxVideoFrameSize = UVC_ATOMIC_LOAD(stream_hdl->dynamic.dwMaxVideoFrameSize);
    return ESP_OK;
}

esp_err_t uvc_host_stream_stop(uvc_host_stream_hdl_t stream_hdl)
{
    UVC_CHECK(stream_hdl, ESP_ERR_INVALID_ARG);

    ESP_RETURN_ON_ERROR(uvc_host_stream_pause(stream_hdl), TAG, "Could not pause the stream");

    //@todo this is not a clean solution
    // Note: Increased from 50ms to 100ms until proper fix is implemented
    vTaskDelay(pdMS_TO_TICKS(100)); // Wait for all transfers to finish

    if (stream_hdl->constant.bAlternateSetting != 0) { // if (is_isoc_stream)
        // ISOC streams are stopped by setting alternate interface 0
        return uvc_set_interface(stream_hdl, false);
    } else {
        // BULK streams are stopped by halting the endpoint
        return uvc_clear_endpoint_feature(stream_hdl);
    }
}

esp_err_t uvc_host_stream_pause(uvc_host_stream_hdl_t stream_hdl)
{
    UVC_CHECK(stream_hdl, ESP_ERR_INVALID_ARG);

    // We do not cancel the ongoing transfers here, it is not supported by USB Host Library
    // By setting stream_hdl->dynamic.streaming = false; no frame callbacks will be called and the transfer can gracefully finish
    UVC_ENTER_CRITICAL();
    UVC_CHECK_FROM_CRIT(stream_hdl->dynamic.streaming, ESP_OK); // Return immediately if already paused
    stream_hdl->dynamic.streaming = false;
    uvc_host_frame_t *current_frame = stream_hdl->dynamic.current_frame;
    stream_hdl->dynamic.current_frame = NULL;
    UVC_EXIT_CRITICAL();

    if (current_frame) {
        uvc_host_frame_return(stream_hdl, current_frame);
    }

    return ESP_OK;
}

esp_err_t uvc_host_stream_unpause(uvc_host_stream_hdl_t stream_hdl)
{
    UVC_CHECK(stream_hdl, ESP_ERR_INVALID_ARG);
    esp_err_t ret = ESP_OK;

    UVC_ENTER_CRITICAL();
    UVC_CHECK_FROM_CRIT(!stream_hdl->dynamic.streaming, ESP_ERR_INVALID_STATE);
    stream_hdl->dynamic.streaming = true;
    // Start of Frame is detected when received FrameID != current_frame_id
    // We set current_frame_id to illegal value (FrameID can be 0 or 1) so we catch SoF of the very first frame
    stream_hdl->single_thread.current_frame_id = 2;
    stream_hdl->single_thread.next_bulk_packet = UVC_STREAM_BULK_PACKET_SOF;
    UVC_EXIT_CRITICAL();

    for (int i = 0; i < stream_hdl->constant.num_of_xfers; i++) {
        ESP_GOTO_ON_ERROR(
            usb_host_transfer_submit(stream_hdl->constant.xfers[i]),
            stop_stream, TAG, "Could not submit transfer %d", i);
    }
    return ret;

stop_stream:
    uvc_host_stream_pause(stream_hdl);
    return ret;
}

static void ctrl_xfer_cb(usb_transfer_t *transfer)
{
    ESP_LOGD(TAG, "ctrl xfer cb");
    assert(transfer->context);
    xSemaphoreGive((SemaphoreHandle_t)transfer->context);
}

esp_err_t uvc_host_usb_ctrl(uvc_host_stream_hdl_t stream_hdl, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint16_t wLength, uint8_t *data)
{
    UVC_CHECK(stream_hdl, ESP_ERR_INVALID_ARG);
    if (wLength > 0) {
        UVC_CHECK(data, ESP_ERR_INVALID_ARG);
    }
    UVC_CHECK(p_uvc_host_driver->ctrl_transfer->data_buffer_size >= wLength, ESP_ERR_INVALID_SIZE);

    esp_err_t ret;

    // Take Mutex and fill the CTRL request
    BaseType_t taken = xSemaphoreTake(p_uvc_host_driver->ctrl_mutex, pdMS_TO_TICKS(5000));
    if (!taken) {
        return ESP_ERR_TIMEOUT;
    }
    usb_setup_packet_t *req = (usb_setup_packet_t *)(p_uvc_host_driver->ctrl_transfer->data_buffer);
    uint8_t *start_of_data = (uint8_t *)req + sizeof(usb_setup_packet_t);
    req->bmRequestType = bmRequestType;
    req->bRequest = bRequest;
    req->wValue = wValue;
    req->wIndex = wIndex;
    req->wLength = wLength;

    // Bind the transfer and the device
    p_uvc_host_driver->ctrl_transfer->device_handle = stream_hdl->constant.dev_hdl;
    p_uvc_host_driver->ctrl_transfer->num_bytes = wLength + sizeof(usb_setup_packet_t);

    // For IN transfers we must transfer data ownership to the driver
    const bool in_transfer = bmRequestType & USB_BM_REQUEST_TYPE_DIR_IN;
    if (!in_transfer) {
        memcpy(start_of_data, data, wLength);
    }

    ESP_GOTO_ON_ERROR(
        usb_host_transfer_submit_control(p_uvc_host_driver->usb_client_hdl, p_uvc_host_driver->ctrl_transfer),
        unblock, TAG, "CTRL transfer failed");

    taken = xSemaphoreTake((SemaphoreHandle_t)p_uvc_host_driver->ctrl_transfer->context, pdMS_TO_TICKS(5000)); // This is a fixed timeout. Every device should be able to respond to CTRL transfer in 5 seconds
    ESP_GOTO_ON_FALSE(taken, ESP_ERR_TIMEOUT, unblock, TAG, "CTRL timeout");
    ESP_GOTO_ON_FALSE(p_uvc_host_driver->ctrl_transfer->status == USB_TRANSFER_STATUS_COMPLETED, ESP_ERR_INVALID_RESPONSE, unblock, TAG, "Control transfer error");
    ESP_GOTO_ON_FALSE(p_uvc_host_driver->ctrl_transfer->actual_num_bytes == p_uvc_host_driver->ctrl_transfer->num_bytes, ESP_ERR_INVALID_RESPONSE, unblock, TAG, "Incorrect number of bytes transferred");

    // For OUT transfers, we must transfer data ownership to user
    if (in_transfer) {
        memcpy(data, start_of_data, wLength);
    }
    ret = ESP_OK;

unblock:
    xSemaphoreGive(p_uvc_host_driver->ctrl_mutex);
    return ret;
}

esp_err_t uvc_host_get_frame_list(uint8_t dev_addr, uint8_t uvc_stream_index, uvc_host_frame_info_t (*frame_info_list)[], size_t *list_size)
{
    UVC_CHECK(list_size, ESP_ERR_INVALID_ARG);

    usb_device_handle_t dev_hdl;
    const usb_config_desc_t *config_desc = NULL;
    if (usb_host_device_open(p_uvc_host_driver->usb_client_hdl, dev_addr, &dev_hdl) == ESP_OK) {
        usb_host_get_active_config_descriptor(dev_hdl, &config_desc);
        ESP_RETURN_ON_ERROR(usb_host_device_close(p_uvc_host_driver->usb_client_hdl, dev_hdl), TAG, "Unable to close USB device");
    }

    return uvc_desc_get_frame_list(config_desc, uvc_stream_index, frame_info_list, list_size);
}
