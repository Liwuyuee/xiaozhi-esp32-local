/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <catch2/catch_test_macros.hpp>

#include "usb/uvc_host.h"
#include "mock_add_usb_device.h"
#include "test_fixtures.hpp"

#include "descriptors/logitech_c270.hpp"
#include "descriptors/customer.hpp"
#include "descriptors/customer_dual.hpp"
#include "descriptors/elp_h265.hpp"

extern "C" {
#include "Mockusb_host.h"
}

#define ADD_MOCK_DEV(addr, namespc) REQUIRE(ESP_OK == usb_host_mock_add_device(addr, (const usb_device_desc_t *)namespc::dev_desc, (const usb_config_desc_t *)namespc::cfg_desc))

/**
 * @brief Add mocked devices
 *
 * Mocked devices are defined by a device descriptor, a configuration descriptor and a device address
 */
static void _add_mocked_devices(void)
{
    // Init mocked devices list at the beginning of the test
    usb_host_mock_dev_list_init();

    // Fill mocked devices list
    // @todo add all the cameras
    ADD_MOCK_DEV(1, logitech_c270);
    ADD_MOCK_DEV(2, customer_camera);
    ADD_MOCK_DEV(3, elp_h265);
    ADD_MOCK_DEV(4, customer_camera_dual);
}

SCENARIO("UVC driver install/uninstall")
{
    WHEN("UVC driver is not installed") {
        THEN("Stream cannot be opened") {
            REQUIRE(ESP_ERR_INVALID_STATE == uvc_host_stream_open(nullptr, 1000, nullptr));
        }
        THEN("Uninstallation fails") {
            REQUIRE(ESP_ERR_INVALID_STATE == uvc_host_uninstall());
        }
    }

    WHEN("UVC driver is installed") {
        const uvc_host_driver_config_t uvc_driver_config = {
            .driver_task_stack_size = 4 * 1024,
            .driver_task_priority = 10,
            .xCoreID = tskNO_AFFINITY,
            .create_background_task = true,
            .event_cb = nullptr,
            .user_ctx = nullptr,
        };
        REQUIRE(ESP_OK == test_uvc_host_install(&uvc_driver_config));

        THEN("Installing again fails") {
            REQUIRE(ESP_ERR_INVALID_STATE == uvc_host_install(&uvc_driver_config));
        }

        REQUIRE(ESP_OK == test_uvc_host_uninstall());

        AND_WHEN("UVC driver is installed again") {
            THEN("Installation succeeds") {
                REQUIRE(ESP_OK == test_uvc_host_install(&uvc_driver_config));
                REQUIRE(ESP_OK == test_uvc_host_uninstall());
            }
        }
    }
}

