/*
 * SPDX-FileCopyrightText: 2021-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "esp_sccb_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief sccb controller type
 */
typedef struct esp_sccb_io_t esp_sccb_io_t;

/**
 * @brief sccb controller type
 */
struct esp_sccb_io_t {

    /**
     * @brief Perform a write transaction for 8-bit reg_addr and 8-bit reg_val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_reg_a8v8)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write transaction for 16-bit reg_addr and 8-bit reg_val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_reg_a16v8)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write transaction for 8-bit reg_addr and 16-bit reg_val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_reg_a8v16)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write transaction for 16-bit reg_addr and 16-bit reg_val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_reg_a16v16)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write-read transaction for 8-bit reg_addr and 8-bit reg_val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] read_buffer Data bytes to read on the sccb bus.
     * @param[in] read_size   Size, in bytes, of the read buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit-receive success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_receive_reg_a8v8)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write-read transaction for 16-bit reg_addr and 8-bit reg_val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] read_buffer Data bytes to read on the sccb bus.
     * @param[in] read_size   Size, in bytes, of the read buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit-receive success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_receive_reg_a16v8)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write-read transaction for 8-bit reg_addr and 16-bit reg_val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] read_buffer Data bytes to read on the sccb bus.
     * @param[in] read_size   Size, in bytes, of the read buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit-receive success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_receive_reg_a8v16)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write-read transaction for 16-bit reg_addr and 16-bit reg_val.
     *
     * @param[in] handle       SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] read_buffer Data bytes to read on the sccb bus.
     * @param[in] read_size   Size, in bytes, of the read buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit-receive success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_receive_reg_a16v16)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);

    /**
     * @brief Perform a write transaction for 16-bit val.
     *
     * @param[in] handle SCCB IO handle
     * @param[in] write_buffer Data bytes to send on the sccb bus.
     * @param[in] write_size   Size, in bytes, of the write buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*transmit_v16)(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);

    /**
     * @brief Perform a read transaction for 16-bit val.
     *
     * @param[in] handle       SCCB IO handle
     * @param[in] read_buffer Data bytes to read on the sccb bus.
     * @param[in] read_size   Size, in bytes, of the read buffer.
     * @param[in] xfer_timeout_ms Wait timeout, in ms.
     * @return
     *      - ESP_OK: sccb transmit success
     *      - ESP_ERR_INVALID_ARG: sccb transmit parameter invalid.
     *      - ESP_ERR_TIMEOUT: Operation timeout(larger than xfer_timeout_ms) because the bus is busy or hardware crash.
     */
    esp_err_t (*receive_v16)(esp_sccb_io_t *io_handle, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);

    /**
     * @brief Delete sccb io handle
     *
     * @param[in] handle SCCB handle
     * @return
     *        - ESP_OK: If controller is successfully deleted.
     */
    esp_err_t (*del)(esp_sccb_io_t *io_handle);
};

#ifdef __cplusplus
}
#endif
