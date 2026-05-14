/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <sdkconfig.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "usb/usb_host.h"
#include "usb/uvc_host.h"

#define EXAMPLE_USB_HOST_PRIORITY   (15)
#define EXAMPLE_USB_DEVICE_VID      (UVC_HOST_ANY_VID)
#define EXAMPLE_USB_DEVICE_PID      (UVC_HOST_ANY_PID)
#if CONFIG_SPIRAM
#define EXAMPLE_FRAME_COUNT         (3)
#else
#define EXAMPLE_FRAME_COUNT         (2)
#endif
#define EXAMPLE_RECORDING_LENGTH_S  (5) // The stream(s) is enabled, run for EXAMPLE_RECORDING_LENGTH_S and then stopped
#define EXAMPLE_NUMBER_OF_STREAMS   (1) // This example shows how to control multiple UVC streams. Set this to 1 if you camera offers only 1 stream
#define EXAMPLE_USE_SDCARD          (0) // SD card on P4 evaluation board will be initialized

static const char *TAG = "UVC example";
static QueueHandle_t rx_frames_queue[EXAMPLE_NUMBER_OF_STREAMS];
static bool dev_connected = false;

bool frame_callback(const uvc_host_frame_t *frame, void *user_ctx)
{
    assert(frame);
    assert(user_ctx);
    QueueHandle_t frame_q = *((QueueHandle_t *)user_ctx);
    ESP_LOGD(TAG, "Frame callback! data len: %d", frame->data_len);
    BaseType_t result = xQueueSendToBack(frame_q, &frame, 0);
    if (pdPASS != result) {
        ESP_LOGW(TAG, "Queue full, losing frame"); // This should never happen. We allocated queue with the same size as EXAMPLE_FRAME_COUNT
        return true; // We will not process this frame, return it immediately
    }
    return false; // We only passed the frame to Queue, so we must return false and call uvc_host_frame_return() later
}

static void stream_callback(const uvc_host_stream_event_data_t *event, void *user_ctx)
{
    switch (event->type) {
    case UVC_HOST_TRANSFER_ERROR:
        ESP_LOGE(TAG, "USB error has occurred, err_no = %i", event->transfer_error.error);
        break;
    case UVC_HOST_DEVICE_DISCONNECTED:
        ESP_LOGI(TAG, "Device suddenly disconnected");
        dev_connected = false;
        ESP_ERROR_CHECK(uvc_host_stream_close(event->device_disconnected.stream_hdl));
        break;
    case UVC_HOST_FRAME_BUFFER_OVERFLOW:
        ESP_LOGW(TAG, "Frame buffer overflow");
        break;
    case UVC_HOST_FRAME_BUFFER_UNDERFLOW:
        ESP_LOGW(TAG, "Frame buffer underflow");
        break;
    default:
        abort();
        break;
    }
}

static void usb_lib_task(void *arg)
{
    while (1) {
        // Start handling system events
        uint32_t event_flags;
        usb_host_lib_handle_events(portMAX_DELAY, &event_flags);
        if (event_flags & USB_HOST_LIB_EVENT_FLAGS_NO_CLIENTS) {
            usb_host_device_free_all();
        }
        if (event_flags & USB_HOST_LIB_EVENT_FLAGS_ALL_FREE) {
            ESP_LOGI(TAG, "USB: All devices freed");
            // Continue handling USB events to allow device reconnection
        }
    }
}

