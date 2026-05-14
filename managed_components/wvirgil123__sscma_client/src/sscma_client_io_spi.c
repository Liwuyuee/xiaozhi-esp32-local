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
#include "cJSON.h"
#include "sscma_client_io_interface.h"
#include "sscma_client_io.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_check.h"

static const char *TAG = "sscma_client.io.spi";

#define HEADER_LEN   (uint8_t)4
#define MAX_PL_LEN   (uint8_t)250
#define CHECKSUM_LEN (uint8_t)2

#define PACKET_SIZE (uint16_t)(HEADER_LEN + MAX_PL_LEN + CHECKSUM_LEN)

#define MAX_RECIEVE_SIZE (uint16_t)4095

#define FEATURE_TRANSPORT               0x10
#define FEATURE_TRANSPORT_CMD_READ      0x01
#define FEATURE_TRANSPORT_CMD_WRITE     0x02
#define FEATURE_TRANSPORT_CMD_AVAILABLE 0x03
#define FEATURE_TRANSPORT_CMD_START     0x04
#define FEATURE_TRANSPORT_CMD_STOP      0x05
#define FEATURE_TRANSPORT_CMD_RESET     0x06

static esp_err_t client_io_spi_del(sscma_client_io_t *io);
static esp_err_t client_io_spi_write(sscma_client_io_t *io, const void *data, size_t len);
static esp_err_t client_io_spi_read(sscma_client_io_t *io, void *data, size_t len);
static esp_err_t client_io_spi_available(sscma_client_io_t *io, size_t *len);
static esp_err_t client_io_spi_flush(sscma_client_io_t *io);

typedef struct
{
    sscma_client_io_t base;
    spi_device_handle_t spi_dev;          // SPI bus id, indicating which SPI port
    int sync_gpio_num;                    // D/C line GPIO number
    size_t spi_trans_max_bytes;           // SPI transaction max bytes
    int wait_delay;                       // SPI wait delay
    void *user_ctx;                       // User context
    esp_io_expander_handle_t io_expander; // IO expander
    SemaphoreHandle_t lock;               // Lock
    uint8_t buffer[PACKET_SIZE];
} sscma_client_io_spi_t;

esp_err_t sscma_client_new_io_spi_bus(sscma_client_spi_bus_handle_t bus, const sscma_client_io_spi_config_t *io_config, sscma_client_io_handle_t *ret_io)
{
#if CONFIG_SSCMA_ENABLE_DEBUG_LOG
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
#endif
    esp_err_t ret = ESP_OK;
    sscma_client_io_spi_t *spi_client_io = NULL;
    ESP_GOTO_ON_FALSE(io_config && ret_io, ESP_ERR_INVALID_ARG, err, TAG, "invalid argument");
    spi_client_io = (sscma_client_io_spi_t *)calloc(1, sizeof(sscma_client_io_spi_t));
    ESP_GOTO_ON_FALSE(spi_client_io, ESP_ERR_NO_MEM, err, TAG, "no mem for spi client io");

    spi_device_interface_config_t dev_config = {
        .flags = (io_config->flags.lsb_first ? SPI_DEVICE_TXBIT_LSBFIRST : 0) | (io_config->flags.sio_mode ? SPI_DEVICE_3WIRE : 0) | (io_config->flags.cs_high_active ? SPI_DEVICE_POSITIVE_CS : 0),
        .clock_speed_hz = io_config->pclk_hz,
        .mode = io_config->spi_mode,
        .spics_io_num = io_config->cs_gpio_num,
        .queue_size = 1,
    };

    ret = spi_bus_add_device((spi_host_device_t)bus, &dev_config, &spi_client_io->spi_dev);
    ESP_GOTO_ON_ERROR(ret, err, TAG, "adding spi device to bus failed");

    if (io_config->sync_gpio_num >= 0)
    {
        if (io_config->flags.sync_use_expander)
        {
            if (io_config->io_expander == NULL)
            {
                ESP_GOTO_ON_FALSE(false, ESP_ERR_INVALID_ARG, err, TAG, "io expander not set");
            }
            spi_client_io->io_expander = io_config->io_expander;
            ESP_GOTO_ON_ERROR(esp_io_expander_set_dir(io_config->io_expander, io_config->sync_gpio_num, IO_EXPANDER_INPUT), err, TAG, "setting sync GPIO for sync failed");
        }
        else
        {
            // zero-initialize the config structure.
            gpio_config_t io_conf = {};
            io_conf.intr_type = GPIO_INTR_DISABLE;
            io_conf.pin_bit_mask = (1 << io_config->sync_gpio_num);
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_down_en = 1;
            ESP_GOTO_ON_ERROR(gpio_config(&io_conf), err, TAG, "configuring sync GPIO for sync failed");
        }
    }

    spi_client_io->sync_gpio_num = io_config->sync_gpio_num;
    spi_client_io->wait_delay = io_config->wait_delay;
    spi_client_io->user_ctx = io_config->user_ctx;
    spi_client_io->base.del = client_io_spi_del;
    spi_client_io->base.write = client_io_spi_write;
    spi_client_io->base.read = client_io_spi_read;
    spi_client_io->base.available = client_io_spi_available;
    spi_client_io->base.flush = client_io_spi_flush;
    spi_client_io->base.handle = spi_client_io->spi_dev;

    spi_client_io->lock = xSemaphoreCreateMutex();
    ESP_GOTO_ON_FALSE(spi_client_io->lock, ESP_ERR_NO_MEM, err, TAG, "no mem for mutex");

    size_t max_trans_bytes = 0;
    ESP_GOTO_ON_ERROR(spi_bus_get_max_transaction_len((spi_host_device_t)bus, &max_trans_bytes), err, TAG, "get spi max transaction len failed");
    spi_client_io->spi_trans_max_bytes = max_trans_bytes;
    ESP_LOGI(TAG, "spi max trans bytes: %d", spi_client_io->spi_trans_max_bytes);

    *ret_io = &spi_client_io->base;
    ESP_LOGD(TAG, "new spi sscma client io @%p", spi_client_io);

    return ESP_OK;

err:
    if (spi_client_io)
    {
        if (spi_client_io->spi_dev)
        {
            spi_bus_remove_device(spi_client_io->spi_dev);
            spi_bus_free((spi_host_device_t)bus);
        }
        if (spi_client_io->lock)
        {
            vSemaphoreDelete(spi_client_io->lock);
        }
        free(spi_client_io);
    }
    return ret;
}

