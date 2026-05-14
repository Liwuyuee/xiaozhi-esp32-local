#include <stdlib.h>
#include <string.h>
#include <sys/cdefs.h>
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "sscma_client_io_interface.h"
#include "sscma_client_io.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_check.h"

static const char *TAG = "sscma_client.io.uart";

static esp_err_t client_io_uart_del(sscma_client_io_t *io);
static esp_err_t client_io_uart_write(sscma_client_io_t *io, const void *data, size_t len);
static esp_err_t client_io_uart_read(sscma_client_io_t *io, void *data, size_t len);
static esp_err_t client_io_uart_available(sscma_client_io_t *io, size_t *len);
static esp_err_t client_io_uart_flush(sscma_client_io_t *io);

typedef struct
{
    sscma_client_io_t base;
    SemaphoreHandle_t lock; // Mutex lock
    uint32_t uart_port;     // UART port
    void *user_ctx;         // User context
} sscma_client_io_uart_t;

esp_err_t sscma_client_new_io_uart_bus(sscma_client_uart_bus_handle_t bus, const sscma_client_io_uart_config_t *io_config, sscma_client_io_handle_t *ret_io)
{
#if CONFIG_SSCMA_ENABLE_DEBUG_LOG
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
#endif
    esp_err_t ret = ESP_OK;
    sscma_client_io_uart_t *uart_client_io = NULL;
    ESP_GOTO_ON_FALSE(io_config && ret_io, ESP_ERR_INVALID_ARG, err, TAG, "invalid argument");

    uart_client_io = (sscma_client_io_uart_t *)calloc(1, sizeof(sscma_client_io_uart_t));
    ESP_GOTO_ON_FALSE(uart_client_io, ESP_ERR_NO_MEM, err, TAG, "no mem for uart client io");

    uart_client_io->uart_port = (uint32_t)bus;
    uart_client_io->user_ctx = io_config->user_ctx;
    uart_client_io->base.del = client_io_uart_del;
    uart_client_io->base.write = client_io_uart_write;
    uart_client_io->base.read = client_io_uart_read;
    uart_client_io->base.available = client_io_uart_available;
    uart_client_io->base.flush = client_io_uart_flush;

    uart_client_io->lock = xSemaphoreCreateMutex();
    ESP_GOTO_ON_FALSE(uart_client_io->lock, ESP_ERR_NO_MEM, err, TAG, "no mem for mutex");

    *ret_io = &uart_client_io->base;
    ESP_LOGI(TAG, "new uart sscma client io @%p", uart_client_io);

    return ESP_OK;

err:
    if (uart_client_io)
    {
        if (uart_client_io->lock)
        {
            vSemaphoreDelete(uart_client_io->lock);
        }
        free(uart_client_io);
    }

    return ret;
}

esp_err_t client_io_uart_del(sscma_client_io_t *io)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_uart_t *uart_client_io = __containerof(io, sscma_client_io_uart_t, base);

    if (uart_client_io->lock)
    {
        vSemaphoreDelete(uart_client_io->lock);
    }

    free(uart_client_io);

    ESP_LOGD(TAG, "del uart sscma client io @%p", uart_client_io);
    return ret;
}

static esp_err_t client_io_uart_write(sscma_client_io_t *io, const void *data, size_t len)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_uart_t *uart_client_io = __containerof(io, sscma_client_io_uart_t, base);
    ESP_GOTO_ON_FALSE(uart_client_io, ESP_ERR_INVALID_STATE, err, TAG, "uart not initialized");

    xSemaphoreTake(uart_client_io->lock, portMAX_DELAY);

    ret = uart_write_bytes(uart_client_io->uart_port, data, len);

    xSemaphoreGive(uart_client_io->lock);

err:
    return ret == len ? ESP_OK : ESP_FAIL;
}

static esp_err_t client_io_uart_read(sscma_client_io_t *io, void *data, size_t len)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_uart_t *uart_client_io = __containerof(io, sscma_client_io_uart_t, base);
    ESP_GOTO_ON_FALSE(uart_client_io, ESP_ERR_INVALID_STATE, err, TAG, "uart not initialized");

    xSemaphoreTake(uart_client_io->lock, portMAX_DELAY);
    ret = uart_read_bytes(uart_client_io->uart_port, data, len, portMAX_DELAY);
    xSemaphoreGive(uart_client_io->lock);

err:
    return ret == len ? ESP_OK : ESP_FAIL;
}

static esp_err_t client_io_uart_available(sscma_client_io_t *io, size_t *len)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_uart_t *uart_client_io = __containerof(io, sscma_client_io_uart_t, base);
    ESP_GOTO_ON_FALSE(uart_client_io, ESP_ERR_INVALID_STATE, err, TAG, "uart not initialized");

    xSemaphoreTake(uart_client_io->lock, portMAX_DELAY);
    ret = uart_get_buffered_data_len(uart_client_io->uart_port, len);

    if (ret != ESP_OK)
    {
        *len = 0;
    }

    xSemaphoreGive(uart_client_io->lock);

err:
    return ret;
}

static esp_err_t client_io_uart_flush(sscma_client_io_t *io)
{
    sscma_client_io_uart_t *uart_client_io = __containerof(io, sscma_client_io_uart_t, base);
    ESP_RETURN_ON_ERROR(uart_flush(uart_client_io->uart_port), TAG, "uart flush failed");
    return ESP_OK;
}