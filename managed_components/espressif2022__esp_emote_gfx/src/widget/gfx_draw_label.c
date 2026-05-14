/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"
#include "core/gfx_types.h"
#include "core/gfx_obj.h"
#include "core/gfx_timer.h"
#include "core/gfx_blend_internal.h"
#include "core/gfx_obj_internal.h"
#include "core/gfx_core_internal.h"
#include "widget/gfx_comm.h"
#include "widget/gfx_label.h"
#include "widget/gfx_label_internal.h"
#include "widget/gfx_font_internal.h"

static const char *TAG = "gfx_label";

static esp_err_t gfx_parse_text_lines(gfx_obj_t *obj, void *font_ctx, int total_line_height,
                                      char ***ret_lines, int *ret_line_count, int *ret_text_width, int **ret_line_widths);
static esp_err_t gfx_render_lines_to_mask(gfx_obj_t *obj, gfx_opa_t *mask, char **lines, int line_count,
        void *font_ctx, int line_height, int base_line,
        int total_line_height, int *cached_line_widths);

void gfx_label_clear_cached_lines(gfx_label_t *label)
{
    if (label->lines) {
        for (int i = 0; i < label->line_count; i++) {
            if (label->lines[i]) {
                free(label->lines[i]);
            }
        }
        free(label->lines);
        label->lines = NULL;
        label->line_count = 0;
    }

    if (label->line_widths) {
        free(label->line_widths);
        label->line_widths = NULL;
    }
}

/**
 * @brief Convert UTF-8 string to Unicode code point for LVGL font processing
 * @param p Pointer to the current position in the string (updated after conversion)
 * @param unicode Pointer to store the Unicode code point
 * @return Number of bytes consumed from the string, or 0 on error
 */
static int gfx_utf8_to_unicode(const char **p, uint32_t *unicode)
{
    const char *ptr = *p;
    uint8_t c = (uint8_t) * ptr;
    int bytes_in_char = 1;

    if (c < 0x80) {
        *unicode = c;
    } else if ((c & 0xE0) == 0xC0) {
        bytes_in_char = 2;
        if (*(ptr + 1) == 0) {
            return 0;
        }
        *unicode = ((c & 0x1F) << 6) | (*(ptr + 1) & 0x3F);
    } else if ((c & 0xF0) == 0xE0) {
        bytes_in_char = 3;
        if (*(ptr + 1) == 0 || *(ptr + 2) == 0) {
            return 0;
        }
        *unicode = ((c & 0x0F) << 12) | ((*(ptr + 1) & 0x3F) << 6) | (*(ptr + 2) & 0x3F);
    } else if ((c & 0xF8) == 0xF0) {
        bytes_in_char = 4;
        if (*(ptr + 1) == 0 || *(ptr + 2) == 0 || *(ptr + 3) == 0) {
            return 0;
        }
        *unicode = ((c & 0x07) << 18) | ((*(ptr + 1) & 0x3F) << 12) |
                   ((*(ptr + 2) & 0x3F) << 6) | (*(ptr + 3) & 0x3F);
    } else {
        *unicode = 0xFFFD;
        bytes_in_char = 1;
    }

    *p += bytes_in_char;
    return bytes_in_char;
}

static void gfx_label_scroll_timer_callback(void *arg)
{
    gfx_obj_t *obj = (gfx_obj_t *)arg;
    if (!obj || obj->type != GFX_OBJ_TYPE_LABEL) {
        return;
    }

    gfx_label_t *label = (gfx_label_t *)obj->src;
    if (!label || !label->scrolling || label->long_mode != GFX_LABEL_LONG_SCROLL) {
        return;
    }

    label->scroll_offset++;

    if (label->scroll_loop) {
        if (label->scroll_offset > label->text_width) {
            label->scroll_offset = -obj->width;
        }
    } else {
        if (label->scroll_offset > label->text_width) {
            label->scrolling = false;
            gfx_timer_pause(label->scroll_timer);
            return;
        }
    }

    label->scroll_changed = true;
    obj->is_dirty = true;
}

