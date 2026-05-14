/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "soc/soc_caps.h"
#if SOC_USB_OTG_SUPPORTED

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "unity.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_private/usb_phy.h"
#include "usb/usb_host.h"
#include "usb/uvc_host.h"
#include "esp_private/uvc_esp_video.h"

void usb_lib_task(void *arg)
{
    const usb_host_config_t host_config = {
        .skip_phy_setup = false,
        .intr_flags = ESP_INTR_FLAG_LEVEL1,
    };
    TEST_ASSERT_EQUAL(ESP_OK, usb_host_install(&host_config));
    printf("USB Host installed\n");
    xTaskNotifyGive(arg);

    bool has_clients = true;
    bool has_devices = false;
    while (has_clients) {
        uint32_t event_flags;
        ESP_ERROR_CHECK(usb_host_lib_handle_events(portMAX_DELAY, &event_flags));
        if (event_flags & USB_HOST_LIB_EVENT_FLAGS_NO_CLIENTS) {
            printf("Get FLAGS_NO_CLIENTS\n");
            if (ESP_OK == usb_host_device_free_all()) {
                printf("All devices marked as free, no need to wait FLAGS_ALL_FREE event\n");
                has_clients = false;
            } else {
                printf("Wait for the FLAGS_ALL_FREE\n");
                has_devices = true;
            }
        }
        if (has_devices && event_flags & USB_HOST_LIB_EVENT_FLAGS_ALL_FREE) {
            printf("Get FLAGS_ALL_FREE\n");
            has_clients = false;
        }
    }
    printf("No more clients and devices, uninstall USB Host library\n");

    // Clean up USB Host
    vTaskDelay(10); // Short delay to allow clients clean-up
    TEST_ASSERT_EQUAL(ESP_OK, usb_host_uninstall());
    vTaskDelete(NULL);
}

/**
 * @brief Install UVC driver
 *
 * This function installs prerequisites for many tests: USB Host library and UVC driver.
 * It also creates a task that handles USB library events.
 */
void test_install_uvc_driver(void)
{
    // Create a task that will handle USB library events
    TEST_ASSERT_EQUAL(pdTRUE, xTaskCreatePinnedToCore(usb_lib_task, "usb_lib", 4 * 4096, xTaskGetCurrentTaskHandle(), 10, NULL, 0));
    ulTaskNotifyTake(false, 1000);

    printf("Installing UVC driver\n");
    const uvc_host_driver_config_t uvc_driver_config = {
        .driver_task_stack_size = 4 * 1024,
        .driver_task_priority = 10,
        .xCoreID = tskNO_AFFINITY,
        .create_background_task = true,
        .event_cb = NULL,
        .user_ctx = NULL,
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_install(&uvc_driver_config));
}

/**
 * @brief UVC default FPS test
 *
 * -# Request default FPS
 * -# Check that the stream can be opened
 * -# Check that the FPS is set 30 (default FPS for 1280x720 MJPEG format on Logitech C270 camera)
 */
TEST_CASE("Open with default FPS", "[uvc]")
{
    test_install_uvc_driver();

    printf("Opening UVC stream\n");
    uvc_host_stream_hdl_t stream = NULL;
    uvc_host_stream_config_t stream_config = {
        .event_cb = NULL,
        .frame_cb = NULL,
        .user_ctx = NULL,
        .usb = {
            .dev_addr = UVC_HOST_ANY_DEV_ADDR,
            .vid = UVC_HOST_ANY_VID,
            .pid = UVC_HOST_ANY_PID,
            .uvc_stream_index = 0,
        },
        .vs_format = {
            .h_res = 1280,
            .v_res = 720,
            .fps = 0, // Default FPS
            .format = UVC_VS_FORMAT_MJPEG,
        },
        .advanced = {
            .number_of_frame_buffers = 3,
            .frame_size = 0,
            .frame_heap_caps = 0,
            .number_of_urbs = 4,
            .urb_size = 10 * 1024,
        },
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_open(&stream_config, 1000, &stream));
    TEST_ASSERT_NOT_NULL(stream);
    vTaskDelay(10);

    // Get format, check if it matches the requested format
    uvc_host_stream_format_t format_set;
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_get(stream, &format_set));
    printf("\tFormat: %dx%d@%2.0f, %d\n", format_set.h_res, format_set.v_res, format_set.fps, format_set.format);
    TEST_ASSERT_EQUAL(stream_config.vs_format.h_res,  format_set.h_res);
    TEST_ASSERT_EQUAL(stream_config.vs_format.v_res,  format_set.v_res);
    TEST_ASSERT_EQUAL(30,                             format_set.fps); // Default FPS
    TEST_ASSERT_EQUAL(stream_config.vs_format.format, format_set.format);

    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_close(stream));
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_uninstall());
    vTaskDelay(20); // Short delay to allow task to be cleaned up
}

