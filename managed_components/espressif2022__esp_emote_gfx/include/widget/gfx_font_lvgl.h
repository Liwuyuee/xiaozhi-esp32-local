/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 * @file gfx_font_lvgl.h
 * @brief LVGL Font Compatibility Layer
 *
 * This header provides LVGL font structure definitions and compatibility
 * functions for the ESP Graphics Framework.
 */

#ifndef GFX_FONT_LV_PARSER_H
#define GFX_FONT_LV_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*********************
 *   LVGL COMPATIBILITY DEFINES
 *********************/

/* Helper macro for converting numbers to strings */
#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

/* Debug: Check if LVGL_VERSION_MAJOR is already defined */
#ifdef LVGL_VERSION_MAJOR
// #pragma message "Detect LVGL version: " STRINGIFY(LVGL_VERSION_MAJOR) "." STRINGIFY(LVGL_VERSION_MINOR) "." STRINGIFY(LVGL_VERSION_PATCH)

#ifndef LV_FONT_FMT_TXT_LARGE
#define LV_FONT_FMT_TXT_LARGE 1
#endif

#else

/* LVGL Version Information - for compatibility checking */
#define LVGL_VERSION_MAJOR 8
#define LVGL_VERSION_MINOR 4
#define LVGL_VERSION_PATCH 0

#define LV_FONT_FMT_TXT_LARGE 1

/* LVGL Memory Attributes - for const data placement */
#define LV_ATTRIBUTE_LARGE_CONST const

/* LVGL Version Check Macro - for conditional compilation */
#define LV_VERSION_CHECK(x,y,z) (x == LVGL_VERSION_MAJOR && (y < LVGL_VERSION_MINOR || (y == LVGL_VERSION_MINOR && z <= LVGL_VERSION_PATCH)))

/**********************
 *   LVGL COMPATIBILITY TYPEDEFS
 **********************/

/*------------------
 * LVGL Font Cache Structure - for glyph caching compatibility
 *-----------------*/
typedef struct {
    /* Empty structure for LVGL font cache compatibility */
} lv_font_fmt_txt_glyph_cache_t;

/*------------------
 * LVGL Glyph Descriptor - minimal structure for compatibility
 *-----------------*/
/** Describes the properties of a glyph (LVGL compatible) */
typedef struct {
    /* Empty structure for LVGL glyph descriptor compatibility */
} lv_font_glyph_dsc_t;


typedef struct {
    /* Empty structure for LVGL image descriptor compatibility */
} lv_image_dsc_t;

/*------------------
 * LVGL Subpixel Rendering Enums
 *-----------------*/
/** LVGL subpixel rendering types - bitmaps might be upscaled for subpixel rendering */
enum {
    LV_FONT_SUBPX_NONE,     /**< No subpixel rendering */
    LV_FONT_SUBPX_HOR,      /**< Horizontal subpixel rendering */
    LV_FONT_SUBPX_VER,      /**< Vertical subpixel rendering */
    LV_FONT_SUBPX_BOTH,     /**< Both horizontal and vertical subpixel rendering */
};

/** LVGL character map format types */
typedef enum {
    LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL,  /**< Full format 0 character map */
    LV_FONT_FMT_TXT_CMAP_SPARSE_FULL,   /**< Sparse full character map */
    LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY,  /**< Tiny format 0 character map */
    LV_FONT_FMT_TXT_CMAP_SPARSE_TINY,   /**< Sparse tiny character map */
} lv_font_fmt_txt_cmap_type_t;

/** This describes a glyph.*/
typedef struct {
    /* Large format (up to 4GB font size) - for very large fonts */
    uint32_t bitmap_index;          /**< Start index of the bitmap. A font can be max 4 GB.*/
    uint32_t adv_w;                 /**< Draw the next glyph after this width. 28.4 format (real_value * 16 is stored).*/
    uint16_t box_w;                 /**< Width of the glyph's bounding box*/
    uint16_t box_h;                 /**< Height of the glyph's bounding box*/
    int16_t ofs_x;                  /**< x offset of the bounding box*/
    int16_t ofs_y;                  /**< y offset of the bounding box. Measured from the top of the line*/
} lv_font_fmt_txt_glyph_dsc_t;

