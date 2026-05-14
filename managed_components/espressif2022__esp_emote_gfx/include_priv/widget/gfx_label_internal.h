/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "core/gfx_types.h"
#include "core/gfx_obj.h"
#include "core/gfx_timer.h"
#include "widget/gfx_label.h"
#include "widget/gfx_font_lvgl.h"
#include "widget/gfx_font_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Label context structure */
typedef struct {
    void *font_ctx;         /**< Font context interface */
    char *text;             /**< Text string */
    gfx_color_t color;      /**< Text color */
    gfx_opa_t opa;          /**< Text opacity */
    gfx_color_t bg_color;   /**< Background color */
    bool bg_enable;         /**< Enable background */
    gfx_opa_t *mask;        /**< Text mask buffer */
    gfx_text_align_t text_align;  /**< Text alignment */
    gfx_label_long_mode_t long_mode; /**< Long text handling mode */
    uint16_t line_spacing;  /**< Spacing between lines */

    /* Cached line data for scroll optimization */
    char **lines;           /**< Cached parsed lines */
    int line_count;         /**< Number of cached lines */
    int *line_widths;       /**< Cached line widths for alignment */

    /* Scroll properties */
    int32_t scroll_offset;  /**< Current scroll offset */
    uint32_t scroll_speed;  /**< Scroll speed in ms per pixel */
    bool scroll_loop;       /**< Enable continuous looping */
    bool scrolling;         /**< Is currently scrolling */
    bool scroll_changed;    /**< Scroll position changed */
    void *scroll_timer;     /**< Timer handle for scroll animation */
    int32_t text_width;     /**< Total text width */
} gfx_label_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Internal drawing functions
 *====================*/

/**
 * @brief Draw a label object
 * @param obj Label object
 * @param x1 Left coordinate
 * @param y1 Top coordinate
 * @param x2 Right coordinate
 * @param y2 Bottom coordinate
 * @param dest_buf Destination buffer
 * @param swap Whether to swap the color format
 */
esp_err_t gfx_draw_label(gfx_obj_t *obj, int x1, int y1, int x2, int y2, const void *dest_buf, bool swap);

/**
 * @brief Get glyph descriptor for label rendering
 * @param obj Label object
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_get_glphy_dsc(gfx_obj_t *obj);

/**
 * @brief Clear cached line data
 * @param label Label context
 */
void gfx_label_clear_cached_lines(gfx_label_t *label);

#ifdef __cplusplus
}
#endif
