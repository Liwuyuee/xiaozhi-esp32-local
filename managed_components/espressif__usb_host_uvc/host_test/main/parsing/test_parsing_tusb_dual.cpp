/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <catch2/catch_test_macros.hpp>

#include "usb/uvc_host.h"
#include "uvc_descriptors_priv.h"

#include "test_parsing_helpers.hpp"
#include "descriptors/dual_tusb.hpp"
using namespace dual_tusb;

SCENARIO("Camera descriptor parsing: TinyUSB dual UVC", "[tusb][dual]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("TinyUSB dual UVC MJPEG 0") {
        uvc_host_stream_format_t formats[] = {
            {480, 270, 20, UVC_VS_FORMAT_MJPEG},
            {480, 270, 0, UVC_VS_FORMAT_MJPEG},
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("TinyUSB dual UVC MJPEG 1") {
        uvc_host_stream_format_t formats[] = {
            {1280, 720, 15, UVC_VS_FORMAT_MJPEG},
            {1280, 720, 0, UVC_VS_FORMAT_MJPEG},
        };

        for (uvc_host_stream_format_t this_format : formats) {
            // Here we test uvc_index = 1
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                uint8_t bInterfaceNumber = 0;
                uint16_t bcdUVC = 0;
                REQUIRE(ESP_OK == uvc_desc_get_streaming_interface_num(cfg, 1, &this_format, &bcdUVC, &bInterfaceNumber));
                REQUIRE(bInterfaceNumber == 3);
                const usb_intf_desc_t *intf_desc = nullptr;
                const usb_ep_desc_t *ep_desc = nullptr;
                REQUIRE(ESP_OK == uvc_desc_get_streaming_intf_and_ep(cfg, bInterfaceNumber, 1024, &intf_desc, &ep_desc));
                REQUIRE(intf_desc != nullptr);
                REQUIRE(ep_desc != nullptr);
                const uvc_format_desc_t *format_desc = nullptr;
                const uvc_frame_desc_t *frame_desc = nullptr;
                REQUIRE(ESP_OK == uvc_desc_get_frame_format_by_format(cfg, bInterfaceNumber, &this_format, &format_desc, &frame_desc));
                REQUIRE(format_desc != nullptr);
                REQUIRE(frame_desc != nullptr);
            }
        }
    }

    GIVEN("Default format") {
        REQUIRE_FORMAT_DEFAULT(cfg, 1);
    }

    GIVEN("TinyUSB dual UVC Unsupported") {
        uvc_host_stream_format_t formats[] = {
            {640, 480, 28, UVC_VS_FORMAT_MJPEG}, // Invalid FPS
            {645, 480, 25, UVC_VS_FORMAT_MJPEG}, // Invalid definition
            {640, 480, 20, UVC_VS_FORMAT_H264},  // Invalid format
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_NOT_SUPPORTED(cfg, this_format);
            }
        }
    }
}