/*------------------
 * LVGL Character Map Structure - maps Unicode codepoints to glyph descriptors
 *-----------------*/
/**
 * LVGL Character Map - maps codepoints to glyph descriptors
 * Several formats are supported to optimize memory usage
 * See https://github.com/lvgl/lv_font_conv/blob/master/doc/font_spec.md
 */
typedef struct {
    /** First Unicode character for this range */
    uint32_t range_start;

    /** Number of Unicode characters related to this range.
     * Last Unicode character = range_start + range_length - 1 */
    uint16_t range_length;

    /** First glyph ID (array index of `glyph_dsc`) for this range */
    uint16_t glyph_id_start;

    /*
     * LVGL Font Converter Format Specification:
     * According the specification there are 4 formats:
     *     https://github.com/lvgl/lv_font_conv/blob/master/doc/font_spec.md
     *
     * For simplicity introduce "relative code point":
     *     rcp = codepoint - range_start
     *
     * and a search function:
     *     search a "value" in an "array" and returns the index of "value".
     *
     * Format 0 tiny:
     *     unicode_list == NULL && glyph_id_ofs_list == NULL
     *     glyph_id = glyph_id_start + rcp
     *
     * Format 0 full:
     *     unicode_list == NULL && glyph_id_ofs_list != NULL
     *     glyph_id = glyph_id_start + glyph_id_ofs_list[rcp]
     *
     * Sparse tiny:
     *     unicode_list != NULL && glyph_id_ofs_list == NULL
     *     glyph_id = glyph_id_start + search(unicode_list, rcp)
     *
     * Sparse full:
     *     unicode_list != NULL && glyph_id_ofs_list != NULL
     *     glyph_id = glyph_id_start + glyph_id_ofs_list[search(unicode_list, rcp)]
     */

    /** Unicode character list for sparse formats */
    const uint16_t *unicode_list;

    /** Glyph ID offset list
     * if(type == LV_FONT_FMT_TXT_CMAP_FORMAT0_...) it's `uint8_t *`
     * if(type == LV_FONT_FMT_TXT_CMAP_SPARSE_...)  it's `uint16_t *`
     */
    const void *glyph_id_ofs_list;

    /** Length of `unicode_list` and/or `glyph_id_ofs_list` */
    uint16_t list_length;

    /** Type of this character map (see lv_font_fmt_txt_cmap_type_t) */
    lv_font_fmt_txt_cmap_type_t type;
} lv_font_fmt_txt_cmap_t;

/** A simple mapping of kern values from pairs*/
typedef struct {
    /*To get a kern value of two code points:
       1. Get the `glyph_id_left` and `glyph_id_right` from `lv_font_fmt_txt_cmap_t
       2. for(i = 0; i < pair_cnt * 2; i += 2)
             if(glyph_ids[i] == glyph_id_left &&
                glyph_ids[i+1] == glyph_id_right)
                 return values[i / 2];
     */
    const void *glyph_ids;
    const int8_t *values;
    uint32_t pair_cnt   : 30;
    uint32_t glyph_ids_size : 2;    /**< 0: `glyph_ids` is stored as `uint8_t`; 1: as `uint16_t` */
} lv_font_fmt_txt_kern_pair_t;

/** More complex but more optimal class based kern value storage*/
typedef struct {
    /*To get a kern value of two code points:
          1. Get the `glyph_id_left` and `glyph_id_right` from `lv_font_fmt_txt_cmap_t
          2. Get the class of the left and right glyphs as `left_class` and `right_class`
              left_class = left_class_mapping[glyph_id_left];
              right_class = right_class_mapping[glyph_id_right];
          3. value = class_pair_values[(left_class-1)*right_class_cnt + (right_class-1)]
        */

    const int8_t *class_pair_values;      /**< left_class_cnt * right_class_cnt value */
    const uint8_t *left_class_mapping;    /**< Map the glyph_ids to classes: index -> glyph_id -> class_id */
    const uint8_t *right_class_mapping;   /**< Map the glyph_ids to classes: index -> glyph_id -> class_id */
    uint8_t left_class_cnt;
    uint8_t right_class_cnt;
} lv_font_fmt_txt_kern_classes_t;