static esp_err_t client_io_spi_del(sscma_client_io_t *io)
{
    esp_err_t ret = ESP_OK;
    sscma_client_io_spi_t *spi_client_io = __containerof(io, sscma_client_io_spi_t, base);
    if (spi_client_io->lock)
    {
        vSemaphoreDelete(spi_client_io->lock);
    }
    spi_bus_remove_device(spi_client_io->spi_dev);
    spi_bus_free((spi_host_device_t)spi_client_io->spi_dev);
    if (spi_client_io->sync_gpio_num >= 0)
    {
        gpio_reset_pin(spi_client_io->sync_gpio_num);
    }
    ESP_LOGD(TAG, "del spi sscma client io @%p", spi_client_io);

    free(spi_client_io);
    return ret;
}

static esp_err_t client_io_spi_write(sscma_client_io_t *io, const void *data, size_t len)
{
    esp_err_t ret = ESP_OK;
    spi_transaction_t spi_trans = {};
    sscma_client_io_spi_t *spi_client_io = __containerof(io, sscma_client_io_spi_t, base);
    uint16_t packets = len / MAX_PL_LEN;
    uint16_t remain = len % MAX_PL_LEN;
    size_t trans_len = 0;

    xSemaphoreTake(spi_client_io->lock, portMAX_DELAY);

    if (spi_device_acquire_bus(spi_client_io->spi_dev, portMAX_DELAY) != ESP_OK)
    {
        xSemaphoreGive(spi_client_io->lock);
        return ESP_FAIL;
    }

    if (data)
    {
        for (uint16_t i = 0; i < packets; i++)
        {
            trans_len = PACKET_SIZE;
            memset(spi_client_io->buffer, 0, sizeof(spi_client_io->buffer));
            spi_client_io->buffer[0] = FEATURE_TRANSPORT;
            spi_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_WRITE;
            spi_client_io->buffer[2] = MAX_PL_LEN >> 8;
            spi_client_io->buffer[3] = MAX_PL_LEN & 0xFF;
            spi_client_io->buffer[4 + MAX_PL_LEN] = 0xFF;
            spi_client_io->buffer[5 + MAX_PL_LEN] = 0xFF;
            memcpy(spi_client_io->buffer + 4, data + i * MAX_PL_LEN, MAX_PL_LEN);
            spi_trans.tx_buffer = spi_client_io->buffer;
            if (spi_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
            }
            do
            {
                uint16_t chunk_size = trans_len;
                if (chunk_size > spi_client_io->spi_trans_max_bytes)
                {
                    chunk_size = spi_client_io->spi_trans_max_bytes;
                    spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
                }
                else
                {
                    chunk_size = trans_len;
                    spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
                }
                spi_trans.length = chunk_size * 8;
                spi_trans.rxlength = 0;
                spi_trans.rx_buffer = NULL;
                spi_trans.user = spi_client_io;
                ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
                ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
                spi_trans.tx_buffer = spi_trans.tx_buffer + chunk_size;
                trans_len -= chunk_size;
            }
            while (trans_len > 0);
        }

        if (remain)
        {
            trans_len = PACKET_SIZE;
            memset(spi_client_io->buffer, 0, sizeof(spi_client_io->buffer));
            spi_client_io->buffer[0] = FEATURE_TRANSPORT;
            spi_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_WRITE;
            spi_client_io->buffer[2] = remain >> 8;
            spi_client_io->buffer[3] = remain & 0xFF;
            spi_client_io->buffer[4 + remain] = 0xFF;
            spi_client_io->buffer[5 + remain] = 0xFF;
            memcpy(spi_client_io->buffer + 4, data + packets * MAX_PL_LEN, remain);
            spi_trans.tx_buffer = spi_client_io->buffer;
            if (spi_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
            }
            do
            {
                uint16_t chunk_size = trans_len;
                if (chunk_size > spi_client_io->spi_trans_max_bytes)
                {
                    chunk_size = spi_client_io->spi_trans_max_bytes;
                    spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
                }
                else
                {
                    chunk_size = trans_len;
                    spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
                }
                spi_trans.length = chunk_size * 8;
                spi_trans.tx_buffer = spi_client_io->buffer;
                spi_trans.rxlength = 0;
                spi_trans.rx_buffer = NULL;
                spi_trans.user = spi_client_io;
                ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
                ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
                spi_trans.tx_buffer = spi_trans.tx_buffer + chunk_size;
                trans_len -= chunk_size;
            }
            while (trans_len > 0);
        }
    }

err:
    spi_device_release_bus(spi_client_io->spi_dev);
    xSemaphoreGive(spi_client_io->lock);
    return ret;
}

