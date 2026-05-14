/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_sccb_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Perform a write transaction for 8-bit reg_addr and 8-bit reg_val.
 *
 * @param[in] handle SCCB IO handle
 * @param[in] reg_addr address to send on the sccb bus.
 * @param[in] reg_val  Data to send on the sccb bus.
 * @return
 *      - ESP_OK: sccb transmit success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_reg_a8v8(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint8_t reg_val);

/**
 * @brief Perform a write transaction for 16-bit reg_addr and 8-bit reg_val.
 *
 * @param[in] handle SCCB IO handle
 * @param[in] reg_addr address to send on the sccb bus.
 * @param[in] reg_val  Data to send on the sccb bus.
 * @return
 *      - ESP_OK: sccb transmit success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_reg_a16v8(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint8_t reg_val);

/**
 * @brief Perform a write transaction for 8-bit reg_addr and 16-bit reg_val.
 *
 * @param[in] handle SCCB IO handle
 * @param[in] reg_addr address to send on the sccb bus.
 * @param[in] reg_val  Data to send on the sccb bus.
 * @return
 *      - ESP_OK: sccb transmit success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_reg_a8v16(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint16_t reg_val);

/**
 * @brief Perform a write transaction for 16-bit reg_addr and 16-bit reg_val.
 *
 * @param[in] handle SCCB IO handle
 * @param[in] reg_addr address to send on the sccb bus.
 * @param[in] reg_val  Data to send on the sccb bus.
 * @return
 *      - ESP_OK: sccb transmit success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_reg_a16v16(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint16_t reg_val);

/**
 * @brief Perform a write-read transaction for 8-bit reg_addr and 8-bit reg_val.
 *
 * @param[in] handle SCCB IO handle
 * @param[in] reg_addr address to send on the sccb bus.
 * @param[out] reg_val Data bytes received from sccb bus.
 * @return
 *      - ESP_OK: sccb transmit-receive success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_receive_reg_a8v8(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint8_t *reg_val);

/**
 * @brief Perform a write-read transaction for 16-bit reg_addr and 8-bit reg_val.
 *
 * @param[in] handle SCCB IO handle
 * @param[in] reg_addr address to send on the sccb bus.
 * @param[out] reg_val Data bytes received from sccb bus.
 * @return
 *      - ESP_OK: sccb transmit-receive success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_receive_reg_a16v8(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint8_t *reg_val);

/**
 * @brief Perform a write-read transaction for 8-bit reg_addr and 16-bit reg_val.
 *
 * @param[in]  handle   SCCB IO handle
 * @param[in]  reg_addr address to send on the sccb bus.
 * @param[out] reg_val  Data bytes received from sccb bus.
 * @return
 *      - ESP_OK: sccb transmit-receive success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_receive_reg_a8v16(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint16_t *reg_val);

/**
 * @brief Perform a write-read transaction for 16-bit reg_addr and 16-bit reg_val.
 *
 * @param[in] handle SCCB IO handle
 * @param[in] reg_addr address to send on the sccb bus.
 * @param[out] reg_val Data bytes received from sccb bus.
 * @return
 *      - ESP_OK: sccb transmit-receive success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_receive_reg_a16v16(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint16_t *reg_val);

/**
 * @brief Perform a write transaction for 16-bit val.
 *
 * @param[in]  handle   SCCB IO handle
 * @param[in] val  Data to send on the sccb bus.
 * @return
 *      - ESP_OK: sccb transmit success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_transmit_v16(esp_sccb_io_handle_t io_handle, uint16_t val);

/**
 * @brief Perform a read transaction for 16-bit val.
 *
 * @param[in] handle SCCB IO handle
 * @param[out] val Data bytes received from sccb bus.
 * @return
 *      - ESP_OK: sccb receive success
 *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
 */
esp_err_t esp_sccb_receive_v16(esp_sccb_io_handle_t io_handle, uint16_t *val);

/**
 * @brief Delete sccb I2C IO handle
 *
 * @param[in] handle SCCB IO handle
 * @return
 *        - ESP_OK: If controller is successfully deleted.
 */
esp_err_t esp_sccb_del_i2c_io(esp_sccb_io_handle_t io_handle);

#ifdef __cplusplus
}
#endif
