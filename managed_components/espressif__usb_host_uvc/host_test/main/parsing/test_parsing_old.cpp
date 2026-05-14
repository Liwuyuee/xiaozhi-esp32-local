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
#include "descriptors/old.hpp"

// Here is a collection of raw Configuration descriptors, but I don't have the cameras
// so not all supported formats are added :'(
using namespace old_cameras;

SCENARIO("Camera descriptor parsing: Logitech C980", "[old][logitech][c980]")
{
    const usb_config_desc_t *cfg = (const usb_config_desc_t *)Logitech_C980;

    GIVEN("Logitech C980") {
        uvc_host_stream_format_t formats[] = {
            {640, 480, 30, UVC_VS_FORMAT_MJPEG},
            {640, 480, 0, UVC_VS_FORMAT_MJPEG},
        };

        for (uvc_host_stream_format_t this_format : formats) {
            SECTION(std::to_string(this_format.h_res) + "x" + std::to_string(this_format.v_res) + "@" + std::to_string(this_format.fps)) {
                REQUIRE_FORMAT_SUPPORTED(cfg, this_format, 1);
            }
        }
    }
}
