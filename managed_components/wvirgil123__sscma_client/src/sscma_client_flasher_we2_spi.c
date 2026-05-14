#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/cdefs.h>
#include "sdkconfig.h"
#if CONFIG_SSCMA_ENABLE_DEBUG_LOG
// The local log level must be defined before including esp_log.h
// Set the maximum log level for this source file
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#endif
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_check.h"
#include "esp_timer.h"

#include "sscma_client_commands.h"
#include "sscma_client_io.h"
#include "sscma_client_io_interface.h"
#include "sscma_client_flasher.h"
#include "sscma_client_flasher_interface.h"
#include "driver/spi_master.h"

static const char *TAG = "sscma_client.flasher.we2.spi";

typedef enum {
    REG_OFF = 0x00,
    REG_BYPASS_CACHE = 0x00, // removeds
    REG_ISP_WRITE_EN = 0x01,
    REG_XIP_EN = 0x02,
    REG_ISP_TEST_MODE = 0x04,
    REG_D8_ISP_EN = 0x01,
    REG_D8_TEST_MODE = 0x02,
    REG_D8_SPI_DO_EN = 0x04,
} FlashSubMod_t;

#define OTA_MAX_OFFSET (0x1000000) // 16 MB

#define OTA_BASE_ADDR    (0x38000000)
#define OTA_START_OFFSET (0x400000)

#define OTA_CONTROL_ADDR      (0x51010000)
#define OTA_PPDONE_COUNT_ADDR (OTA_CONTROL_ADDR + 0x40)
#define OTA_CRC_WRITTEN_ADDR  (OTA_CONTROL_ADDR + 0x04)
#define OTA_CRC_READ_ADDR     (OTA_CONTROL_ADDR + 0x08)
#define OTA_CRC_CLEAR_ADDR    (OTA_CONTROL_ADDR + 0x30)

#define OTA_CONTROL_REG_DEFAULT (0x028C208B)

#define OTA_CHUNKED_SIZE (256)

#define OTA_CMD_WRITE        (0xF2)
#define OTA_CMD_READ         (0xF3)
#define OTA_ENABLE_REG       (0xD8)
#define OTA_STATUS_REG       (0x0C)
#define OTA_BURST_MODE_REG   (0x0D)
#define OTA_BURST_ENABLE_REG (0x13)
#define OTA_BURST_WRITE_REG  (0x00)
#define OTA_PP_STATUS_REG    (0x1D)

static esp_err_t sscma_client_flasher_we2_start(sscma_client_flasher_handle_t flasher, size_t offset);
static esp_err_t sscma_client_flasher_we2_write(sscma_client_flasher_handle_t flasher, const void *data, size_t len);
static esp_err_t sscma_client_flasher_we2_finish(sscma_client_flasher_handle_t flasher);
static esp_err_t sscma_client_flasher_we2_abort(sscma_client_flasher_handle_t flasher);
static esp_err_t sscma_client_flasher_we2_del(sscma_client_flasher_handle_t flasher);

typedef struct
{
    sscma_client_flasher_t base;          /*!< The base class. */
    sscma_client_io_t *io;                /*!< The IO interface. */
    esp_io_expander_handle_t io_expander; /* !< IO expander handle */
    int reset_gpio_num;                   /*!< The reset GPIO number. */
    bool reset_level;                     /*!< The reset GPIO level. */
    size_t offset;                        /*!< The offset. */
    uint32_t count;                       /*!< The Page Program Count. */
    void *user_ctx;                       /* !< User context */
    uint8_t data[OTA_CHUNKED_SIZE + 6];   /* !< The data buffer. */
    SemaphoreHandle_t lock;               /*!< The lock. */
} sscma_client_flasher_we2_spi_t;

