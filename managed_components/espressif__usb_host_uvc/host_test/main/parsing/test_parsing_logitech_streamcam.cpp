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
#include "descriptors/logitech_streamcam.hpp"
using namespace logitech_streamcam;

#define FORMAT_MJPEG(x, y)             \
    {x, y, 30, UVC_VS_FORMAT_MJPEG},   \
    {x, y, 24, UVC_VS_FORMAT_MJPEG},   \
    {x, y, 20, UVC_VS_FORMAT_MJPEG},   \
    {x, y, 15, UVC_VS_FORMAT_MJPEG},   \
    {x, y, 10, UVC_VS_FORMAT_MJPEG},   \
    {x, y, 7.5f, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 5, UVC_VS_FORMAT_MJPEG}

#define FORMAT_UNCOMPRESSED(x, y)      \
    {x, y, 30, UVC_VS_FORMAT_YUY2},    \
    {x, y, 24, UVC_VS_FORMAT_YUY2},    \
    {x, y, 20, UVC_VS_FORMAT_YUY2},    \
    {x, y, 15, UVC_VS_FORMAT_YUY2},    \
    {x, y, 10, UVC_VS_FORMAT_YUY2},    \
    {x, y, 7.5f, UVC_VS_FORMAT_YUY2},  \
    {x, y, 5, UVC_VS_FORMAT_YUY2}

SCENARIO("Camera descriptor parsing: Logitech Streamcam", "[logitech][streamcam]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)cfg_desc;

    GIVEN("Logitech Streamcam MJPEG") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_MJPEG(640, 480),
            FORMAT_MJPEG(176, 144),
            FORMAT_MJPEG(320, 240),
            FORMAT_MJPEG(424, 240),
            FORMAT_MJPEG(640, 360),
            FORMAT_MJPEG(848, 480),
            FORMAT_MJPEG(960, 540),
            FORMAT_MJPEG(1280, 720),
            FORMAT_MJPEG(1600, 896),
            FORMAT_MJPEG(1920, 1080),
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }

    GIVEN("Logitech Streamcam Uncompressed") {
        uvc_host_stream_format_t formats[] = {
            FORMAT_UNCOMPRESSED(640, 480),
            FORMAT_UNCOMPRESSED(176, 144),
            FORMAT_UNCOMPRESSED(320, 240),
            FORMAT_UNCOMPRESSED(424, 240),
            FORMAT_UNCOMPRESSED(640, 360),
            FORMAT_UNCOMPRESSED(848, 480),

            {960, 540, 15, UVC_VS_FORMAT_YUY2},
            {960, 540, 10, UVC_VS_FORMAT_YUY2},
            {960, 540, 7.5f, UVC_VS_FORMAT_YUY2},
            {960, 540, 5, UVC_VS_FORMAT_YUY2},
            {960, 540, 0, UVC_VS_FORMAT_YUY2},

            {1280, 720, 10, UVC_VS_FORMAT_YUY2},
            {1280, 720, 7.5f, UVC_VS_FORMAT_YUY2},
            {1280, 720, 5, UVC_VS_FORMAT_YUY2},
            {1280, 720, 0, UVC_VS_FORMAT_YUY2},

            {1600, 896, 7.5f, UVC_VS_FORMAT_YUY2},
            {1600, 896, 5, UVC_VS_FORMAT_YUY2},
            {1600, 896, 0, UVC_VS_FORMAT_YUY2},

            {1920, 1080, 5, UVC_VS_FORMAT_YUY2},
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

    GIVEN("Logitech Streamcam Unsupported") {
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
