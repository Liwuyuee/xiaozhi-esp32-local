/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <catch2/catch_test_macros.hpp>

#include "usb/uvc_host.h"
#include "uvc_descriptors_priv.h"

#include "test_parsing_helpers.hpp"
#include "descriptors/canyon_cne_cwc2.hpp"
using namespace canyon_cne_cwc2;

SCENARIO("Camera descriptor parsing: Canyon CNE CWC2", "[canyon][cne_cwc2]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("Canyon CNE CWC2 MJPEG") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_MJPEG_30_5(640, 480),
            FORMAT_MJPEG_30_5(352, 288),
            FORMAT_MJPEG_30_5(320, 240),
            FORMAT_MJPEG_30_5(176, 144),
            FORMAT_MJPEG_30_5(160, 120),
            FORMAT_MJPEG_30_5(800, 600),
            {1280, 720, 15, UVC_VS_FORMAT_MJPEG},
            {1280, 720, 10, UVC_VS_FORMAT_MJPEG},
            {1280, 720, 5, UVC_VS_FORMAT_MJPEG},
            {1280, 720, 0, UVC_VS_FORMAT_MJPEG},
            {1280, 960, 15, UVC_VS_FORMAT_MJPEG},
            {1280, 960, 10, UVC_VS_FORMAT_MJPEG},
            {1280, 960, 5, UVC_VS_FORMAT_MJPEG},
            {1280, 960, 0, UVC_VS_FORMAT_MJPEG},
            {1600, 1200, 15, UVC_VS_FORMAT_MJPEG},
            {1600, 1200, 10, UVC_VS_FORMAT_MJPEG},
            {1600, 1200, 5, UVC_VS_FORMAT_MJPEG},
            {1600, 1200, 0, UVC_VS_FORMAT_MJPEG},
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("Canyon CNE CWC2 Uncompressed") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_UNCOMPRESSED_30_5(640, 480),
            FORMAT_UNCOMPRESSED_30_5(352, 288),
            FORMAT_UNCOMPRESSED_30_5(320, 240),
            FORMAT_UNCOMPRESSED_30_5(176, 144),
            FORMAT_UNCOMPRESSED_30_5(160, 120),
            FORMAT_UNCOMPRESSED_20_5(800, 600),
            {1280, 720, 10, UVC_VS_FORMAT_YUY2},
            {1280, 720, 5, UVC_VS_FORMAT_YUY2},
            {1280, 720, 0, UVC_VS_FORMAT_YUY2},
            {1280, 960, 9, UVC_VS_FORMAT_YUY2},
            {1280, 960, 5, UVC_VS_FORMAT_YUY2},
            {1280, 960, 0, UVC_VS_FORMAT_YUY2},
            {1600, 1200, 5, UVC_VS_FORMAT_YUY2},
            {1600, 1200, 0, UVC_VS_FORMAT_YUY2},
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

    GIVEN("Canyon CNE CWC2 Unsupported") {
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
