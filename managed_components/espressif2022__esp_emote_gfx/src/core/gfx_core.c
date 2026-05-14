/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <string.h>
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "core/gfx_core.h"
#include "core/gfx_core_internal.h"
#include "core/gfx_timer.h"
#include "core/gfx_timer_internal.h"
#include "core/gfx_obj.h"
#include "widget/gfx_img.h"
#include "widget/gfx_img_internal.h"
#include "widget/gfx_label.h"
#include "widget/gfx_anim.h"
#include "decoder/gfx_img_dec.h"
#include "core/gfx_types.h"
#include "widget/gfx_font_internal.h"
#include "widget/gfx_label_internal.h"
#include "widget/gfx_anim_internal.h"

static const char *TAG = "gfx_core";

// Forward declarations
static bool gfx_refr_handler(gfx_core_context_t *ctx);
static bool gfx_event_handler(gfx_core_context_t *ctx);
static bool gfx_object_handler(gfx_core_context_t *ctx);
static esp_err_t gfx_buf_init_frame(gfx_core_context_t *ctx, const gfx_core_config_t *cfg);
static void gfx_buf_free_frame(gfx_core_context_t *ctx);
static uint32_t gfx_calculate_task_delay(uint32_t timer_delay);

/**
 * @brief Calculate task delay based on timer delay and system tick rate
 * @param timer_delay Timer delay in milliseconds
 * @return Calculated task delay in milliseconds
 */
static uint32_t gfx_calculate_task_delay(uint32_t timer_delay)
{
    uint32_t min_delay_ms = (1000 / configTICK_RATE_HZ) + 1; // At least one tick + 1ms

    if (timer_delay == ANIM_NO_TIMER_READY) {
        return (min_delay_ms > 5) ? min_delay_ms : 5;
    } else {
        return (timer_delay < min_delay_ms) ? min_delay_ms : timer_delay;
    }
}

/**
 * @brief Handle system events and user requests
 * @param ctx Player context
 * @return true if event was handled, false otherwise
 */
static bool gfx_event_handler(gfx_core_context_t *ctx)
{
    EventBits_t event_bits = xEventGroupWaitBits(ctx->sync.event_group,
                             NEED_DELETE, pdTRUE, pdFALSE, pdMS_TO_TICKS(0));

    if (event_bits & NEED_DELETE) {
        xEventGroupSetBits(ctx->sync.event_group, DELETE_DONE);
        vTaskDeleteWithCaps(NULL);
        return true;
    }

    return false;
}

/**
 * @brief Handle object updates and preprocessing
 * @param ctx Player context
 * @return true if objects need rendering, false otherwise
 */
static bool gfx_object_handler(gfx_core_context_t *ctx)
{
    if (ctx->disp.child_list == NULL) {
        return false;
    }

    bool updated = false;
    gfx_core_child_t *child_node = ctx->disp.child_list;

    while (child_node != NULL) {
        gfx_obj_t *obj = (gfx_obj_t *)child_node->src;

        if (obj->is_dirty) {
            updated = true;
        }

        if (obj->type == GFX_OBJ_TYPE_ANIMATION) {
            gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
            if (anim && anim->file_desc) {

                if (ESP_OK != gfx_anim_preprocess_frame(anim)) {
                    child_node = child_node->next;
                    continue;
                }
            }
        }
        child_node = child_node->next;
    }

    updated = true;

    return updated;
}

/**
 * @brief Calculate frame buffer height from buffer size
 * @param ctx Player context
 * @return Frame buffer height in pixels, or 0 if invalid
 */
static int gfx_buf_get_height(gfx_core_context_t *ctx)
{
    if (ctx->disp.buf_pixels == 0 || ctx->display.h_res == 0) {
        return 0;
    }
    return ctx->disp.buf_pixels / (ctx->display.h_res);
}

/**
 * @brief Initialize frame buffers (internal or external)
 * @param ctx Player context
 * @param cfg Graphics configuration (includes buffer configuration)
 * @return esp_err_t ESP_OK on success, otherwise error code
 */
