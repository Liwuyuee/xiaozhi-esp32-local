/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "core/gfx_types.h"
#include "core/gfx_core.h"
#include "core/gfx_obj.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Animation object creation
 *====================*/

/**
 * @brief Create an animation object
 * @param handle Animation player handle
 * @return Pointer to the created animation object
 */
gfx_obj_t *gfx_anim_create(gfx_handle_t handle);

/*=====================
 * Animation setter functions
 *====================*/

/**
 * @brief Set the source data for an animation object
 * @param obj Pointer to the animation object
 * @param src_data Source data
 * @param src_len Source data length
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_anim_set_src(gfx_obj_t *obj, const void *src_data, size_t src_len);

/**
 * @brief Set the segment for an animation object
 * @param obj Pointer to the animation object
 * @param start Start frame index
 * @param end End frame index
 * @param fps Frames per second
 * @param repeat Whether to repeat the animation
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_anim_set_segment(gfx_obj_t *obj, uint32_t start, uint32_t end, uint32_t fps, bool repeat);

/**
 * @brief Start the animation
 * @param obj Pointer to the animation object
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_anim_start(gfx_obj_t *obj);

/**
 * @brief Stop the animation
 * @param obj Pointer to the animation object
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_anim_stop(gfx_obj_t *obj);

/**
 * @brief Set mirror display for an animation object
 * @param obj Pointer to the animation object
 * @param enabled Whether to enable mirror display
 * @param offset Mirror offset in pixels
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t gfx_anim_set_mirror(gfx_obj_t *obj, bool enabled, int16_t offset);

/**
 * @brief Set auto mirror alignment for animation object
 *
 * @param obj Animation object
 * @param enabled Whether to enable auto mirror alignment
 * @return ESP_OK on success, ESP_ERR_* otherwise
 */
esp_err_t gfx_anim_set_auto_mirror(gfx_obj_t *obj, bool enabled);

#ifdef __cplusplus
}
#endif
