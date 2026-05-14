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

static const char *TAG = "sscma_client.flasher.we2.uart";

#define OTA_ENTER_CMD     "1"
#define OTA_ENTER_HINT    "Send data using the xmodem protocol from your terminal"
#define OTA_ENTER_TIMEOUT 5000
#define OTA_DONE_HINT     "Do you want to end file transmission and reboot system?"
#define OTA_DONE_TIMEOUT  60000

#define XSOH  0x01 // Start Of Header
#define XSTX  0x02
#define XETX  0x03
#define XEOT  0x04 // End Of Transfer
#define XENQ  0x05
#define XACK  0x06 // ACK
#define XNACK 0x15 // NACK
#define XETB  0x17 //
#define XCAN  0x18 // CANCEL
#define XC    0x43
#define XEOF  0x1A

#define XMODEM_BLOCK_SIZE     128
#define XMODEM_RX_BUFFER_SIZE 1024

#define WRITE_BLOCK_MAX_RETRIES      15
#define TRANSFER_ACK_TIMEOUT         30000 // 30 seconds
#define TRANSFER_EOT_TIMEOUT         30000 // 30 seconds
#define TRANSFER_ETB_TIMEOUT         30000 // 30 seconds
#define TRANSFER_WRITE_BLOCK_TIMEOUT 30000 // 30 seconds

static esp_err_t sscma_client_flasher_we2_start(sscma_client_flasher_handle_t flasher, size_t offset);
static esp_err_t sscma_client_flasher_we2_write(sscma_client_flasher_handle_t flasher, const void *data, size_t len);
static esp_err_t sscma_client_flasher_we2_finish(sscma_client_flasher_handle_t flasher);
static esp_err_t sscma_client_flasher_we2_abort(sscma_client_flasher_handle_t flasher);
static esp_err_t sscma_client_flasher_we2_del(sscma_client_flasher_handle_t flasher);

typedef enum {
    INITIAL,
    WAIT_FOR_C,
    WAIT_FOR_C_TIMEOUT,
    WAIT_FOR_C_ACK,
    WRITE_BLOCK_FAILED,
    ABORT_TRANSFER,
    WRITE_BLOCK,
    C_ACK_RECEIVED,
    COMPLETE,
    WRITE_EOT,
    WAIT_FOR_EOT_ACK,
    TIMEOUT_EOT,
    WRITE_BLOCK_TIMEOUT,
    WRITE_ETB,
    WAIT_FOR_ETB_ACK,
    TIMEOUT_ETB,
    WAIT_WRITE_BLOCK,
    FAILED,
    FINAL,
} xmodem_state_t;

typedef struct xmodem_packet_t
{
    uint8_t preamble;
    uint8_t id;
    uint8_t id_complement;
    uint8_t data[XMODEM_BLOCK_SIZE];
    union
    {
        uint8_t data[2];
        uint16_t value;
    } crc;
} __attribute__((packed, aligned(1))) xmodem_packet_t;

typedef struct
{
    sscma_client_flasher_t base;          /*!< The base class. */
    sscma_client_io_t *io;                /*!< The IO interface. */
    esp_io_expander_handle_t io_expander; /* !< IO expander handle */
    int reset_gpio_num;                   /*!< The reset GPIO number. */
    bool reset_level;                     /*!< The reset GPIO level. */
    void *user_ctx;                       /* !< User context */
    SemaphoreHandle_t lock;               /*!< The lock. */
    xmodem_state_t state;                 /*!< The state of the flasher. */
    xmodem_packet_t cur_packet;           /*!< The current packet being transmitted. */
    uint8_t cur_packet_id;                /*!< The ID of the current packet. */
    int64_t cur_time;                     /*!< The current time. */
    struct
    {
        char *data;         /* !< Data buffer */
        size_t len;         /* !< Data length */
        size_t pos;         /* !< Data position */
    } rx_buffer, tx_buffer; /* !< RX and TX buffer */
    uint32_t xfer_size;
    uint8_t write_block_retries; /*!< The write block retries. */
} sscma_client_flasher_we2_uart_t;

