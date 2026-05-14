/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * NOTE: This file contains code derived from LVGL v8.4
 * Copyright (c) 2024 LVGL LLC
 * Used for Unicode glyph index search and font format decoding
 */

#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_check.h"
#include "widget/gfx_font_lvgl.h"
#include "widget/gfx_font_internal.h"

static const char *TAG = "gfx_lv";

/**********************
 *   STATIC PROTOTYPES
 **********************/

// Utility functions
static int unicode_list_compare(const void *ref, const void *element);
static void *_lv_utils_bsearch(const void *key, const void *base, uint32_t n, uint32_t size,
                               int (*cmp)(const void *pRef, const void *pElement));

// Internal LVGL font interface functions
static uint32_t gfx_font_lv_get_glyph_index(const lv_font_t *font, uint32_t unicode);
static bool gfx_font_lv_get_glyph_dsc(gfx_font_ctx_t *font, void *glyph_dsc, uint32_t unicode, uint32_t unicode_next);
static const uint8_t *gfx_font_lv_get_glyph_bitmap(gfx_font_ctx_t *font, uint32_t unicode, void *glyph_dsc);
static int gfx_font_lv_get_glyph_width(gfx_font_ctx_t *font, uint32_t unicode);
static int gfx_font_lv_get_line_height(gfx_font_ctx_t *font);
static int gfx_font_lv_get_base_line(gfx_font_ctx_t *font);
static uint8_t gfx_font_lv_get_pixel_value(gfx_font_ctx_t *font, const uint8_t *bitmap, int32_t x, int32_t y, int32_t box_w);
static int gfx_font_lv_adjust_baseline_offset(gfx_font_ctx_t *font, void *glyph_dsc);
static int gfx_font_lv_get_advance_width(gfx_font_ctx_t *font, void *glyph_dsc);

/**********************
 *   UTILITY FUNCTIONS
 **********************/

static int unicode_list_compare(const void *ref, const void *element)
{
    uint16_t ref_val = *(const uint16_t *)ref;
    uint16_t element_val = *(const uint16_t *)element;

    if (ref_val < element_val) {
        return -1;
    }
    if (ref_val > element_val) {
        return 1;
    }
    return 0;
}

static void *_lv_utils_bsearch(const void *key, const void *base, uint32_t n, uint32_t size,
                               int (*cmp)(const void *pRef, const void *pElement))
{
    const char *middle;
    int32_t c;

    for (middle = base; n != 0;) {
        middle += (n / 2) * size;
        if ((c = (*cmp)(key, middle)) > 0) {
            n    = (n / 2) - ((n & 1) == 0);
            base = (middle += size);
        } else if (c < 0) {
            n /= 2;
            middle = base;
        } else {
            return (char *)middle;
        }
    }
    return NULL;
}

/**********************
 *   INTERNAL FONT INTERFACE FUNCTIONS
 **********************/

static uint32_t gfx_font_lv_get_glyph_index(const lv_font_t *font, uint32_t unicode)
{
    if (!font) {
        return 0;
    }

    const lv_font_fmt_txt_dsc_t *dsc = font->dsc;

    for (uint16_t i = 0; i < dsc->cmap_num; i++) {
        const lv_font_fmt_txt_cmap_t *cmap = &dsc->cmaps[i];

        uint32_t rcp = unicode - cmap->range_start;
        if (rcp > cmap->range_length) {
            continue;
        }

        if (cmap->type == LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY) {
            if (unicode >= cmap->range_start &&
                    unicode < cmap->range_start + cmap->range_length) {
                return cmap->glyph_id_start + (unicode - cmap->range_start);
            }
        } else if (cmap->type == LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL) {
            const uint8_t *gid_ofs_8 = cmap->glyph_id_ofs_list;
            return cmap->glyph_id_start + gid_ofs_8[rcp];
        } else if (cmap->type == LV_FONT_FMT_TXT_CMAP_SPARSE_TINY) {
            if (cmap->unicode_list && cmap->list_length > 0) {
                uint16_t key = (uint16_t)rcp;
                uint16_t *found = (uint16_t *)_lv_utils_bsearch(&key, cmap->unicode_list, cmap->list_length,
                                  sizeof(cmap->unicode_list[0]), unicode_list_compare);
                if (found) {
                    uintptr_t offset = found - cmap->unicode_list;
                    return cmap->glyph_id_start + offset;
                }
            }
        } else if (dsc->cmaps[i].type == LV_FONT_FMT_TXT_CMAP_SPARSE_FULL) {
            uint16_t key = rcp;
            uint16_t *p = _lv_utils_bsearch(&key, dsc->cmaps[i].unicode_list, dsc->cmaps[i].list_length,
                                            sizeof(dsc->cmaps[i].unicode_list[0]), unicode_list_compare);

            if (p) {
                uintptr_t ofs = p - dsc->cmaps[i].unicode_list;
                const uint16_t *gid_ofs_16 = dsc->cmaps[i].glyph_id_ofs_list;
                return dsc->cmaps[i].glyph_id_start + gid_ofs_16[ofs];
            }
        }
    }

    return 0;
}

