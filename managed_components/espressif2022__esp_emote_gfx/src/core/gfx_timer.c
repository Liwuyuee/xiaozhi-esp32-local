/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "core/gfx_core.h"
#include "core/gfx_core_internal.h"
#include "core/gfx_timer.h"
#include "core/gfx_timer_internal.h"

static const char *TAG = "gfx_timer";

#define GFX_NO_TIMER_READY 0xFFFFFFFF

uint32_t gfx_timer_tick_get(void)
{
    return (uint32_t)(esp_timer_get_time() / 1000); // Convert microseconds to milliseconds
}

uint32_t gfx_timer_tick_elaps(uint32_t prev_tick)
{
    uint32_t act_time = gfx_timer_tick_get();

    /*If there is no overflow in sys_time simple subtract*/
    if (act_time >= prev_tick) {
        prev_tick = act_time - prev_tick;
    } else {
        prev_tick = UINT32_MAX - prev_tick + 1;
        prev_tick += act_time;
    }

    return prev_tick;
}

bool gfx_timer_exec(gfx_timer_t *timer)
{
    if (timer == NULL || timer->paused) {
        ESP_LOGD(TAG, "timer is NULL or paused");
        return false;
    }

    // Don't execute if repeat_count is 0 (timer completed)
    if (timer->repeat_count == 0) {
        return false;
    }

    uint32_t time_elapsed = gfx_timer_tick_elaps(timer->last_run);

    if (time_elapsed >= timer->period) {
        timer->last_run = gfx_timer_tick_get() - (time_elapsed % timer->period);

        if (timer->timer_cb) {
            timer->timer_cb(timer->user_data);
        }

        if (timer->repeat_count > 0) {
            timer->repeat_count--;
        }

        return true;
    }

    return false;
}

uint32_t gfx_timer_handler(gfx_timer_manager_t *timer_mgr)
{
    static uint32_t fps_sample_count = 0;
    static uint32_t fps_total_time = 0;

    uint32_t next_timer_delay = GFX_NO_TIMER_READY;
    gfx_timer_t *timer_node = timer_mgr->timer_list;
    gfx_timer_t *next_timer = NULL;

    while (timer_node != NULL) {
        next_timer = timer_node->next;

        gfx_timer_exec(timer_node);

        if (!timer_node->paused && timer_node->repeat_count != 0) {
            uint32_t elapsed_time = gfx_timer_tick_elaps(timer_node->last_run);
            uint32_t remaining_time = (elapsed_time >= timer_node->period) ? 0 : (timer_node->period - elapsed_time);

            if (remaining_time < next_timer_delay) {
                next_timer_delay = remaining_time;
            }
        }

        timer_node = next_timer;
    }

    uint32_t schedule_elapsed = gfx_timer_tick_elaps(timer_mgr->last_tick);
    timer_mgr->last_tick = gfx_timer_tick_get();

    uint32_t schedule_period_ms = (timer_mgr->fps > 0) ? (1000 / timer_mgr->fps) : 30;
    uint32_t schedule_remaining = (schedule_elapsed >= schedule_period_ms) ? 0 : (schedule_period_ms - schedule_elapsed);

    uint32_t final_delay;
    if (next_timer_delay == GFX_NO_TIMER_READY) {
        final_delay = schedule_remaining;
    } else {
        final_delay = (next_timer_delay < schedule_remaining) ? next_timer_delay : schedule_remaining;
    }

    fps_sample_count++;
    // ESP_LOGI(TAG, "elapsed=%d, period_ms=%d, next_timer_delay=%d, final_delay=%d", schedule_elapsed, schedule_period_ms, next_timer_delay, final_delay);
    fps_total_time += schedule_elapsed;
    if (fps_sample_count >= 10) {
        timer_mgr->actual_fps = 1000 / (fps_total_time / fps_sample_count);
        ESP_LOGD(TAG, "average fps: %"PRIu32"(%"PRIu32")", timer_mgr->actual_fps, timer_mgr->fps);
        fps_sample_count = 0;
        fps_total_time = 0;
    }

    if (final_delay == 0) {
        final_delay = 1;
    }

    timer_mgr->time_until_next = final_delay;
    return final_delay;
}

