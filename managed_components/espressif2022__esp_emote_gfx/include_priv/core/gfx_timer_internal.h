/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "core/gfx_types.h"
#include "core/gfx_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Timer handle type for external use */
typedef void *gfx_timer_handle_t;

/* Timer structure (internal use) */
typedef struct gfx_timer_s {
    uint32_t period;
    uint32_t last_run;
    gfx_timer_cb_t timer_cb;
    void *user_data;
    int32_t repeat_count;
    bool paused;
    struct gfx_timer_s *next;
} gfx_timer_t;

/* Timer manager structure (internal use) */
typedef struct {
    gfx_timer_t *timer_list;
    uint32_t time_until_next;
    uint32_t last_tick;
    uint32_t fps; ///< Target FPS for timer scheduling
    uint32_t actual_fps; ///< Actual measured FPS
    /* FPS statistics */
    uint32_t fps_last_report_tick; ///< Last time FPS was reported
    uint32_t fps_report_interval_ms; ///< FPS report interval in milliseconds (default 500 ms)
} gfx_timer_manager_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Internal timer functions
 *====================*/

/**
 * @brief Execute a timer
 * @param timer Timer to execute
 * @return true if timer was executed, false otherwise
 */
bool gfx_timer_exec(gfx_timer_t *timer);

/**
 * @brief Handle timer manager operations
 * @param timer_mgr Timer manager
 * @return Time until next timer execution
 */
uint32_t gfx_timer_handler(gfx_timer_manager_t *timer_mgr);

/**
 * @brief Initialize timer manager
 * @param timer_mgr Timer manager to initialize
 * @param fps Target FPS for timer scheduling
 */
void gfx_timer_manager_init(gfx_timer_manager_t *timer_mgr, uint32_t fps);

/**
 * @brief Deinitialize timer manager
 * @param timer_mgr Timer manager to deinitialize
 */
void gfx_timer_manager_deinit(gfx_timer_manager_t *timer_mgr);

#ifdef __cplusplus
}
#endif