esp_err_t sscma_client_new_flasher_we2_spi(const sscma_client_io_handle_t io, const sscma_client_flasher_we2_config_t *config, sscma_client_flasher_handle_t *ret_flasher)
{
    esp_err_t ret = ESP_OK;
    sscma_client_flasher_we2_spi_t *flasher_we2 = NULL;

    ESP_RETURN_ON_FALSE(io && config && ret_flasher, ESP_ERR_INVALID_ARG, TAG, "invalid argument");

    flasher_we2 = (sscma_client_flasher_we2_spi_t *)calloc(1, sizeof(sscma_client_flasher_we2_spi_t));

    ESP_RETURN_ON_FALSE(flasher_we2, ESP_ERR_NO_MEM, TAG, "no mem for flasher");

    flasher_we2->reset_gpio_num = config->reset_gpio_num;
    flasher_we2->reset_level = config->flags.reset_high_active ? 1 : 0;

    flasher_we2->io = io;

    flasher_we2->base.start = sscma_client_flasher_we2_start;
    flasher_we2->base.write = sscma_client_flasher_we2_write;
    flasher_we2->base.finish = sscma_client_flasher_we2_finish;
    flasher_we2->base.abort = sscma_client_flasher_we2_abort;
    flasher_we2->base.del = sscma_client_flasher_we2_del;

    if (config->flags.reset_use_expander)
    {
        flasher_we2->io_expander = config->io_expander;
        ESP_GOTO_ON_FALSE(flasher_we2->io_expander, ESP_ERR_INVALID_ARG, err, TAG, "invalid io expander");
        ESP_GOTO_ON_ERROR(esp_io_expander_set_dir(flasher_we2->io_expander, config->reset_gpio_num, IO_EXPANDER_OUTPUT), err, TAG, "set GPIO direction failed");
    }
    else
    {
        gpio_config_t io_conf = {
            .mode = GPIO_MODE_INPUT,
            .pin_bit_mask = 1ULL << config->reset_gpio_num,
        };
        ESP_GOTO_ON_ERROR(gpio_config(&io_conf), err, TAG, "configure GPIO for RST line failed");
    }

    flasher_we2->lock = xSemaphoreCreateMutex();

    ESP_GOTO_ON_FALSE(flasher_we2->lock, ESP_ERR_NO_MEM, err, TAG, "no mem for flasher lock");

    *ret_flasher = &flasher_we2->base;

    return ESP_OK;

err:
    if (flasher_we2->lock != NULL)
    {
        vSemaphoreDelete(flasher_we2->lock);
    }
    if (flasher_we2->reset_gpio_num >= 0)
    {
        if (flasher_we2->io_expander)
        {
            esp_io_expander_set_dir(flasher_we2->io_expander, flasher_we2->reset_gpio_num, IO_EXPANDER_INPUT);
        }
        else
        {
            gpio_reset_pin(flasher_we2->reset_gpio_num);
        }
    }
    if (flasher_we2 != NULL)
    {
        free(flasher_we2);
    }

    return ret;
}

esp_err_t sscma_client_flasher_we2_del(sscma_client_flasher_handle_t flasher)
{
    sscma_client_flasher_we2_spi_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_spi_t, base);
    if (flasher_we2->lock != NULL)
    {
        vSemaphoreDelete(flasher_we2->lock);
    }
    if (flasher_we2->reset_gpio_num >= 0)
    {
        if (flasher_we2->io_expander)
        {
            esp_io_expander_set_dir(flasher_we2->io_expander, flasher_we2->reset_gpio_num, IO_EXPANDER_INPUT);
        }
        else
        {
            gpio_reset_pin(flasher_we2->reset_gpio_num);
        }
    }
    if (flasher != NULL)
    {
        free(flasher);
    }
    return ESP_OK;
}