gfx_timer_handle_t gfx_timer_create(void *handle, gfx_timer_cb_t timer_cb, uint32_t period, void *user_data)
{
    if (handle == NULL || timer_cb == NULL) {
        return NULL;
    }

    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    gfx_timer_manager_t *timer_mgr = &ctx->timer.timer_mgr;

    gfx_timer_t *new_timer = (gfx_timer_t *)malloc(sizeof(gfx_timer_t));
    if (new_timer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate timer");
        return NULL;
    }

    new_timer->period = period;
    new_timer->timer_cb = timer_cb;
    new_timer->user_data = user_data;
    new_timer->repeat_count = -1; // Infinite repeat
    new_timer->paused = false;
    new_timer->last_run = gfx_timer_tick_get();
    new_timer->next = NULL;

    // Add to timer list
    if (timer_mgr->timer_list == NULL) {
        timer_mgr->timer_list = new_timer;
    } else {
        // Add to end of list
        gfx_timer_t *current_timer = timer_mgr->timer_list;
        while (current_timer->next != NULL) {
            current_timer = current_timer->next;
        }
        current_timer->next = new_timer;
    }

    return (gfx_timer_handle_t)new_timer;
}

void gfx_timer_delete(void *handle, gfx_timer_handle_t timer_handle)
{
    if (handle == NULL || timer_handle == NULL) {
        return;
    }

    gfx_timer_t *timer = (gfx_timer_t *)timer_handle;
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    gfx_timer_manager_t *timer_mgr = &ctx->timer.timer_mgr;

    // Remove from timer list
    gfx_timer_t *current_timer = timer_mgr->timer_list;
    gfx_timer_t *prev_timer = NULL;

    while (current_timer != NULL && current_timer != timer) {
        prev_timer = current_timer;
        current_timer = current_timer->next;
    }

    if (current_timer == timer) {
        if (prev_timer == NULL) {
            timer_mgr->timer_list = timer->next;
        } else {
            prev_timer->next = timer->next;
        }

        free(timer);
        ESP_LOGD(TAG, "Deleted timer");
    }
}

void gfx_timer_pause(gfx_timer_handle_t timer_handle)
{
    if (timer_handle != NULL) {
        gfx_timer_t *timer = (gfx_timer_t *)timer_handle;
        timer->paused = true;
    }
}

void gfx_timer_resume(gfx_timer_handle_t timer_handle)
{
    if (timer_handle != NULL) {
        gfx_timer_t *timer = (gfx_timer_t *)timer_handle;
        timer->paused = false;
        timer->last_run = gfx_timer_tick_get();

        // If timer was completed (repeat_count = 0), restore infinite repeat
        if (timer->repeat_count == 0) {
            timer->repeat_count = -1;
        }
    }
}

void gfx_timer_set_repeat_count(gfx_timer_handle_t timer_handle, int32_t repeat_count)
{
    if (timer_handle != NULL) {
        gfx_timer_t *timer = (gfx_timer_t *)timer_handle;
        timer->repeat_count = repeat_count;
    }
}

void gfx_timer_set_period(gfx_timer_handle_t timer_handle, uint32_t period)
{
    if (timer_handle != NULL) {
        gfx_timer_t *timer = (gfx_timer_t *)timer_handle;
        timer->period = period;
    }
}

void gfx_timer_reset(gfx_timer_handle_t timer_handle)
{
    if (timer_handle != NULL) {
        gfx_timer_t *timer = (gfx_timer_t *)timer_handle;
        timer->last_run = gfx_timer_tick_get();
    }
}

void gfx_timer_manager_init(gfx_timer_manager_t *timer_mgr, uint32_t fps)
{
    if (timer_mgr != NULL) {
        timer_mgr->timer_list = NULL;
        timer_mgr->time_until_next = GFX_NO_TIMER_READY;
        timer_mgr->last_tick = gfx_timer_tick_get();
        timer_mgr->fps = fps; // Store FPS directly
        timer_mgr->actual_fps = 0; // Initialize actual FPS
        ESP_LOGI(TAG, "Timer manager initialized with FPS: %"PRIu32" (period: %"PRIu32" ms)", fps, (fps > 0) ? (1000 / fps) : 30);
        esp_cpu_set_watchpoint(0, timer_mgr->timer_list, 4, ESP_CPU_WATCHPOINT_STORE);
    }
}

void gfx_timer_manager_deinit(gfx_timer_manager_t *timer_mgr)
{
    if (timer_mgr == NULL) {
        return;
    }

    // Free all timers
    gfx_timer_t *timer_node = timer_mgr->timer_list;
    while (timer_node != NULL) {
        gfx_timer_t *next_timer = timer_node->next;
        free(timer_node);
        timer_node = next_timer;
    }

    timer_mgr->timer_list = NULL;
}

uint32_t gfx_timer_get_actual_fps(void *handle)
{
    if (handle == NULL) {
        return 0;
    }

    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    gfx_timer_manager_t *timer_mgr = &ctx->timer.timer_mgr;

    return timer_mgr->actual_fps;
}