static inline bool xmodem_calculate_crc(const uint8_t *data, const uint32_t size, uint16_t *result)
{
    uint16_t crc = 0x0;
    uint32_t count = size;
    bool status = false;
    uint8_t i = 0;

    if (0 != data && 0 != result)
    {
        status = true;

        while (0 < count--)
        {
            crc = crc ^ (uint16_t)*data << 8;
            data++;
            i = 8;

            do
            {
                if (0x8000 & crc)
                {
                    crc = crc << 1 ^ 0x1021;
                }
                else
                {
                    crc = crc << 1;
                }
            }
            while (0 < --i);
        }
        *result = ((crc & 0xFF) << 8) + ((crc >> 8) & 0xFF);
    }

    return status;
}

static inline bool xmodem_verify_packet(const xmodem_packet_t packet, uint8_t expected_packet_id)
{
    bool status = false;
    uint8_t crc_status = false;
    uint16_t calculated_crc = 0;

    crc_status = xmodem_calculate_crc(packet.data, XMODEM_BLOCK_SIZE, &calculated_crc);

    if (packet.preamble == XSOH && packet.id == expected_packet_id && packet.id_complement == 0xFF - packet.id && crc_status && calculated_crc == packet.crc.value)
    {
        status = true;
    }

    return status;
}

static inline bool xmodem_timeout(sscma_client_flasher_we2_uart_t *flasher_we2, int64_t timeout)
{
    if (esp_timer_get_time() - flasher_we2->cur_time >= (timeout * 1000))
    {
        return true;
    }

    vTaskDelay(1 / portTICK_PERIOD_MS);

    return false;
}

