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
#include "descriptors/anker_powerconf_c200.hpp"
using namespace anker_powerconf_c200;

SCENARIO("Camera descriptor parsing: Anker Powerconf C200", "[anker][powerconf][c200]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("Anker Powerconf C200 MJPEG") {
        uvc_host_stream_format_t formats[] = {
            {2560, 1440, 30, UVC_VS_FORMAT_MJPEG},
            {1920, 1080, 30, UVC_VS_FORMAT_MJPEG},
            {1280, 720, 30, UVC_VS_FORMAT_MJPEG},
            {640, 480, 30, UVC_VS_FORMAT_MJPEG},
            {640, 360, 30, UVC_VS_FORMAT_MJPEG},
            {320, 240, 30, UVC_VS_FORMAT_MJPEG},
            {320, 240, 0, UVC_VS_FORMAT_MJPEG},
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("Anker Powerconf C200 Uncompressed") {
        uvc_host_stream_format_t formats[] = {
            {640, 480, 30, UVC_VS_FORMAT_YUY2},
            {640, 360, 30, UVC_VS_FORMAT_YUY2},
            {320, 240, 30, UVC_VS_FORMAT_YUY2},
            {320, 240, 0, UVC_VS_FORMAT_YUY2},
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("Anker Powerconf C200 h264") {
        uvc_host_stream_format_t formats[] = {
            {2560, 1440, 30, UVC_VS_FORMAT_H264},
            {1920, 1080, 30, UVC_VS_FORMAT_H264},
            {1280, 720, 30,  UVC_VS_FORMAT_H264},
            {640, 480, 30,   UVC_VS_FORMAT_H264},
            {640, 360, 30,   UVC_VS_FORMAT_H264},
            {320, 240, 30,   UVC_VS_FORMAT_H264},
            {320, 240, 0,   UVC_VS_FORMAT_H264},
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

    GIVEN("Anker Powerconf C200 Unsupported") {
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
