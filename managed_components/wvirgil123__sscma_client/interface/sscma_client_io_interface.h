#pragma once

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sscma_client_io_t sscma_client_io_t; /*!< Type of SSCMA client IO */

/**
 * @brief SSCMA IO interface
 */
struct sscma_client_io_t
{
    /**
     * @brief Bus handle
     */
    void *handle;

    /**
     * @brief Destory SCCMA client
     *
     * @param[in] io SCCMA client handle]
     * @return
     *          - ESP_OK on success
     */
    esp_err_t (*del)(sscma_client_io_t *io);

    /**
     * @brief Write data to SCCMA client
     *
     * @param[in] io SCCMA client handle
     * @param[in] data Data to be written
     * @param[in] size Size of data
     * @return
     *          - ESP_ERR_INVALID_ARG   if parameter is invalid
     *          - ESP_ERR_NOT_SUPPORTED if read is not supported by transport
     *          - ESP_OK                on success
     */
    esp_err_t (*write)(sscma_client_io_t *io, const void *data, size_t size);

    /**
     * @brief Read data from SCCMA client
     *
     * @param[in] io SCCMA client IO handle
     * @param[in] data Data to be read
     * @param[in] size Size of data
     * @return
     *          - ESP_ERR_INVALID_ARG   if parameter is invalid
     *          - ESP_ERR_NOT_SUPPORTED if read is not supported by transport
     *          - ESP_OK                on success
     *
     */
    esp_err_t (*read)(sscma_client_io_t *io, void *data, size_t size);

    /**
     * @brief Get available size of data
     *
     * @param[in] io SCCMA client IO handle
     * @param[out] ret_avail Available size
     * @return
     *          - ESP_ERR_INVALID_ARG   if parameter is invalid
     *          - ESP_ERR_NOT_SUPPORTED if read is not supported by transport
     *          - ESP_OK
     */
    esp_err_t (*available)(sscma_client_io_t *io, size_t *ret_avail);

    /**
     * @brief Flush data
     *
     * @param[in] io IO handle
     * @return
     *          - ESP_OK
     */
    esp_err_t (*flush)(sscma_client_io_t *io);
};

#ifdef __cplusplus
}
#endif