static esp_err_t client_io_spi_read(sscma_client_io_t *io, void *data, size_t len)
{
    esp_err_t ret = ESP_OK;
    spi_transaction_t spi_trans = {};
    sscma_client_io_spi_t *spi_client_io = __containerof(io, sscma_client_io_spi_t, base);
    uint16_t packets = len / MAX_RECIEVE_SIZE;
    uint16_t remain = len % MAX_RECIEVE_SIZE;
    size_t trans_len = 0;

    xSemaphoreTake(spi_client_io->lock, portMAX_DELAY);

    if (spi_device_acquire_bus(spi_client_io->spi_dev, portMAX_DELAY) != ESP_OK)
    {
        xSemaphoreGive(spi_client_io->lock);
        return ESP_FAIL;
    }

    if (data)
    {
        for (uint16_t i = 0; i < packets; i++)
        {
            trans_len = PACKET_SIZE;
            memset(spi_client_io->buffer, 0, sizeof(spi_client_io->buffer));
            spi_client_io->buffer[0] = FEATURE_TRANSPORT;
            spi_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_READ;
            spi_client_io->buffer[2] = MAX_RECIEVE_SIZE >> 8;
            spi_client_io->buffer[3] = MAX_RECIEVE_SIZE & 0xFF;
            spi_client_io->buffer[4] = 0xFF;
            spi_client_io->buffer[5] = 0xFF;
            spi_trans.tx_buffer = spi_client_io->buffer;
            if (spi_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
            }
            do
            {
                uint16_t chunk_size = trans_len;
                if (chunk_size > spi_client_io->spi_trans_max_bytes)
                {
                    chunk_size = spi_client_io->spi_trans_max_bytes;
                    spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
                }
                else
                {
                    chunk_size = trans_len;
                    spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
                }
                spi_trans.length = chunk_size * 8;
                spi_trans.rxlength = 0;
                spi_trans.rx_buffer = NULL;
                spi_trans.user = spi_client_io;
                ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
                ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
                spi_trans.tx_buffer = spi_trans.tx_buffer + chunk_size;
                trans_len -= chunk_size;
            }
            while (trans_len > 0);
            if (spi_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
            }

            trans_len = MAX_RECIEVE_SIZE;
            spi_trans.rx_buffer = data + i * MAX_RECIEVE_SIZE;
            do
            {
                uint16_t chunk_size = trans_len;
                if (chunk_size > spi_client_io->spi_trans_max_bytes)
                {
                    chunk_size = spi_client_io->spi_trans_max_bytes;
                    spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
                }
                else
                {
                    chunk_size = trans_len;
                    spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
                }
                spi_trans.length = chunk_size * 8;
                spi_trans.tx_buffer = NULL;
                spi_trans.rxlength = chunk_size * 8;
                spi_trans.user = spi_client_io;
                ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
                ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
                spi_trans.rx_buffer = spi_trans.rx_buffer + chunk_size;
                trans_len -= chunk_size;
            }
            while (trans_len > 0);
        }
        if (remain)
        {
            trans_len = PACKET_SIZE;
            memset(spi_client_io->buffer, 0, sizeof(spi_client_io->buffer));
            spi_client_io->buffer[0] = FEATURE_TRANSPORT;
            spi_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_READ;
            spi_client_io->buffer[2] = remain >> 8;
            spi_client_io->buffer[3] = remain & 0xFF;
            spi_client_io->buffer[4] = 0xFF;
            spi_client_io->buffer[5] = 0xFF;
            spi_trans.tx_buffer = spi_client_io->buffer;
            if (spi_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
            }
            do
            {
                uint16_t chunk_size = trans_len;
                if (chunk_size > spi_client_io->spi_trans_max_bytes)
                {
                    chunk_size = spi_client_io->spi_trans_max_bytes;
                    spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
                }
                else
                {
                    chunk_size = trans_len;
                    spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
                }
                spi_trans.rxlength = 0;
                spi_trans.rx_buffer = NULL;
                spi_trans.length = chunk_size * 8;
                spi_trans.user = spi_client_io;
                ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
                ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
                spi_trans.tx_buffer = spi_trans.tx_buffer + chunk_size;
                trans_len -= chunk_size;
            }
            while (trans_len > 0);

            if (spi_client_io->wait_delay > 0)
            {
                vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
            }
            trans_len = remain;
            spi_trans.rx_buffer = data + packets * MAX_RECIEVE_SIZE;
            do
            {
                uint16_t chunk_size = trans_len;
                if (chunk_size > spi_client_io->spi_trans_max_bytes)
                {
                    chunk_size = spi_client_io->spi_trans_max_bytes;
                    spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
                }
                else
                {
                    chunk_size = trans_len;
                    spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
                }
                spi_trans.length = chunk_size * 8;
                spi_trans.tx_buffer = NULL;
                spi_trans.rxlength = chunk_size * 8;
                spi_trans.user = spi_client_io;
                ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
                ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
                spi_trans.rx_buffer = spi_trans.rx_buffer + chunk_size;
                trans_len -= chunk_size;
            }
            while (trans_len > 0);
        }
    }

err:
    spi_device_release_bus(spi_client_io->spi_dev);
    xSemaphoreGive(spi_client_io->lock);
    return ret;
}

