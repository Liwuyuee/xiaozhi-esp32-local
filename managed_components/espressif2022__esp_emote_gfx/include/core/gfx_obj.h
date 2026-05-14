/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "gfx_types.h"
#include "gfx_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/* Object types */
#define GFX_OBJ_TYPE_IMAGE        0x01
#define GFX_OBJ_TYPE_LABEL        0x02
#define GFX_OBJ_TYPE_ANIMATION    0x03

/* Alignment constants (similar to LVGL) */
#define GFX_ALIGN_DEFAULT         0x00
#define GFX_ALIGN_TOP_LEFT        0x00
#define GFX_ALIGN_TOP_MID         0x01
#define GFX_ALIGN_TOP_RIGHT       0x02
#define GFX_ALIGN_LEFT_MID        0x03
#define GFX_ALIGN_CENTER          0x04
#define GFX_ALIGN_RIGHT_MID       0x05
#define GFX_ALIGN_BOTTOM_LEFT     0x06
#define GFX_ALIGN_BOTTOM_MID      0x07
#define GFX_ALIGN_BOTTOM_RIGHT    0x08
#define GFX_ALIGN_OUT_TOP_LEFT    0x09
#define GFX_ALIGN_OUT_TOP_MID     0x0A
#define GFX_ALIGN_OUT_TOP_RIGHT   0x0B
#define GFX_ALIGN_OUT_LEFT_TOP    0x0C
#define GFX_ALIGN_OUT_LEFT_MID    0x0D
#define GFX_ALIGN_OUT_LEFT_BOTTOM 0x0E
#define GFX_ALIGN_OUT_RIGHT_TOP   0x0F
#define GFX_ALIGN_OUT_RIGHT_MID   0x10
#define GFX_ALIGN_OUT_RIGHT_BOTTOM 0x11
#define GFX_ALIGN_OUT_BOTTOM_LEFT 0x12
#define GFX_ALIGN_OUT_BOTTOM_MID  0x13
#define GFX_ALIGN_OUT_BOTTOM_RIGHT 0x14

/**********************
 *      TYPEDEFS
 **********************/

/* Graphics object structure */
typedef struct gfx_obj {
    void *src;                  /**< Source data (image, label, etc.) */
    int type;                   /**< Object type */
    gfx_coord_t x;              /**< X position */
    gfx_coord_t y;              /**< Y position */
    uint16_t width;             /**< Object width */
    uint16_t height;            /**< Object height */
    bool is_visible;            /**< Object visibility */
    bool is_dirty;              /**< Object dirty flag */
    uint8_t align_type;         /**< Alignment type (see GFX_ALIGN_* constants) */
    gfx_coord_t align_x_ofs;    /**< X offset for alignment */
    gfx_coord_t align_y_ofs;    /**< Y offset for alignment */
    bool use_align;             /**< Whether to use alignment instead of absolute position */
    gfx_handle_t parent_handle; /**< Parent graphics handle */
} gfx_obj_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Object setter functions
 *====================*/

/**
 * @brief Set the position of an object
 * @param obj Pointer to the object
 * @param x X coordinate
 * @param y Y coordinate
 */
void gfx_obj_set_pos(gfx_obj_t *obj, gfx_coord_t x, gfx_coord_t y);

/**
 * @brief Set the size of an object
 * @param obj Pointer to the object
 * @param w Width
 * @param h Height
 */
void gfx_obj_set_size(gfx_obj_t *obj, uint16_t w, uint16_t h);

/**
 * @brief Align an object relative to the screen or another object
 * @param obj Pointer to the object to align
 * @param align Alignment type (see GFX_ALIGN_* constants)
 * @param x_ofs X offset from the alignment position
 * @param y_ofs Y offset from the alignment position
 */
void gfx_obj_align(gfx_obj_t *obj, uint8_t align, gfx_coord_t x_ofs, gfx_coord_t y_ofs);

/**
 * @brief Set object visibility
 * @param obj Object to set visibility for
 * @param visible True to make object visible, false to hide
 */
void gfx_obj_set_visible(gfx_obj_t *obj, bool visible);

/**
 * @brief Get object visibility
 * @param obj Object to check visibility for
 * @return True if object is visible, false if hidden
 */
bool gfx_obj_get_visible(gfx_obj_t *obj);

/*=====================
 * Object getter functions
 *====================*/

/**
 * @brief Get the position of an object
 * @param obj Pointer to the object
 * @param x Pointer to store X coordinate
 * @param y Pointer to store Y coordinate
 */
void gfx_obj_get_pos(gfx_obj_t *obj, gfx_coord_t *x, gfx_coord_t *y);

/**
 * @brief Get the size of an object
 * @param obj Pointer to the object
 * @param w Pointer to store width
 * @param h Pointer to store height
 */
void gfx_obj_get_size(gfx_obj_t *obj, uint16_t *w, uint16_t *h);

/*=====================
 * Object management functions
 *====================*/

/**
 * @brief Delete an object
 * @param obj Pointer to the object to delete
 */
void gfx_obj_delete(gfx_obj_t *obj);

#ifdef __cplusplus
}
#endif