static esp_err_t sscma_client_flasher_we2_start(sscma_client_flasher_handle_t flasher, size_t offset)
{
    esp_err_t ret = ESP_OK;
    int64_t start = 0;
    uint32_t addr = 0;
    size_t remain = 0;
    uint32_t status = 0;
    sscma_client_flasher_we2_spi_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_spi_t, base);
    spi_transaction_t spi_trans = {};

    // assert(offset >= OTA_START_OFFSET);
    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);

    flasher_we2->count = 0;
    flasher_we2->offset = offset;

    ESP_GOTO_ON_ERROR(spi_device_acquire_bus(flasher_we2->io->handle, portMAX_DELAY), err, TAG, "acquire spi bus failed");

    flasher_we2->data[0] = OTA_CMD_WRITE;
    flasher_we2->data[1] = OTA_ENABLE_REG;
    flasher_we2->data[2] = REG_D8_ISP_EN + REG_D8_TEST_MODE + REG_D8_SPI_DO_EN;
    spi_trans.length = 3 * 8;
    spi_trans.tx_buffer = flasher_we2->data;
    spi_trans.rx_buffer = NULL;
    spi_trans.rxlength = 0;
    ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
    if (ret != ESP_OK)
    {
        spi_device_release_bus(flasher_we2->io->handle);
        goto err;
    }

    flasher_we2->data[0] = OTA_CMD_WRITE;
    flasher_we2->data[1] = OTA_BURST_ENABLE_REG;
    flasher_we2->data[2] = 0x31;
    spi_trans.length = 3 * 8;
    spi_trans.tx_buffer = flasher_we2->data;
    spi_trans.rx_buffer = NULL;
    spi_trans.rxlength = 0;
    ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
    if (ret != ESP_OK)
    {
        spi_device_release_bus(flasher_we2->io->handle);
        goto err;
    }

    flasher_we2->data[0] = OTA_CMD_WRITE;
    flasher_we2->data[1] = OTA_BURST_MODE_REG;
    flasher_we2->data[2] = 0x11;
    spi_trans.length = 3 * 8;
    spi_trans.tx_buffer = flasher_we2->data;
    spi_trans.rx_buffer = NULL;
    spi_trans.rxlength = 0;
    ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
    if (ret != ESP_OK)
    {
        spi_device_release_bus(flasher_we2->io->handle);
        goto err;
    }

    flasher_we2->data[0] = OTA_CMD_WRITE;
    flasher_we2->data[1] = 0x00;
    flasher_we2->data[2] = (OTA_CONTROL_ADDR & 0xFF);
    flasher_we2->data[3] = (OTA_CONTROL_ADDR >> 8) & 0xFF;
    flasher_we2->data[4] = (OTA_CONTROL_ADDR >> 16) & 0xFF;
    flasher_we2->data[5] = (OTA_CONTROL_ADDR >> 24) & 0xFF;
    flasher_we2->data[6] = (OTA_CONTROL_REG_DEFAULT & 0xFF);
    flasher_we2->data[7] = (OTA_CONTROL_REG_DEFAULT >> 8) & 0xFF;
    flasher_we2->data[8] = (OTA_CONTROL_REG_DEFAULT >> 16) & 0xFF;
    flasher_we2->data[9] = (OTA_CONTROL_REG_DEFAULT >> 24) & 0xFF;
    spi_trans.length = 10 * 8;
    spi_trans.tx_buffer = flasher_we2->data;
    spi_trans.rx_buffer = NULL;
    spi_trans.rxlength = 0;
    ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
    if (ret != ESP_OK)
    {
        spi_device_release_bus(flasher_we2->io->handle);
        goto err;
    }

    // if offset == 0, clear boot slot magic first
    if (offset == 0)
    {
        ESP_LOGW(TAG, "Writing firmware... clearing magic for boot from slot 0");
        remain = 4096; // magic partition size 4K
        addr = OTA_BASE_ADDR + OTA_MAX_OFFSET - remain;
        // write chunk
        do
        {
            flasher_we2->data[0] = OTA_CMD_WRITE;
            flasher_we2->data[1] = 0x00;
            flasher_we2->data[2] = (addr & 0xFF);
            flasher_we2->data[3] = (addr >> 8) & 0xFF;
            flasher_we2->data[4] = (addr >> 16) & 0xFF;
            flasher_we2->data[5] = (addr >> 24) & 0xFF;
            memset(flasher_we2->data + 6, 0xFF, OTA_CHUNKED_SIZE);
            spi_trans.length = (6 + OTA_CHUNKED_SIZE) * 8;
            spi_trans.tx_buffer = flasher_we2->data;
            spi_trans.rx_buffer = NULL;
            spi_trans.rxlength = 0;
            ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
            if (ret != ESP_OK)
            {
                spi_device_release_bus(flasher_we2->io->handle);
                goto err;
            }

            remain -= OTA_CHUNKED_SIZE;
            addr += OTA_CHUNKED_SIZE;
            flasher_we2->count++;

            // check status
            start = esp_timer_get_time();
            status = 0xFFFFFFFF;
            do
            {
                flasher_we2->data[0] = OTA_CMD_WRITE;
                flasher_we2->data[1] = 0x00;
                flasher_we2->data[2] = (OTA_PPDONE_COUNT_ADDR & 0xFF);
                flasher_we2->data[3] = (OTA_PPDONE_COUNT_ADDR >> 8) & 0xFF;
                flasher_we2->data[4] = (OTA_PPDONE_COUNT_ADDR >> 16) & 0xFF;
                flasher_we2->data[5] = (OTA_PPDONE_COUNT_ADDR >> 24) & 0xFF;
                spi_trans.length = (6) * 8;
                spi_trans.tx_buffer = &flasher_we2->data;
                spi_trans.rx_buffer = NULL;
                spi_trans.rxlength = 0;
                ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
                if (ret != ESP_OK)
                {
                    spi_device_release_bus(flasher_we2->io->handle);
                    goto err;
                }

                flasher_we2->data[0] = OTA_CMD_WRITE;
                flasher_we2->data[1] = OTA_STATUS_REG;
                flasher_we2->data[2] = 0;
                spi_trans.length = (3) * 8;
                spi_trans.tx_buffer = &flasher_we2->data;
                spi_trans.rx_buffer = NULL;
                spi_trans.rxlength = 0;
                ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
                if (ret != ESP_OK)
                {
                    spi_device_release_bus(flasher_we2->io->handle);
                    goto err;
                }
                status = 0;
                memset(&flasher_we2->data[0], 0x00, 7);
                memset(&flasher_we2->data[7], 0xFF, 7);
                flasher_we2->data[0] = OTA_CMD_READ;
                flasher_we2->data[1] = 0x08;
                flasher_we2->data[2] = 0x00;
                spi_trans.length = 7 * 8;
                spi_trans.tx_buffer = &flasher_we2->data[0];
                spi_trans.rx_buffer = &flasher_we2->data[7];
                spi_trans.rxlength = 7 * 8;
                ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
                if (ret != ESP_OK)
                {
                    spi_device_release_bus(flasher_we2->io->handle);
                    goto err;
                }
                memcpy(&status, &flasher_we2->data[10], 4);
                if ((esp_timer_get_time() - start) > 10000000)
                {
                    spi_device_release_bus(flasher_we2->io->handle);
                    ESP_LOGE(TAG, "Timeout");
                    ret = ESP_ERR_TIMEOUT;
                    goto err;
                }
                taskYIELD();
            }
            while (!((status >> 28) == 1 || (status & 0xFFFFF) == flasher_we2->count));
            // CRC Error
            if (((status >> 28) == 1) || (status >> 28) == 3)
            {
                ESP_LOGE(TAG, "CRC Error");
                ret = ESP_FAIL;
                goto err;
            }
        }
        while (remain > 0);
    }

    spi_device_release_bus(flasher_we2->io->handle);

