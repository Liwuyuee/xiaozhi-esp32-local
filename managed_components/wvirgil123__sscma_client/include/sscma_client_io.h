#pragma once

#include <stdbool.h>
#include "soc/soc_caps.h"
#include "esp_err.h"
#include "esp_io_expander.h"

#include "sscma_client_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *sscma_client_spi_bus_handle_t;  /*!< Type of SSCMA SPI bus handle */
typedef void *sscma_client_i2c_bus_handle_t;  /*!< Type of SSCMA I2C bus handle */
typedef void *sscma_client_uart_bus_handle_t; /*!< Type of SSCMA UART bus handle */

/**
 * @brief Client IO configuration structure, for SPI interface
 */
typedef struct
{
    int cs_gpio_num;   /*!< GPIO used for CS line */
    int sync_gpio_num; /*!< GPIO used for SYNC line */
    int spi_mode;
    int wait_delay;                       /*!< Traditional SPI mode (0~3) */
    unsigned int pclk_hz;                 /*!< Frequency of pixel clock */
    size_t trans_queue_depth;             /*!< Size of internal transaction queue */
    void *user_ctx;                       /*!< User private data, passed directly to on_color_trans_done's user_ctx */
    esp_io_expander_handle_t io_expander; /*!< IO expander handle */
    struct
    {
        unsigned int octal_mode : 1;        /*!< transmit with octal mode (8 data lines), this mode is used to simulate Intel 8080 timing */
        unsigned int sio_mode : 1;          /*!< Read and write through a single data line (MOSI) */
        unsigned int lsb_first : 1;         /*!< transmit LSB bit first */
        unsigned int cs_high_active : 1;    /*!< CS line is high active */
        unsigned int sync_high_active : 1;  /*!< SYNC line is high active */
        unsigned int sync_use_expander : 1; /*!< SYNC line use IO expander */
    } flags;
} sscma_client_io_spi_config_t;

/**
 * @brief Create SSCMA client IO handle, for SPI interface
 *
 * @param[in] bus SPI bus handle
 * @param[in] io_config IO configuration, for SPI interface
 * @param[out] ret_io Returned IO handle
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NO_MEM        if out of memory
 *          - ESP_OK                on success
 */

esp_err_t sscma_client_new_io_spi_bus(sscma_client_spi_bus_handle_t bus, const sscma_client_io_spi_config_t *io_config, sscma_client_io_handle_t *ret_io);

/**
 * @brief Client IO configuration structure, for I2C interface
 *
 */
typedef struct
{
    uint32_t dev_addr; /*!< I2C device address */
    int wait_delay;
    void *user_ctx; /*!< User private data, passed directly to user_ctx */
} sscma_client_io_i2c_config_t;

/**
 * @brief Create SSCMA client IO handle, for I2C interface
 *
 * @param[in] bus I2C bus handle
 * @param[in] io_config IO configuration, for I2C interface
 * @param[out] ret_io Returned IO handle
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NO_MEM        if out of memory
 *          - ESP_OK                on success
 */
esp_err_t sscma_client_new_io_i2c_bus(sscma_client_i2c_bus_handle_t bus, const sscma_client_io_i2c_config_t *io_config, sscma_client_io_handle_t *ret_io);

/**
 * @brief Client IO configuration structure, for uart interface
 *
 */
typedef struct
{
    void *user_ctx; /*!< User private data, passed directly to user_ctx */
} sscma_client_io_uart_config_t;

/**
 * @brief Create SSCMA client IO handle, for uart interface
 *
 * @param[in] bus UART bus handle
 * @param[in] io_config IO configuration, for uart interface
 * @param[out] ret_io Returned IO handle
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NO_MEM        if out of memory
 *          - ESP_OK                on success
 */
esp_err_t sscma_client_new_io_uart_bus(sscma_client_uart_bus_handle_t bus, const sscma_client_io_uart_config_t *io_config, sscma_client_io_handle_t *ret_io);

/**
 * @brief Destory SSCMA client IO handle
 *
 * @param[in] io IO handle
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_del_io(sscma_client_io_handle_t io);

/**
 * @brief Write data to SSCMA client IO
 *
 * @param[in] io IO handle
 * @param[in] data Data to be written
 * @param[in] size Size of data
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_OK                on success
 */
esp_err_t sscma_client_io_write(sscma_client_io_handle_t io, const void *data, size_t size);

/**
 * @brief Read data from SSCMA client IO
 *
 * @param[in] io IO handle
 * @param[in] data Data to be read
 * @param[in] size Size of data
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_OK                on success
 */
esp_err_t sscma_client_io_read(sscma_client_io_handle_t io, void *data, size_t size);

/**
 * @brief Get available size of data
 *
 * @param[in] io IO handle
 * @param[out] len Available size
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_OK
 */
esp_err_t sscma_client_io_available(sscma_client_io_handle_t io, size_t *len);

/**
 * @brief Flush data
 *
 * @param[in] io IO handle
 * @return
 *          - ESP_OK
 */
esp_err_t sscma_client_io_flush(sscma_client_io_handle_t io);

#ifdef __cplusplus
}
#endif
