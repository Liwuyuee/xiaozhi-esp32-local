/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <string.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "core/gfx_core.h"
#include "core/gfx_core_internal.h"
#include "core/gfx_timer.h"
#include "core/gfx_obj.h"
#include "widget/gfx_img.h"
#include "widget/gfx_img_internal.h"
#include "widget/gfx_label.h"
#include "widget/gfx_label_internal.h"
#include "widget/gfx_anim.h"
#include "core/gfx_types.h"
#include "widget/gfx_anim_internal.h"
#include "widget/gfx_font_internal.h"
#include "decoder/gfx_img_dec.h"
#include "gfx_eaf_dec.h"

static const char *TAG = "gfx_obj";

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*=====================
 * Object creation
 *====================*/

gfx_obj_t *gfx_img_create(gfx_handle_t handle)
{
    gfx_obj_t *obj = (gfx_obj_t *)malloc(sizeof(gfx_obj_t));
    if (obj == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for image object");
        return NULL;
    }

    memset(obj, 0, sizeof(gfx_obj_t));
    obj->type = GFX_OBJ_TYPE_IMAGE;
    obj->parent_handle = handle;
    obj->is_visible = true;
    obj->is_dirty = true;
    gfx_emote_add_chlid(handle, GFX_OBJ_TYPE_IMAGE, obj);
    ESP_LOGD(TAG, "Created image object");
    return obj;
}

gfx_obj_t *gfx_label_create(gfx_handle_t handle)
{
    gfx_obj_t *obj = (gfx_obj_t *)malloc(sizeof(gfx_obj_t));
    if (obj == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for label object");
        return NULL;
    }

    memset(obj, 0, sizeof(gfx_obj_t));
    obj->type = GFX_OBJ_TYPE_LABEL;
    obj->parent_handle = handle;
    obj->is_visible = true;
    obj->is_dirty = true;

    gfx_label_t *label = (gfx_label_t *)malloc(sizeof(gfx_label_t));
    if (label == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for label object");
        free(obj);
        return NULL;
    }
    memset(label, 0, sizeof(gfx_label_t));

    label->opa = 0xFF;
    label->mask = NULL;
    label->bg_color = (gfx_color_t) {
        .full = 0x0000
    };
    label->bg_enable = false;
    label->text_align = GFX_TEXT_ALIGN_LEFT;
    label->long_mode = GFX_LABEL_LONG_CLIP;
    label->line_spacing = 2;

    label->scroll_offset = 0;
    label->scroll_speed = 50;
    label->scroll_loop = true;
    label->scrolling = false;
    label->scroll_changed = false;
    label->scroll_timer = NULL;
    label->text_width = 0;

    label->lines = NULL;
    label->line_count = 0;
    label->line_widths = NULL;

    obj->src = label;

    gfx_emote_add_chlid(handle, GFX_OBJ_TYPE_LABEL, obj);
    ESP_LOGD(TAG, "Created label object with default font config");
    return obj;
}

/*=====================
 * Setter functions
 *====================*/

gfx_obj_t *gfx_img_set_src(gfx_obj_t *obj, void *src)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return NULL;
    }

    if (obj->type != GFX_OBJ_TYPE_IMAGE) {
        ESP_LOGE(TAG, "Object is not an image type");
        return NULL;
    }

    obj->src = src;

    if (src != NULL) {
        gfx_image_header_t header;
        gfx_image_decoder_dsc_t dsc = {
            .src = src,
        };
        esp_err_t ret = gfx_image_decoder_info(&dsc, &header);
        if (ret == ESP_OK) {
            obj->width = header.w;
            obj->height = header.h;
        } else {
            ESP_LOGE(TAG, "Failed to get image info from source");
        }
    }

    obj->is_dirty = true;
    ESP_LOGD(TAG, "Set image source, size: %dx%d", obj->width, obj->height);
    return obj;
}

void gfx_obj_set_pos(gfx_obj_t *obj, gfx_coord_t x, gfx_coord_t y)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return;
    }

    obj->x = x;
    obj->y = y;
    obj->use_align = false;
    obj->is_dirty = true;

    ESP_LOGD(TAG, "Set object position: (%d, %d)", x, y);
}

void gfx_obj_set_size(gfx_obj_t *obj, uint16_t w, uint16_t h)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return;
    }

    if (obj->type == GFX_OBJ_TYPE_ANIMATION || obj->type == GFX_OBJ_TYPE_IMAGE) {
        ESP_LOGW(TAG, "Set size for animation or image is not allowed");
    } else {
        obj->width = w;
        obj->height = h;
        obj->is_dirty = true;
    }

    ESP_LOGD(TAG, "Set object size: %dx%d", w, h);
}

