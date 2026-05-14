/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "driver/spi_slave.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Enable Camera private SPI slave driver
 */
#if CONFIG_SPIRAM
#define ESP_CAM_SPI_DRIVER 1
#endif

/**
 * @brief Initialize a SPI bus as a slave interface and enable it by default
 *
 * @warning SPI0/1 is not supported
 *
 * @param host          SPI peripheral to use as a SPI slave interface
 * @param bus_config    Pointer to a spi_bus_config_t struct specifying how the host should be initialized
 * @param slave_config  Pointer to a spi_slave_interface_config_t struct specifying the details for the slave interface
 * @param dma_chan      - Selecting a DMA channel for an SPI bus allows transactions on the bus with size only limited by the amount of internal memory.
 *                      - Selecting SPI_DMA_DISABLED limits the size of transactions.
 *                      - Set to SPI_DMA_DISABLED if only the SPI flash uses this bus.
 *                      - Set to SPI_DMA_CH_AUTO to let the driver to allocate the DMA channel.
 *
 * @warning If a DMA channel is selected, any transmit and receive buffer used should be allocated in
 *          DMA-capable memory.
 *
 * @warning The ISR of SPI is always executed on the core which calls this
 *          function. Never starve the ISR on this core or the SPI transactions will not
 *          be handled.
 *
 * @return
 *         - ESP_ERR_INVALID_ARG   if configuration is invalid
 *         - ESP_ERR_INVALID_STATE if host already is in use
 *         - ESP_ERR_NOT_FOUND     if there is no available DMA channel
 *         - ESP_ERR_NO_MEM        if out of memory
 *         - ESP_OK                on success
 */
#if ESP_CAM_SPI_DRIVER
esp_err_t esp_cam_spi_slave_initialize(spi_host_device_t host, const spi_bus_config_t *bus_config, const spi_slave_interface_config_t *slave_config, spi_dma_chan_t dma_chan);
#else
#define esp_cam_spi_slave_initialize(host, bus_config, slave_config, dma_chan) spi_slave_initialize(host, bus_config, slave_config, dma_chan)
#endif

/**
 * @brief Free a SPI bus claimed as a SPI slave interface
 *
 * @param host SPI peripheral to free
 * @return
 *         - ESP_ERR_INVALID_ARG   if parameter is invalid
 *         - ESP_ERR_INVALID_STATE if not all devices on the bus are freed
 *         - ESP_OK                on success
 */
#if ESP_CAM_SPI_DRIVER
esp_err_t esp_cam_spi_slave_free(spi_host_device_t host);
#else
#define esp_cam_spi_slave_free(host) spi_slave_free(host)
#endif

/**
 * @brief Enable the spi slave function for an initialized spi host
 * @note No need to call this function additionally after `spi_slave_initialize`,
 *       because it has been enabled already during the initialization.
 *
 * @param host SPI peripheral to be enabled
 * @return
 *         - ESP_OK                 On success
 *         - ESP_ERR_INVALID_ARG    Unsupported host
 *         - ESP_ERR_INVALID_STATE  Peripheral already enabled
 */
#if ESP_CAM_SPI_DRIVER
esp_err_t esp_cam_spi_slave_enable(spi_host_device_t host);
#else
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
#define esp_cam_spi_slave_enable(host) spi_slave_enable(host)
#else
#define esp_cam_spi_slave_enable(host) ESP_OK
#endif
#endif

/**
 * @brief Disable the spi slave function for an initialized spi host
 *
 * @param host SPI peripheral to be disabled
 * @return
 *         - ESP_OK                 On success
 *         - ESP_ERR_INVALID_ARG    Unsupported host
 *         - ESP_ERR_INVALID_STATE  Peripheral already disabled
 */

#if ESP_CAM_SPI_DRIVER
esp_err_t esp_cam_spi_slave_disable(spi_host_device_t host);
#else
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
#define esp_cam_spi_slave_disable(host) spi_slave_disable(host)
#else
#define esp_cam_spi_slave_disable(host) ESP_OK
#endif
#endif

/**
 * @brief Queue a SPI transaction for execution
 *
 * @note On esp32, if trans length not WORD aligned, the rx buffer last word memory will still overwritten by DMA HW
 *
 * Queues a SPI transaction to be executed by this slave device. (The transaction queue size was specified when the slave
 * device was initialised via spi_slave_initialize.) This function may block if the queue is full (depending on the
 * ticks_to_wait parameter). No SPI operation is directly initiated by this function, the next queued transaction
 * will happen when the master initiates a SPI transaction by pulling down CS and sending out clock signals.
 *
 * This function hands over ownership of the buffers in ``trans_desc`` to the SPI slave driver; the application is
 * not to access this memory until ``spi_slave_queue_trans`` is called to hand ownership back to the application.
 *
 * @param host SPI peripheral that is acting as a slave
 * @param trans_desc Description of transaction to execute. Not const because we may want to write status back
 *                   into the transaction description.
 * @param ticks_to_wait Ticks to wait until there's room in the queue; use portMAX_DELAY to
 *                      never time out.
 * @return
 *         - ESP_ERR_INVALID_ARG   if parameter is invalid
 *         - ESP_ERR_NO_MEM        if set flag `SPI_SLAVE_TRANS_DMA_BUFFER_ALIGN_AUTO` but there is no free memory
 *         - ESP_ERR_INVALID_STATE if sync data between Cache and memory failed
 *         - ESP_OK                on success
 */
#if ESP_CAM_SPI_DRIVER
esp_err_t esp_cam_spi_slave_queue_trans(spi_host_device_t host, const spi_slave_transaction_t *trans_desc, TickType_t ticks_to_wait);
#else
#define esp_cam_spi_slave_queue_trans(host, trans_desc, ticks_to_wait) spi_slave_queue_trans(host, trans_desc, ticks_to_wait)
#endif

/**
 * @brief Queue a SPI transaction in ISR
 * @note
 * Similar as ``spi_slave_queue_trans``, but can and can only called within an ISR, then get the transaction results
 * through the transaction descriptor passed in ``spi_slave_interface_config_t::post_trans_cb``. if use this API, you
 * should trigger a transaction by normal ``spi_slave_queue_trans`` once and only once to start isr
 *
 * If you use both ``spi_slave_queue_trans`` and ``spi_slave_queue_trans_isr`` simultaneously to transfer valid data,
 * you should deal with concurrency issues on your self risk
 *
 * @param host SPI peripheral that is acting as a slave
 * @param trans_desc Description of transaction to execute. Not const because we may want to write status back
 *                   into the transaction description.
 * @return
 *         - ESP_ERR_INVALID_ARG   if parameter is invalid
 *         - ESP_ERR_NO_MEM        if trans_queue is full
 *         - ESP_OK                on success
 */
#if ESP_CAM_SPI_DRIVER
esp_err_t esp_cam_spi_slave_queue_trans_isr(spi_host_device_t host, const spi_slave_transaction_t *trans_desc);
#else
#define esp_cam_spi_slave_queue_trans_isr(host, trans_desc) spi_slave_queue_trans_isr(host, trans_desc)
#endif

#ifdef __cplusplus
}
#endif
