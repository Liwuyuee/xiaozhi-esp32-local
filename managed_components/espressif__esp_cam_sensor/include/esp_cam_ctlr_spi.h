/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "driver/spi_slave.h"
#include "hal/cam_types.h"
#include "esp_cam_ctlr.h"
#include "esp_cam_sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPI CAM configuration
 */
typedef struct esp_cam_ctlr_spi_config {
    spi_host_device_t spi_port;                         /*!< SPI port */
    gpio_num_t spi_cs_pin;                              /*!< SPI CS pin */
    gpio_num_t spi_sclk_pin;                            /*!< SPI SCLK pin */
    gpio_num_t spi_data0_io_pin;                        /*!< SPI data0 I/O pin */

    gpio_num_t reset_pin;                               /*!< Reset pin */
    gpio_num_t pwdn_pin;                                /*!< Power down pin */

    uint32_t h_res;                                     /*!< Input horizontal resolution, i.e. the number of pixels in a line */
    uint32_t v_res;                                     /*!< Input vertical resolution, i.e. the number of lines in a frame */

    cam_ctlr_color_t input_data_color_type;             /*!< Input pixel format */

    const esp_cam_sensor_spi_frame_info *frame_info;    /*!< Frame information */

    uint8_t frame_buffer_count;                         /*!< Number of frame buffers, this is used when auto_decode_dis=0 */

    struct {
        uint32_t bk_buffer_dis      : 1;                /*!< Disable backup buffer */
        uint32_t bk_buffer_sram     : 1;                /*!< Use SRAM for backup buffer */
        uint32_t auto_decode_dis    : 1;                /*!< Disable auto decode, letting application decode the image frame */
        uint32_t decode_check_dis   : 1;                /*!< Disable checking the image frame header and line header, just copy the image data to the destination buffer */
    };
} esp_cam_ctlr_spi_config_t;

/**
 * @brief New ESP CAM SPI controller
 *
 * @param config      SPI controller configurations
 * @param ret_handle  Returned CAM controller handle
 *
 * @return
 *        - ESP_OK on success
 *        - ESP_ERR_INVALID_ARG:   Invalid argument
 *        - ESP_ERR_NO_MEM:        Out of memory
 *        - ESP_ERR_NOT_SUPPORTED: Currently not support modes or types
 *        - ESP_ERR_NOT_FOUND:     SPI is registered already
 */
esp_err_t esp_cam_new_spi_ctlr(const esp_cam_ctlr_spi_config_t *config, esp_cam_ctlr_handle_t *ret_handle);

/**
 * @brief Decode frame, remove frame header and line header, then copy the image data to the destination buffer
 *
 * @note The source buffer and the destination buffer can be the same buffer
 *
 * @param handle ESP CAM controller handle
 *
 * @param src Source buffer pointer
 * @param src_len Source buffer length
 * @param dst Destination buffer pointer
 * @param dst_len Destination buffer length
 * @param decoded_size Decoded size pointer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_cam_spi_decode_frame(esp_cam_ctlr_handle_t handle, uint8_t *src, uint32_t src_len, uint8_t *dst, uint32_t dst_len, uint32_t *decoded_size);

#ifdef __cplusplus
}
#endif
