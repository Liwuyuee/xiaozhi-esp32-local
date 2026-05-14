/*
 * SH1106 ESP-IDF Driver by TNY Robotics
 *
 * SPDX-FileCopyrightText: 2025 TNY Robotics
 * SPDX-License-Identifier: MIT
 * 
 * 
 * Copyright (C) 2025 TNY Robotics
 * 
 * This file is part of the SH1106 ESP-IDF Driver.
 * 
 * License: MIT
 * Repository: https://github.com/tny-robotics/sh1106-esp-idf
 * 
 * Author: TNY Robotics
 * Date: 13/02/2025
 * Version: 1.0
 */

#include <stdlib.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include "sdkconfig.h"
#if CONFIG_LCD_ENABLE_DEBUG_LOG
// The local log level must be defined before including esp_log.h
// Set the maximum log level for this source file
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#endif
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_lcd_panel_interface.h>
#include <esp_lcd_panel_io.h>
#include "esp_lcd_panel_sh1106.h"
#include <esp_lcd_panel_ops.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_check.h>

static const char *TAG = "lcd_panel.sh1106";

// SH1106 commands
#define SH1106_CMD_SET_CHARGE_PUMP_CTRL  0xAD
#define SH1106_CMD_SET_CHARGE_PUMP_ON    0x8B
#define SH1106_CMD_SET_CHARGE_PUMP_OFF   0x8A
#define SH1106_CMD_SET_DISPLAY_NORMAL 0xA6
#define SH1106_CMD_SET_DISPLAY_REVERSE 0xA7
#define SH1106_CMD_SET_ENTIRE_DISPLAY_OFF 0xA4
#define SH1106_CMD_SET_ENTIRE_DISPLAY_ON 0xA5
#define SH1106_CMD_SET_DISPLAY_OFF 0xAE
#define SH1106_CMD_SET_DISPLAY_ON 0xAF
#define SH1106_CMD_SET_PAGE_ADDR 0xB0
#define SH1106_CMD_SET_COLUMN_ADDR_LOW 0x00
#define SH1106_CMD_SET_COLUMN_ADDR_HIGH 0x10
#define SH1106_CMD_SET_DISPLAY_START_LINE 0x40
#define SH1106_CMD_SET_DISPLAY_OFFSET 0xD3
#define SH1106_CMD_SET_CONTRAST 0x81
#define SH1106_CMD_SET_COM_SCAN_MODE_NORMAL  0xC0
#define SH1106_CMD_SET_COM_SCAN_MODE_REVERSE 0xC8
#define SH1106_CMD_SET_SEGMENT_REMAP_INVERSE 0xA1
#define SH1106_CMD_SET_SEGMENT_REMAP_NORMAL 0xA0
#define SH1106_CMD_SET_PADS_HW_CONFIG 0xDA
#define SH1106_CMD_SET_PADS_HW_SEQUENTIAL 0x02
#define SH1106_CMD_SET_PADS_HW_ALTERNATIVE 0x12
#define SH1106_CMD_SET_MULTIPLEX_RATIO 0xA8

static esp_err_t panel_sh1106_del(esp_lcd_panel_t *panel);
static esp_err_t panel_sh1106_reset(esp_lcd_panel_t *panel);
static esp_err_t panel_sh1106_init(esp_lcd_panel_t *panel);
static esp_err_t panel_sh1106_draw_bitmap(esp_lcd_panel_t *panel, int x_start, int y_start, int x_end, int y_end, const void *color_data);
static esp_err_t panel_sh1106_invert_color(esp_lcd_panel_t *panel, bool invert_color_data);
static esp_err_t panel_sh1106_mirror(esp_lcd_panel_t *panel, bool mirror_x, bool mirror_y);
static esp_err_t panel_sh1106_swap_xy(esp_lcd_panel_t *panel, bool swap_axes);
static esp_err_t panel_sh1106_set_gap(esp_lcd_panel_t *panel, int x_gap, int y_gap);
static esp_err_t panel_sh1106_disp_on_off(esp_lcd_panel_t *panel, bool off);

typedef struct {
    esp_lcd_panel_t base;
    esp_lcd_panel_io_handle_t io;
    int reset_gpio_num;
    int x_gap;
    int y_gap;
    unsigned int bits_per_pixel;
    bool reset_level;
    bool swap_axes;
} sh1106_panel_t;