/*Describe store additional data for fonts*/
typedef struct {
    /*The bitmaps of all glyphs*/
    const uint8_t *glyph_bitmap;

    /*Describe the glyphs*/
    const lv_font_fmt_txt_glyph_dsc_t *glyph_dsc;

    /*Map the glyphs to Unicode characters.
     *Array of `lv_font_cmap_fmt_txt_t` variables*/
    const lv_font_fmt_txt_cmap_t *cmaps;

    /**
     * Store kerning values.
     * Can be `lv_font_fmt_txt_kern_pair_t *  or `lv_font_kern_classes_fmt_txt_t *`
     * depending on `kern_classes`
     */
    const void *kern_dsc;

    /*Scale kern values in 12.4 format*/
    uint16_t kern_scale;

    /*Number of cmap tables*/
    uint16_t cmap_num       : 9;

    /*Bit per pixel: 1, 2, 3, 4, 8*/
    uint16_t bpp            : 4;

    /*Type of `kern_dsc`*/
    uint16_t kern_classes   : 1;

    /*
     * storage format of the bitmap
     * from `lv_font_fmt_txt_bitmap_format_t`
     */
    uint16_t bitmap_format  : 2;

    /*Cache the last letter and is glyph id*/
    lv_font_fmt_txt_glyph_cache_t *cache;
} lv_font_fmt_txt_dsc_t;

/*------------------
 * LVGL Main Font Structure - core font interface
 *-----------------*/
/** Describe the properties of a font*/
typedef struct _lv_font_t {
    /** Get a glyph's descriptor from a font*/
    bool (*get_glyph_dsc)(const struct _lv_font_t *, lv_font_glyph_dsc_t *, uint32_t letter, uint32_t letter_next);

    /** Get a glyph's bitmap from a font*/
    const uint8_t *(*get_glyph_bitmap)(const struct _lv_font_t *, uint32_t);

    /** Release a glyph*/
    void (*release_glyph)(const struct _lv_font_t *, lv_font_glyph_dsc_t *); //v8 vs v9

    /*Pointer to the font in a font pack (must have the same line height)*/
    int32_t line_height;         /**< The real line height where any text fits*/
    int32_t base_line;           /**< Base line measured from the top of the line_height*/
    uint8_t subpx  : 2;             /**< An element of `lv_font_subpx_t`*/
    uint8_t static_bitmap : 1;      /**< The font will be used as static bitmap */

    int8_t underline_position;      /**< Distance between the top of the underline and base line (< 0 means below the base line)*/
    int8_t underline_thickness;     /**< Thickness of the underline*/

    const void *dsc;                /**< Store implementation specific or run_time data or caching here*/
    const struct _lv_font_t *fallback;    /**< Fallback font for missing glyph. Resolved recursively */
    void *user_data;                /**< Custom user data for font.*/
} lv_font_t;

/**********************
 *   LVGL COMPATIBILITY FUNCTIONS
 **********************/

/**
 * LVGL Compatibility Function: Get glyph bitmap
 * @note Empty implementation for LVGL compatibility - always returns NULL
 */
static inline const uint8_t *lv_font_get_bitmap_fmt_txt(const lv_font_t *font, uint32_t letter)
{
    (void)font;
    (void)letter;
    return NULL; // Empty function for LVGL compatibility
}

/**
 * LVGL Compatibility Function: Get glyph descriptor
 * @note Empty implementation for LVGL compatibility - always returns false
 */
static inline bool lv_font_get_glyph_dsc_fmt_txt(const lv_font_t *font, lv_font_glyph_dsc_t *dsc_out, uint32_t unicode_letter,
        uint32_t unicode_letter_next)
{
    (void)font;
    (void)dsc_out;
    (void)unicode_letter;
    (void)unicode_letter_next;
    return false; // Empty function for LVGL compatibility
}
#endif
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*GFX_FONT_LV_PARSER_H*/