static xmodem_state_t xmodem_process(sscma_client_flasher_we2_uart_t *flasher)
{
    uint8_t response = 0;
    uint8_t ctrl = 0;
    size_t rlen = 0;
    uint16_t crc = 0;

    switch (flasher->state)
    {
        case INITIAL: {
            flasher->state = WAIT_FOR_C;
            flasher->cur_time = esp_timer_get_time();
            break;
        }
        case WAIT_FOR_C: {
            if (sscma_client_io_available(flasher->io, &rlen) == ESP_OK && rlen)
            {
                sscma_client_io_read(flasher->io, &response, 1);
                if (response == XC)
                {
                    flasher->state = WRITE_BLOCK;
                    flasher->cur_time = esp_timer_get_time();
                }
            }
            else if (xmodem_timeout(flasher, TRANSFER_ACK_TIMEOUT))
            {
                flasher->state = WAIT_FOR_C_TIMEOUT;
            }
            break;
        }
        case WRITE_BLOCK: {
            if (flasher->tx_buffer.data == NULL || flasher->tx_buffer.len == 0)
            {
                break;
            }
            /* setup current packet */
            if (flasher->cur_packet.id != flasher->cur_packet_id || flasher->cur_packet_id == 1)
            {
                flasher->cur_packet.preamble = XSOH;
                flasher->cur_packet.id = flasher->cur_packet_id;
                flasher->cur_packet.id_complement = 0xFF - flasher->cur_packet_id;
                memset(flasher->cur_packet.data, 0xFF, XMODEM_BLOCK_SIZE);
                flasher->xfer_size = flasher->tx_buffer.len - flasher->tx_buffer.pos > XMODEM_BLOCK_SIZE ? XMODEM_BLOCK_SIZE : flasher->tx_buffer.len - flasher->tx_buffer.pos;
                memcpy(flasher->cur_packet.data, flasher->tx_buffer.data + flasher->tx_buffer.pos, flasher->xfer_size);
                xmodem_calculate_crc(flasher->cur_packet.data, XMODEM_BLOCK_SIZE, &crc);
                flasher->cur_packet.crc.value = crc;
            }
            sscma_client_io_write(flasher->io, (uint8_t *)&flasher->cur_packet, sizeof(xmodem_packet_t));
            flasher->cur_packet_id++;
            flasher->tx_buffer.pos += flasher->xfer_size;
            flasher->state = WAIT_FOR_C_ACK;
            flasher->cur_time = esp_timer_get_time();

            break;
        }
        case WAIT_WRITE_BLOCK: {
            if (flasher->tx_buffer.data != NULL && flasher->tx_buffer.len != 0)
            {
                flasher->state = WRITE_BLOCK;
            }
            break;
        }
        case WAIT_FOR_C_ACK: {
            if (sscma_client_io_available(flasher->io, &rlen) == ESP_OK && rlen)
            {
                sscma_client_io_read(flasher->io, &response, 1);
                flasher->cur_time = esp_timer_get_time();
                switch (response)
                {
                    case XACK: {
                        flasher->state = C_ACK_RECEIVED;
                        break;
                    }
                    case XNACK: {
                        flasher->state = WRITE_BLOCK_FAILED;
                        break;
                    }
                    case XEOF: {
                        flasher->state = COMPLETE;
                        break;
                    }
                    default:
                        break;
                }
            }
            else if (xmodem_timeout(flasher, TRANSFER_ACK_TIMEOUT))
            {
                flasher->state = WRITE_BLOCK_TIMEOUT;
            }
            break;
        }
        case WRITE_BLOCK_FAILED: {
            if (flasher->write_block_retries > WRITE_BLOCK_MAX_RETRIES)
            {
                flasher->state = ABORT_TRANSFER;
            }
            else
            {
                flasher->state = WRITE_BLOCK;
                flasher->cur_packet_id--;
                flasher->tx_buffer.pos -= flasher->xfer_size;
                flasher->write_block_retries++;
            }
            break;
        }
        case C_ACK_RECEIVED: {
            if (flasher->tx_buffer.pos >= flasher->tx_buffer.len)
            {
                flasher->tx_buffer.len = 0;
                flasher->tx_buffer.data = NULL;
                flasher->state = WAIT_WRITE_BLOCK;
            }
            else
            {
                flasher->write_block_retries = 0;
                flasher->state = WRITE_BLOCK;
            }

            break;
        }
        case WRITE_EOT: {
            ctrl = XEOT;
            sscma_client_io_write(flasher->io, (uint8_t *)&ctrl, sizeof(char));
            flasher->state = WAIT_FOR_EOT_ACK;
            break;
        }
        case WAIT_FOR_EOT_ACK: {
            if (sscma_client_io_available(flasher->io, &rlen) == ESP_OK && rlen)
            {
                sscma_client_io_read(flasher->io, &response, 1);
                switch (response)
                {
                    case XACK:
                        flasher->state = COMPLETE;
                        break;
                    case XNACK:
                        flasher->state = ABORT_TRANSFER;
                        break;
                    default:
                        break;
                }
            }
            else if (xmodem_timeout(flasher, TRANSFER_EOT_TIMEOUT))
            {
                flasher->state = TIMEOUT_EOT;
            }
            break;
        }
        case COMPLETE: {
            ctrl = XEOT;
            sscma_client_io_write(flasher->io, (uint8_t *)&ctrl, sizeof(char));
            flasher->state = FINAL;
            break;
        }
        case ABORT_TRANSFER: {
            ctrl = XCAN;
            sscma_client_io_write(flasher->io, (uint8_t *)&ctrl, sizeof(char));
            flasher->state = FINAL;
            break;
        }
        case TIMEOUT_EOT: {
            flasher->state = ABORT_TRANSFER;
            break;
        }
        case WRITE_BLOCK_TIMEOUT: {
            flasher->state = WRITE_BLOCK_FAILED;
            break;
        }
        default: {
            flasher->state = ABORT_TRANSFER;
            break;
        }
    }

    return flasher->state;
}

