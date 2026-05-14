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
#include "descriptors/logitech_c270.hpp"
using namespace logitech_c270;

SCENARIO("Camera descriptor parsing: Logitech C270", "[logitech][c270]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("Logitech C270 MJPEG") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_MJPEG_30_5(640, 480),
            FORMAT_MJPEG_30_5(160, 120),
            FORMAT_MJPEG_30_5(176, 144),
            FORMAT_MJPEG_30_5(320, 176),
            FORMAT_MJPEG_30_5(320, 240),
            FORMAT_MJPEG_30_5(352, 288),
            FORMAT_MJPEG_30_5(432, 240),
            FORMAT_MJPEG_30_5(544, 288),
            FORMAT_MJPEG_30_5(640, 360),
            FORMAT_MJPEG_30_5(752, 416),
            FORMAT_MJPEG_30_5(800, 448),
            FORMAT_MJPEG_30_5(800, 600),
            FORMAT_MJPEG_30_5(864, 480),
            FORMAT_MJPEG_30_5(960, 544),
            FORMAT_MJPEG_30_5(960, 720),
            FORMAT_MJPEG_30_5(1024, 576),
            FORMAT_MJPEG_30_5(1184, 656),
            FORMAT_MJPEG_30_5(1280, 720),
            FORMAT_MJPEG_30_5(1280, 960),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("Logitech C270 Uncompressed") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_UNCOMPRESSED_30_5(640, 480),
            FORMAT_UNCOMPRESSED_30_5(160, 120),
            FORMAT_UNCOMPRESSED_30_5(176, 144),
            FORMAT_UNCOMPRESSED_30_5(320, 176),
            FORMAT_UNCOMPRESSED_30_5(320, 240),
            FORMAT_UNCOMPRESSED_30_5(352, 288),
            FORMAT_UNCOMPRESSED_30_5(432, 240),
            FORMAT_UNCOMPRESSED_30_5(544, 288),
            FORMAT_UNCOMPRESSED_30_5(640, 360),
            {752, 416, 25, UVC_VS_FORMAT_YUY2},
            FORMAT_UNCOMPRESSED_20_5(752, 416),
            FORMAT_UNCOMPRESSED_20_5(800, 448),
            FORMAT_UNCOMPRESSED_20_5(800, 600),
            FORMAT_UNCOMPRESSED_20_5(864, 480),
            {960, 544, 15, UVC_VS_FORMAT_YUY2},
            {960, 544, 10, UVC_VS_FORMAT_YUY2},
            {960, 544, 5, UVC_VS_FORMAT_YUY2},
            {960, 544, 0, UVC_VS_FORMAT_YUY2},
            {960, 720, 10, UVC_VS_FORMAT_YUY2},
            {960, 720, 5, UVC_VS_FORMAT_YUY2},
            {960, 720, 0, UVC_VS_FORMAT_YUY2},
            {1024, 576, 10, UVC_VS_FORMAT_YUY2},
            {1024, 576, 5, UVC_VS_FORMAT_YUY2},
            {1024, 576, 0, UVC_VS_FORMAT_YUY2},
            {1184, 656, 10, UVC_VS_FORMAT_YUY2},
            {1184, 656, 5, UVC_VS_FORMAT_YUY2},
            {1184, 656, 0, UVC_VS_FORMAT_YUY2},
            {1280, 720, 7.5f, UVC_VS_FORMAT_YUY2},
            {1280, 720, 5, UVC_VS_FORMAT_YUY2},
            {1280, 720, 0, UVC_VS_FORMAT_YUY2},
            {1280, 960, 7.5f, UVC_VS_FORMAT_YUY2},
            {1280, 960, 5, UVC_VS_FORMAT_YUY2},
            {1280, 960, 0, UVC_VS_FORMAT_YUY2},
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

    GIVEN("Logitech C270 Unsupported") {
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
