/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "core/gfx_types.h"
#include "core/gfx_core.h"
#include "core/gfx_obj.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

// Default screen dimensions for alignment calculation
#define DEFAULT_SCREEN_WIDTH  320
#define DEFAULT_SCREEN_HEIGHT 240

/**********************
 *      TYPEDEFS
 **********************/

typedef struct gfx_core_child_t {
    int type;
    void *src;
    struct gfx_core_child_t *next;  // Pointer to next child in the list
} gfx_core_child_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Internal alignment functions
 *====================*/

/**
 * @brief Calculate aligned position for an object (internal use)
 * @param obj Pointer to the object
 * @param parent_width Parent container width in pixels
 * @param parent_height Parent container height in pixels
 * @param x Pointer to store calculated X coordinate
 * @param y Pointer to store calculated Y coordinate
 */
void gfx_obj_calculate_aligned_position(gfx_obj_t *obj, uint32_t parent_width, uint32_t parent_height, gfx_coord_t *x, gfx_coord_t *y);

#ifdef __cplusplus
}
#endif