esp_err_t xmodem_start(sscma_client_flasher_we2_uart_t *flasher)
{
    esp_err_t ret = ESP_OK;

    flasher->state = INITIAL;
    flasher->cur_packet_id = 1;
    flasher->tx_buffer.data = NULL;
    flasher->tx_buffer.len = 0;
    flasher->tx_buffer.pos = 0;
    flasher->xfer_size = 0;
    flasher->cur_time = esp_timer_get_time();
    do
    {
        xmodem_process(flasher);
        if (flasher->state == WRITE_BLOCK)
        {
            ret = ESP_OK;
            break;
        }
        if (flasher->state == WAIT_FOR_C_TIMEOUT)
        {
            ret = ESP_ERR_TIMEOUT;
            break;
        }
    }
    while ((esp_timer_get_time() - flasher->cur_time) / 1000 < TRANSFER_ACK_TIMEOUT);

    return ret;
}

esp_err_t xmodem_write(sscma_client_flasher_we2_uart_t *flasher, const void *data, size_t len)
{
    esp_err_t ret = ESP_OK;

    flasher->tx_buffer.data = (char *)data;
    flasher->tx_buffer.pos = 0;
    flasher->tx_buffer.len = len;
    flasher->xfer_size = 0;

    do
    {
        xmodem_process(flasher);
        if (flasher->state == WAIT_WRITE_BLOCK)
        {
            ret = ESP_OK;
            break;
        }
        if (flasher->state == WRITE_BLOCK_TIMEOUT)
        {
            ret = ESP_ERR_TIMEOUT;
            break;
        }
        if (flasher->state == FAILED)
        {
            ret = ESP_FAIL;
            break;
        }
    }
    while (1);

    return ret;
}

esp_err_t xmodem_finish(sscma_client_flasher_we2_uart_t *flasher)
{
    esp_err_t ret = ESP_OK;

    flasher->state = WRITE_EOT;
    flasher->cur_packet_id = -1;
    flasher->tx_buffer.data = NULL;
    flasher->tx_buffer.len = 0;
    flasher->tx_buffer.pos = 0;
    flasher->xfer_size = 0;
    do
    {
        xmodem_process(flasher);
        if (flasher->state == COMPLETE)
        {
            ret = ESP_OK;
            break;
        }
        if (flasher->state == WRITE_BLOCK_TIMEOUT)
        {
            ret = ESP_ERR_TIMEOUT;
            break;
        }
        if (flasher->state == FAILED)
        {
            ret = ESP_FAIL;
            break;
        }
    }
    while (1);

    return ret;
}

esp_err_t xmodem_abort(sscma_client_flasher_we2_uart_t *flasher)
{
    esp_err_t ret = ESP_OK;

    flasher->state = ABORT_TRANSFER;
    flasher->tx_buffer.data = NULL;
    flasher->tx_buffer.len = 0;
    flasher->tx_buffer.pos = 0;
    flasher->xfer_size = 0;

    do
    {
        xmodem_process(flasher);
        if (flasher->state == FINAL)
        {
            ret = ESP_OK;
            break;
        }
        if (flasher->state == TIMEOUT_EOT)
        {
            ret = ESP_ERR_TIMEOUT;
            break;
        }
        if (flasher->state == FAILED)
        {
            ret = ESP_FAIL;
            break;
        }
    }
    while (1);

    return ret;
}