static esp_err_t gfx_buf_init_frame(gfx_core_context_t *ctx, const gfx_core_config_t *cfg)
{
    ESP_LOGD(TAG, "cfg.buffers.buf1=%p, cfg.buffers.buf2=%p", cfg->buffers.buf1, cfg->buffers.buf2);
    if (cfg->buffers.buf1 != NULL) {
        ctx->disp.buf1 = (uint16_t *)cfg->buffers.buf1;
        ctx->disp.buf2 = (uint16_t *)cfg->buffers.buf2;

        if (cfg->buffers.buf_pixels > 0) {
            ctx->disp.buf_pixels = cfg->buffers.buf_pixels;
        } else {
            ESP_LOGW(TAG, "cfg.buffers.buf_pixels is 0, use default size");
            ctx->disp.buf_pixels = ctx->display.h_res * ctx->display.v_res;
        }

        ctx->disp.ext_bufs = true;
    } else {
        // Allocate internal buffers
        uint32_t buff_caps = 0;
#if SOC_PSRAM_DMA_CAPABLE == 0
        if (cfg->flags.buff_dma && cfg->flags.buff_spiram) {
            ESP_LOGW(TAG, "Alloc DMA capable buffer in SPIRAM is not supported!");
            return ESP_ERR_NOT_SUPPORTED;
        }
#endif
        if (cfg->flags.buff_dma) {
            buff_caps |= MALLOC_CAP_DMA;
        }
        if (cfg->flags.buff_spiram) {
            buff_caps |= MALLOC_CAP_SPIRAM;
        }
        if (buff_caps == 0) {
            buff_caps |= MALLOC_CAP_DEFAULT;
        }

        size_t buf_pixels = cfg->buffers.buf_pixels > 0 ? cfg->buffers.buf_pixels : ctx->display.h_res * ctx->display.v_res;

        ctx->disp.buf1 = (uint16_t *)heap_caps_malloc(buf_pixels * sizeof(uint16_t), buff_caps);
        if (!ctx->disp.buf1) {
            ESP_LOGE(TAG, "Failed to allocate frame buffer 1");
            return ESP_ERR_NO_MEM;
        }

        if (cfg->flags.double_buffer) {
            ctx->disp.buf2 = (uint16_t *)heap_caps_malloc(buf_pixels * sizeof(uint16_t), buff_caps);
            if (!ctx->disp.buf2) {
                ESP_LOGE(TAG, "Failed to allocate frame buffer 2");
                free(ctx->disp.buf1);
                ctx->disp.buf1 = NULL;
                return ESP_ERR_NO_MEM;
            }
        }

        ctx->disp.buf_pixels = buf_pixels;
        ctx->disp.ext_bufs = false;
    }
    ESP_LOGD(TAG, "Use frame buffers: buf1=%p, buf2=%p, size=%zu, ext_bufs=%d",
             ctx->disp.buf1, ctx->disp.buf2, ctx->disp.buf_pixels, ctx->disp.ext_bufs);

    ctx->disp.buf_act = ctx->disp.buf1;
    ctx->disp.bg_color.full = 0x0000;
    return ESP_OK;
}

/**
 * @brief Free frame buffers (only internal buffers)
 * @param ctx Player context
 */
static void gfx_buf_free_frame(gfx_core_context_t *ctx)
{
    // Only free buffers if they were internally allocated
    if (!ctx->disp.ext_bufs) {
        if (ctx->disp.buf1) {
            free(ctx->disp.buf1);
            ctx->disp.buf1 = NULL;
        }
        if (ctx->disp.buf2) {
            free(ctx->disp.buf2);
            ctx->disp.buf2 = NULL;
        }
        ESP_LOGI(TAG, "Freed internal frame buffers");
    } else {
        ESP_LOGI(TAG, "External buffers provided by user, not freeing");
    }
    ctx->disp.buf_pixels = 0;
    ctx->disp.ext_bufs = false;
}

void gfx_draw_child(gfx_core_context_t *ctx, int x1, int y1, int x2, int y2, const void *dest_buf)
{
    if (ctx->disp.child_list == NULL) {
        ESP_LOGD(TAG, "no child objects");
        return;
    }

    gfx_core_child_t *child_node = ctx->disp.child_list;
    bool swap = ctx->display.flags.swap;

    while (child_node != NULL) {
        gfx_obj_t *obj = (gfx_obj_t *)child_node->src;

        // Skip rendering if object is not visible
        if (!obj->is_visible) {
            child_node = child_node->next;
            continue;
        }

        if (obj->type == GFX_OBJ_TYPE_LABEL) {
            gfx_draw_label(obj, x1, y1, x2, y2, dest_buf, swap);
        } else if (obj->type == GFX_OBJ_TYPE_IMAGE) {
            gfx_draw_img(obj, x1, y1, x2, y2, dest_buf, swap);
        } else if (obj->type == GFX_OBJ_TYPE_ANIMATION) {
            gfx_draw_animation(obj, x1, y1, x2, y2, dest_buf, swap);
        }

        child_node = child_node->next;
    }
}