esp_err_t gfx_label_set_font(gfx_obj_t *obj, gfx_font_t font)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");
    gfx_label_t *label = (gfx_label_t *)obj->src;

    if (label->font_ctx) {
        free(label->font_ctx);
        label->font_ctx = NULL;
    }

    if (font) {
        gfx_font_ctx_t *font_ctx = (gfx_font_ctx_t *)calloc(1, sizeof(gfx_font_ctx_t));
        if (font_ctx) {
            if (gfx_is_lvgl_font(font)) {
                gfx_font_lv_init_context(font_ctx, font);
            } else {
#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
                gfx_font_ft_init_context(font_ctx, font);
#else
                ESP_LOGW(TAG, "FreeType font detected but support is not enabled");
                free(font_ctx);
                font_ctx = NULL;
#endif
            }

            label->font_ctx = font_ctx;
        } else {
            ESP_LOGW(TAG, "Failed to allocate unified font interface");
        }
    }

    obj->is_dirty = true;
    return ESP_OK;
}

esp_err_t gfx_label_set_text(gfx_obj_t *obj, const char *text)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;

    if (text == NULL) {
        text = label->text;
    }

    if (label->text == text) {
        label->text = realloc(label->text, strlen(label->text) + 1);
        assert(label->text);
        if (label->text == NULL) {
            return ESP_FAIL;
        }
    } else {
        if (label->text != NULL) {
            free(label->text);
            label->text = NULL;
        }

        size_t len = strlen(text) + 1;

        label->text = malloc(len);
        assert(label->text);
        if (label->text == NULL) {
            return ESP_FAIL;
        }
        strcpy(label->text, text);
    }

    obj->is_dirty = true;

    gfx_label_clear_cached_lines(label);

    if (label->long_mode == GFX_LABEL_LONG_SCROLL) {
        if (label->scrolling) {
            label->scrolling = false;
            if (label->scroll_timer) {
                gfx_timer_pause(label->scroll_timer);
            }
        }
        label->scroll_offset = 0;
        label->text_width = 0;
    }

    label->scroll_changed = false;

    return ESP_OK;
}

esp_err_t gfx_label_set_text_fmt(gfx_obj_t *obj, const char *fmt, ...)
{
    ESP_RETURN_ON_FALSE(obj && fmt, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;

    if (label->text != NULL) {
        free(label->text);
        label->text = NULL;
    }

    va_list args;
    va_start(args, fmt);

    /*Allocate space for the new text by using trick from C99 standard section 7.19.6.12*/
    va_list args_copy;
    va_copy(args_copy, args);
    uint32_t len = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);

    label->text = malloc(len + 1);
    if (label->text == NULL) {
        va_end(args);
        return ESP_ERR_NO_MEM;
    }
    label->text[len] = '\0';

    vsnprintf(label->text, len + 1, fmt, args);
    va_end(args);

    obj->is_dirty = true;

    return ESP_OK;
}

esp_err_t gfx_label_set_opa(gfx_obj_t *obj, gfx_opa_t opa)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    label->opa = opa;
    ESP_LOGD(TAG, "set font opa: %d", label->opa);

    return ESP_OK;
}

esp_err_t gfx_label_set_color(gfx_obj_t *obj, gfx_color_t color)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    label->color = color;
    ESP_LOGD(TAG, "set font color: %d", label->color.full);

    return ESP_OK;
}

esp_err_t gfx_label_set_bg_color(gfx_obj_t *obj, gfx_color_t bg_color)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    label->bg_color = bg_color;
    ESP_LOGD(TAG, "set background color: %d", label->bg_color.full);

    return ESP_OK;
}

esp_err_t gfx_label_set_bg_enable(gfx_obj_t *obj, bool enable)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    label->bg_enable = enable;
    obj->is_dirty = true;
    ESP_LOGD(TAG, "set background enable: %s", enable ? "enabled" : "disabled");

    return ESP_OK;
}

esp_err_t gfx_label_set_text_align(gfx_obj_t *obj, gfx_text_align_t align)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    label->text_align = align;
    obj->is_dirty = true;
    ESP_LOGD(TAG, "set text align: %d", align);

    return ESP_OK;
}

