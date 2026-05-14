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
#include "descriptors/customer.hpp"
using namespace customer_camera;

SCENARIO("Camera descriptor parsing: Customer", "[customer][single]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("Customer MJPEG") {
        uvc_host_stream_format_t formats[] = {
            {1280, 720, 15, UVC_VS_FORMAT_MJPEG},
            {1280, 720, 10, UVC_VS_FORMAT_MJPEG},
            {1280, 720, 0, UVC_VS_FORMAT_MJPEG},
            {800, 480, 20, UVC_VS_FORMAT_MJPEG},
            {800, 480, 15, UVC_VS_FORMAT_MJPEG},
            {800, 480, 0, UVC_VS_FORMAT_MJPEG},
            {640, 480, 25, UVC_VS_FORMAT_MJPEG},
            {640, 480, 15, UVC_VS_FORMAT_MJPEG},
            {640, 480, 0, UVC_VS_FORMAT_MJPEG},
            {480, 320, 25, UVC_VS_FORMAT_MJPEG},
            {480, 320, 15, UVC_VS_FORMAT_MJPEG},
            {480, 320, 0, UVC_VS_FORMAT_MJPEG},
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("Default format") {
        REQUIRE_FORMAT_DEFAULT(cfg, 1);
    }

    GIVEN("Customer Unsupported") {
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
