/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Basic types */
typedef uint8_t     gfx_opa_t;      /**< Opacity (0-255) */
typedef int16_t     gfx_coord_t;    /**< Coordinate type */

/* Color type with full member for compatibility */
typedef union {
    uint16_t full;                  /**< Full 16-bit color value */
} gfx_color_t;

/* Area structure */
typedef struct {
    gfx_coord_t x1;
    gfx_coord_t y1;
    gfx_coord_t x2;
    gfx_coord_t y2;
} gfx_area_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * @brief Convert a 32-bit hexadecimal color to gfx_color_t
 * @param c The 32-bit hexadecimal color to convert
 * @return Converted color in gfx_color_t type
 */
gfx_color_t gfx_color_hex(uint32_t c);


/**********************
 *      MACROS
 **********************/

#define GFX_COLOR_HEX(color) ((gfx_color_t)gfx_color_hex(color))

#ifdef __cplusplus
}
#endif