static esp_err_t client_io_spi_available(sscma_client_io_t *io, size_t *len)
{
    esp_err_t ret = ESP_OK;
    spi_transaction_t spi_trans = {};
    sscma_client_io_spi_t *spi_client_io = __containerof(io, sscma_client_io_spi_t, base);
    size_t trans_len = 0;
    uint32_t sync_level = 0;

    *len = 0;

    xSemaphoreTake(spi_client_io->lock, portMAX_DELAY);

    if (spi_client_io->sync_gpio_num >= 0)
    {
        if (spi_client_io->io_expander)
        {
            if (esp_io_expander_get_level(spi_client_io->io_expander, spi_client_io->sync_gpio_num, &sync_level) != ESP_OK)
            {
                xSemaphoreGive(spi_client_io->lock);
                return ESP_FAIL;
            }
        }
        else
        {
            sync_level = gpio_get_level(spi_client_io->sync_gpio_num);
        }
        if (sync_level == 0)
        {
            xSemaphoreGive(spi_client_io->lock);
            return ESP_OK;
        }
    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
    }

    if (spi_device_acquire_bus(spi_client_io->spi_dev, portMAX_DELAY) != ESP_OK)
    {
        xSemaphoreGive(spi_client_io->lock);
        return ESP_FAIL;
    }

    trans_len = PACKET_SIZE;
    memset(spi_client_io->buffer, 0, sizeof(spi_client_io->buffer));
    spi_client_io->buffer[0] = FEATURE_TRANSPORT;
    spi_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_AVAILABLE;
    spi_client_io->buffer[2] = 0x00;
    spi_client_io->buffer[3] = 0x00;
    spi_client_io->buffer[4] = 0xFF;
    spi_client_io->buffer[5] = 0xFF;
    spi_trans.tx_buffer = spi_client_io->buffer;
    if (spi_client_io->wait_delay > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
    }
    do
    {
        uint16_t chunk_size = trans_len;
        if (chunk_size > spi_client_io->spi_trans_max_bytes)
        {
            chunk_size = spi_client_io->spi_trans_max_bytes;
            spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
        }
        else
        {
            chunk_size = trans_len;
            spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
        }
        spi_trans.length = chunk_size * 8;
        spi_trans.rxlength = 0;
        spi_trans.rx_buffer = NULL;
        spi_trans.user = spi_client_io;
        ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
        ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
        spi_trans.tx_buffer = spi_trans.tx_buffer + chunk_size;
        trans_len -= chunk_size;
    }
    while (trans_len > 0);

    spi_trans.length = 2 * 8;
    spi_trans.tx_buffer = NULL;
    spi_trans.rxlength = 2 * 8; // 8 bits per byte
    spi_trans.rx_buffer = spi_client_io->buffer;
    spi_trans.user = spi_client_io;
    spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
    memset(spi_client_io->buffer, 0, sizeof(spi_client_io->buffer));
    if (spi_client_io->wait_delay > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
    }
    ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
    ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
    *len = (spi_client_io->buffer[0] << 8) | spi_client_io->buffer[1];
    if (*len == 0xFFFF)
    {
        *len = 0;
    }
err:
    spi_device_release_bus(spi_client_io->spi_dev);
    xSemaphoreGive(spi_client_io->lock);
    return ret;
}