err:
    if (ret != ESP_OK)
    {
        if (flasher_we2->reset_gpio_num >= 0)
        {
            if (flasher_we2->io_expander)
            {
                esp_io_expander_set_level(flasher_we2->io_expander, flasher_we2->reset_gpio_num, flasher_we2->reset_level);
                vTaskDelay(50 / portTICK_PERIOD_MS);
                esp_io_expander_set_level(flasher_we2->io_expander, flasher_we2->reset_gpio_num, !flasher_we2->reset_level);
                vTaskDelay(50);
            }
            else
            {
                gpio_config_t io_conf = {
                    .mode = GPIO_MODE_OUTPUT,
                    .pin_bit_mask = 1ULL << flasher_we2->reset_gpio_num,
                };
                gpio_config(&io_conf);
                gpio_set_level(flasher_we2->reset_gpio_num, flasher_we2->reset_level);
                vTaskDelay(50 / portTICK_PERIOD_MS);
                gpio_set_level(flasher_we2->reset_gpio_num, !flasher_we2->reset_level);
                gpio_reset_pin(flasher_we2->reset_gpio_num);
                vTaskDelay(50);
            }
        }
    }
    xSemaphoreGive(flasher_we2->lock);

    return ret;
}
static esp_err_t sscma_client_flasher_we2_write(sscma_client_flasher_handle_t flasher, const void *data, size_t len)
{
    esp_err_t ret = ESP_OK;
    int64_t start = 0;
    size_t remain = len;
    uint32_t addr = 0;
    uint32_t status = 0;
    spi_transaction_t spi_trans = {};
    sscma_client_flasher_we2_spi_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_spi_t, base);
    assert(len % OTA_CHUNKED_SIZE == 0);
    assert(flasher_we2->offset + len <= OTA_MAX_OFFSET);

    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);
    ESP_GOTO_ON_ERROR(spi_device_acquire_bus(flasher_we2->io->handle, portMAX_DELAY), err, TAG, "acquire spi bus failed");
    do
    {
        // write chunk
        addr = OTA_BASE_ADDR + flasher_we2->offset;
        flasher_we2->data[0] = OTA_CMD_WRITE;
        flasher_we2->data[1] = 0x00;
        flasher_we2->data[2] = (addr & 0xFF);
        flasher_we2->data[3] = (addr >> 8) & 0xFF;
        flasher_we2->data[4] = (addr >> 16) & 0xFF;
        flasher_we2->data[5] = (addr >> 24) & 0xFF;
        memcpy(&flasher_we2->data[6], (uint8_t *)data + (len - remain), OTA_CHUNKED_SIZE);
        spi_trans.length = (6 + OTA_CHUNKED_SIZE) * 8;
        spi_trans.tx_buffer = flasher_we2->data;
        spi_trans.rx_buffer = NULL;
        spi_trans.rxlength = 0;
        ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
        if (ret != ESP_OK)
        {
            spi_device_release_bus(flasher_we2->io->handle);
            goto err;
        }
        remain -= OTA_CHUNKED_SIZE;
        flasher_we2->offset += OTA_CHUNKED_SIZE;
        flasher_we2->count++;

        // check status
        start = esp_timer_get_time();
        status = 0xFFFFFFFF;
        do
        {
            flasher_we2->data[0] = OTA_CMD_WRITE;
            flasher_we2->data[1] = 0x00;
            flasher_we2->data[2] = (OTA_PPDONE_COUNT_ADDR & 0xFF);
            flasher_we2->data[3] = (OTA_PPDONE_COUNT_ADDR >> 8) & 0xFF;
            flasher_we2->data[4] = (OTA_PPDONE_COUNT_ADDR >> 16) & 0xFF;
            flasher_we2->data[5] = (OTA_PPDONE_COUNT_ADDR >> 24) & 0xFF;
            spi_trans.length = (6) * 8;
            spi_trans.tx_buffer = &flasher_we2->data;
            spi_trans.rx_buffer = NULL;
            spi_trans.rxlength = 0;
            ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
            if (ret != ESP_OK)
            {
                spi_device_release_bus(flasher_we2->io->handle);
                goto err;
            }

            flasher_we2->data[0] = OTA_CMD_WRITE;
            flasher_we2->data[1] = OTA_STATUS_REG;
            flasher_we2->data[2] = 0;
            spi_trans.length = (3) * 8;
            spi_trans.tx_buffer = &flasher_we2->data;
            spi_trans.rx_buffer = NULL;
            spi_trans.rxlength = 0;
            ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
            if (ret != ESP_OK)
            {
                spi_device_release_bus(flasher_we2->io->handle);
                goto err;
            }
            status = 0;
            memset(&flasher_we2->data[0], 0x00, 7);
            memset(&flasher_we2->data[7], 0xFF, 7);
            flasher_we2->data[0] = OTA_CMD_READ;
            flasher_we2->data[1] = 0x08;
            flasher_we2->data[2] = 0x00;
            spi_trans.length = 7 * 8;
            spi_trans.tx_buffer = &flasher_we2->data[0];
            spi_trans.rx_buffer = &flasher_we2->data[7];
            spi_trans.rxlength = 7 * 8;
            ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);
            if (ret != ESP_OK)
            {
                spi_device_release_bus(flasher_we2->io->handle);
                goto err;
            }
            memcpy(&status, &flasher_we2->data[10], 4);
            if ((esp_timer_get_time() - start) > 3000000)
            {
                spi_device_release_bus(flasher_we2->io->handle);
                ESP_LOGE(TAG, "Timeout");
                ret = ESP_ERR_TIMEOUT;
                goto err;
            }
            taskYIELD();
        }
        while (!((status >> 28) == 1 || (status & 0xFFFFF) == flasher_we2->count));
        // CRC Error
        if (((status >> 28) == 1) || (status >> 28) == 3)
        {
            ESP_LOGE(TAG, "CRC Error");
            ret = ESP_FAIL;
            goto err;
        }
    }
    while (remain > 0);

    spi_device_release_bus(flasher_we2->io->handle);
