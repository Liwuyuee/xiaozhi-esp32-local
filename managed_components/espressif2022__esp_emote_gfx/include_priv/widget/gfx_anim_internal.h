/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "core/gfx_types.h"
#include "core/gfx_obj.h"
#include "core/gfx_timer.h"
#include "widget/gfx_anim.h"
#include "gfx_eaf_dec.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Frame processing information structure */
typedef struct {
    /*!< Pre-parsed header information to avoid repeated parsing */
    eaf_header_t header;           /*!< Pre-parsed header for current frame */

    /*!< Pre-fetched frame data to avoid repeated fetching */
    const void *frame_data;          /*!< Pre-fetched frame data for current frame */
    size_t frame_size;               /*!< Size of pre-fetched frame data */

    /*!< Pre-allocated parsing resources to avoid repeated allocation */
    uint32_t *block_offsets;         /*!< Pre-allocated block offsets array */
    uint8_t *pixel_buffer;           /*!< Pre-allocated pixel decode buffer */
    uint32_t *color_palette;         /*!< Pre-allocated color palette cache */

    /*!< Decoding state tracking */
    int last_block;                  /*!< Last decoded block index to avoid repeated decoding */
} gfx_anim_frame_info_t;

typedef enum {
    GFX_MIRROR_DISABLED = 0,     /*!< Mirror disabled */
    GFX_MIRROR_MANUAL = 1,       /*!< Manual mirror with fixed offset */
    GFX_MIRROR_AUTO = 2          /*!< Auto mirror with calculated offset */
} gfx_mirror_mode_t;

typedef struct {
    uint32_t start_frame;            /*!< Start frame index */
    uint32_t end_frame;              /*!< End frame index */
    uint32_t current_frame;          /*!< Current frame index */
    uint32_t fps;                    /*!< Frames per second */
    bool is_playing;                 /*!< Whether animation is currently playing */
    bool repeat;                     /*!< Whether animation should repeat */
    gfx_timer_handle_t timer;        /*!< Timer handle for frame updates */

    /*!< Frame processing information */
    eaf_format_handle_t file_desc;      /*!< Animation file descriptor */
    gfx_anim_frame_info_t frame;     /*!< Frame processing info */

    /*!< Widget-specific display properties */
    gfx_mirror_mode_t mirror_mode;   /*!< Mirror mode */
    int16_t mirror_offset;          /*!< Mirror buffer offset for positioning */
} gfx_anim_property_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Internal drawing functions
 *====================*/

/**
 * @brief Free frame processing information and allocated resources
 * @param frame Frame processing information structure
 */
void gfx_anim_free_frame_info(gfx_anim_frame_info_t *frame);

/**
 * @brief Preprocess animation frame data and allocate parsing resources
 * @param anim Animation property structure
 * @return true if preprocessing was successful, false otherwise
 */
esp_err_t gfx_anim_preprocess_frame(gfx_anim_property_t *anim);

/**
 * @brief Draw an animation object
 * @param obj Animation object
 * @param x1 Left coordinate
 * @param y1 Top coordinate
 * @param x2 Right coordinate
 * @param y2 Bottom coordinate
 * @param dest_buf Destination buffer
 * @param swap_color Whether to swap color format
 */
esp_err_t gfx_draw_animation(gfx_obj_t *obj, int x1, int y1, int x2, int y2, const void *dest_buf, bool swap_color);

#ifdef __cplusplus
}
#endif
