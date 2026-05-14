/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <esp_types.h>
#include <stdlib.h>
#include <string.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "driver/i2c_master.h"
#include "esp_sccb_types.h"
#include "esp_sccb_i2c.h"
#include "sccb_i2c_internal.h"
#include "esp_sccb_io_interface.h"

#define SCCB_I2C_MEM_CAPS   MALLOC_CAP_DEFAULT

static const char *TAG = "sccb_i2c";

static esp_err_t s_sccb_i2c_transmit_reg_a8v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_reg_a16v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_reg_a8v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_reg_a16v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_receive_reg_a8v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_receive_reg_a16v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_receive_reg_a8v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_receive_reg_a16v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_transmit_v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_receive_v16(esp_sccb_io_t *io_handle, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms);
static esp_err_t s_sccb_i2c_destroy(esp_sccb_io_t *io_handle);

esp_err_t sccb_new_i2c_io(i2c_master_bus_handle_t bus_handle, const sccb_i2c_config_t *config, esp_sccb_io_handle_t *io_handle)
{
    esp_err_t ret = ESP_FAIL;
    ESP_RETURN_ON_FALSE(bus_handle && config && io_handle, ESP_ERR_INVALID_ARG, TAG, "invalid argument");
    sccb_io_i2c_t *io_i2c = heap_caps_calloc(1, sizeof(sccb_io_i2c_t), SCCB_I2C_MEM_CAPS);
    ESP_RETURN_ON_FALSE(io_i2c, ESP_ERR_NO_MEM, TAG, "no mem for io handle");

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = config->dev_addr_length,
        .device_address = config->device_address,
        .scl_speed_hz = config->scl_speed_hz,
    };
    i2c_master_dev_handle_t dev_handle = NULL;
    ESP_GOTO_ON_ERROR(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle), err, TAG, "failed to add device");

    io_i2c->i2c_device = dev_handle;
    io_i2c->base.transmit_reg_a8v8 = s_sccb_i2c_transmit_reg_a8v8;
    io_i2c->base.transmit_reg_a16v8 = s_sccb_i2c_transmit_reg_a16v8;
    io_i2c->base.transmit_reg_a8v16 = s_sccb_i2c_transmit_reg_a8v16;
    io_i2c->base.transmit_reg_a16v16 = s_sccb_i2c_transmit_reg_a16v16;
    io_i2c->base.transmit_receive_reg_a8v8 = s_sccb_i2c_transmit_receive_reg_a8v8;
    io_i2c->base.transmit_receive_reg_a16v8 = s_sccb_i2c_transmit_receive_reg_a16v8;
    io_i2c->base.transmit_receive_reg_a8v16 = s_sccb_i2c_transmit_receive_reg_a8v16;
    io_i2c->base.transmit_receive_reg_a16v16 = s_sccb_i2c_transmit_receive_reg_a16v16;
    io_i2c->base.transmit_v16 = s_sccb_i2c_transmit_v16;
    io_i2c->base.receive_v16 = s_sccb_i2c_receive_v16;
    io_i2c->base.del = s_sccb_i2c_destroy;
    *io_handle = &(io_i2c->base);
    ESP_LOGD(TAG, "new io_i2c: %p", io_i2c);
    return ESP_OK;

err:
    free(io_i2c);
    return ret;
}

static esp_err_t s_sccb_i2c_transmit_reg_a8v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit(io_i2c->i2c_device, write_buffer, write_size, xfer_timeout_ms), TAG, "failed to i2c transmit");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_reg_a16v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit(io_i2c->i2c_device, write_buffer, write_size, xfer_timeout_ms), TAG, "failed to i2c transmit");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_reg_a8v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit(io_i2c->i2c_device, write_buffer, write_size, xfer_timeout_ms), TAG, "failed to i2c transmit");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_reg_a16v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit(io_i2c->i2c_device, write_buffer, write_size, xfer_timeout_ms), TAG, "failed to i2c transmit");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_receive_reg_a8v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit_receive(io_i2c->i2c_device, write_buffer, write_size, read_buffer, read_size, xfer_timeout_ms), TAG, "faled to transmit receive");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_receive_reg_a16v8(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit_receive(io_i2c->i2c_device, write_buffer, write_size, read_buffer, read_size, xfer_timeout_ms), TAG, "faled to transmit receive");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_receive_reg_a8v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit_receive(io_i2c->i2c_device, write_buffer, write_size, read_buffer, read_size, xfer_timeout_ms), TAG, "faled to transmit receive");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_receive_reg_a16v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit_receive(io_i2c->i2c_device, write_buffer, write_size, read_buffer, read_size, xfer_timeout_ms), TAG, "faled to transmit receive");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_transmit_v16(esp_sccb_io_t *io_handle, const uint8_t *write_buffer, size_t write_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_transmit(io_i2c->i2c_device, write_buffer, write_size, xfer_timeout_ms), TAG, "faled to transmit");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_receive_v16(esp_sccb_io_t *io_handle, uint8_t *read_buffer, size_t read_size, int xfer_timeout_ms)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_receive(io_i2c->i2c_device, read_buffer, read_size, xfer_timeout_ms), TAG, "faled to receive");

    return ESP_OK;
}

static esp_err_t s_sccb_i2c_destroy(esp_sccb_io_t *io_handle)
{
    sccb_io_i2c_t *io_i2c = __containerof(io_handle, sccb_io_i2c_t, base);
    ESP_RETURN_ON_ERROR(i2c_master_bus_rm_device(io_i2c->i2c_device), TAG, "failed to remove device");

    heap_caps_free(io_i2c);

    return ESP_OK;
}
