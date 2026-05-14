/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

#include "core/gfx_types.h"
#include "core/gfx_core.h"
#include "core/gfx_timer_internal.h"
#include "core/gfx_obj_internal.h"
#include "widget/gfx_font_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/* Event bits for synchronization */
#define NEED_DELETE     BIT0
#define DELETE_DONE     BIT1
#define WAIT_FLUSH_DONE BIT2

/* Animation timer constants */
#define ANIM_NO_TIMER_READY 0xFFFFFFFF

/**********************
 *      TYPEDEFS
 **********************/

/* Core context structure */
typedef struct {
    /* Display configuration */
    struct {
        uint32_t h_res;                /**< Horizontal resolution */
        uint32_t v_res;                /**< Vertical resolution */
        uint32_t fb_v_res;             /**< Frame buffer vertical resolution */
        struct {
            unsigned char swap: 1;     /**< Color swap flag */
        } flags;                       /**< Display flags */
    } display;                         /**< Display configuration */

    /* Callback functions */
    struct {
        gfx_player_flush_cb_t flush_cb;       /**< Flush callback function */
        gfx_player_update_cb_t update_cb;     /**< Update callback function */
        void *user_data;               /**< User data pointer */
    } callbacks;                       /**< Callback functions */

    /* Timer management */
    struct {
        gfx_timer_manager_t timer_mgr; /**< Timer manager */
    } timer;                           /**< Timer management */

    /* Graphics rendering */
    struct {
        gfx_core_child_t *child_list;  /**< Child object list */
        uint16_t *buf1;                /**< Frame buffer 1 */
        uint16_t *buf2;                /**< Frame buffer 2 */
        uint16_t *buf_act;          /**< Active frame buffer */
        size_t buf_pixels;              /**< Buffer size in pixels */
        gfx_color_t bg_color;     /**< Default background color */
        bool ext_bufs;         /**< Whether using external buffers */
        bool flushing_last;      /**< Whether flushing the last block */
        bool swap_act_buf;       /**< Whether swap the active buffer */
    } disp;

    /* Synchronization primitives */
    struct {
        SemaphoreHandle_t lock_mutex;  /**< Render mutex for thread safety */
        EventGroupHandle_t event_group; /**< Event group for synchronization */
    } sync;                            /**< Synchronization primitives */
} gfx_core_context_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Internal core functions
 *====================*/

/**
 * @brief Add a child element to the graphics context
 *
 * @param handle Graphics handle
 * @param type Type of the child element
 * @param src Source data pointer
 * @return esp_err_t ESP_OK on success, otherwise an error code
 */
esp_err_t gfx_emote_add_chlid(gfx_handle_t handle, int type, void *src);

/**
 * @brief Remove a child element from the graphics context
 *
 * @param handle Graphics handle
 * @param src Source data pointer to remove
 * @return esp_err_t ESP_OK on success, otherwise an error code
 */
esp_err_t gfx_emote_remove_child(gfx_handle_t handle, void *src);

/**
 * @brief Blend child objects to destination buffer
 * @param ctx Graphics context
 * @param x1 Left coordinate
 * @param y1 Top coordinate
 * @param x2 Right coordinate
 * @param y2 Bottom coordinate
 * @param dest_buf Destination buffer
 */
void gfx_draw_child(gfx_core_context_t *ctx, int x1, int y1, int x2, int y2, const void *dest_buf);

#ifdef __cplusplus
}
#endif