static void frame_handling_task(void *arg)
{
    const uvc_host_stream_config_t *stream_config = (const uvc_host_stream_config_t *)arg;
    QueueHandle_t frame_q = *((QueueHandle_t *)(stream_config->user_ctx));
    const int uvc_index = stream_config->usb.uvc_stream_index;

    while (true) {
        uvc_host_stream_hdl_t uvc_stream = NULL;

        ESP_LOGI(TAG, "Opening UVC device 0x%04X:0x%04X-%d\n\t%dx%d@%2.1fFPS...",
                 stream_config->usb.vid, stream_config->usb.pid, uvc_index, stream_config->vs_format.h_res, stream_config->vs_format.v_res, stream_config->vs_format.fps);
        esp_err_t err = uvc_host_stream_open(stream_config, pdMS_TO_TICKS(5000), &uvc_stream);
        if (ESP_OK != err) {
            ESP_LOGI(TAG, "Failed to open device");
            vTaskDelay(pdMS_TO_TICKS(5000));
            continue;
        }
        //uvc_host_desc_print(uvc_stream);
        dev_connected = true;
        ESP_LOGI(TAG, "Device 0x%04X:0x%04X-%d OPENED!", stream_config->usb.vid, stream_config->usb.pid, uvc_index);
        vTaskDelay(pdMS_TO_TICKS(100));
        unsigned count = 0;

        // This is the main processing loop. It enables the stream for EXAMPLE_RECORDING_LENGTH_S seconds and then closes it
        while (true) {
            ESP_LOGI(TAG, "Stream %d start. Iteration %u", uvc_index, count);
            count++;
            uvc_host_stream_start(uvc_stream);
            TickType_t timeout_ticks = pdMS_TO_TICKS(EXAMPLE_RECORDING_LENGTH_S * 1000);
            TimeOut_t stream_timeout;
            vTaskSetTimeOutState(&stream_timeout);

            do {
                uvc_host_frame_t *frame;
                if (xQueueReceive(frame_q, &frame, pdMS_TO_TICKS(5000)) == pdPASS) {
                    ESP_LOGI(TAG, "Stream %d: New frame %dx%d! Len: %d", uvc_index, frame->vs_format.h_res, frame->vs_format.v_res, frame->data_len);

                    // Process the frame data here!!

                    uvc_host_frame_return(uvc_stream, frame);
                } else {
                    ESP_LOGW(TAG, "Stream %d: Frame not received on time", uvc_index);
                    break;
                }
            } while (xTaskCheckForTimeOut(&stream_timeout, &timeout_ticks) == pdFALSE);

            if (dev_connected) {
                // Stop and wait 2 seconds
                ESP_LOGI(TAG, "Stream %d stop", uvc_index);
                uvc_host_stream_stop(uvc_stream);
                vTaskDelay(pdMS_TO_TICKS(2000));
            }
            if (!dev_connected) {
                ESP_LOGI(TAG, "device disconnected, breaking");
                break;
            }
        }
    }
}

static const uvc_host_stream_config_t stream_mjpeg_config = {
    .event_cb = stream_callback,
    .frame_cb = frame_callback,
    .user_ctx = &rx_frames_queue[0],
    .usb = {
        .vid = EXAMPLE_USB_DEVICE_VID,
        .pid = EXAMPLE_USB_DEVICE_PID,
        .uvc_stream_index = 0,
    },
    .vs_format = {
        .h_res = 720,
        .v_res = 1280,
        .fps = 15,
        .format = UVC_VS_FORMAT_MJPEG,
    },
    .advanced = {
        .number_of_frame_buffers = EXAMPLE_FRAME_COUNT,
        .frame_size = 0,
        .number_of_urbs = 4,
        .urb_size = 10 * 1024,
    },
};

#if EXAMPLE_NUMBER_OF_STREAMS > 1
static const uvc_host_stream_config_t stream_h265_config = {
    .event_cb = stream_callback,
    .frame_cb = frame_callback,
    .user_ctx = &rx_frames_queue[1],
    .usb = {
        .vid = EXAMPLE_USB_DEVICE_VID,
        .pid = EXAMPLE_USB_DEVICE_PID,
        .uvc_stream_index = 1,
    },
    .vs_format = {
        .h_res = 1280,
        .v_res = 720,
        .fps = 15,
        .format = UVC_VS_FORMAT_H265,
    },
    .advanced = {
        .number_of_frame_buffers = EXAMPLE_FRAME_COUNT,
        .frame_size = 0,
        .number_of_urbs = 4,
        .urb_size = 10 * 1024,
    },
};
#endif // EXAMPLE_NUMBER_OF_STREAMS > 1