esp_err_t gfx_label_set_long_mode(gfx_obj_t *obj, gfx_label_long_mode_t long_mode)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    ESP_RETURN_ON_FALSE(label, ESP_ERR_INVALID_STATE, TAG, "label property is NULL");

    gfx_label_long_mode_t old_mode = label->long_mode;
    label->long_mode = long_mode;

    if (old_mode != long_mode) {
        if (label->scrolling) {
            label->scrolling = false;
            if (label->scroll_timer) {
                gfx_timer_pause(label->scroll_timer);
            }
        }
        label->scroll_offset = 0;
        label->text_width = 0;

        if (long_mode == GFX_LABEL_LONG_SCROLL && !label->scroll_timer) {
            label->scroll_timer = gfx_timer_create(obj->parent_handle,
                                                   gfx_label_scroll_timer_callback,
                                                   label->scroll_speed,
                                                   obj);
            if (label->scroll_timer) {
                gfx_timer_set_repeat_count(label->scroll_timer, -1);
            }
        } else if (long_mode != GFX_LABEL_LONG_SCROLL && label->scroll_timer) {
            gfx_timer_delete(obj->parent_handle, label->scroll_timer);
            label->scroll_timer = NULL;
        }

        obj->is_dirty = true;
    }

    label->scroll_changed = false;

    ESP_LOGD(TAG, "set long mode: %d", long_mode);
    return ESP_OK;
}

esp_err_t gfx_label_set_line_spacing(gfx_obj_t *obj, uint16_t spacing)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    label->line_spacing = spacing;
    obj->is_dirty = true;
    ESP_LOGD(TAG, "set line spacing: %d", spacing);

    return ESP_OK;
}

esp_err_t gfx_label_set_scroll_speed(gfx_obj_t *obj, uint32_t speed_ms)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");
    ESP_RETURN_ON_FALSE(speed_ms > 0, ESP_ERR_INVALID_ARG, TAG, "invalid speed");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    ESP_RETURN_ON_FALSE(label, ESP_ERR_INVALID_STATE, TAG, "label property is NULL");

    label->scroll_speed = speed_ms;

    if (label->scroll_timer) {
        gfx_timer_set_period(label->scroll_timer, speed_ms);
    }

    ESP_LOGD(TAG, "set scroll speed: %"PRIu32" ms", speed_ms);
    return ESP_OK;
}

esp_err_t gfx_label_set_scroll_loop(gfx_obj_t *obj, bool loop)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    ESP_RETURN_ON_FALSE(label, ESP_ERR_INVALID_STATE, TAG, "label property is NULL");

    label->scroll_loop = loop;
    ESP_LOGD(TAG, "set scroll loop: %s", loop ? "enabled" : "disabled");

    return ESP_OK;
}