err:
    xSemaphoreGive(flasher_we2->lock);

    return ret;
}
static esp_err_t sscma_client_flasher_we2_finish(sscma_client_flasher_handle_t flasher)
{
    esp_err_t ret = ESP_OK;
    spi_transaction_t spi_trans = {};
    sscma_client_flasher_we2_spi_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_spi_t, base);

    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);

    ESP_GOTO_ON_ERROR(spi_device_acquire_bus(flasher_we2->io->handle, portMAX_DELAY), err, TAG, "acquire spi bus failed");

    flasher_we2->data[0] = OTA_CMD_WRITE;
    flasher_we2->data[1] = OTA_ENABLE_REG;
    flasher_we2->data[2] = REG_OFF;
    spi_trans.length = 3 * 8;
    spi_trans.tx_buffer = &flasher_we2->data;
    spi_trans.rx_buffer = NULL;
    spi_trans.rxlength = 0;
    ret = spi_device_transmit(flasher_we2->io->handle, &spi_trans);

    spi_device_release_bus(flasher_we2->io->handle);

err:
    if (flasher_we2->reset_gpio_num >= 0)
    {
        if (flasher_we2->io_expander)
        {
            esp_io_expander_set_level(flasher_we2->io_expander, flasher_we2->reset_gpio_num, flasher_we2->reset_level);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            esp_io_expander_set_level(flasher_we2->io_expander, flasher_we2->reset_gpio_num, !flasher_we2->reset_level);
            vTaskDelay(200);
        }
        else
        {
            gpio_config_t io_conf = {
                .mode = GPIO_MODE_OUTPUT,
                .pin_bit_mask = 1ULL << flasher_we2->reset_gpio_num,
            };
            gpio_config(&io_conf);
            gpio_set_level(flasher_we2->reset_gpio_num, flasher_we2->reset_level);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            gpio_set_level(flasher_we2->reset_gpio_num, !flasher_we2->reset_level);
            gpio_reset_pin(flasher_we2->reset_gpio_num);
            vTaskDelay(200);
        }
    }
    xSemaphoreGive(flasher_we2->lock);

    return ret;
}
static esp_err_t sscma_client_flasher_we2_abort(sscma_client_flasher_handle_t flasher)
{
    esp_err_t ret = ESP_OK;
    sscma_client_flasher_we2_spi_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_spi_t, base);

    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);

    if (flasher_we2->reset_gpio_num >= 0)
    {
        if (flasher_we2->io_expander)
        {
            esp_io_expander_set_level(flasher_we2->io_expander, flasher_we2->reset_gpio_num, flasher_we2->reset_level);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            esp_io_expander_set_level(flasher_we2->io_expander, flasher_we2->reset_gpio_num, !flasher_we2->reset_level);
            vTaskDelay(200);
        }
        else
        {
            gpio_config_t io_conf = {
                .mode = GPIO_MODE_OUTPUT,
                .pin_bit_mask = 1ULL << flasher_we2->reset_gpio_num,
            };
            gpio_config(&io_conf);
            gpio_set_level(flasher_we2->reset_gpio_num, flasher_we2->reset_level);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            gpio_set_level(flasher_we2->reset_gpio_num, !flasher_we2->reset_level);
            gpio_reset_pin(flasher_we2->reset_gpio_num);
            vTaskDelay(200);
        }
    }

    xSemaphoreGive(flasher_we2->lock);

    return ret;
}