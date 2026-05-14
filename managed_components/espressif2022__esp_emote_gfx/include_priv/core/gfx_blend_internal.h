/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "core/gfx_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/
gfx_color_t gfx_blend_color_mix(gfx_color_t c1, gfx_color_t c2, uint8_t mix);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Software blending functions
 *====================*/

/**
 * @brief Draw a blended color onto a destination buffer
 * @param dest_buf Pointer to the destination buffer where the color will be drawn
 * @param dest_stride Stride (width) of the destination buffer
 * @param color The color to draw in gfx_color_t type
 * @param opa The opacity of the color to draw (0-255)
 * @param mask Pointer to the mask buffer, if any
 * @param clip_area Pointer to the clipping area, which limits the area to draw
 * @param mask_stride Stride (width) of the mask buffer
 */
void gfx_sw_blend_draw(gfx_color_t *dest_buf, gfx_coord_t dest_stride, gfx_color_t color, gfx_opa_t opa,
                       const gfx_opa_t *mask, gfx_area_t *clip_area, gfx_coord_t mask_stride, bool swap);

/**
 * @brief Draw a blended image onto a destination buffer
 * @param dest_buf Pointer to the destination buffer where the image will be drawn
 * @param dest_stride Stride (width) of the destination buffer
 * @param src_buf Pointer to the source image buffer
 * @param src_stride Stride (width) of the source image buffer
 * @param mask Pointer to the mask buffer, if any
 * @param mask_stride Stride (width) of the mask buffer
 * @param clip_area Pointer to the clipping area, which limits the area to draw
 * @param opa The opacity of the image to draw (0-255)
 * @param swap Whether to swap the color format
 */
void gfx_sw_blend_img_draw(gfx_color_t *dest_buf, gfx_coord_t dest_stride,
                           const gfx_color_t *src_buf, gfx_coord_t src_stride,
                           const gfx_opa_t *mask, gfx_coord_t mask_stride,
                           gfx_area_t *clip_area, gfx_opa_t opa, bool swap);

#ifdef __cplusplus
}
#endif