static esp_err_t gfx_parse_text_lines(gfx_obj_t *obj, void *font_ctx, int total_line_height,
                                      char ***ret_lines, int *ret_line_count, int *ret_text_width, int **ret_line_widths)
{
    gfx_label_t *label = (gfx_label_t *)obj->src;

    int total_text_width = 0;
    const char *p_width = label->text;

    while (*p_width) {
        uint32_t unicode = 0;
        int bytes_in_char = gfx_utf8_to_unicode(&p_width, &unicode);
        if (bytes_in_char == 0) {
            p_width++;
            continue;
        }

        gfx_font_ctx_t *font = (gfx_font_ctx_t *)font_ctx;
        int glyph_width = font->get_glyph_width(font, unicode);
        total_text_width += glyph_width;

        if (*(p_width - bytes_in_char) == '\n') {
            break;
        }
    }

    *ret_text_width = total_text_width;

    const char *text = label->text;
    int max_lines = obj->height / total_line_height;
    if (max_lines <= 0) {
        max_lines = 1;
    }

    char **lines = (char **)malloc(max_lines * sizeof(char *));
    if (!lines) {
        return ESP_ERR_NO_MEM;
    }

    for (int i = 0; i < max_lines; i++) {
        lines[i] = NULL;
    }

    int *line_widths = NULL;
    if (ret_line_widths) {
        line_widths = (int *)malloc(max_lines * sizeof(int));
        if (!line_widths) {
            free(lines);
            return ESP_ERR_NO_MEM;
        }
        for (int i = 0; i < max_lines; i++) {
            line_widths[i] = 0;
        }
    }

    int line_count = 0;

    if (label->long_mode == GFX_LABEL_LONG_WRAP) {
        const char *line_start = text;
        while (*line_start && line_count < max_lines) {
            const char *line_end = line_start;
            int line_width = 0;
            const char *last_space = NULL;

            while (*line_end) {
                uint32_t unicode = 0;
                uint8_t c = (uint8_t) * line_end;
                int bytes_in_char;
                int char_width = 0;

                bytes_in_char = gfx_utf8_to_unicode(&line_end, &unicode);
                if (bytes_in_char == 0) {
                    break;
                }

                gfx_font_ctx_t *font = (gfx_font_ctx_t *)font_ctx;
                char_width = font->get_glyph_width(font, unicode);

                if (line_width + char_width > obj->width) {
                    if (last_space && last_space > line_start) {
                        line_end = last_space;
                    } else {
                        line_end -= bytes_in_char;
                    }
                    break;
                }

                line_width += char_width;

                if (c == ' ') {
                    last_space = line_end - bytes_in_char;
                }

                if (c == '\n') {
                    break;
                }
            }

            int line_len = line_end - line_start;
            if (line_len > 0) {
                lines[line_count] = (char *)malloc(line_len + 1);
                if (!lines[line_count]) {
                    for (int i = 0; i < line_count; i++) {
                        if (lines[i]) {
                            free(lines[i]);
                        }
                    }
                    free(lines);
                    if (line_widths) {
                        free(line_widths);
                    }
                    return ESP_ERR_NO_MEM;
                }
                memcpy(lines[line_count], line_start, line_len);
                lines[line_count][line_len] = '\0';

                if (line_widths) {
                    line_widths[line_count] = line_width;
                }

                line_count++;
            }

            line_start = line_end;
            if (*line_start == ' ' || *line_start == '\n') {
                line_start++;
            }
        }
    } else {
        const char *line_start = text;
        const char *line_end = text;

        while (*line_end && line_count < max_lines) {
            if (*line_end == '\n' || *(line_end + 1) == '\0') {
                int line_len = line_end - line_start;
                if (*line_end != '\n') {
                    line_len++;
                }

                if (line_len > 0) {
                    lines[line_count] = (char *)malloc(line_len + 1);
                    if (!lines[line_count]) {
                        for (int i = 0; i < line_count; i++) {
                            if (lines[i]) {
                                free(lines[i]);
                            }
                        }
                        free(lines);
                        if (line_widths) {
                            free(line_widths);
                        }
                        return ESP_ERR_NO_MEM;
                    }
                    memcpy(lines[line_count], line_start, line_len);
                    lines[line_count][line_len] = '\0';

                    if (line_widths) {
                        int current_line_width = 0;
                        const char *p_calc = lines[line_count];
                        while (*p_calc) {
                            uint32_t unicode = 0;
                            int bytes_consumed = gfx_utf8_to_unicode(&p_calc, &unicode);
                            if (bytes_consumed == 0) {
                                p_calc++;
                                continue;
                            }

                            gfx_font_ctx_t *font = (gfx_font_ctx_t *)font_ctx;
                            int glyph_width = font->get_glyph_width(font, unicode);
                            current_line_width += glyph_width;
                        }
                        line_widths[line_count] = current_line_width;
                    }

                    line_count++;
                }

                line_start = line_end + 1;
            }
            line_end++;
        }
    }

    *ret_lines = lines;
    *ret_line_count = line_count;

    if (ret_line_widths) {
        *ret_line_widths = line_widths;
    }

    return ESP_OK;
}

static int gfx_calculate_line_width(const char *line_text, gfx_font_ctx_t *font)
{
    int line_width = 0;
    const char *p = line_text;

    while (*p) {
        uint32_t unicode = 0;
        int bytes_consumed = gfx_utf8_to_unicode(&p, &unicode);
        if (bytes_consumed == 0) {
            p++;
            continue;
        }

        line_width += font->get_glyph_width(font, unicode);
    }

    return line_width;
}

static int gfx_calculate_text_start_x(gfx_text_align_t align, int obj_width, int line_width)
{
    int start_x = 0;

    switch (align) {
    case GFX_TEXT_ALIGN_LEFT:
    case GFX_TEXT_ALIGN_AUTO:
        start_x = 0;
        break;
    case GFX_TEXT_ALIGN_CENTER:
        start_x = (obj_width - line_width) / 2;
        break;
    case GFX_TEXT_ALIGN_RIGHT:
        start_x = obj_width - line_width;
        break;
    }

    return start_x < 0 ? 0 : start_x;
}

