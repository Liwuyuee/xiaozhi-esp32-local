/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "widget/gfx_font_lvgl.h"
#include "core/gfx_types.h"

#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SIZES_H
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**********************
 *      TYPEDEFS
 **********************/

/* Forward declaration */
typedef struct _gfx_font_ctx_t gfx_font_ctx_t;

/**
 * Universal glyph descriptor structure
 */
typedef struct {
    uint32_t bitmap_index;      /**< Start index of the bitmap */
    uint32_t adv_w;             /**< Advance width in 1/256 pixels */
    uint16_t box_w;             /**< Width of the glyph's bounding box */
    uint16_t box_h;             /**< Height of the glyph's bounding box */
    int16_t ofs_x;              /**< X offset of the bounding box */
    int16_t ofs_y;              /**< Y offset of the bounding box */
} gfx_glyph_dsc_t;

/**
 * Font context structure with function pointers
 */
typedef struct _gfx_font_ctx_t {
    void *font;

    bool (*get_glyph_dsc)(struct _gfx_font_ctx_t *font, void *glyph_dsc, uint32_t unicode, uint32_t unicode_next);
    const uint8_t *(*get_glyph_bitmap)(struct _gfx_font_ctx_t *font, uint32_t unicode, void *glyph_dsc);
    int (*get_glyph_width)(struct _gfx_font_ctx_t *font, uint32_t unicode);
    int (*get_line_height)(struct _gfx_font_ctx_t *font);
    int (*get_base_line)(struct _gfx_font_ctx_t *font);
    uint8_t (*get_pixel_value)(struct _gfx_font_ctx_t *font, const uint8_t *bitmap, int32_t x, int32_t y, int32_t box_w);
    int (*adjust_baseline_offset)(struct _gfx_font_ctx_t *font, void *glyph_dsc);
    int (*get_advance_width)(struct _gfx_font_ctx_t *font, void *glyph_dsc);
} gfx_font_ctx_t;

typedef gfx_font_ctx_t *gfx_font_handle_t;

#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
typedef void *gfx_ft_handle_t;
typedef void *gfx_ft_lib_handle_t;

typedef struct face_entry {
    void *face;
    const void *mem;
    struct face_entry *next;
} gfx_ft_face_entry_t;

typedef struct {
    gfx_ft_face_entry_t *ft_face_head;
    void *ft_library;
} gfx_ft_lib_t;

typedef struct {
    FT_Face face;
    int size;
    int line_height;
    int base_line;
    int underline_position;
    int underline_thickness;
} gfx_font_ft_t;
#endif

/**********************
 * GLOBAL PROTOTYPES
 **********************/

// Font type detection
bool gfx_is_lvgl_font(const void *font);

// LVGL font interface
void gfx_font_lv_init_context(gfx_font_ctx_t *font_ctx, const void *font);

#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
// FreeType library management
esp_err_t gfx_ft_lib_create(void);
esp_err_t gfx_ft_lib_cleanup(void);

// FreeType font interface
void gfx_font_ft_init_context(gfx_font_ctx_t *font_ctx, const void *font);
#endif

#ifdef __cplusplus
}
#endif