esp_err_t sscma_client_new_flasher_we2_uart(const sscma_client_io_handle_t io, const sscma_client_flasher_we2_config_t *config, sscma_client_flasher_handle_t *ret_flasher)
{
    esp_err_t ret = ESP_OK;
    sscma_client_flasher_we2_uart_t *flasher_we2 = NULL;

    ESP_RETURN_ON_FALSE(io && config && ret_flasher, ESP_ERR_INVALID_ARG, TAG, "invalid argument");

    flasher_we2 = (sscma_client_flasher_we2_uart_t *)calloc(1, sizeof(sscma_client_flasher_we2_uart_t));

    ESP_RETURN_ON_FALSE(flasher_we2, ESP_ERR_NO_MEM, TAG, "no mem for flasher");

    flasher_we2->reset_gpio_num = config->reset_gpio_num;
    flasher_we2->reset_level = config->flags.reset_high_active ? 1 : 0;

    flasher_we2->io = io;

    flasher_we2->tx_buffer.data = NULL;
    flasher_we2->tx_buffer.len = 0;
    flasher_we2->tx_buffer.pos = 0;
    flasher_we2->xfer_size = 0;

    flasher_we2->state = INITIAL;
    flasher_we2->cur_packet_id = 0;
    flasher_we2->cur_time = esp_timer_get_time();
    flasher_we2->write_block_retries = 0;

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

    flasher_we2->rx_buffer.data = (char *)malloc(XMODEM_RX_BUFFER_SIZE);
    ESP_GOTO_ON_FALSE(flasher_we2->rx_buffer.data, ESP_ERR_NO_MEM, err, TAG, "no mem for rx buffer");
    flasher_we2->rx_buffer.pos = 0;
    flasher_we2->rx_buffer.len = XMODEM_RX_BUFFER_SIZE;

    flasher_we2->lock = xSemaphoreCreateMutex();

    ESP_GOTO_ON_FALSE(flasher_we2->lock, ESP_ERR_NO_MEM, err, TAG, "no mem for flasher lock");

    *ret_flasher = &flasher_we2->base;

    return ESP_OK;

err:
    if (flasher_we2->rx_buffer.data)
    {
        free(flasher_we2->rx_buffer.data);
    }
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
    sscma_client_flasher_we2_uart_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_uart_t, base);
    if (flasher_we2->rx_buffer.data)
    {
        free(flasher_we2->rx_buffer.data);
    }
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
    size_t rlen = 0;
    sscma_client_flasher_we2_uart_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_uart_t, base);

    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);

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
    else
    {
        ESP_GOTO_ON_ERROR(sscma_client_io_write(flasher_we2->io, CMD_PREFIX CMD_AT_RESET CMD_SUFFIX, sizeof(CMD_PREFIX CMD_AT_RESET CMD_SUFFIX) - 1), err, TAG, "reset sscma failed");
        vTaskDelay(50 / portTICK_PERIOD_MS); // wait for sscma to be ready
    }

    // enter ota mode
    flasher_we2->rx_buffer.pos = 0;
    start = esp_timer_get_time();
    ret = ESP_ERR_TIMEOUT;
    sscma_client_io_flush(flasher_we2->io);
    do
    {
        sscma_client_io_write(flasher_we2->io, OTA_ENTER_CMD, sizeof(OTA_ENTER_CMD) - 1);
        if (sscma_client_io_available(flasher_we2->io, &rlen) == ESP_OK && rlen > 0)
        {
            if (rlen + flasher_we2->rx_buffer.pos > flasher_we2->rx_buffer.len)
            {
                ret = ESP_ERR_NO_MEM;
                break;
            }
            for (int i = 0; i < rlen; i++)
            {
                char c = '\0';
                sscma_client_io_read(flasher_we2->io, &c, 1);
                if (isprint(c))
                {
                    flasher_we2->rx_buffer.data[flasher_we2->rx_buffer.pos++] = c;
                }
            }
            flasher_we2->rx_buffer.data[flasher_we2->rx_buffer.pos] = 0;
            if (strnstr(flasher_we2->rx_buffer.data, OTA_ENTER_HINT, flasher_we2->rx_buffer.pos) != NULL)
            {
                vTaskDelay(100 / portTICK_PERIOD_MS);
                ret = ESP_OK;
                break;
            }
        }
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
    while ((esp_timer_get_time() - start) / 1000 < OTA_ENTER_TIMEOUT);

    ESP_GOTO_ON_ERROR(ret, err, TAG, "enter ota mode failed");

    // write offset config
    if (offset != 0)
    {
        char config[12] = { 0xC0, 0x5A, (offset >> 0) & 0xFF, (offset >> 8) & 0xFF, (offset >> 16) & 0xFF, (offset >> 24) & 0xFF, 0x00, 0x00, 0x00, 0x00, 0x5A, 0xC0 };

        ESP_GOTO_ON_ERROR(xmodem_start(flasher_we2), err, TAG, "write config failed");

        ESP_GOTO_ON_ERROR(xmodem_write(flasher_we2, config, sizeof(config)), err, TAG, "write config failed");

        ESP_GOTO_ON_ERROR(xmodem_finish(flasher_we2), err, TAG, "write config failed");

        flasher_we2->tx_buffer.pos = 0;
        start = esp_timer_get_time();
        ret = ESP_ERR_TIMEOUT;
        do
        {
            if (sscma_client_io_available(flasher_we2->io, &rlen) == ESP_OK && rlen > 0)
            {
                if (rlen + flasher_we2->rx_buffer.pos > flasher_we2->rx_buffer.len)
                {
                    ret = ESP_ERR_NO_MEM;
                    break;
                }
                for (int i = 0; i < rlen; i++)
                {
                    char c = '\0';
                    sscma_client_io_read(flasher_we2->io, &c, 1);
                    if (isprint(c))
                    {
                        flasher_we2->rx_buffer.data[flasher_we2->rx_buffer.pos++] = c;
                    }
                }
                flasher_we2->rx_buffer.data[flasher_we2->rx_buffer.pos] = 0;
                if (strnstr(flasher_we2->rx_buffer.data, OTA_DONE_HINT, flasher_we2->rx_buffer.pos) != NULL)
                {
                    sscma_client_io_write(flasher_we2->io, "n", 1);
                    ret = ESP_OK;
                    break;
                }
            }
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
        while ((esp_timer_get_time() - start) / 1000 < OTA_DONE_TIMEOUT);

        ESP_GOTO_ON_ERROR(ret, err, TAG, "enter ota mode failed");
    }

    ESP_GOTO_ON_ERROR(xmodem_start(flasher_we2), err, TAG, "start xmodem failed");

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
    sscma_client_flasher_we2_uart_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_uart_t, base);

    assert(len % XMODEM_BLOCK_SIZE == 0);

    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);

    ret = xmodem_write(flasher_we2, data, len);

    xSemaphoreGive(flasher_we2->lock);

    return ret;
}
static esp_err_t sscma_client_flasher_we2_finish(sscma_client_flasher_handle_t flasher)
{
    esp_err_t ret = ESP_OK;
    int64_t start = 0;
    size_t rlen = 0;
    sscma_client_flasher_we2_uart_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_uart_t, base);

    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);

    ret = xmodem_finish(flasher_we2);

    flasher_we2->tx_buffer.pos = 0;
    start = esp_timer_get_time();
    ret = ESP_ERR_TIMEOUT;
    do
    {
        if (sscma_client_io_available(flasher_we2->io, &rlen) == ESP_OK && rlen > 0)
        {
            if (rlen + flasher_we2->rx_buffer.pos > flasher_we2->rx_buffer.len)
            {
                ret = ESP_ERR_NO_MEM;
                break;
            }
            for (int i = 0; i < rlen; i++)
            {
                char c = '\0';
                sscma_client_io_read(flasher_we2->io, &c, 1);
                if (isprint(c))
                {
                    flasher_we2->rx_buffer.data[flasher_we2->rx_buffer.pos++] = c;
                }
            }
            flasher_we2->rx_buffer.data[flasher_we2->rx_buffer.pos] = 0;
            if (strnstr(flasher_we2->rx_buffer.data, OTA_DONE_HINT, flasher_we2->rx_buffer.pos) != NULL)
            {
                sscma_client_io_write(flasher_we2->io, "y", 1);
                ret = ESP_OK;
                break;
            }
        }
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
    while ((esp_timer_get_time() - start) / 1000 < OTA_DONE_TIMEOUT);

    ESP_GOTO_ON_ERROR(ret, err, TAG, "finish ota failed");

    vTaskDelay(100 / portTICK_PERIOD_MS);

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
    sscma_client_flasher_we2_uart_t *flasher_we2 = __containerof(flasher, sscma_client_flasher_we2_uart_t, base);

    xSemaphoreTake(flasher_we2->lock, portMAX_DELAY);

    ret = xmodem_abort(flasher_we2);

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