static bool gfx_font_lv_get_glyph_dsc(gfx_font_ctx_t *font, void *glyph_dsc, uint32_t unicode, uint32_t unicode_next)
{
    if (!font || !glyph_dsc) {
        return false;
    }

    const lv_font_t *lvgl_font = (const lv_font_t *)font->font;
    if (!lvgl_font || !lvgl_font->dsc) {
        return false;
    }

    uint32_t glyph_index = gfx_font_lv_get_glyph_index(lvgl_font, unicode);
    if (glyph_index == 0) {
        return false;
    }

    const lv_font_fmt_txt_dsc_t *dsc = lvgl_font->dsc;
    if (glyph_index >= 65536 || !dsc->glyph_dsc) {
        return false;
    }

    const lv_font_fmt_txt_glyph_dsc_t *src_glyph = &dsc->glyph_dsc[glyph_index];

    gfx_glyph_dsc_t *out_glyph = (gfx_glyph_dsc_t *)glyph_dsc;
    out_glyph->bitmap_index = src_glyph->bitmap_index;
    out_glyph->adv_w = src_glyph->adv_w;
    out_glyph->box_w = src_glyph->box_w;
    out_glyph->box_h = src_glyph->box_h;
    out_glyph->ofs_x = src_glyph->ofs_x;
    out_glyph->ofs_y = src_glyph->ofs_y;

    return true;
}

static const uint8_t *gfx_font_lv_get_glyph_bitmap(gfx_font_ctx_t *font, uint32_t unicode, void *glyph_dsc)
{
    if (!font || !font->font) {
        return NULL;
    }

    lv_font_t *lvgl_font = (lv_font_t *)font->font;
    gfx_glyph_dsc_t *glyph = (gfx_glyph_dsc_t *)glyph_dsc;

    lv_font_fmt_txt_dsc_t *dsc = (lv_font_fmt_txt_dsc_t *)lvgl_font->dsc;
    if (!dsc || !dsc->glyph_bitmap) {
        return NULL;
    }

    return &dsc->glyph_bitmap[glyph->bitmap_index];
}

static int gfx_font_lv_get_glyph_width(gfx_font_ctx_t *font, uint32_t unicode)
{
    if (!font || !font->font) {
        return -1;
    }

    gfx_glyph_dsc_t glyph_dsc;

    if (!gfx_font_lv_get_glyph_dsc(font, &glyph_dsc, unicode, 0)) {
        return -1;
    }

    int advance_pixels = (glyph_dsc.adv_w >> 8);
    int actual_width = glyph_dsc.box_w + glyph_dsc.ofs_x;
    return (advance_pixels > actual_width) ? advance_pixels : actual_width;
}

static int gfx_font_lv_get_line_height(gfx_font_ctx_t *font)
{
    const lv_font_t *lvgl_font = (const lv_font_t *)font->font;
    return lvgl_font->line_height;
}

static int gfx_font_lv_get_base_line(gfx_font_ctx_t *font)
{
    const lv_font_t *lvgl_font = (const lv_font_t *)font->font;
    return lvgl_font->base_line;
}