void gfx_obj_align(gfx_obj_t *obj, uint8_t align, gfx_coord_t x_ofs, gfx_coord_t y_ofs)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return;
    }

    if (obj->parent_handle == NULL) {
        ESP_LOGE(TAG, "Object has no parent handle");
        return;
    }

    if (align > GFX_ALIGN_OUT_BOTTOM_RIGHT) {
        ESP_LOGW(TAG, "Unknown alignment type: %d", align);
        return;
    }
    obj->align_type = align;
    obj->align_x_ofs = x_ofs;
    obj->align_y_ofs = y_ofs;
    obj->use_align = true;
    obj->is_dirty = true;

    ESP_LOGD(TAG, "Set object alignment: type=%d, offset=(%d, %d)", align, x_ofs, y_ofs);
}

void gfx_obj_set_visible(gfx_obj_t *obj, bool visible)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return;
    }

    obj->is_visible = visible;
    obj->is_dirty = true;
    ESP_LOGD(TAG, "Set object visibility: %s", visible ? "visible" : "hidden");
}

bool gfx_obj_get_visible(gfx_obj_t *obj)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return false;
    }

    return obj->is_visible;
}

/*=====================
 * Static helper functions
 *====================*/

void gfx_obj_calculate_aligned_position(gfx_obj_t *obj, uint32_t parent_width, uint32_t parent_height, gfx_coord_t *x, gfx_coord_t *y)
{
    if (obj == NULL || x == NULL || y == NULL) {
        return;
    }

    if (!obj->use_align) {
        *x = obj->x;
        *y = obj->y;
        return;
    }

    gfx_coord_t calculated_x = 0;
    gfx_coord_t calculated_y = 0;
    switch (obj->align_type) {
    case GFX_ALIGN_TOP_LEFT:
        calculated_x = obj->align_x_ofs;
        calculated_y = obj->align_y_ofs;
        break;
    case GFX_ALIGN_TOP_MID:
        calculated_x = ((gfx_coord_t)parent_width - obj->width) / 2 + obj->align_x_ofs;
        calculated_y = obj->align_y_ofs;
        break;
    case GFX_ALIGN_TOP_RIGHT:
        calculated_x = (gfx_coord_t)parent_width - obj->width + obj->align_x_ofs;
        calculated_y = obj->align_y_ofs;
        break;
    case GFX_ALIGN_LEFT_MID:
        calculated_x = obj->align_x_ofs;
        calculated_y = ((gfx_coord_t)parent_height - obj->height) / 2 + obj->align_y_ofs;
        break;
    case GFX_ALIGN_CENTER:
        calculated_x = ((gfx_coord_t)parent_width - obj->width) / 2 + obj->align_x_ofs;
        calculated_y = ((gfx_coord_t)parent_height - obj->height) / 2 + obj->align_y_ofs;
        break;
    case GFX_ALIGN_RIGHT_MID:
        calculated_x = (gfx_coord_t)parent_width - obj->width + obj->align_x_ofs;
        calculated_y = ((gfx_coord_t)parent_height - obj->height) / 2 + obj->align_y_ofs;
        break;
    case GFX_ALIGN_BOTTOM_LEFT:
        calculated_x = obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height - obj->height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_BOTTOM_MID:
        calculated_x = ((gfx_coord_t)parent_width - obj->width) / 2 + obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height - obj->height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_BOTTOM_RIGHT:
        calculated_x = (gfx_coord_t)parent_width - obj->width + obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height - obj->height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_TOP_LEFT:
        calculated_x = obj->align_x_ofs;
        calculated_y = -obj->height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_TOP_MID:
        calculated_x = ((gfx_coord_t)parent_width - obj->width) / 2 + obj->align_x_ofs;
        calculated_y = -obj->height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_TOP_RIGHT:
        calculated_x = (gfx_coord_t)parent_width + obj->align_x_ofs;
        calculated_y = -obj->height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_LEFT_TOP:
        calculated_x = -obj->width + obj->align_x_ofs;
        calculated_y = obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_LEFT_MID:
        calculated_x = -obj->width + obj->align_x_ofs;
        calculated_y = ((gfx_coord_t)parent_height - obj->height) / 2 + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_LEFT_BOTTOM:
        calculated_x = -obj->width + obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_RIGHT_TOP:
        calculated_x = (gfx_coord_t)parent_width + obj->align_x_ofs;
        calculated_y = obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_RIGHT_MID:
        calculated_x = (gfx_coord_t)parent_width + obj->align_x_ofs;
        calculated_y = ((gfx_coord_t)parent_height - obj->height) / 2 + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_RIGHT_BOTTOM:
        calculated_x = (gfx_coord_t)parent_width + obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_BOTTOM_LEFT:
        calculated_x = obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_BOTTOM_MID:
        calculated_x = ((gfx_coord_t)parent_width - obj->width) / 2 + obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height + obj->align_y_ofs;
        break;
    case GFX_ALIGN_OUT_BOTTOM_RIGHT:
        calculated_x = (gfx_coord_t)parent_width + obj->align_x_ofs;
        calculated_y = (gfx_coord_t)parent_height + obj->align_y_ofs;
        break;
    default:
        ESP_LOGW(TAG, "Unknown alignment type: %d", obj->align_type);
        calculated_x = obj->x;
        calculated_y = obj->y;
        break;
    }

    *x = calculated_x;
    *y = calculated_y;
}