/**
 * @brief UVC default format test
 *
 * -# Request UVC_VS_FORMAT_DEFAULT format
 * -# Check that the stream can be opened
 * -# Check that the format is set to 640x480@30fps YUY2 (default format after power on Logitech C270 camera)
 */
TEST_CASE("Open with default format", "[uvc]")
{
    test_install_uvc_driver();

    printf("Opening UVC stream\n");
    uvc_host_stream_hdl_t stream = NULL;
    // Minimalistic stream config
    uvc_host_stream_config_t stream_config = {
        .advanced = {
            .number_of_frame_buffers = 3,
            .number_of_urbs = 4,
            .urb_size = 10 * 1024,
        },
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_open(&stream_config, 1000, &stream));
    TEST_ASSERT_NOT_NULL(stream);
    vTaskDelay(10);

    // Get format, check if it matches the requested format
    uvc_host_stream_format_t format_set;
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_get(stream, &format_set));
    printf("\tDefault format: %dx%d@%2.0f, %d\n", format_set.h_res, format_set.v_res, format_set.fps, format_set.format);
    TEST_ASSERT_EQUAL(640,                format_set.h_res);
    TEST_ASSERT_EQUAL(480,                format_set.v_res);
    TEST_ASSERT_EQUAL(30,                 format_set.fps);
    TEST_ASSERT_EQUAL(UVC_VS_FORMAT_YUY2, format_set.format);

    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_close(stream));
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_uninstall());
    vTaskDelay(20); // Short delay to allow task to be cleaned up
}

/**
 * @brief UVC dynamic format change test
 *
 * After each check, dwMaxVideoFrameSize is checked to be correct for the format.
 * The test is done on Logitech C270 camera.
 *
 * -# Open UVC stream with 1280x720@15fps MJPEG format
 * -# Check that the stream can be opened
 * -# Check that the format is set to 1280x720@15fps MJPEG
 * -# Change the format to 640x480@30fps MJPEG
 * -# Check that the format is set to 640x480@30fps MJPEG
 * -# Change the format to 1280x720 MJPEG
 * -# Check that the format is set to 1280x720@30fps MJPEG
 * -# Change the format to YUY2
 * -# Check that the format is set to 1280x720@5fps YUY2
 */