esp_err_t esp_lcd_new_panel_sh1106(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel)
{
#if CONFIG_LCD_ENABLE_DEBUG_LOG
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
#endif
    esp_err_t ret = ESP_OK;
    sh1106_panel_t *sh1106 = NULL;
    ESP_GOTO_ON_FALSE(io && panel_dev_config && ret_panel, ESP_ERR_INVALID_ARG, err, TAG, "invalid argument");
    ESP_GOTO_ON_FALSE(panel_dev_config->bits_per_pixel == 1, ESP_ERR_INVALID_ARG, err, TAG, "bpp must be 1");
    // esp_lcd_panel_sh1106_config_t *sh1106_spec_config = (esp_lcd_panel_sh1106_config_t *)panel_dev_config->vendor_config;
    // leak detection of sh1106 because saving sh1106->base address
    ESP_COMPILER_DIAGNOSTIC_PUSH_IGNORE("-Wanalyzer-malloc-leak")
    sh1106 = calloc(1, sizeof(sh1106_panel_t));
    ESP_GOTO_ON_FALSE(sh1106, ESP_ERR_NO_MEM, err, TAG, "no mem for sh1106 panel");

    if (panel_dev_config->reset_gpio_num >= 0) {
        gpio_config_t io_conf = {
            .mode = GPIO_MODE_OUTPUT,
            .pin_bit_mask = 1ULL << panel_dev_config->reset_gpio_num,
        };
        ESP_GOTO_ON_ERROR(gpio_config(&io_conf), err, TAG, "configure GPIO for RST line failed");
    }

    sh1106->io = io;
    sh1106->bits_per_pixel = panel_dev_config->bits_per_pixel;
    sh1106->reset_gpio_num = panel_dev_config->reset_gpio_num;
    sh1106->reset_level = panel_dev_config->flags.reset_active_high;
    sh1106->base.del = panel_sh1106_del;
    sh1106->base.reset = panel_sh1106_reset;
    sh1106->base.init = panel_sh1106_init;
    sh1106->base.draw_bitmap = panel_sh1106_draw_bitmap;
    sh1106->x_gap = 0;
    sh1106->y_gap = 0;
    sh1106->base.invert_color = panel_sh1106_invert_color;
    sh1106->base.set_gap = panel_sh1106_set_gap;
    sh1106->base.mirror = panel_sh1106_mirror;
    sh1106->base.swap_xy = panel_sh1106_swap_xy;
    sh1106->base.disp_on_off = panel_sh1106_disp_on_off;
    *ret_panel = &(sh1106->base);
    ESP_LOGD(TAG, "new sh1106 panel @%p", sh1106);

    return ESP_OK;

err:
    if (sh1106) {
        if (panel_dev_config->reset_gpio_num >= 0) {
            gpio_reset_pin(panel_dev_config->reset_gpio_num);
        }
        free(sh1106);
    }
    return ret;
    ESP_COMPILER_DIAGNOSTIC_POP("-Wanalyzer-malloc-leak")
}

static esp_err_t panel_sh1106_del(esp_lcd_panel_t *panel)
{
    sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    if (sh1106->reset_gpio_num >= 0) {
        gpio_reset_pin(sh1106->reset_gpio_num);
    }
    ESP_LOGD(TAG, "del sh1106 panel @%p", sh1106);
    free(sh1106);
    return ESP_OK;
}

static esp_err_t panel_sh1106_reset(esp_lcd_panel_t *panel)
{
    sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);

    // perform hardware reset
    if (sh1106->reset_gpio_num >= 0) {
        gpio_set_level(sh1106->reset_gpio_num, sh1106->reset_level);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(sh1106->reset_gpio_num, !sh1106->reset_level);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return ESP_OK;
}

static esp_err_t panel_sh1106_init(esp_lcd_panel_t *panel)
{
    sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    esp_lcd_panel_io_handle_t io = sh1106->io;

    // Enable the charge pump (DC voltage converter for OLED panel)
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_CHARGE_PUMP_CTRL, (uint8_t[1]) {
        SH1106_CMD_SET_CHARGE_PUMP_ON
    }, 1), TAG, "io tx param SH1106_CMD_SET_CHARGE_PUMP_CTRL failed");

    // Set direction of SEG and COM
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_SEGMENT_REMAP_INVERSE, NULL, 0), TAG, "io tx param SH1106_CMD_SET_SEGMENT_REMAP_INVERSE failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_COM_SCAN_MODE_REVERSE, NULL, 0), TAG, "io tx param SH1106_CMD_SET_COM_SCAN_MODE_REVERSE failed");

    // Set display start line and 0 offset
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_DISPLAY_START_LINE | 0x00, NULL, 0), TAG, "io tx param SH1106_CMD_SET_DISPLAY_START_LINE failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_DISPLAY_OFFSET, (uint8_t[1]) {
        0x00
    }, 1), TAG, "io tx param SH1106_CMD_SET_DISPLAY_OFFSET failed");

    // Set display padding to 0
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_PADS_HW_CONFIG, (uint8_t[1]) {
        SH1106_CMD_SET_PADS_HW_ALTERNATIVE
    }, 1), TAG, "io tx param SH1106_CMD_SET_PADS_HW_CONFIG failed");

    // Set multiplex ratio
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_MULTIPLEX_RATIO, (uint8_t[1]) {
        0x3F
    }, 1), TAG, "io tx param SH1106_CMD_SET_MULTIPLEX_RATIO failed");

    // Set cursor at (0, 0)
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_PAGE_ADDR | 0x00, NULL, 0), TAG, "io tx param SH1106_CMD_SET_PAGE_ADDR failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_COLUMN_ADDR_LOW | 0x00, NULL, 0), TAG, "io tx param SH1106_CMD_SET_COLUMN_ADDR_LOW failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_COLUMN_ADDR_HIGH | 0x00, NULL, 0), TAG, "io tx param SH1106_CMD_SET_COLUMN_ADDR_HIGH failed");

    // Set entire display mode OFF (using ram to display)
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_ENTIRE_DISPLAY_OFF, NULL, 0), TAG, "io tx param SH1106_CMD_SET_ENTIRE_DISPLAY_OFF failed");

    return ESP_OK;
}

