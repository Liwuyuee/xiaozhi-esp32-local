/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_ra8875.h"
#include "display.h"

/* Display */
#define BSP_LCD_DB0     (13)
#define BSP_LCD_DB1     (12)
#define BSP_LCD_DB2     (11)
#define BSP_LCD_DB3     (10)
#define BSP_LCD_DB4     (9)
#define BSP_LCD_DB5     (46)
#define BSP_LCD_DB6     (3)
#define BSP_LCD_DB7     (8)
#define BSP_LCD_DB8     (18)
#define BSP_LCD_DB9     (17)
#define BSP_LCD_DB10    (16)
#define BSP_LCD_DB11    (15)
#define BSP_LCD_DB12    (7)
#define BSP_LCD_DB13    (6)
#define BSP_LCD_DB14    (5)
#define BSP_LCD_DB15    (4)
#define BSP_LCD_CS      (-1)
#define BSP_LCD_DC      (37)
#define BSP_LCD_WR      (38)
#define BSP_LCD_RD      (-1)
#define BSP_LCD_RST     (39)
#define BSP_LCD_WAIT    (1)
#define BSP_LCD_BL      (-1)
#define BSP_LCD_TP_INT  (2)

// Bit number used to represent command and parameter
#define LCD_CMD_BITS           16
#define LCD_PARAM_BITS         8
#define BSP_LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)
#define BSP_LCD_WIDTH   (16)

static const char *TAG = "display";

esp_err_t bsp_display_new(const bsp_display_config_t *config, esp_lcd_panel_handle_t *ret_panel, esp_lcd_panel_io_handle_t *ret_io)
{
    esp_err_t ret = ESP_OK;

    ESP_LOGD(TAG, "Initialize Intel 8080 bus");
    /* Init Intel 8080 bus */
    esp_lcd_i80_bus_handle_t i80_bus = NULL;
    esp_lcd_i80_bus_config_t bus_config = {
        .clk_src = LCD_CLK_SRC_PLL160M,
        .dc_gpio_num = BSP_LCD_DC,
        .wr_gpio_num = BSP_LCD_WR,
        .data_gpio_nums = {
            BSP_LCD_DB0,
            BSP_LCD_DB1,
            BSP_LCD_DB2,
            BSP_LCD_DB3,
            BSP_LCD_DB4,
            BSP_LCD_DB5,
            BSP_LCD_DB6,
            BSP_LCD_DB7,
            BSP_LCD_DB8,
            BSP_LCD_DB9,
            BSP_LCD_DB10,
            BSP_LCD_DB11,
            BSP_LCD_DB12,
            BSP_LCD_DB13,
            BSP_LCD_DB14,
            BSP_LCD_DB15,
        },
        .bus_width = BSP_LCD_WIDTH,
        .max_transfer_bytes = config->max_transfer_sz,
        .dma_burst_size = 64,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_i80_bus(&bus_config, &i80_bus), TAG, "I80 init failed");

    ESP_LOGD(TAG, "Install panel IO");
    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = BSP_LCD_CS,
        .pclk_hz = BSP_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 10,
        .dc_levels = {
            .dc_idle_level = 0,
            .dc_cmd_level = 1,
            .dc_dummy_level = 0,
            .dc_data_level = 0,
        },
        .flags = {
            .swap_color_bytes = 1,
            .pclk_idle_low = 0,
        },
        .lcd_cmd_bits = LCD_CMD_BITS,
        .lcd_param_bits = LCD_PARAM_BITS,
    };
    ESP_GOTO_ON_ERROR(esp_lcd_new_panel_io_i80(i80_bus, &io_config, ret_io), err, TAG, "New panel IO failed");

    ESP_LOGD(TAG, "Install LCD driver of RA8875");
    const esp_lcd_panel_ra8875_config_t vendor_config = {
        .wait_gpio_num = BSP_LCD_WAIT,
        .lcd_width = BSP_LCD_H_RES,
        .lcd_height = BSP_LCD_V_RES,
        .mcu_bit_interface = BSP_LCD_WIDTH,
    };
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = BSP_LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
        .vendor_config = (void *) &vendor_config,
    };
    ESP_GOTO_ON_ERROR(esp_lcd_new_panel_ra8875(*ret_io, &panel_config, ret_panel), err, TAG, "New panel RA8875 failed");

    ESP_GOTO_ON_ERROR(esp_lcd_panel_reset(*ret_panel), err, TAG, "");
    ESP_GOTO_ON_ERROR(esp_lcd_panel_init(*ret_panel), err, TAG, "");
    ESP_GOTO_ON_ERROR(esp_lcd_panel_disp_on_off(*ret_panel, true), err, TAG, "");
    return ret;

err:
    if (*ret_panel) {
        esp_lcd_panel_del(*ret_panel);
    }
    if (*ret_io) {
        esp_lcd_panel_io_del(*ret_io);
    }
    if (i80_bus) {
        esp_lcd_del_i80_bus(i80_bus);
    }
    return ret;
}
