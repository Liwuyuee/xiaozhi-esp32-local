/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <sys/cdefs.h>
#include "esp_types.h"
#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_sccb_io_interface.h"
#include "esp_sccb_intf.h"

#define ESP_SCCB_TRANS_DEALY CONFIG_ESP_SCCB_TRANS_TIMEOUT_DEFAULT

static const char *TAG = "sccb";

esp_err_t esp_sccb_transmit_reg_a8v8(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint8_t reg_val)
{
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_reg_a8v8, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");

    uint8_t data[2] = {0};
    data[0] = reg_addr & 0xff;
    data[1] = reg_val;

    return io_handle->transmit_reg_a8v8(io_handle, data, 2, ESP_SCCB_TRANS_DEALY);
}

esp_err_t esp_sccb_transmit_reg_a16v8(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint8_t reg_val)
{
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_reg_a16v8, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");

    uint8_t data[3] = {0};
    data[0] = (reg_addr & 0xff00) >> 8;
    data[1] = reg_addr & 0xff;
    data[2] = reg_val;

    return io_handle->transmit_reg_a16v8(io_handle, data, 3, ESP_SCCB_TRANS_DEALY);
}

esp_err_t esp_sccb_transmit_reg_a8v16(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint16_t reg_val)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_reg_a8v16, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");

    uint8_t data[3] = {0};
    data[0] = reg_addr & 0xff;
    data[1] = (reg_val & 0xff00) >> 8;
    data[2] = reg_val & 0xff;

    ESP_RETURN_ON_ERROR(io_handle->transmit_reg_a8v16(io_handle, data, 3, ESP_SCCB_TRANS_DEALY), TAG, "failed to transmit_reg_a8v16");
    reg_val = __builtin_bswap16(reg_val);
    return ret;
}

esp_err_t esp_sccb_transmit_reg_a16v16(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint16_t reg_val)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_reg_a16v16, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");

    uint8_t data[4] = {0};
    data[0] = (reg_addr & 0xff00) >> 8;
    data[1] = reg_addr & 0xff;
    data[2] = (reg_val & 0xff00) >> 8;
    data[3] = reg_val & 0xff;

    ESP_RETURN_ON_ERROR(io_handle->transmit_reg_a16v16(io_handle, data, 4, ESP_SCCB_TRANS_DEALY), TAG, "failed to transmit_reg_a16v16");
    reg_val = __builtin_bswap16(reg_val);
    return ret;
}

esp_err_t esp_sccb_transmit_receive_reg_a8v8(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint8_t *reg_val)
{
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_receive_reg_a8v8, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");
    ESP_RETURN_ON_FALSE(reg_val, ESP_ERR_INVALID_ARG, TAG, "invalid argument: reg_val null pointer");

    uint8_t data[1] = {0};
    data[0] = reg_addr & 0xff;

    return io_handle->transmit_receive_reg_a8v8(io_handle, data, 1, reg_val, 1, ESP_SCCB_TRANS_DEALY);
}

esp_err_t esp_sccb_transmit_receive_reg_a16v8(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint8_t *reg_val)
{
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_receive_reg_a16v8, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");
    ESP_RETURN_ON_FALSE(reg_val, ESP_ERR_INVALID_ARG, TAG, "invalid argument: reg_val null pointer");

    uint8_t data[2] = {0};
    data[0] = (reg_addr & 0xff00) >> 8;
    data[1] = reg_addr & 0xff;

    return io_handle->transmit_receive_reg_a16v8(io_handle, data, 2, reg_val, 1, ESP_SCCB_TRANS_DEALY);
}

esp_err_t esp_sccb_transmit_receive_reg_a8v16(esp_sccb_io_handle_t io_handle, uint8_t reg_addr, uint16_t *reg_val)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_receive_reg_a8v16, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");
    ESP_RETURN_ON_FALSE(reg_val, ESP_ERR_INVALID_ARG, TAG, "invalid argument: reg_val null pointer");

    uint8_t data[1] = {0};
    data[0] = reg_addr & 0xff;

    ESP_RETURN_ON_ERROR(io_handle->transmit_receive_reg_a8v16(io_handle, data, 1, (void *)reg_val, 2, ESP_SCCB_TRANS_DEALY), TAG, "failed to transmit_receive_reg_a8v16");
    *reg_val = __builtin_bswap16(*reg_val);
    return ret;
}

esp_err_t esp_sccb_transmit_receive_reg_a16v16(esp_sccb_io_handle_t io_handle, uint16_t reg_addr, uint16_t *reg_val)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_receive_reg_a16v16, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");
    ESP_RETURN_ON_FALSE(reg_val, ESP_ERR_INVALID_ARG, TAG, "invalid argument: reg_val null pointer");

    uint8_t data[2] = {0};
    data[0] = (reg_addr & 0xff00) >> 8;
    data[1] = reg_addr & 0xff;

    ESP_RETURN_ON_ERROR(io_handle->transmit_receive_reg_a16v16(io_handle, data, 2, (void *)reg_val, 2, ESP_SCCB_TRANS_DEALY), TAG, "failed to transmit_receive_reg_a16v16");
    *reg_val = __builtin_bswap16(*reg_val);
    return ret;
}

esp_err_t esp_sccb_transmit_v16(esp_sccb_io_handle_t io_handle, uint16_t val)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->transmit_v16, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");
    uint8_t data[2] = {0};
    data[0] = (val & 0xff00) >> 8;
    data[1] = val & 0xff;
    ESP_RETURN_ON_ERROR(io_handle->transmit_v16(io_handle, data, 2, ESP_SCCB_TRANS_DEALY), TAG, "failed to transmit_v16");
    return ret;
}

esp_err_t esp_sccb_receive_v16(esp_sccb_io_handle_t io_handle, uint16_t *val)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->receive_v16, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");
    ESP_RETURN_ON_FALSE(val, ESP_ERR_INVALID_ARG, TAG, "invalid argument: val null pointer");

    ESP_RETURN_ON_ERROR(io_handle->receive_v16(io_handle, (void *)val, 2, ESP_SCCB_TRANS_DEALY), TAG, "failed to receive_v16");
    *val = __builtin_bswap16(*val);
    return ret;
}

esp_err_t esp_sccb_del_i2c_io(esp_sccb_io_handle_t io_handle)
{
    ESP_RETURN_ON_FALSE(io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument: null pointer");
    ESP_RETURN_ON_FALSE(io_handle->del, ESP_ERR_NOT_SUPPORTED, TAG, "controller driver function not supported");

    return io_handle->del(io_handle);
}
