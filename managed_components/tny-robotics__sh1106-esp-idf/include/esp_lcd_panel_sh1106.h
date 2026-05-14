/*
 * SH1106 ESP-IDF Driver by TNY Robotics
 *
 * SPDX-FileCopyrightText: 2025 TNY Robotics
 * SPDX-License-Identifier: MIT
 * 
 * 
 * Copyright (C) 2025 TNY Robotics
 * 
 * This file is part of the SH1106 ESP-IDF driver.
 * 
 * License: MIT
 * Repository: https://github.com/tny-robotics/sh1106-esp-idf
 * 
 * Author: TNY Robotics
 * Date: 13/02/2025
 * Version: 1.0
 */

#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "esp_lcd_panel_dev.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SH1106_HEIGHT 64
#define SH1106_WIDTH 128
#define SH1106_PIXELS_PER_BYTE 8
#define SH1106_BUFFER_SIZE (SH1106_HEIGHT * SH1106_WIDTH / SH1106_PIXELS_PER_BYTE)
#define SH1106_I2C_ADDR 0x3C

#define ESP_SH1106_DEFAULT_IO_CONFIG {\
    .dev_addr = 0x3C,\
    .on_color_trans_done = NULL,\
    .user_ctx = NULL,\
    .control_phase_bytes = 1,\
    .dc_bit_offset = 6,\
    .lcd_cmd_bits = 8,\
    .lcd_param_bits = 8,\
    .flags = {\
        .dc_low_on_data = false,\
        .disable_control_phase = false,\
    },\
    .scl_speed_hz = 400 * 1000,\
};

/**
 * @brief sh1106 configuration structure
 *
 * To be used as esp_lcd_panel_dev_config_t.vendor_config.
 * See esp_lcd_new_panel_sh1106().
 */
typedef struct {
    // Nothing to configure
} esp_lcd_panel_sh1106_config_t;

/**
 * @brief Create LCD panel for model sh1106
 *
 * @param[in] io LCD panel IO handle
 * @param[in] panel_dev_config general panel device configuration
 * @param[out] ret_panel Returned LCD panel handle
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NO_MEM        if out of memory
 *          - ESP_OK                on success
 *
 * @note The default panel size is 128x64.
 * @note Use esp_lcd_panel_sh1106_config_t to set the correct size.
 * Example usage:
 * @code {c}
 *
 * esp_lcd_panel_sh1106_config_t sh1106_config;
 * esp_lcd_panel_dev_config_t panel_config = {
 *     <...>
 *     .vendor_config = &sh1106_config
 * };
 *
 * esp_lcd_panel_handle_t panel_handle = NULL;
 * esp_lcd_new_panel_sh1106(io_handle, &panel_config, &panel_handle);
 * @endcode
 */
esp_err_t esp_lcd_new_panel_sh1106(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel);

#ifdef __cplusplus
}
#endif