/*=====================
 * Getter functions
 *====================*/

void gfx_obj_get_pos(gfx_obj_t *obj, gfx_coord_t *x, gfx_coord_t *y)
{
    if (obj == NULL || x == NULL || y == NULL) {
        ESP_LOGE(TAG, "Invalid parameters");
        return;
    }

    *x = obj->x;
    *y = obj->y;
}

void gfx_obj_get_size(gfx_obj_t *obj, uint16_t *w, uint16_t *h)
{
    if (obj == NULL || w == NULL || h == NULL) {
        ESP_LOGE(TAG, "Invalid parameters");
        return;
    }

    *w = obj->width;
    *h = obj->height;
}

/*=====================
 * Other functions
 *====================*/

void gfx_obj_delete(gfx_obj_t *obj)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return;
    }

    ESP_LOGD(TAG, "Deleting object type: %d", obj->type);

    if (obj->parent_handle != NULL) {
        gfx_emote_remove_child(obj->parent_handle, obj);
    }

    if (obj->type == GFX_OBJ_TYPE_LABEL) {
        gfx_label_t *label = (gfx_label_t *)obj->src;
        if (label) {
            if (label->scroll_timer) {
                gfx_timer_delete(obj->parent_handle, label->scroll_timer);
                label->scroll_timer = NULL;
            }

            gfx_label_clear_cached_lines(label);

            if (label->text) {
                free(label->text);
            }
            if (label->font_ctx) {
                free(label->font_ctx);
            }
            if (label->mask) {
                free(label->mask);
            }
            free(label);
        }
    } else if (obj->type == GFX_OBJ_TYPE_ANIMATION) {
        gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
        if (anim) {
            if (anim->is_playing) {
                gfx_anim_stop(obj);
            }

            if (anim->timer != NULL) {
                gfx_timer_delete((void *)obj->parent_handle, anim->timer);
                anim->timer = NULL;
            }

            gfx_anim_free_frame_info(&anim->frame);

            if (anim->file_desc) {
                eaf_deinit(anim->file_desc);
            }

            free(anim);
        }
    }
    free(obj);
}

/*=====================
 * Animation object functions
 *====================*/

static void gfx_anim_timer_callback(void *arg)
{
    gfx_obj_t *obj = (gfx_obj_t *)arg;
    gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;

    if (!anim || !anim->is_playing) {
        ESP_LOGD(TAG, "anim is NULL or not playing, %p, %d", anim, anim->is_playing);
        return;
    }

    gfx_core_context_t *ctx = obj->parent_handle;
    if (anim->current_frame >= anim->end_frame) {
        if (anim->repeat) {
            ESP_LOGD(TAG, "REPEAT");
            if (ctx->callbacks.update_cb) {
                ctx->callbacks.update_cb(ctx, GFX_PLAYER_EVENT_ALL_FRAME_DONE, obj);
            }
            anim->current_frame = anim->start_frame;
        } else {
            ESP_LOGD(TAG, "STOP");
            anim->is_playing = false;
            if (ctx->callbacks.update_cb) {
                ctx->callbacks.update_cb(ctx, GFX_PLAYER_EVENT_ALL_FRAME_DONE, obj);
            }
            return;
        }
    } else {
        anim->current_frame++;
        if (ctx->callbacks.update_cb) {
            ctx->callbacks.update_cb(ctx, GFX_PLAYER_EVENT_ONE_FRAME_DONE, obj);
        }
        ESP_LOGD("anim cb", " %"PRIu32" (%"PRIu32" / %"PRIu32")", anim->current_frame, anim->start_frame, anim->end_frame);
    }

    obj->is_dirty = true;
}

