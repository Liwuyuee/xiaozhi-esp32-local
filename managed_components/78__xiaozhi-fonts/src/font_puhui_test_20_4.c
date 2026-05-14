/*******************************************************************************
 * Size: 20 px
 * Bpp: 4
 * Opts: --force-fast-kern-format --no-compress --no-prefilter --font build/puhui-basic.ttf --format lvgl --lv-include lvgl.h --bpp 4 -o src/font_puhui_test_20_4.c --size 20 --symbols 我
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_PUHUI_TEST_20_4
#define FONT_PUHUI_TEST_20_4 1
#endif

#if FONT_PUHUI_TEST_20_4

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+6211 "我" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0x8, 0xe0, 0x20,
    0x0, 0x0, 0x1, 0x35, 0x8b, 0xef, 0x27, 0xf0,
    0xcd, 0x10, 0x0, 0x3f, 0xff, 0xfd, 0x73, 0x7,
    0xf0, 0x1d, 0xd1, 0x0, 0x3, 0x10, 0xe9, 0x0,
    0x6, 0xf0, 0x2, 0xec, 0x0, 0x0, 0x0, 0xe9,
    0x0, 0x5, 0xf1, 0x0, 0x36, 0x0, 0x56, 0x66,
    0xfb, 0x66, 0x69, 0xf7, 0x66, 0x66, 0x62, 0xef,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5,
    0x0, 0x0, 0xe9, 0x0, 0x2, 0xf5, 0x0, 0x1,
    0x0, 0x0, 0x0, 0xe9, 0x0, 0x0, 0xf6, 0x0,
    0x4f, 0x30, 0x0, 0x0, 0xe9, 0x15, 0x50, 0xe8,
    0x1, 0xea, 0x0, 0x1, 0x47, 0xff, 0xff, 0xb0,
    0xca, 0x1d, 0xd0, 0x0, 0xbf, 0xff, 0xfc, 0x51,
    0x0, 0x9d, 0xce, 0x20, 0x0, 0x56, 0x30, 0xe9,
    0x0, 0x0, 0x7f, 0xe2, 0x0, 0x0, 0x0, 0x0,
    0xe9, 0x0, 0x8, 0xff, 0x60, 0x0, 0x70, 0x0,
    0x0, 0xe9, 0x5, 0xdf, 0xad, 0xc0, 0x3, 0xf4,
    0x0, 0x0, 0xf9, 0xbf, 0xe5, 0x5, 0xf5, 0x8,
    0xe0, 0x4, 0xad, 0xf6, 0x47, 0x0, 0x0, 0xcf,
    0xbf, 0x90, 0x4, 0xdb, 0x70, 0x0, 0x0, 0x0,
    0x1b, 0xfb, 0x10
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 315, .box_w = 18, .box_h = 19, .ofs_x = 1, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 25105, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_puhui_test_20_4 = {
#else
lv_font_t font_puhui_test_20_4 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if FONT_PUHUI_TEST_20_4*/