TEST_CASE("Open and change format", "[uvc]")
{
    test_install_uvc_driver();

    printf("Opening UVC stream\n");
    uvc_host_stream_hdl_t stream = NULL;
    uvc_host_stream_config_t stream_config = {
        .event_cb = NULL,
        .frame_cb = NULL,
        .user_ctx = NULL,
        .usb = {
            .dev_addr = UVC_HOST_ANY_DEV_ADDR,
            .vid = UVC_HOST_ANY_VID,
            .pid = UVC_HOST_ANY_PID,
            .uvc_stream_index = 0,
        },
        .vs_format = {
            .h_res = 1280,
            .v_res = 720,
            .fps = 15,
            .format = UVC_VS_FORMAT_MJPEG,
        },
        .advanced = {
            .number_of_frame_buffers = 3,
            .frame_size = 0,
            .frame_heap_caps = 0,
            .number_of_urbs = 4,
            .urb_size = 10 * 1024,
        },
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_open(&stream_config, 1000, &stream)); // 0x303A:0x4002 (TinyUSB Dual CDC device)
    TEST_ASSERT_NOT_NULL(stream);
    vTaskDelay(10);

    // Get format, check if it matches the requested format
    uvc_host_stream_format_t format_set;
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_get(stream, &format_set));
    TEST_ASSERT_EQUAL(stream_config.vs_format.h_res,  format_set.h_res);
    TEST_ASSERT_EQUAL(stream_config.vs_format.v_res,  format_set.v_res);
    TEST_ASSERT_EQUAL(stream_config.vs_format.fps,    format_set.fps);
    TEST_ASSERT_EQUAL(stream_config.vs_format.format, format_set.format);

    // Check dwMaxVideoFrameSize
    uvc_host_buf_info_t buf_info;
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_buf_info_get(stream, &buf_info));
    TEST_ASSERT_EQUAL(1632000, buf_info.dwMaxVideoFrameSize); // For this format on Logitech C270 camera

    // Change the format
    uvc_host_stream_format_t format2 = {
        .h_res = 640,
        .v_res = 480,
        .fps = 30,
        .format = UVC_VS_FORMAT_MJPEG,
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_select(stream, &format2));

    // Get format, check if it matches the requested format
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_get(stream, &format_set));
    TEST_ASSERT_EQUAL(format2.h_res,  format_set.h_res);
    TEST_ASSERT_EQUAL(format2.v_res,  format_set.v_res);
    TEST_ASSERT_EQUAL(format2.fps,    format_set.fps);
    TEST_ASSERT_EQUAL(format2.format, format_set.format);

    // Check dwMaxVideoFrameSize for the changed format
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_buf_info_get(stream, &buf_info));
    TEST_ASSERT_EQUAL(102400, buf_info.dwMaxVideoFrameSize); // For this format on Logitech C270 camera

    // Change only FPS
    uvc_host_stream_format_t format3 = {
        .fps = 15,
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_select(stream, &format3));
    // Get format, check if it matches the requested format
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_get(stream, &format_set));
    TEST_ASSERT_EQUAL(format3.fps,    format_set.fps);
    // Check the rest, should not be changed
    TEST_ASSERT_EQUAL(format2.h_res,  format_set.h_res);
    TEST_ASSERT_EQUAL(format2.v_res,  format_set.v_res);
    TEST_ASSERT_EQUAL(format2.format, format_set.format);

    // Change only resolution with default FPS
    uvc_host_stream_format_t format4 = {
        .h_res = 1280,
        .v_res = 720,
        .fps = 0,
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_select(stream, &format4));
    // Get format, check if it matches the requested format
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_get(stream, &format_set));
    TEST_ASSERT_EQUAL(format4.h_res,  format_set.h_res);  // Must be set exactly
    TEST_ASSERT_EQUAL(format4.v_res,  format_set.v_res);  // Must be set exactly
    TEST_ASSERT_EQUAL(30,             format_set.fps);    // Must be default
    TEST_ASSERT_EQUAL(format2.format, format_set.format); // Must be preserved

    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_buf_info_get(stream, &buf_info));
    TEST_ASSERT_EQUAL(816000, buf_info.dwMaxVideoFrameSize); // For this format on Logitech C270 camera

    // Change only format with default FPS
    uvc_host_stream_format_t format5 = {
        .format = UVC_VS_FORMAT_YUY2,
    };
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_select(stream, &format5));
    // Get format, check if it matches the requested format
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_format_get(stream, &format_set));
    TEST_ASSERT_EQUAL(format5.format, format_set.format); // Must be set exactly
    TEST_ASSERT_EQUAL(format4.h_res,  format_set.h_res);  // Must be preserved
    TEST_ASSERT_EQUAL(format4.v_res,  format_set.v_res);  // Must be preserved
    TEST_ASSERT_EQUAL(5,              format_set.fps);    // Must be default

    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_buf_info_get(stream, &buf_info));
    TEST_ASSERT_EQUAL(1843200, buf_info.dwMaxVideoFrameSize); // For this format on Logitech C270 camera

    // Clean-up
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_stream_close(stream));
    TEST_ASSERT_EQUAL(ESP_OK, uvc_host_uninstall());
    vTaskDelay(20); // Short delay to allow task to be cleaned up
}

#endif // SOC_USB_OTG_SUPPORTED
