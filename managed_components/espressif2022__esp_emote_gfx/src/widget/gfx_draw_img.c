/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "core/gfx_core.h"
#include "core/gfx_obj.h"
#include "widget/gfx_img.h"
#include "widget/gfx_img_internal.h"
#include "core/gfx_blend_internal.h"
#include "widget/gfx_comm.h"
#include "widget/gfx_font_internal.h"
#include "core/gfx_obj_internal.h"
#include "decoder/gfx_img_dec.h"

static const char *TAG = "gfx_img";

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

void gfx_draw_img(gfx_obj_t *obj, int x1, int y1, int x2, int y2, const void *dest_buf, bool swap)
{
    if (obj == NULL || obj->src == NULL) {
        ESP_LOGD(TAG, "Invalid object or source");
        return;
    }

    if (obj->type != GFX_OBJ_TYPE_IMAGE) {
        ESP_LOGW(TAG, "Object is not an image type");
        return;
    }

    // Use unified decoder to get image information
    gfx_image_header_t header;
    gfx_image_decoder_dsc_t dsc = {
        .src = obj->src,
    };
    esp_err_t ret = gfx_image_decoder_info(&dsc, &header);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get image info");
        return;
    }

    uint16_t image_width = header.w;
    uint16_t image_height = header.h;
    uint8_t color_format = header.cf;

    // Check color format - support RGB565A8 format
    if (color_format != GFX_COLOR_FORMAT_RGB565A8) {
        ESP_LOGW(TAG, "Unsupported color format: 0x%02X, only RGB565A8 (0x%02X) is supported",
                 color_format, GFX_COLOR_FORMAT_RGB565A8);
        return;
    }

    // Get image data using unified decoder
    gfx_image_decoder_dsc_t decoder_dsc = {
        .src = obj->src,
        .header = header,
        .data = NULL,
        .data_size = 0,
        .user_data = NULL
    };

    ret = gfx_image_decoder_open(&decoder_dsc);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open image decoder");
        return;
    }

    const uint8_t *image_data = decoder_dsc.data;
    if (image_data == NULL) {
        ESP_LOGE(TAG, "No image data available");
        gfx_image_decoder_close(&decoder_dsc);
        return;
    }

    ESP_LOGD(TAG, "Drawing image: %dx%d, format: 0x%02X", image_width, image_height, color_format);

    // Get parent container dimensions for alignment calculation
    uint32_t parent_width, parent_height;
    if (obj->parent_handle != NULL) {
        esp_err_t ret = gfx_emote_get_screen_size(obj->parent_handle, &parent_width, &parent_height);
        if (ret != ESP_OK) {
            ESP_LOGW(TAG, "Failed to get screen size, using defaults");
            parent_width = DEFAULT_SCREEN_WIDTH;
            parent_height = DEFAULT_SCREEN_HEIGHT;
        }
    } else {
        parent_width = DEFAULT_SCREEN_WIDTH;
        parent_height = DEFAULT_SCREEN_HEIGHT;
    }

    gfx_coord_t obj_x = obj->x;
    gfx_coord_t obj_y = obj->y;

    gfx_obj_calculate_aligned_position(obj, parent_width, parent_height, &obj_x, &obj_y);

    gfx_area_t clip_region;
    clip_region.x1 = MAX(x1, obj_x);
    clip_region.y1 = MAX(y1, obj_y);
    clip_region.x2 = MIN(x2, obj_x + image_width);
    clip_region.y2 = MIN(y2, obj_y + image_height);

    // Check if there's any overlap
    if (clip_region.x1 >= clip_region.x2 || clip_region.y1 >= clip_region.y2) {
        gfx_image_decoder_close(&decoder_dsc);
        return;
    }

    gfx_coord_t dest_buffer_stride = (x2 - x1);
    gfx_coord_t source_buffer_stride = image_width;

    // Calculate data pointers based on format
    gfx_color_t *source_pixels = (gfx_color_t *)(image_data + (clip_region.y1 - obj_y) * source_buffer_stride * 2);
    gfx_opa_t *alpha_mask = (gfx_opa_t *)(image_data + source_buffer_stride * image_height * 2 + (clip_region.y1 - obj_y) * source_buffer_stride);
    gfx_color_t *dest_pixels = (gfx_color_t *)dest_buf + (clip_region.y1 - y1) * dest_buffer_stride + (clip_region.x1 - x1);

    gfx_sw_blend_img_draw(
        dest_pixels,
        dest_buffer_stride,
        source_pixels,
        source_buffer_stride,
        alpha_mask,
        source_buffer_stride,
        &clip_region,
        255,
        swap
    );

    // Close decoder
    gfx_image_decoder_close(&decoder_dsc);
}