static esp_err_t panel_sh1106_draw_bitmap(esp_lcd_panel_t *panel, int x_start, int y_start, int x_end, int y_end, const void *color_data)
{
    sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    esp_lcd_panel_io_handle_t io = sh1106->io;

    // For each line, shift at the line and send the bitmap line data
    for (int y = 0; y < 8; y++) {
        ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_COLUMN_ADDR_LOW | 0x02, NULL, 0), TAG, "io tx param SH1106_CMD_SET_COLUMN_ADDR_LOW failed");
        ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_COLUMN_ADDR_HIGH | 0x00, NULL, 0), TAG, "io tx param SH1106_CMD_SET_COLUMN_ADDR_HIGH failed");
        ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, SH1106_CMD_SET_PAGE_ADDR | y, NULL, 0), TAG, "io tx param SH1106_CMD_SET_PAGE_ADDR failed");
        ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_color(io, -1, color_data + y * SH1106_WIDTH, SH1106_WIDTH), TAG, "io tx color failed");
    }
    
    return ESP_OK;
}

static esp_err_t panel_sh1106_invert_color(esp_lcd_panel_t *panel, bool invert_color_data)
{
    // NOTE : Cannot invert colors on the SH1106
    // sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    // esp_lcd_panel_io_handle_t io = sh1106->io;
    // int command = 0;
    // if (invert_color_data) {
    //     command = SH1106_CMD_INVERT_ON;
    // } else {
    //     command = SH1106_CMD_INVERT_OFF;
    // }
    // ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, command, NULL, 0), TAG, "io tx param SH1106_CMD_INVERT_ON/OFF failed");
    return ESP_OK;
}

static esp_err_t panel_sh1106_mirror(esp_lcd_panel_t *panel, bool mirror_x, bool mirror_y)
{
    sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    esp_lcd_panel_io_handle_t io = sh1106->io;

    int command = 0;
    if (mirror_x) {
        command = SH1106_CMD_SET_DISPLAY_REVERSE;
    } else {
        command = SH1106_CMD_SET_DISPLAY_NORMAL;
    }
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, command, NULL, 0), TAG, "io tx param SH1106_CMD_MIRROR_X_ON/OFF failed");
    if (mirror_y) {
        command = SH1106_CMD_SET_COM_SCAN_MODE_REVERSE;
    } else {
        command = SH1106_CMD_SET_COM_SCAN_MODE_NORMAL;
    }
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, command, NULL, 0), TAG, "io tx param SH1106_CMD_MIRROR_Y_ON/OFF failed");
    return ESP_OK;
}

static esp_err_t panel_sh1106_swap_xy(esp_lcd_panel_t *panel, bool swap_axes)
{
    // sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    // sh1106->swap_axes = swap_axes;

    return ESP_OK;
}

static esp_err_t panel_sh1106_set_gap(esp_lcd_panel_t *panel, int x_gap, int y_gap)
{
    // sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    // sh1106->x_gap = x_gap;
    // sh1106->y_gap = y_gap;
    return ESP_OK;
}

static esp_err_t panel_sh1106_disp_on_off(esp_lcd_panel_t *panel, bool on_off)
{
    sh1106_panel_t *sh1106 = __containerof(panel, sh1106_panel_t, base);
    esp_lcd_panel_io_handle_t io = sh1106->io;
    int command = 0;
    if (on_off) {
        command = SH1106_CMD_SET_DISPLAY_ON;
    } else {
        command = SH1106_CMD_SET_DISPLAY_OFF;
    }
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, command, NULL, 0), TAG, "io tx param SH1106_CMD_DISP_ON/OFF failed");
    // SEG/COM will be ON/OFF after 100ms after sending DISP_ON/OFF command
    vTaskDelay(pdMS_TO_TICKS(100));
    return ESP_OK;
}
