/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "gfx_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**
 * @brief LVGL port configuration structure
 */
#define GFX_EMOTE_INIT_CONFIG()                   \
    {                                              \
        .task_priority = 4,                        \
        .task_stack = 7168,                        \
        .task_affinity = -1,                       \
        .task_stack_caps = MALLOC_CAP_DEFAULT,     \
    }

typedef void *gfx_handle_t;

typedef enum {
    GFX_PLAYER_EVENT_IDLE = 0,
    GFX_PLAYER_EVENT_ONE_FRAME_DONE,
    GFX_PLAYER_EVENT_ALL_FRAME_DONE,
} gfx_player_event_t;

typedef void (*gfx_player_flush_cb_t)(gfx_handle_t handle, int x1, int y1, int x2, int y2, const void *data);

typedef void (*gfx_player_update_cb_t)(gfx_handle_t handle, gfx_player_event_t event, const void *obj);

typedef struct {
    gfx_player_flush_cb_t flush_cb;         ///< Callback function for flushing decoded data
    gfx_player_update_cb_t update_cb;       ///< Callback function for updating player
    void *user_data;             ///< User data
    struct {
        unsigned char swap: 1;
        unsigned char double_buffer: 1;
        unsigned char buff_dma: 1;
        unsigned char buff_spiram: 1;
    } flags;

    uint32_t h_res;        ///< Screen width in pixels
    uint32_t v_res;       ///< Screen height in pixels
    uint32_t fps;              ///< Target frame rate (frames per second)

    /* Buffer configuration */
    struct {
        void *buf1;                ///< Frame buffer 1 (NULL for internal allocation)
        void *buf2;                ///< Frame buffer 2 (NULL for internal allocation)
        size_t buf_pixels;         ///< Size of each buffer in pixels (0 for auto-calculation)
    } buffers;

    struct {
        int task_priority;      ///< Task priority (1-20)
        int task_stack;         ///< Task stack size in bytes
        int task_affinity;      ///< CPU core ID (-1: no affinity, 0: core 0, 1: core 1)
        unsigned task_stack_caps; /*!< LVGL task stack memory capabilities (see esp_heap_caps.h) */
    } task;
} gfx_core_config_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Core initialization
 *====================*/

/**
 * @brief Initialize graphics context
 *
 * @param cfg Graphics configuration (includes buffer configuration)
 * @return gfx_handle_t Graphics handle, NULL on error
 *
 * @note Buffer configuration:
 * - If cfg.buffers.buf1 and cfg.buffers.buf2 are NULL, internal buffers will be allocated
 * - If buffers are provided, external buffers will be used (user must manage memory)
 * - cfg.buffers.buf_pixels can be 0 for auto-calculation based on resolution
 *
 * @example Using internal buffers:
 * @code
 * gfx_core_config_t cfg = {
 *     .h_res = 320,
 *     .v_res = 240,
 *     .fps = 30,
 *     .buffers = {
 *         .buf1 = NULL,
 *         .buf2 = NULL,
 *         .buf_pixels = 0,  // Auto-calculate
 *     },
 *     .task = GFX_EMOTE_INIT_CONFIG(),
 * };
 * gfx_handle_t handle = gfx_emote_init(&cfg);
 * @endcode
 *
 * @example Using external buffers:
 * @code
 * uint16_t my_buf1[320 * 40]; // 320x40 pixels
 * uint16_t my_buf2[320 * 40];
 *
 * gfx_core_config_t cfg = {
 *     .h_res = 320,
 *     .v_res = 240,
 *     .fps = 30,
 *     .buffers = {
 *         .buf1 = my_buf1,
 *         .buf2 = my_buf2,
 *         .buf_pixels = 320 * 40,
 *     },
 *     .task = GFX_EMOTE_INIT_CONFIG(),
 * };
 * gfx_handle_t handle = gfx_emote_init(&cfg);
 * @endcode
 */
gfx_handle_t gfx_emote_init(const gfx_core_config_t *cfg);

/**
 * @brief Deinitialize graphics context
 *
 * @param handle Graphics handle
 */
void gfx_emote_deinit(gfx_handle_t handle);

/**
 * @brief Check if flush is ready
 *
 * @param handle Graphics handle
 * @param swap_act_buf Whether to swap the active buffer
 * @return bool True if the flush is ready, false otherwise
 */
bool gfx_emote_flush_ready(gfx_handle_t handle, bool swap_act_buf);

/**
 * @brief Get the user data of the graphics context
 *
 * @param handle Graphics handle
 * @return void* User data
 */
void *gfx_emote_get_user_data(gfx_handle_t handle);

/**
 * @brief Get screen dimensions from graphics handle
 *
 * @param handle Graphics handle
 * @param width Pointer to store screen width
 * @param height Pointer to store screen height
 * @return esp_err_t ESP_OK on success, otherwise an error code
 */
esp_err_t gfx_emote_get_screen_size(gfx_handle_t handle, uint32_t *width, uint32_t *height);

/**
 * @brief Lock the recursive render mutex to prevent rendering during external operations
 *
 * @param handle Graphics handle
 * @return esp_err_t ESP_OK on success, otherwise an error code
 */
esp_err_t gfx_emote_lock(gfx_handle_t handle);

/**
 * @brief Unlock the recursive render mutex after external operations
 *
 * @param handle Graphics handle
 * @return esp_err_t ESP_OK on success, otherwise an error code
 */
esp_err_t gfx_emote_unlock(gfx_handle_t handle);

/**
 * @brief Set the default background color for frame buffers
 *
 * @param handle Graphics handle
 * @param color Default background color in RGB565 format
 * @return esp_err_t ESP_OK on success, otherwise an error code
 */
esp_err_t gfx_emote_set_bg_color(gfx_handle_t handle, gfx_color_t color);

/**
 * @brief Check if the system is currently flushing the last block
 *
 * @param handle Graphics handle
 * @return bool True if flushing the last block, false otherwise
 */
bool gfx_emote_is_flushing_last(gfx_handle_t handle);

#ifdef __cplusplus
}
#endif