static void gfx_render_glyph_to_mask(gfx_opa_t *mask, int obj_width, int obj_height,
                                     gfx_font_ctx_t *font, uint32_t unicode,
                                     const gfx_glyph_dsc_t *glyph_dsc,
                                     const uint8_t *glyph_bitmap, int x, int y)
{
    int ofs_x = glyph_dsc->ofs_x;
    int ofs_y = font->adjust_baseline_offset(font, (void *)glyph_dsc);

    for (int32_t iy = 0; iy < glyph_dsc->box_h; iy++) {
        for (int32_t ix = 0; ix < glyph_dsc->box_w; ix++) {
            int32_t pixel_x = ix + x + ofs_x;
            int32_t pixel_y = iy + y + ofs_y;

            if (pixel_x >= 0 && pixel_x < obj_width && pixel_y >= 0 && pixel_y < obj_height) {
                uint8_t pixel_value = font->get_pixel_value(font, glyph_bitmap, ix, iy, glyph_dsc->box_w);
                *(mask + pixel_y * obj_width + pixel_x) = pixel_value;
            }
        }
    }
}

static esp_err_t gfx_render_line_to_mask(gfx_obj_t *obj, gfx_opa_t *mask, const char *line_text,
        gfx_font_ctx_t *font, int line_width, int y_pos)
{
    gfx_label_t *label = (gfx_label_t *)obj->src;

    int start_x = gfx_calculate_text_start_x(label->text_align, obj->width, line_width);

    if (label->long_mode == GFX_LABEL_LONG_SCROLL && label->scrolling) {
        start_x -= label->scroll_offset;
    }

    int x = start_x;
    const char *p = line_text;

    while (*p) {
        uint32_t unicode = 0;
        int bytes_consumed = gfx_utf8_to_unicode(&p, &unicode);
        if (bytes_consumed == 0) {
            p++;
            continue;
        }

        gfx_glyph_dsc_t glyph_dsc;
        const uint8_t *glyph_bitmap = NULL;

        if (!font->get_glyph_dsc(font, &glyph_dsc, unicode, 0)) {
            continue;
        }

        glyph_bitmap = font->get_glyph_bitmap(font, unicode, &glyph_dsc);
        if (!glyph_bitmap) {
            continue;
        }

        gfx_render_glyph_to_mask(mask, obj->width, obj->height, font, unicode,
                                 &glyph_dsc, glyph_bitmap, x, y_pos);

        x += font->get_advance_width(font, &glyph_dsc);

        if (x >= obj->width) {
            break;
        }
    }

    return ESP_OK;
}

static esp_err_t gfx_render_lines_to_mask(gfx_obj_t *obj, gfx_opa_t *mask, char **lines, int line_count,
        void *font_ctx, int line_height, int base_line,
        int total_line_height, int *cached_line_widths)
{
    gfx_font_ctx_t *font = (gfx_font_ctx_t *)font_ctx;
    int current_y = 0;

    for (int line_idx = 0; line_idx < line_count; line_idx++) {
        if (current_y + line_height > obj->height) {
            break;
        }

        const char *line_text = lines[line_idx];
        int line_width;

        if (cached_line_widths) {
            line_width = cached_line_widths[line_idx];
        } else {
            line_width = gfx_calculate_line_width(line_text, font);
        }

        gfx_render_line_to_mask(obj, mask, line_text, font, line_width, current_y);

        current_y += total_line_height;
    }

    return ESP_OK;
}

static bool gfx_can_use_cached_data(gfx_label_t *label, gfx_obj_t *obj)
{
    return (label->long_mode == GFX_LABEL_LONG_SCROLL &&
            label->lines != NULL &&
            label->line_widths != NULL &&
            label->line_count > 0 &&
            label->mask != NULL &&
            !obj->is_dirty &&
            label->scroll_changed);
}

