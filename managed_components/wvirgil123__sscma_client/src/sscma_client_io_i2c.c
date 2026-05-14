#include <stdlib.h>
#include <string.h>
#include <sys/cdefs.h>
#include "sdkconfig.h"
#if CONFIG_SSCMA_ENABLE_DEBUG_LOG
// The local log level must be defined before including esp_log.h
// Set the maximum log level for this source file
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#endif
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "sscma_client_io_interface.h"
#include "sscma_client_io.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_check.h"

static const char *TAG = "sscma_client.io.i2c";

#define I2C_ADDRESS (0x62)

#define HEADER_LEN   (uint8_t)4
#define MAX_PL_LEN   (uint8_t)250
#define CHECKSUM_LEN (uint8_t)2

#define PACKET_SIZE (uint16_t)(HEADER_LEN + MAX_PL_LEN + CHECKSUM_LEN)

#define FEATURE_TRANSPORT               0x10
#define FEATURE_TRANSPORT_CMD_READ      0x01
#define FEATURE_TRANSPORT_CMD_WRITE     0x02
#define FEATURE_TRANSPORT_CMD_AVAILABLE 0x03
#define FEATURE_TRANSPORT_CMD_START     0x04
#define FEATURE_TRANSPORT_CMD_STOP      0x05
#define FEATURE_TRANSPORT_CMD_RESET     0x06

static esp_err_t client_io_i2c_del(sscma_client_io_t *io);
static esp_err_t client_io_i2c_write(sscma_client_io_t *io, const void *data, size_t len);
static esp_err_t client_io_i2c_read(sscma_client_io_t *io, void *data, size_t len);
static esp_err_t client_io_i2c_available(sscma_client_io_t *io, size_t *len);
static esp_err_t client_io_i2c_flush(sscma_client_io_t *io);

typedef struct
{
    sscma_client_io_t base;
    uint32_t i2c_bus_id;         // I2C bus id, indicating which I2C port
    uint32_t dev_addr;           // Device address
    int wait_delay;              // I2C wait delay
    void *user_ctx;              // User context
    SemaphoreHandle_t lock;      // Lock
    uint8_t buffer[PACKET_SIZE]; // I2C packet buffer
} sscma_client_io_i2c_t;

esp_err_t sscma_client_new_io_i2c_bus(sscma_client_i2c_bus_handle_t bus, const sscma_client_io_i2c_config_t *io_config, sscma_client_io_handle_t *ret_io)
{
#if CONFIG_SSCMA_ENABLE_DEBUG_LOG
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
#endif
    esp_err_t ret = ESP_OK;
    sscma_client_io_i2c_t *i2c_client_io = NULL;
    ESP_GOTO_ON_FALSE(io_config && ret_io, ESP_ERR_INVALID_ARG, err, TAG, "invalid argument");
    i2c_client_io = (sscma_client_io_i2c_t *)calloc(1, sizeof(sscma_client_io_i2c_t));
    ESP_GOTO_ON_FALSE(i2c_client_io, ESP_ERR_NO_MEM, err, TAG, "no mem for i2c client io");

    i2c_client_io->i2c_bus_id = (uint32_t)bus;
    i2c_client_io->dev_addr = io_config->dev_addr;
    i2c_client_io->wait_delay = io_config->wait_delay;
    i2c_client_io->user_ctx = io_config->user_ctx;
    i2c_client_io->base.del = client_io_i2c_del;
    i2c_client_io->base.write = client_io_i2c_write;
    i2c_client_io->base.read = client_io_i2c_read;
    i2c_client_io->base.available = client_io_i2c_available;
    i2c_client_io->base.flush = client_io_i2c_flush;

    i2c_client_io->lock = xSemaphoreCreateMutex();
    ESP_GOTO_ON_FALSE(i2c_client_io->lock, ESP_ERR_NO_MEM, err, TAG, "no mem for lock");

    *ret_io = &i2c_client_io->base;
    ESP_LOGD(TAG, "new i2c sscma client io @%p", i2c_client_io);

    return ESP_OK;

err:
    if (i2c_client_io)
    {
        if (i2c_client_io->lock)
        {
            vSemaphoreDelete(i2c_client_io->lock);
        }
        free(i2c_client_io);
    }
    return ret;
}

static esp_err_t client_io_i2c_del(sscma_client_io_t *io)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_i2c_t *i2c_client_io = __containerof(io, sscma_client_io_i2c_t, base);

    vSemaphoreDelete(i2c_client_io->lock);
    free(i2c_client_io);
    ESP_LOGD(TAG, "del i2c sscma client io @%p", i2c_client_io);
    return ret;
}

static esp_err_t client_io_i2c_write(sscma_client_io_t *io, const void *data, size_t len)
{
    esp_err_t ret = ESP_OK;

    sscma_client_io_i2c_t *i2c_client_io = __containerof(io, sscma_client_io_i2c_t, base);
    uint16_t packets = len / MAX_PL_LEN;
    uint16_t remain = len % MAX_PL_LEN;

    xSemaphoreTake(i2c_client_io->lock, portMAX_DELAY);

    if (data)
    {
        for (uint16_t i = 0; i < packets; i++)
        {
            i2c_client_io->buffer[0] = FEATURE_TRANSPORT;
            i2c_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_WRITE;
            i2c_client_io->buffer[2] = MAX_PL_LEN >> 8;
            i2c_client_io->buffer[3] = MAX_PL_LEN & 0xFF;
            memcpy(i2c_client_io->buffer + 4, data + i * MAX_PL_LEN, MAX_PL_LEN);
            // TODO CRC
            i2c_client_io->buffer[4 + MAX_PL_LEN] = 0xFF;
            i2c_client_io->buffer[5 + MAX_PL_LEN] = 0xFF;
            if (i2c_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
            }
            ESP_GOTO_ON_ERROR(i2c_master_write_to_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, MAX_PL_LEN + 6, portMAX_DELAY), err, TAG,
                "i2c master write failed");
        }

        if (remain)
        {
            i2c_client_io->buffer[0] = FEATURE_TRANSPORT;
            i2c_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_WRITE;
            i2c_client_io->buffer[2] = remain >> 8;
            i2c_client_io->buffer[3] = remain & 0xFF;
            memcpy(i2c_client_io->buffer + 4, data + packets * MAX_PL_LEN, remain);
            // TODO CRC
            i2c_client_io->buffer[4 + remain] = 0xFF;
            i2c_client_io->buffer[5 + remain] = 0xFF;
            if (i2c_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
            }
            ESP_GOTO_ON_ERROR(i2c_master_write_to_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, remain + 6, portMAX_DELAY), err, TAG, "i2c master write failed");
        }
    }