#if EXAMPLE_USE_SDCARD
#define MOUNT_POINT "/sdcard"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "sd_pwr_ctrl_by_on_chip_ldo.h"
void app_init_sdcard(void)
{
    esp_err_t ret;
    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 64 * 1024
    };
    sdmmc_card_t *card;
    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(TAG, "Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.

    ESP_LOGI(TAG, "Using SDMMC peripheral");

    // By default, SD card frequency is initialized to SDMMC_FREQ_DEFAULT (20MHz)
    // For setting a specific frequency, use host.max_freq_khz (range 400kHz - 40MHz for SDMMC)
    // Example: for fixed frequency of 10MHz, use host.max_freq_khz = 10000;
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    // For SoCs where the SD power can be supplied both via an internal or external (e.g. on-board LDO) power supply.
    // When using specific IO pins (which can be used for ultra high-speed SDMMC) to connect to the SD card
    // and the internal LDO power supply, we need to initialize the power supply first.
    sd_pwr_ctrl_ldo_config_t ldo_config = {
        .ldo_chan_id = 4,
    };
    sd_pwr_ctrl_handle_t pwr_ctrl_handle = NULL;

    ret = sd_pwr_ctrl_new_on_chip_ldo(&ldo_config, &pwr_ctrl_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create a new on-chip LDO power control driver");
        return;
    }
    host.pwr_ctrl_handle = pwr_ctrl_handle;
    host.max_freq_khz = SDMMC_FREQ_HIGHSPEED;

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    slot_config.width = 4;
    slot_config.clk = 43;
    slot_config.cmd = 44;
    slot_config.d0 = 39;
    slot_config.d1 = 40;
    slot_config.d2 = 41;
    slot_config.d3 = 42;
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return;
    }
}
#endif // EXAMPLE_USE_SDCARD

/**
 * @brief Main application
 */
void app_main(void)
{
    for (int i = 0; i < EXAMPLE_NUMBER_OF_STREAMS; i++) {
        rx_frames_queue[i] = xQueueCreate(EXAMPLE_FRAME_COUNT, sizeof(uvc_host_frame_t *));
        assert(rx_frames_queue[i]);
    }

#if EXAMPLE_USE_SDCARD
    app_init_sdcard();
#endif // EXAMPLE_USE_SDCARD

    // Install USB Host driver. Should only be called once in entire application
    ESP_LOGI(TAG, "Installing USB Host");
    const usb_host_config_t host_config = {
        .skip_phy_setup = false,
        .intr_flags = ESP_INTR_FLAG_LEVEL1,
    };
    ESP_ERROR_CHECK(usb_host_install(&host_config));

    // Create a task that will handle USB library events
    BaseType_t task_created = xTaskCreatePinnedToCore(usb_lib_task, "usb_lib", 4096, NULL, EXAMPLE_USB_HOST_PRIORITY, NULL, tskNO_AFFINITY);
    assert(task_created == pdTRUE);

    ESP_LOGI(TAG, "Installing UVC driver");
    const uvc_host_driver_config_t uvc_driver_config = {
        .driver_task_stack_size = 4 * 1024,
        .driver_task_priority = EXAMPLE_USB_HOST_PRIORITY + 1,
        .xCoreID = tskNO_AFFINITY,
        .create_background_task = true,
    };
    ESP_ERROR_CHECK(uvc_host_install(&uvc_driver_config));

    task_created = xTaskCreatePinnedToCore(frame_handling_task, "mjpeg_handling", 4096, (void *)&stream_mjpeg_config, EXAMPLE_USB_HOST_PRIORITY - 2, NULL, tskNO_AFFINITY);
    assert(task_created == pdTRUE);

#if EXAMPLE_NUMBER_OF_STREAMS > 1
    vTaskDelay(pdMS_TO_TICKS(1000));
    task_created = xTaskCreatePinnedToCore(frame_handling_task, "h265_handling", 4096, (void *)&stream_h265_config, EXAMPLE_USB_HOST_PRIORITY - 3, NULL, tskNO_AFFINITY);
    assert(task_created == pdTRUE);
#endif // EXAMPLE_USE_SDCARD
}