gfx_obj_t *gfx_anim_create(gfx_handle_t handle)
{
    gfx_obj_t *obj = (gfx_obj_t *)malloc(sizeof(gfx_obj_t));
    if (obj == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for animation object");
        return NULL;
    }

    memset(obj, 0, sizeof(gfx_obj_t));
    obj->parent_handle = handle;
    obj->is_visible = true;

    gfx_anim_property_t *anim = (gfx_anim_property_t *)malloc(sizeof(gfx_anim_property_t));
    if (anim == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for animation property");
        free(obj);
        return NULL;
    }
    memset(anim, 0, sizeof(gfx_anim_property_t));

    anim->file_desc = NULL;
    anim->start_frame = 0;
    anim->end_frame = 0;
    anim->current_frame = 0;
    anim->fps = 30;
    anim->repeat = true;
    anim->is_playing = false;

    // Initialize mirror properties
    anim->mirror_mode = GFX_MIRROR_DISABLED;
    anim->mirror_offset = 0;

    uint32_t period_ms = 1000 / anim->fps;
    anim->timer = gfx_timer_create((void *)obj->parent_handle, gfx_anim_timer_callback, period_ms, obj);
    if (anim->timer == NULL) {
        ESP_LOGE(TAG, "Failed to create animation timer");
        free(anim);
        free(obj);
        return NULL;
    }

    memset(&anim->frame.header, 0, sizeof(eaf_header_t));

    anim->frame.frame_data = NULL;
    anim->frame.frame_size = 0;

    anim->frame.block_offsets = NULL;
    anim->frame.pixel_buffer = NULL;
    anim->frame.color_palette = NULL;

    anim->frame.last_block = -1;

    anim->mirror_mode = GFX_MIRROR_DISABLED;
    anim->mirror_offset = 0;

    obj->src = anim;
    obj->type = GFX_OBJ_TYPE_ANIMATION;

    gfx_emote_add_chlid(handle, GFX_OBJ_TYPE_ANIMATION, obj);
    return obj;
}

esp_err_t gfx_anim_set_src(gfx_obj_t *obj, const void *src_data, size_t src_len)
{
    if (obj == NULL || src_data == NULL) {
        ESP_LOGE(TAG, "Invalid parameters");
        return ESP_ERR_INVALID_ARG;
    }

    if (obj->type != GFX_OBJ_TYPE_ANIMATION) {
        ESP_LOGE(TAG, "Object is not an animation type");
        return ESP_ERR_INVALID_ARG;
    }

    obj->is_dirty = true;

    gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
    if (anim == NULL) {
        ESP_LOGE(TAG, "Animation property is NULL");
        return ESP_ERR_INVALID_STATE;
    }

    if (anim->is_playing) {
        ESP_LOGD(TAG, "stop current animation");
        gfx_anim_stop(obj);
    }

    if (anim->frame.header.width > 0) {
        eaf_free_header(&anim->frame.header);
        memset(&anim->frame.header, 0, sizeof(eaf_header_t));
    }
    anim->frame.frame_data = NULL;
    anim->frame.frame_size = 0;

    eaf_format_handle_t new_desc;
    eaf_init(src_data, src_len, &new_desc);
    if (new_desc == NULL) {
        ESP_LOGE(TAG, "Failed to initialize asset parser");
        return ESP_FAIL;
    }

    if (anim->file_desc) {
        eaf_deinit(anim->file_desc);
        anim->file_desc = NULL;
    }

    anim->file_desc = new_desc;
    anim->start_frame = 0;
    anim->current_frame = 0;
    //last block is empty
    anim->end_frame = eaf_get_total_frames(new_desc) - 2;

    ESP_LOGD(TAG, "set src, start: %"PRIu32", end: %"PRIu32", file_desc: %p", anim->start_frame, anim->end_frame, anim->file_desc);
    return ESP_OK;
}