err:
    xSemaphoreGive(i2c_client_io->lock);
    return ret;
}

static esp_err_t client_io_i2c_read(sscma_client_io_t *io, void *data, size_t len)
{
    esp_err_t ret = ESP_OK;

    sscma_client_io_i2c_t *i2c_client_io = __containerof(io, sscma_client_io_i2c_t, base);
    uint16_t packets = len / MAX_PL_LEN;
    uint16_t remain = len % MAX_PL_LEN;

    xSemaphoreTake(i2c_client_io->lock, portMAX_DELAY);

    if (data)
    {
        for (uint16_t i = 0; i < packets; i++)
        {
            i2c_client_io->buffer[0] = FEATURE_TRANSPORT;
            i2c_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_READ;
            i2c_client_io->buffer[2] = MAX_PL_LEN >> 8;
            i2c_client_io->buffer[3] = MAX_PL_LEN & 0xFF;
            i2c_client_io->buffer[4] = 0xFF;
            i2c_client_io->buffer[5] = 0xFF;
            if (i2c_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
            }
            ESP_GOTO_ON_ERROR(i2c_master_write_to_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, 6, portMAX_DELAY), err, TAG, "i2c master write failed");
            if (i2c_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
            }
            ESP_GOTO_ON_ERROR(i2c_master_read_from_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, MAX_PL_LEN + 6, portMAX_DELAY), err, TAG,
                "i2c master read failed");
            memcpy(data + i * MAX_PL_LEN, i2c_client_io->buffer, MAX_PL_LEN);
        }

        if (remain)
        {
            i2c_client_io->buffer[0] = FEATURE_TRANSPORT;
            i2c_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_READ;
            i2c_client_io->buffer[2] = remain >> 8;
            i2c_client_io->buffer[3] = remain & 0xFF;
            i2c_client_io->buffer[4] = 0xFF;
            i2c_client_io->buffer[5] = 0xFF;
            if (i2c_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
            }
            ESP_GOTO_ON_ERROR(i2c_master_write_to_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, 6, portMAX_DELAY), err, TAG, "i2c master write failed");
            if (i2c_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
            }
            ESP_GOTO_ON_ERROR(i2c_master_read_from_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, remain + 6, portMAX_DELAY), err, TAG, "i2c master read failed");
            memcpy(data + packets * MAX_PL_LEN, i2c_client_io->buffer, remain);
        }
    }

err:
    xSemaphoreGive(i2c_client_io->lock);
    return ret;
}

static esp_err_t client_io_i2c_available(sscma_client_io_t *io, size_t *len)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_i2c_t *i2c_client_io = __containerof(io, sscma_client_io_i2c_t, base);

    xSemaphoreTake(i2c_client_io->lock, portMAX_DELAY);

    i2c_client_io->buffer[0] = FEATURE_TRANSPORT;
    i2c_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_AVAILABLE;
    i2c_client_io->buffer[2] = 0x00;
    i2c_client_io->buffer[3] = 0x00;
    i2c_client_io->buffer[4] = 0xFF;
    i2c_client_io->buffer[5] = 0xFF;

    if (i2c_client_io->wait_delay > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
    }
    ESP_GOTO_ON_ERROR(i2c_master_write_to_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, HEADER_LEN + CHECKSUM_LEN, portMAX_DELAY), err, TAG,
        "i2c master write failed");
    if (i2c_client_io->wait_delay > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
    }
    ESP_GOTO_ON_ERROR(i2c_master_read_from_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, 2, portMAX_DELAY), err, TAG, "i2c master read failed");

    *len = (i2c_client_io->buffer[0] << 8) | i2c_client_io->buffer[1];

err:
    xSemaphoreGive(i2c_client_io->lock);
    return ret;
}

static esp_err_t client_io_i2c_flush(sscma_client_io_t *io)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_i2c_t *i2c_client_io = __containerof(io, sscma_client_io_i2c_t, base);

    xSemaphoreTake(i2c_client_io->lock, portMAX_DELAY);

    i2c_client_io->buffer[0] = FEATURE_TRANSPORT;
    i2c_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_RESET;
    i2c_client_io->buffer[2] = 0x00;
    i2c_client_io->buffer[3] = 0x00;
    i2c_client_io->buffer[4] = 0xFF;
    i2c_client_io->buffer[5] = 0xFF;

    if (i2c_client_io->wait_delay > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
    }
    ESP_GOTO_ON_ERROR(i2c_master_write_to_device(i2c_client_io->i2c_bus_id, i2c_client_io->dev_addr, i2c_client_io->buffer, HEADER_LEN + CHECKSUM_LEN, portMAX_DELAY), err, TAG,
        "i2c master write failed");
    if (i2c_client_io->wait_delay > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(i2c_client_io->wait_delay));
    }

err:
    xSemaphoreGive(i2c_client_io->lock);
    return ret;
}
