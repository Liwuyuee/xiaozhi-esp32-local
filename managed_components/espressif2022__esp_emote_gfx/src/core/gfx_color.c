/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "core/gfx_types.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

gfx_color_t gfx_color_hex(uint32_t c)
{
    gfx_color_t r;
    r.full = (uint16_t)(((c & 0xF80000) >> 8) | ((c & 0xFC00) >> 5) | ((c & 0xFF) >> 3));
    return r;
}