static gfx_opa_t *gfx_allocate_mask_buffer(gfx_obj_t *obj, gfx_label_t *label)
{
    if (label->mask) {
        free(label->mask);
        label->mask = NULL;
    }

    gfx_opa_t *mask_buf = (gfx_opa_t *)malloc(obj->width * obj->height);
    if (!mask_buf) {
        ESP_LOGE(TAG, "Failed to allocate mask buffer");
        return NULL;
    }

    memset(mask_buf, 0x00, obj->height * obj->width);
    return mask_buf;
}

static esp_err_t gfx_cache_line_data(gfx_label_t *label, char **lines,
                                     int line_count, int *line_widths)
{
    if (label->long_mode != GFX_LABEL_LONG_SCROLL || line_count <= 0) {
        return ESP_OK;
    }

    gfx_label_clear_cached_lines(label);

    label->lines = (char **)malloc(line_count * sizeof(char *));
    label->line_widths = (int *)malloc(line_count * sizeof(int));

    if (!label->lines || !label->line_widths) {
        ESP_LOGE(TAG, "Failed to allocate cache memory");
        return ESP_ERR_NO_MEM;
    }

    label->line_count = line_count;
    for (int i = 0; i < line_count; i++) {
        if (lines[i]) {
            size_t len = strlen(lines[i]) + 1;
            label->lines[i] = (char *)malloc(len);
            if (label->lines[i]) {
                strcpy(label->lines[i], lines[i]);
            }
        } else {
            label->lines[i] = NULL;
        }
        label->line_widths[i] = line_widths[i];
    }

    ESP_LOGD(TAG, "Cached %d lines with widths for scroll optimization", line_count);
    return ESP_OK;
}

static void gfx_cleanup_line_data(char **lines, int line_count, int *line_widths)
{
    if (lines) {
        for (int i = 0; i < line_count; i++) {
            if (lines[i]) {
                free(lines[i]);
            }
        }
        free(lines);
    }

    if (line_widths) {
        free(line_widths);
    }
}

static void gfx_update_scroll_state(gfx_label_t *label, gfx_obj_t *obj)
{
    if (label->long_mode == GFX_LABEL_LONG_SCROLL && label->text_width > obj->width) {
        if (!label->scrolling) {
            label->scrolling = true;
            if (label->scroll_timer) {
                gfx_timer_reset(label->scroll_timer);
                gfx_timer_resume(label->scroll_timer);
            }
        }
    } else if (label->scrolling) {
        label->scrolling = false;
        if (label->scroll_timer) {
            gfx_timer_pause(label->scroll_timer);
        }
        label->scroll_offset = 0;
    }
}

static esp_err_t gfx_render_from_cache(gfx_obj_t *obj, gfx_opa_t *mask,
                                       gfx_label_t *label, void *font_ctx)
{
    gfx_font_ctx_t *font = (gfx_font_ctx_t *)font_ctx;
    int line_height = font->get_line_height(font);
    int base_line = font->get_base_line(font);
    int total_line_height = line_height + label->line_spacing;

    ESP_LOGD(TAG, "Reusing %d cached lines for scroll", label->line_count);

    return gfx_render_lines_to_mask(obj, mask, label->lines,
                                    label->line_count, font_ctx,
                                    line_height, base_line, total_line_height,
                                    label->line_widths);
}

static esp_err_t gfx_render_from_parsed_data(gfx_obj_t *obj, gfx_opa_t *mask,
        gfx_label_t *label,
        void *font_ctx, gfx_opa_t *mask_buf)
{
    gfx_font_ctx_t *font = (gfx_font_ctx_t *)font_ctx;
    int line_height = font->get_line_height(font);
    int base_line = font->get_base_line(font);
    int total_line_height = line_height + label->line_spacing;

    char **lines = NULL;
    int line_count = 0;
    int *line_widths = NULL;
    int total_text_width = 0;

    esp_err_t parse_ret = gfx_parse_text_lines(obj, font_ctx, total_line_height,
                          &lines, &line_count, &total_text_width, &line_widths);
    if (parse_ret != ESP_OK) {
        free(mask_buf);
        return parse_ret;
    }

    label->text_width = total_text_width;

    esp_err_t cache_ret = gfx_cache_line_data(label, lines, line_count, line_widths);
    if (cache_ret != ESP_OK) {
        ESP_LOGW(TAG, "Failed to cache line data, continuing without cache");
    }

    esp_err_t render_ret = gfx_render_lines_to_mask(obj, mask, lines, line_count,
                           font_ctx, line_height, base_line,
                           total_line_height, line_widths);
    if (render_ret != ESP_OK) {
        gfx_cleanup_line_data(lines, line_count, line_widths);
        free(mask_buf);
        return render_ret;
    }

    gfx_cleanup_line_data(lines, line_count, line_widths);
    return ESP_OK;
}

