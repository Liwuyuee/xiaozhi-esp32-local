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
#include "descriptors/elp_h265.hpp"
using namespace elp_h265;

SCENARIO("Camera descriptor parsing: ELP h265", "[elp][h265]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("ELP h265 MJPEG") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_MJPEG_30_20_15(640, 360),
            FORMAT_MJPEG_30_20_15(640, 480),
            FORMAT_MJPEG_30_20_15(960, 540),
            FORMAT_MJPEG_30_20_15(1024, 576),
            FORMAT_MJPEG_30_20_15(1280, 720),
            FORMAT_MJPEG_30_20_15(1920, 1080),
            FORMAT_MJPEG_30_20_15(2560, 1440),
            FORMAT_MJPEG_30_20_15(3840, 2160),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("ELP h265 h264") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_H264_30_20_15(640, 360),
            FORMAT_H264_30_20_15(640, 480),
            FORMAT_H264_30_20_15(960, 540),
            FORMAT_H264_30_20_15(1024, 576),
            FORMAT_H264_30_20_15(1280, 720),
            FORMAT_H264_30_20_15(1920, 1080),
            FORMAT_H264_30_20_15(2560, 1440),
            FORMAT_H264_30_20_15(3840, 2160),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("ELP h265 h265") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_H265_30_20_15(640, 360),
            FORMAT_H265_30_20_15(640, 480),
            FORMAT_H265_30_20_15(960, 540),
            FORMAT_H265_30_20_15(1024, 576),
            FORMAT_H265_30_20_15(1280, 720),
            FORMAT_H265_30_20_15(1920, 1080),
            FORMAT_H265_30_20_15(2560, 1440),
            FORMAT_H265_30_20_15(3840, 2160),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("ELP h265 Uncompressed") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_UNCOMPRESSED_30_20_15(640, 360),
            FORMAT_UNCOMPRESSED_30_20_15(640, 480),

            {960, 540, 15, UVC_VS_FORMAT_YUY2},
            {960, 540, 10, UVC_VS_FORMAT_YUY2},
            {960, 540, 5, UVC_VS_FORMAT_YUY2},
            {960, 540, 0, UVC_VS_FORMAT_YUY2},

            {1024, 576, 15, UVC_VS_FORMAT_YUY2},
            {1024, 576, 10, UVC_VS_FORMAT_YUY2},
            {1024, 576, 5, UVC_VS_FORMAT_YUY2},
            {1024, 576, 0, UVC_VS_FORMAT_YUY2},

            {1280, 720, 10, UVC_VS_FORMAT_YUY2},
            {1280, 720, 5, UVC_VS_FORMAT_YUY2},
            {1280, 720, 2, UVC_VS_FORMAT_YUY2},
            {1280, 720, 0, UVC_VS_FORMAT_YUY2},

            {1920, 1080, 5, UVC_VS_FORMAT_YUY2},
            {1920, 1080, 2, UVC_VS_FORMAT_YUY2},
            {1920, 1080, 0, UVC_VS_FORMAT_YUY2},
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

    GIVEN("ELP h265 Unsupported") {
        uvc_host_stream_format_t formats[] = {
            {640, 480, 28, UVC_VS_FORMAT_MJPEG}, // Invalid FPS
            {645, 480, 25, UVC_VS_FORMAT_MJPEG}, // Invalid definition
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_NOT_SUPPORTED(cfg, this_format);
            }
        }
    }
}