esp_err_t gfx_anim_set_segment(gfx_obj_t *obj, uint32_t start, uint32_t end, uint32_t fps, bool repeat)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    if (obj->type != GFX_OBJ_TYPE_ANIMATION) {
        ESP_LOGE(TAG, "Object is not an animation type");
        return ESP_ERR_INVALID_ARG;
    }

    gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
    if (anim == NULL) {
        ESP_LOGE(TAG, "Animation property is NULL");
        return ESP_ERR_INVALID_STATE;
    }

    int total_frames = eaf_get_total_frames(anim->file_desc);

    anim->start_frame = start;
    anim->end_frame = (end > total_frames - 2) ? (total_frames - 2) : end;
    anim->current_frame = start;

    if (anim->fps != fps) {
        ESP_LOGI(TAG, "FPS changed from %"PRIu32" to %"PRIu32", updating timer period", anim->fps, fps);
        anim->fps = fps;

        if (anim->timer != NULL) {
            uint32_t new_period_ms = 1000 / fps;
            gfx_timer_set_period(anim->timer, new_period_ms);
            ESP_LOGI(TAG, "Animation timer period updated to %"PRIu32" ms for %"PRIu32" FPS", new_period_ms, fps);
        }
    }

    anim->repeat = repeat;

    ESP_LOGD(TAG, "Set animation segment: %"PRIu32" -> %"PRIu32"(%d, %"PRIu32"), fps: %"PRIu32", repeat: %d", anim->start_frame, anim->end_frame, total_frames, end, fps, repeat);
    return ESP_OK;
}

esp_err_t gfx_anim_start(gfx_obj_t *obj)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    if (obj->type != GFX_OBJ_TYPE_ANIMATION) {
        ESP_LOGE(TAG, "Object is not an animation type");
        return ESP_ERR_INVALID_ARG;
    }

    gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
    if (anim == NULL) {
        ESP_LOGE(TAG, "Animation property is NULL");
        return ESP_ERR_INVALID_STATE;
    }

    if (anim->file_desc == NULL) {
        ESP_LOGE(TAG, "Animation source not set");
        return ESP_ERR_INVALID_STATE;
    }

    if (anim->is_playing) {
        ESP_LOGD(TAG, "Animation is already playing");
        return ESP_OK;
    }

    anim->is_playing = true;
    anim->current_frame = anim->start_frame;

    ESP_LOGD(TAG, "Started animation");
    return ESP_OK;
}

esp_err_t gfx_anim_stop(gfx_obj_t *obj)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    if (obj->type != GFX_OBJ_TYPE_ANIMATION) {
        ESP_LOGE(TAG, "Object is not an animation type");
        return ESP_ERR_INVALID_ARG;
    }

    gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
    if (anim == NULL) {
        ESP_LOGE(TAG, "Animation property is NULL");
        return ESP_ERR_INVALID_STATE;
    }

    if (!anim->is_playing) {
        ESP_LOGD(TAG, "Animation is not playing");
        return ESP_OK;
    }

    anim->is_playing = false;

    ESP_LOGD(TAG, "Stopped animation");
    return ESP_OK;
}

esp_err_t gfx_anim_set_mirror(gfx_obj_t *obj, bool enabled, int16_t offset)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    if (obj->type != GFX_OBJ_TYPE_ANIMATION) {
        ESP_LOGE(TAG, "Object is not an animation type");
        return ESP_ERR_INVALID_ARG;
    }

    gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
    if (anim == NULL) {
        ESP_LOGE(TAG, "Animation property is NULL");
        return ESP_ERR_INVALID_STATE;
    }

    anim->mirror_mode = enabled ? GFX_MIRROR_MANUAL : GFX_MIRROR_DISABLED;
    anim->mirror_offset = offset;

    ESP_LOGD(TAG, "Set animation mirror: enabled=%s, offset=%d", enabled ? "true" : "false", offset);
    return ESP_OK;
}

esp_err_t gfx_anim_set_auto_mirror(gfx_obj_t *obj, bool enabled)
{
    if (obj == NULL) {
        ESP_LOGE(TAG, "Object is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    if (obj->type != GFX_OBJ_TYPE_ANIMATION) {
        ESP_LOGE(TAG, "Object is not an animation type");
        return ESP_ERR_INVALID_ARG;
    }

    gfx_anim_property_t *anim = (gfx_anim_property_t *)obj->src;
    if (anim == NULL) {
        ESP_LOGE(TAG, "Animation property is NULL");
        return ESP_ERR_INVALID_STATE;
    }

    anim->mirror_mode = enabled ? GFX_MIRROR_AUTO : GFX_MIRROR_DISABLED;

    ESP_LOGD(TAG, "Set auto mirror alignment: enabled=%s", enabled ? "true" : "false");
    return ESP_OK;
}