esp_err_t gfx_get_glphy_dsc(gfx_obj_t *obj)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    void *font_ctx = label->font_ctx;
    if (font_ctx == NULL) {
        ESP_LOGI(TAG, "font context is NULL");
        return ESP_OK;
    }

    bool can_use_cached = gfx_can_use_cached_data(label, obj);

    if (label->mask && !obj->is_dirty && !can_use_cached) {
        return ESP_OK;
    }

    gfx_opa_t *mask_buf = gfx_allocate_mask_buffer(obj, label);
    ESP_RETURN_ON_FALSE(mask_buf, ESP_ERR_NO_MEM, TAG, "no mem for mask_buf");

    esp_err_t render_ret;
    if (can_use_cached) {
        render_ret = gfx_render_from_cache(obj, mask_buf, label, font_ctx);
    } else {
        render_ret = gfx_render_from_parsed_data(obj, mask_buf, label, font_ctx, mask_buf);
    }

    if (render_ret != ESP_OK) {
        free(mask_buf);
        return render_ret;
    }

    label->mask = mask_buf;
    obj->is_dirty = false;
    label->scroll_changed = false;

    gfx_update_scroll_state(label, obj);

    return ESP_OK;
}

/**
 * @brief Blend label object to destination buffer
 *
 * @param obj Graphics object containing label data
 * @param x1 Left boundary of destination area
 * @param y1 Top boundary of destination area
 * @param x2 Right boundary of destination area
 * @param y2 Bottom boundary of destination area
 * @param dest_buf Destination buffer for blending
 */
esp_err_t gfx_draw_label(gfx_obj_t *obj, int x1, int y1, int x2, int y2, const void *dest_buf, bool swap)
{
    ESP_RETURN_ON_FALSE(obj, ESP_ERR_INVALID_ARG, TAG, "invalid handle");

    gfx_label_t *label = (gfx_label_t *)obj->src;
    if (label->text == NULL) {
        ESP_LOGI(TAG, "text is NULL");
        return ESP_ERR_INVALID_ARG;
    }

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
    clip_region.x2 = MIN(x2, obj_x + obj->width);
    clip_region.y2 = MIN(y2, obj_y + obj->height);

    if (clip_region.x1 >= clip_region.x2 || clip_region.y1 >= clip_region.y2) {
        return ESP_ERR_INVALID_STATE;
    }

    if (label->bg_enable) {
        gfx_color_t *dest_pixels = (gfx_color_t *)dest_buf;
        gfx_coord_t buffer_width = (x2 - x1);
        gfx_color_t bg_color = label->bg_color;

        if (swap) {
            bg_color.full = __builtin_bswap16(bg_color.full);
        }

        for (int y = clip_region.y1; y < clip_region.y2; y++) {
            for (int x = clip_region.x1; x < clip_region.x2; x++) {
                int pixel_index = (y - y1) * buffer_width + (x - x1);
                dest_pixels[pixel_index] = bg_color;
            }
        }
    }

    gfx_get_glphy_dsc(obj);
    if (!label->mask) {
        return ESP_ERR_INVALID_STATE;
    }

    gfx_color_t *dest_pixels = (gfx_color_t *)dest_buf + (clip_region.y1 - y1) * (x2 - x1) + (clip_region.x1 - x1);
    gfx_coord_t dest_buffer_stride = (x2 - x1);
    gfx_coord_t mask_offset_y = (clip_region.y1 - obj_y);

    gfx_opa_t *mask = label->mask;
    gfx_coord_t mask_stride = obj->width;
    mask += mask_offset_y * mask_stride;

    gfx_color_t color = label->color;
    if (swap) {
        color.full = __builtin_bswap16(color.full);
    }

    gfx_sw_blend_draw(dest_pixels, dest_buffer_stride, color, label->opa, mask, &clip_region, mask_stride, swap);

    return ESP_OK;
}