static void gfx_core_task(void *arg)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)arg;
    uint32_t timer_delay = 1; // Default delay

    while (1) {
        if (ctx->sync.lock_mutex && xSemaphoreTakeRecursive(ctx->sync.lock_mutex, portMAX_DELAY) == pdTRUE) {
            if (gfx_event_handler(ctx)) {
                xSemaphoreGiveRecursive(ctx->sync.lock_mutex);
                break;
            }

            timer_delay = gfx_timer_handler(&ctx->timer.timer_mgr);

            if (ctx->disp.child_list != NULL) {
                gfx_refr_handler(ctx);
            }

            uint32_t task_delay = gfx_calculate_task_delay(timer_delay);

            xSemaphoreGiveRecursive(ctx->sync.lock_mutex);
            vTaskDelay(pdMS_TO_TICKS(task_delay));
        } else {
            ESP_LOGW(TAG, "Failed to acquire mutex, retrying...");
            vTaskDelay(pdMS_TO_TICKS(1));
        }
    }
}

bool gfx_emote_flush_ready(gfx_handle_t handle, bool swap_act_buf)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL) {
        return false;
    }

    if (xPortInIsrContext()) {
        BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
        ctx->disp.swap_act_buf = swap_act_buf;
        bool result = xEventGroupSetBitsFromISR(ctx->sync.event_group, WAIT_FLUSH_DONE, &pxHigherPriorityTaskWoken);
        if (pxHigherPriorityTaskWoken == pdTRUE) {
            portYIELD_FROM_ISR();
        }
        return result;
    } else {
        ctx->disp.swap_act_buf = swap_act_buf;
        return xEventGroupSetBits(ctx->sync.event_group, WAIT_FLUSH_DONE);
    }
}

void *gfx_emote_get_user_data(gfx_handle_t handle)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid graphics context");
        return NULL;
    }

    return ctx->callbacks.user_data;
}

esp_err_t gfx_emote_get_screen_size(gfx_handle_t handle, uint32_t *width, uint32_t *height)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid graphics context");
        return ESP_ERR_INVALID_ARG;
    }

    if (width == NULL || height == NULL) {
        ESP_LOGE(TAG, "Invalid parameters");
        return ESP_ERR_INVALID_ARG;
    }

    *width = ctx->display.h_res;
    *height = ctx->display.v_res;

    return ESP_OK;
}

