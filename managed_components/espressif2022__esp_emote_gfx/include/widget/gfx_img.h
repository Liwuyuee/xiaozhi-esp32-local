/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "core/gfx_types.h"
#include "core/gfx_obj.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/* Magic numbers for image headers */
#define C_ARRAY_HEADER_MAGIC    0x19

/**********************
 *      TYPEDEFS
 **********************/

/* Color format enumeration - simplified for public use */
typedef enum {
    GFX_COLOR_FORMAT_RGB565A8 = 0x0A,
} gfx_color_format_t;

typedef struct {
    uint32_t magic: 8;          /**< Magic number. Must be GFX_IMAGE_HEADER_MAGIC */
    uint32_t cf : 8;            /**< Color format: See `gfx_color_format_t` */
    uint32_t flags: 16;         /**< Image flags */
    uint32_t w: 16;             /**< Width of the image */
    uint32_t h: 16;             /**< Height of the image */
    uint32_t stride: 16;        /**< Number of bytes in a row */
    uint32_t reserved: 16;      /**< Reserved for future use */
} gfx_image_header_t;

/* Image descriptor structure - compatible with LVGL */
typedef struct {
    gfx_image_header_t header;   /**< A header describing the basics of the image */
    uint32_t data_size;         /**< Size of the image in bytes */
    const uint8_t *data;        /**< Pointer to the data of the image */
    const void *reserved;       /**< Reserved field for future use */
    const void *reserved_2;     /**< Reserved field for future use */
} gfx_image_dsc_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Image object creation
 *====================*/

/**
 * @brief Create an image object
 * @param handle Animation player handle
 * @return Pointer to the created image object
 */
gfx_obj_t *gfx_img_create(gfx_handle_t handle);

/*=====================
 * Image setter functions
 *====================*/

/**
 * @brief Set the source data for an image object
 * @param obj Pointer to the image object
 * @param src Pointer to the image source data
 * @return Pointer to the object
 */
gfx_obj_t *gfx_img_set_src(gfx_obj_t *obj, void *src);

#ifdef __cplusplus
}
#endif
