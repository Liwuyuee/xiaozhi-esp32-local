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
#include "descriptors/elp_h264.hpp"
using namespace elp_h264;

SCENARIO("Camera descriptor parsing: ELP h264", "[elp][h264]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("ELP h264 MJPEG") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_MJPEG_30_25_15(1920, 1080),
            FORMAT_MJPEG_30_25_15(1280, 720),
            FORMAT_MJPEG_30_25_15(800, 600),
            FORMAT_MJPEG_30_25_15(640, 480),
            FORMAT_MJPEG_30_25_15(640, 360),
            FORMAT_MJPEG_30_25_15(352, 288),
            FORMAT_MJPEG_30_25_15(320, 240),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("ELP h264 Uncompressed") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_UNCOMPRESSED_30_25_15(640, 480),
            {800, 600, 15, UVC_VS_FORMAT_YUY2},
            {800, 600, 0, UVC_VS_FORMAT_YUY2},
            FORMAT_UNCOMPRESSED_30_25_15(640, 360),
            FORMAT_UNCOMPRESSED_30_25_15(352, 288),
            FORMAT_UNCOMPRESSED_30_25_15(320, 240),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("ELP h264 h264") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_H264_30_25_15(1920, 1080),
            FORMAT_H264_30_25_15(1280, 720),
            FORMAT_H264_30_25_15(800, 600),
            FORMAT_H264_30_25_15(640, 480),
            FORMAT_H264_30_25_15(640, 360),
            FORMAT_H264_30_25_15(352, 288),
            FORMAT_H264_30_25_15(320, 240),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 2);
            }
        }
    }

    GIVEN("Default format") {
        REQUIRE_FORMAT_DEFAULT(cfg, 1);
    }

    GIVEN("ELP h264 Unsupported") {
        uvc_host_stream_format_t formats[] = {
            {640, 480, 28, UVC_VS_FORMAT_MJPEG}, // Invalid FPS
            {645, 480, 25, UVC_VS_FORMAT_MJPEG}, // Invalid definition
            {640, 480, 20, UVC_VS_FORMAT_H265},  // Invalid format
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_NOT_SUPPORTED(cfg, this_format);
            }
        }
    }
}