static esp_err_t client_io_spi_flush(sscma_client_io_t *io)
{
    esp_err_t ret = ESP_OK;
    spi_transaction_t spi_trans = {};
    sscma_client_io_spi_t *spi_client_io = __containerof(io, sscma_client_io_spi_t, base);
    size_t trans_len = 0;
    uint32_t sync_level = 0;

    xSemaphoreTake(spi_client_io->lock, portMAX_DELAY);

    if (spi_client_io->sync_gpio_num >= 0)
    {
        if (spi_client_io->io_expander)
        {
            if (esp_io_expander_get_level(spi_client_io->io_expander, spi_client_io->sync_gpio_num, &sync_level) != ESP_OK)
            {
                xSemaphoreGive(spi_client_io->lock);
                return ESP_FAIL;
            }
        }
        else
        {
            sync_level = gpio_get_level(spi_client_io->sync_gpio_num);
        }
        if (sync_level == 0)
        {
            xSemaphoreGive(spi_client_io->lock);
            return ESP_OK;
        }
    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
    }

    if (spi_device_acquire_bus(spi_client_io->spi_dev, portMAX_DELAY) != ESP_OK)
    {
        xSemaphoreGive(spi_client_io->lock);
        return ESP_FAIL;
    }

    trans_len = PACKET_SIZE;
    memset(spi_client_io->buffer, 0, sizeof(spi_client_io->buffer));
    spi_client_io->buffer[0] = FEATURE_TRANSPORT;
    spi_client_io->buffer[1] = FEATURE_TRANSPORT_CMD_RESET;
    spi_client_io->buffer[2] = 0x00;
    spi_client_io->buffer[3] = 0x00;
    spi_client_io->buffer[4] = 0xFF;
    spi_client_io->buffer[5] = 0xFF;
    spi_trans.tx_buffer = spi_client_io->buffer;
    if (spi_client_io->wait_delay > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(spi_client_io->wait_delay));
    }
    do
    {
        uint16_t chunk_size = trans_len;
        if (chunk_size > spi_client_io->spi_trans_max_bytes)
        {
            chunk_size = spi_client_io->spi_trans_max_bytes;
            spi_trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
        }
        else
        {
            chunk_size = trans_len;
            spi_trans.flags &= ~SPI_TRANS_CS_KEEP_ACTIVE;
        }
        spi_trans.length = chunk_size * 8;
        spi_trans.rxlength = 0;
        spi_trans.rx_buffer = NULL;
        spi_trans.user = spi_client_io;
        ret = spi_device_transmit(spi_client_io->spi_dev, &spi_trans);
        ESP_GOTO_ON_ERROR(ret, err, TAG, "spi transmit (queue) failed");
        spi_trans.tx_buffer = spi_trans.tx_buffer + chunk_size;
        trans_len -= chunk_size;
    }
    while (trans_len > 0);

err:
    spi_device_release_bus(spi_client_io->spi_dev);
    xSemaphoreGive(spi_client_io->lock);
    return ret;
}