gfx_handle_t gfx_emote_init(const gfx_core_config_t *cfg)
{
    if (!cfg) {
        ESP_LOGE(TAG, "Invalid configuration");
        return NULL;
    }

    gfx_core_context_t *disp_ctx = malloc(sizeof(gfx_core_context_t));
    if (!disp_ctx) {
        ESP_LOGE(TAG, "Failed to allocate player context");
        return NULL;
    }

    // Initialize all fields to zero/NULL
    memset(disp_ctx, 0, sizeof(gfx_core_context_t));

    disp_ctx->display.v_res = cfg->v_res;
    disp_ctx->display.h_res = cfg->h_res;
    disp_ctx->display.flags.swap = cfg->flags.swap;

    disp_ctx->callbacks.flush_cb = cfg->flush_cb;
    disp_ctx->callbacks.update_cb = cfg->update_cb;
    disp_ctx->callbacks.user_data = cfg->user_data;

    disp_ctx->sync.event_group = xEventGroupCreate();

    disp_ctx->disp.child_list = NULL;

    // Initialize frame buffers (internal or external)
    esp_err_t buffer_ret = gfx_buf_init_frame(disp_ctx, cfg);
    if (buffer_ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize frame buffers");
        vEventGroupDelete(disp_ctx->sync.event_group);
        free(disp_ctx);
        return NULL;
    }

    // Initialize timer manager
    gfx_timer_manager_init(&disp_ctx->timer.timer_mgr, cfg->fps);

    // Create recursive render mutex for protecting rendering operations
    disp_ctx->sync.lock_mutex = xSemaphoreCreateRecursiveMutex();
    if (disp_ctx->sync.lock_mutex == NULL) {
        ESP_LOGE(TAG, "Failed to create recursive render mutex");
        gfx_buf_free_frame(disp_ctx);
        vEventGroupDelete(disp_ctx->sync.event_group);
        free(disp_ctx);
        return NULL;
    }

#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
    esp_err_t font_ret = gfx_ft_lib_create();
    if (font_ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create font library");
        gfx_buf_free_frame(disp_ctx);
        vSemaphoreDelete(disp_ctx->sync.lock_mutex);
        vEventGroupDelete(disp_ctx->sync.event_group);
        free(disp_ctx);
        return NULL;
    }
#endif

    // Initialize image decoder system
    esp_err_t decoder_ret = gfx_image_decoder_init();
    if (decoder_ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize image decoder system");
#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
        gfx_ft_lib_cleanup();
#endif
        gfx_buf_free_frame(disp_ctx);
        vSemaphoreDelete(disp_ctx->sync.lock_mutex);
        vEventGroupDelete(disp_ctx->sync.event_group);
        free(disp_ctx);
        return NULL;
    }

    const uint32_t stack_caps = cfg->task.task_stack_caps ? cfg->task.task_stack_caps : MALLOC_CAP_DEFAULT; // caps cannot be zero
    if (cfg->task.task_affinity < 0) {
        xTaskCreateWithCaps(gfx_core_task, "gfx_core", cfg->task.task_stack, disp_ctx, cfg->task.task_priority, NULL, stack_caps);
    } else {
        xTaskCreatePinnedToCoreWithCaps(gfx_core_task, "gfx_core", cfg->task.task_stack, disp_ctx, cfg->task.task_priority, NULL, cfg->task.task_affinity, stack_caps);
    }

    return (gfx_handle_t)disp_ctx;
}

void gfx_emote_deinit(gfx_handle_t handle)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid graphics context");
        return;
    }

    xEventGroupSetBits(ctx->sync.event_group, NEED_DELETE);
    xEventGroupWaitBits(ctx->sync.event_group, DELETE_DONE, pdTRUE, pdFALSE, portMAX_DELAY);

    // Free all child nodes
    gfx_core_child_t *child_node = ctx->disp.child_list;
    while (child_node != NULL) {
        gfx_core_child_t *next_child = child_node->next;
        free(child_node);
        child_node = next_child;
    }
    ctx->disp.child_list = NULL;

    // Clean up timers
    gfx_timer_manager_deinit(&ctx->timer.timer_mgr);

    // Free frame buffers
    gfx_buf_free_frame(ctx);

    // Delete font library
#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
    gfx_ft_lib_cleanup();
#endif

    // Delete mutex
    if (ctx->sync.lock_mutex) {
        vSemaphoreDelete(ctx->sync.lock_mutex);
        ctx->sync.lock_mutex = NULL;
    }

    // Delete event group
    if (ctx->sync.event_group) {
        vEventGroupDelete(ctx->sync.event_group);
        ctx->sync.event_group = NULL;
    }

    // Deinitialize image decoder system
    gfx_image_decoder_deinit();

    // Free context
    free(ctx);
}

esp_err_t gfx_emote_add_chlid(gfx_handle_t handle, int type, void *src)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL || src == NULL) {
        ESP_LOGE(TAG, "Invalid parameters");
        return ESP_ERR_INVALID_ARG;
    }

    gfx_core_child_t *new_child = (gfx_core_child_t *)malloc(sizeof(gfx_core_child_t));
    if (new_child == NULL) {
        ESP_LOGE(TAG, "Failed to allocate child node");
        return ESP_ERR_NO_MEM;
    }

    new_child->type = type;
    new_child->src = src;
    new_child->next = NULL;

    // Add to child list
    if (ctx->disp.child_list == NULL) {
        ctx->disp.child_list = new_child;
    } else {
        gfx_core_child_t *current = ctx->disp.child_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_child;
    }

    ESP_LOGD(TAG, "Added child object of type %d", type);
    return ESP_OK;
}