SCENARIO("Test mocked device opening and closing")
{
    // We will put device adding to the SECTION, to run it just once, not repeatedly for all the following SECTIONs
    // (if multiple sections are present)
    SECTION("Add mocked devices") {
        _add_mocked_devices();

        // Optionally, print all the devices
        //usb_host_mock_print_mocked_devices(0xFF);
    }

    SECTION("Install the UVC driver") {
        const uvc_host_driver_config_t uvc_driver_config = {
            .driver_task_stack_size = 4 * 1024,
            .driver_task_priority = 10,
            .xCoreID = tskNO_AFFINITY,
            .create_background_task = true,
            .event_cb = nullptr,
            .user_ctx = nullptr,
        };
        REQUIRE(ESP_OK == test_uvc_host_install(&uvc_driver_config));

        uvc_host_stream_config_t stream_config = {
            .event_cb = nullptr,
            .frame_cb = nullptr,
            .user_ctx = nullptr,
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

        THEN("Stream can be opened") {
            uvc_host_stream_hdl_t stream = nullptr;
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream, true));
            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream));
        }

        THEN("Multiple streams can be opened") {
            uvc_host_stream_hdl_t stream[10];

            // All these cameras support 1280x720@15 MJPEG format
            stream_config.usb.dev_addr = 1; // Same as = 0
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream[0], true));
            stream_config.usb.dev_addr = 2;
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream[1], false));
            stream_config.usb.dev_addr = 3;
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream[2], true));

            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream[0]));
            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream[1]));
            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream[2]));
        }

        THEN("Multiple streams from the same device can be opened") {
            uvc_host_stream_hdl_t stream[2];

            stream_config.usb.dev_addr = 4; // Dual camera
            stream_config.vs_format.h_res = 720;
            stream_config.vs_format.v_res = 1280;
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream[0], true));

            stream_config.vs_format.h_res = 640;
            stream_config.vs_format.v_res = 480;
            stream_config.vs_format.format = UVC_VS_FORMAT_H265;
            stream_config.usb.uvc_stream_index = 1;
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream[1], true));

            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream[0]));
            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream[1]));
        }

        THEN("Non-existent VID/PID cannot be opened") {
            uvc_host_stream_hdl_t stream = nullptr;
            stream_config.usb.vid = 1;
            stream_config.usb.pid = 1;
            REQUIRE(ESP_ERR_NOT_FOUND == uvc_host_stream_open(&stream_config, 0, &stream));
            REQUIRE(stream == nullptr);
        }

        THEN("Non-existent address cannot be opened") {
            uvc_host_stream_hdl_t stream = nullptr;
            stream_config.usb.dev_addr = 30;
            REQUIRE(ESP_ERR_NOT_FOUND == uvc_host_stream_open(&stream_config, 0, &stream));
            REQUIRE(stream == nullptr);
        }

        THEN("One stream cannot be opened twice") {
            uvc_host_stream_hdl_t stream = nullptr;
            uvc_host_stream_hdl_t stream2 = nullptr;
            stream_config.usb.vid = 0x046D;
            stream_config.usb.pid = 0x0825;
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream, true));

            // Second call to claim the same interface will fail in usb_host_lib
            usb_host_interface_claim_ExpectAnyArgsAndReturn(ESP_FAIL);
            REQUIRE_FALSE(ESP_OK == uvc_host_stream_open(&stream_config, 0, &stream2));

            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream));
        }

        REQUIRE(ESP_OK == test_uvc_host_uninstall());
    }
}

SCENARIO("Test mocked device format negotiation")
{
    // We will put device adding to the SECTION, to run it just once, not repeatedly for all the following SECTIONs
    // (if multiple sections are present)
    SECTION("Add mocked devices") {
        _add_mocked_devices();

        // Optionally, print all the devices
        //usb_host_mock_print_mocked_devices(0xFF);
    }

    SECTION("Install the UVC driver") {
        const uvc_host_driver_config_t uvc_driver_config = {
            .driver_task_stack_size = 4 * 1024,
            .driver_task_priority = 10,
            .xCoreID = tskNO_AFFINITY,
            .create_background_task = true,
            .event_cb = nullptr,
            .user_ctx = nullptr,
        };
        REQUIRE(ESP_OK == test_uvc_host_install(&uvc_driver_config));

        uvc_host_stream_config_t stream_config = {
            .event_cb = nullptr,
            .frame_cb = nullptr,
            .user_ctx = nullptr,
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

        THEN("Stream can be opened with default FPS value") {
            uvc_host_stream_hdl_t stream = nullptr;
            stream_config.vs_format.fps = 0;
            REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream, true));
            REQUIRE(ESP_OK == test_uvc_host_stream_close(stream));
        }

        // @todo this test is not working, because the mock does not support default format negotiation
        // To make it work, we must implement our own usb_host_transfer_submit_control_success_mock_callback()
        // that would return the default format
        // THEN("Stream can be opened with default format") {
        //     uvc_host_stream_hdl_t stream = nullptr;
        //     stream_config.vs_format.format = UVC_VS_FORMAT_DEFAULT;
        //     REQUIRE(ESP_OK == test_uvc_host_stream_open(&stream_config, 0, &stream, true));
        //     REQUIRE(ESP_OK == test_uvc_host_stream_close(stream));
        // }

        REQUIRE(ESP_OK == test_uvc_host_uninstall());
    }
}