static uint8_t gfx_font_lv_get_pixel_value(gfx_font_ctx_t *font, const uint8_t *bitmap, int32_t x, int32_t y, int32_t box_w)
{
    const lv_font_t *lvgl_font = (const lv_font_t *)font->font;
    if (!bitmap || x < 0 || y < 0 || x >= box_w) {
        return 0;
    }

    uint8_t bpp = 1;
    if (lvgl_font && lvgl_font->dsc) {
        const lv_font_fmt_txt_dsc_t *dsc = (const lv_font_fmt_txt_dsc_t *)lvgl_font->dsc;
        bpp = dsc->bpp;
    }

    uint8_t pixel_value = 0;

    if (bpp == 1) {
        uint32_t bit_index = y * box_w + x;
        uint32_t byte_index = bit_index / 8;
        uint8_t bit_pos = bit_index % 8;
        pixel_value = (bitmap[byte_index] >> (7 - bit_pos)) & 0x01;
        pixel_value = pixel_value ? 255 : 0;
    } else if (bpp == 2) {
        uint32_t bit_index = (y * box_w + x) * 2;
        uint32_t byte_index = bit_index / 8;
        uint8_t bit_pos = bit_index % 8;
        pixel_value = (bitmap[byte_index] >> (6 - bit_pos)) & 0x03;
        pixel_value = pixel_value * 85;
    } else if (bpp == 4) {
        uint32_t bit_index = (y * box_w + x) * 4;
        uint32_t byte_index = bit_index / 8;
        uint8_t bit_pos = bit_index % 8;
        if (bit_pos == 0) {
            pixel_value = (bitmap[byte_index] >> 4) & 0x0F;
        } else {
            pixel_value = bitmap[byte_index] & 0x0F;
        }
        pixel_value = pixel_value * 17;
    } else if (bpp == 8) {
        pixel_value = bitmap[y * box_w + x];
    }

    return pixel_value;
}

static int gfx_font_lv_adjust_baseline_offset(gfx_font_ctx_t *font, void *glyph_dsc)
{
    const lv_font_t *lvgl_font = (const lv_font_t *)font->font;
    if (!lvgl_font) {
        ESP_LOGE(TAG, "lvgl_font is NULL");
        return 0;
    }

    gfx_glyph_dsc_t *dsc = (gfx_glyph_dsc_t *)glyph_dsc;

    int line_height = gfx_font_lv_get_line_height(font);
    int base_line = gfx_font_lv_get_base_line(font);
    int adjusted_ofs_y = line_height - base_line - dsc->box_h - dsc->ofs_y;

    return adjusted_ofs_y;
}

static int gfx_font_lv_get_advance_width(gfx_font_ctx_t *font, void *glyph_dsc)
{
    if (!font || !glyph_dsc) {
        return 0;
    }

    gfx_glyph_dsc_t *dsc = (gfx_glyph_dsc_t *)glyph_dsc;
    int advance_pixels = (dsc->adv_w >> 8);
    int actual_width = dsc->box_w + dsc->ofs_x;
    return (advance_pixels > actual_width) ? advance_pixels : actual_width;
}

/**********************
 *   PUBLIC INTERFACE FUNCTIONS
 **********************/

bool gfx_is_lvgl_font(const void *font)
{
    if (!font) {
        return false;
    }

    const lv_font_t *lvgl_font = (const lv_font_t *)font;

    if (lvgl_font->line_height > 0 && lvgl_font->line_height < 1000 &&
            lvgl_font->base_line >= 0 && lvgl_font->base_line <= lvgl_font->line_height &&
            lvgl_font->dsc != NULL) {

        const lv_font_fmt_txt_dsc_t *dsc = (const lv_font_fmt_txt_dsc_t *)lvgl_font->dsc;
        if (dsc->glyph_bitmap != NULL && dsc->glyph_dsc != NULL &&
                dsc->cmaps != NULL && dsc->cmap_num > 0 && dsc->cmap_num < 100) {
            return true;
        }
    }

    return false;
}

void gfx_font_lv_init_context(gfx_font_ctx_t *font_ctx, const void *font)
{
    font_ctx->font = (void *)font;
    font_ctx->get_glyph_dsc = gfx_font_lv_get_glyph_dsc;
    font_ctx->get_glyph_bitmap = gfx_font_lv_get_glyph_bitmap;
    font_ctx->get_glyph_width = gfx_font_lv_get_glyph_width;
    font_ctx->get_line_height = gfx_font_lv_get_line_height;
    font_ctx->get_base_line = gfx_font_lv_get_base_line;
    font_ctx->get_pixel_value = gfx_font_lv_get_pixel_value;
    font_ctx->adjust_baseline_offset = gfx_font_lv_adjust_baseline_offset;
    font_ctx->get_advance_width = gfx_font_lv_get_advance_width;
}
