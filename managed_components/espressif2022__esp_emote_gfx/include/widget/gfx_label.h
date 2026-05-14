/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "sdkconfig.h"
#include "core/gfx_types.h"
#include "core/gfx_core.h"
#include "core/gfx_obj.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/* Font handle type - hides internal FreeType implementation */
typedef void *gfx_font_t;

/* Label configuration structure */
typedef struct {
    const char *name;       /**< The name of the font file */
    const void *mem;        /**< The pointer to the font file */
    size_t mem_size;        /**< The size of the memory */
    uint16_t font_size;     /**< The size of the font */
} gfx_label_cfg_t;

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Text alignment enumeration (similar to LVGL)
 */
typedef enum {
    GFX_TEXT_ALIGN_AUTO,    /**< Align text auto */
    GFX_TEXT_ALIGN_LEFT,    /**< Align text to left */
    GFX_TEXT_ALIGN_CENTER,  /**< Align text to center */
    GFX_TEXT_ALIGN_RIGHT,   /**< Align text to right */
} gfx_text_align_t;

/**
 * Long text mode enumeration (similar to LVGL)
 */
typedef enum {
    GFX_LABEL_LONG_WRAP,    /**< Break the long lines (word wrap) */
    GFX_LABEL_LONG_SCROLL,  /**< Make the text scrolling horizontally */
    GFX_LABEL_LONG_CLIP,    /**< Simply clip the parts which don't fit */
} gfx_label_long_mode_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Label object creation
 *====================*/

/**
 * @brief Create a label object
 * @param handle Animation player handle
 * @param cfg Font configuration
 * @return Pointer to the created label object
 */
gfx_obj_t *gfx_label_create(gfx_handle_t handle);

#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
/**
 * @brief Create a new font
 * @param cfg Font configuration
 * @param ret_font Pointer to store the font handle
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_new_font(const gfx_label_cfg_t *cfg, gfx_font_t *ret_font);

/**
 * @brief Delete a font and free its resources
 * @param font Font handle to delete
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_delete_font(gfx_font_t font);
#endif

/*=====================
 * Label setter functions
 *====================*/

/**
 * @brief Set the text for a label object
 * @param obj Pointer to the label object
 * @param text Text string to display
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_text(gfx_obj_t *obj, const char *text);

/**
 * @brief Set the text for a label object with format
 * @param obj Pointer to the label object
 * @param fmt Format string
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_text_fmt(gfx_obj_t *obj, const char *fmt, ...);

/**
 * @brief Set the color for a label object
 * @param obj Pointer to the label object
 * @param color Color value
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_color(gfx_obj_t *obj, gfx_color_t color);

/**
 * @brief Set the background color for a label object
 * @param obj Pointer to the label object
 * @param bg_color Background color value
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_bg_color(gfx_obj_t *obj, gfx_color_t bg_color);

/**
 * @brief Enable or disable background for a label object
 * @param obj Pointer to the label object
 * @param enable True to enable background, false to disable
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_bg_enable(gfx_obj_t *obj, bool enable);

/**
 * @brief Set the opacity for a label object
 * @param obj Pointer to the label object
 * @param opa Opacity value (0-255)
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_opa(gfx_obj_t *obj, gfx_opa_t opa);

/**
 * @brief Set the font for a label object
 * @param obj Pointer to the label object
 * @param font Font handle
 */
esp_err_t gfx_label_set_font(gfx_obj_t *obj, gfx_font_t font);

/**
 * @brief Set the text alignment for a label object
 * @param obj Pointer to the label object
 * @param align Text alignment value
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_text_align(gfx_obj_t *obj, gfx_text_align_t align);

/**
 * @brief Set the long text mode for a label object
 * @param obj Pointer to the label object
 * @param long_mode Long text handling mode (wrap, scroll, or clip)
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_long_mode(gfx_obj_t *obj, gfx_label_long_mode_t long_mode);

/**
 * @brief Set the line spacing for a label object
 * @param obj Pointer to the label object
 * @param spacing Line spacing in pixels
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_line_spacing(gfx_obj_t *obj, uint16_t spacing);

/**
 * @brief Set the horizontal scrolling speed for a label object
 * @param obj Pointer to the label object
 * @param speed_ms Scrolling speed in milliseconds per pixel
 * @note Only effective when long_mode is GFX_LABEL_LONG_SCROLL
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_scroll_speed(gfx_obj_t *obj, uint32_t speed_ms);

/**
 * @brief Set whether scrolling should loop continuously
 * @param obj Pointer to the label object
 * @param loop True to enable continuous looping, false for one-time scroll
 * @note Only effective when long_mode is GFX_LABEL_LONG_SCROLL
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_label_set_scroll_loop(gfx_obj_t *obj, bool loop);

#ifdef __cplusplus
}
#endif