esp_err_t gfx_emote_remove_child(gfx_handle_t handle, void *src)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL || src == NULL) {
        ESP_LOGE(TAG, "Invalid parameters");
        return ESP_ERR_INVALID_ARG;
    }

    gfx_core_child_t *current = ctx->disp.child_list;
    gfx_core_child_t *prev = NULL;

    while (current != NULL) {
        if (current->src == src) {
            if (prev == NULL) {
                ctx->disp.child_list = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            ESP_LOGD(TAG, "Removed child object from list");
            return ESP_OK;
        }
        prev = current;
        current = current->next;
    }

    ESP_LOGW(TAG, "Child object not found in list");
    return ESP_ERR_NOT_FOUND;
}

esp_err_t gfx_emote_lock(gfx_handle_t handle)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL || ctx->sync.lock_mutex == NULL) {
        ESP_LOGE(TAG, "Invalid graphics context or mutex");
        return ESP_ERR_INVALID_ARG;
    }

    if (xSemaphoreTakeRecursive(ctx->sync.lock_mutex, portMAX_DELAY) != pdTRUE) {
        ESP_LOGE(TAG, "Failed to acquire graphics lock");
        return ESP_ERR_TIMEOUT;
    }

    return ESP_OK;
}

esp_err_t gfx_emote_unlock(gfx_handle_t handle)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL || ctx->sync.lock_mutex == NULL) {
        ESP_LOGE(TAG, "Invalid graphics context or mutex");
        return ESP_ERR_INVALID_ARG;
    }

    if (xSemaphoreGiveRecursive(ctx->sync.lock_mutex) != pdTRUE) {
        ESP_LOGE(TAG, "Failed to release graphics lock");
        return ESP_ERR_INVALID_STATE;
    }

    return ESP_OK;
}

esp_err_t gfx_emote_set_bg_color(gfx_handle_t handle, gfx_color_t color)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid graphics context");
        return ESP_ERR_INVALID_ARG;
    }

    ctx->disp.bg_color = color;
    ESP_LOGD(TAG, "Set background color to 0x%04X", color.full);
    return ESP_OK;
}

bool gfx_emote_is_flushing_last(gfx_handle_t handle)
{
    gfx_core_context_t *ctx = (gfx_core_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid graphics context");
        return false;
    }

    return ctx->disp.flushing_last;
}

/**
 * @brief Handle rendering of all objects in the scene
 * @param ctx Player context
 * @return true if rendering was performed, false otherwise
 */
static bool gfx_refr_handler(gfx_core_context_t *ctx)
{
    bool updated = gfx_object_handler(ctx);

    if (!updated) {
        return false;
    }

    int block_height = gfx_buf_get_height(ctx);
    if (block_height == 0) {
        ESP_LOGE(TAG, "Invalid frame buffer size");
        return false;
    }

    int v_res = ctx->display.v_res;
    int h_res = ctx->display.h_res;
    int total_blocks = (v_res + block_height - 1) / block_height;

    for (int block_idx = 0; block_idx < total_blocks; block_idx++) {
        int x1 = 0;
        int x2 = h_res;

        int y1 = block_idx * block_height;
        int y2 = ((block_idx + 1) * block_height > v_res) ? v_res : (block_idx + 1) * block_height;

        ctx->disp.flushing_last = (block_idx == total_blocks - 1);

        uint16_t *buf_act = ctx->disp.buf_act;

        uint16_t bg_color = ctx->disp.bg_color.full;
        size_t pixels = ctx->disp.buf_pixels;
        for (size_t i = 0; i < pixels; i++) {//影响帧率
            buf_act[i] = bg_color;
        }

        gfx_draw_child(ctx, x1, y1, x2, y2, buf_act);

        if (ctx->callbacks.flush_cb) {
            xEventGroupClearBits(ctx->sync.event_group, WAIT_FLUSH_DONE);
            ctx->callbacks.flush_cb(ctx, x1, y1, x2, y2, buf_act);
            xEventGroupWaitBits(ctx->sync.event_group, WAIT_FLUSH_DONE, pdTRUE, pdFALSE, pdMS_TO_TICKS(20));
        }

        if ((ctx->disp.flushing_last || ctx->disp.swap_act_buf) && ctx->disp.buf2 != NULL) {
            if (ctx->disp.buf_act == ctx->disp.buf1) {
                ctx->disp.buf_act = ctx->disp.buf2;
            } else {
                ctx->disp.buf_act = ctx->disp.buf1;
            }
            ctx->disp.swap_act_buf = false;
        }
    }

    return true;
}
