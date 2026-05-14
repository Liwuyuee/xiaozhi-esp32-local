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

 #include "freertos/FreeRTOS.h"
#include "esp_lcd_io_i2c.h"
#include "esp_lcd_panel_sh1106.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"

#define I2C_SDA_GPIO GPIO_NUM_21
#define I2C_SCL_GPIO GPIO_NUM_22
#define I2C_HOST I2C_NUM_0

#ifdef __cplusplus
extern "C"
#endif
void app_main(void)
{
    /* I2C CONFIGURATION */

    // i2c bus configuration
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_HOST,               // I2C port number
        .sda_io_num = I2C_SDA_GPIO,         // GPIO number for I2C sda signal
        .scl_io_num = I2C_SCL_GPIO,         // GPIO number for I2C scl signal
        .clk_source = I2C_CLK_SRC_DEFAULT,  // I2C clock source, just use the default
        .glitch_ignore_cnt = 7,             // glitch filter, again, just use the default
        .intr_priority = 0,                 // interrupt priority, default to 0
        .trans_queue_depth = 0,             // transaction queue depth, default to 0
        .flags = {
            .enable_internal_pullup = true, // enable internal pullup resistors (oled screen does not have one)
            .allow_pd = false,              // just using the default value
        },
    };

    // Create the i2c bus handle
    i2c_master_bus_handle_t i2c_bus_handle = NULL;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus_handle));

    // Create the i2c io handle
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t io_config = ESP_SH1106_DEFAULT_IO_CONFIG;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(*i2c_bus_handle, &io_config, &io_handle));


    /* SCREEN CONFIGURATION */

    // sh1106 panel configuration (most of the values are not used, but must be set to avoid cpp warnings)
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = -1,                         // sh1106 does not have a reset pin, so set to -1
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,   // not even used, but must be set to avoid cpp warnings
        .data_endian = LCD_RGB_DATA_ENDIAN_LITTLE,    // not even used, but must be set to avoid cpp warnings
        .bits_per_pixel = SH1106_PIXELS_PER_BYTE / 8, // bpp = 1 (monochrome, that's important)
        .flags = {
            .reset_active_high = false,               // not even used, but must be set to avoid cpp warnings
        },
        .vendor_config = NULL,                        // no need for custom vendor config, not implemented
    };

    // Create the panel handle from the sh1106 driver
    esp_lcd_panel_handle_t panel_handle = NULL;
    ESP_ERROR_CHECK(esp_lcd_new_panel_sh1106(io_handle, &panel_config, &panel_handle));

    // Reset the screen (no reset pin, so it's a no-op here, optional)
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));

    // Initialize the screen (this one isn't optional at all!)
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    // Turn on the screen (Easier to see something, right?)
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    /* SCREEN PIXEL TEST */

    // Create a buffer to hold the screen data
    uint8_t buffer_data[SH1106_SCREEN_SIZE];
    memset(buffer_data, 0, SH1106_SCREEN_SIZE);

    // Just turn on the first top-left pixel
    // NOTE : Refer to driver README.md file for more information about the screen buffer format
    buffer_data[0] = 0b10000000;

    // Send the buffer to the screen
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, SH1106_WIDTH, SH1106_HEIGHT, buffer_data));
}