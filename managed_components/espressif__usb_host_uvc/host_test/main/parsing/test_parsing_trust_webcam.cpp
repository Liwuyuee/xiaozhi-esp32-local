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
#include "descriptors/trust_webcam.hpp"
using namespace trust_webcam;

SCENARIO("Camera descriptor parsing: Trust Webcam", "[trust][webcam]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("Trust Webcam Uncompressed") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_UNCOMPRESSED_30_5(640, 480),
            FORMAT_UNCOMPRESSED_30_5(352, 288),
            FORMAT_UNCOMPRESSED_30_5(320, 240),
            FORMAT_UNCOMPRESSED_30_5(176, 144),
            {1280, 1024, 5, UVC_VS_FORMAT_YUY2},
            {1280, 1024, 0, UVC_VS_FORMAT_YUY2},
            FORMAT_UNCOMPRESSED_30_5(160, 120),
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

    GIVEN("Trust Webcam Unsupported") {
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
