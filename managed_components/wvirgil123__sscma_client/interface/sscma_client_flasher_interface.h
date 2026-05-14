#pragma once

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sscma_client_flasher_t sscma_client_flasher_t; /*!< Type of SSCMA flasher handle */

struct sscma_client_flasher_t
{
    /**
     * @brief Start flasher transmitter
     * @param[in] handle transmitter handle
     * @param[in] offset offset
     * @return
     * - ESP_OK
     */
    esp_err_t (*start)(sscma_client_flasher_t *handle, size_t offset);

    /**
     * @brief Write data to flasher transmitter
     * @param[in] handle transmitter handle
     * @param[in] data data
     * @param[in] len length
     * @return
     * - ESP_OK
     */
    esp_err_t (*write)(sscma_client_flasher_t *handle, const void *data, size_t len);

    /**
     * @brief Start flasher transmitter
     * @param[in] handle transmitter handle
     * @return
     * - ESP_OK
     */
    esp_err_t (*finish)(sscma_client_flasher_t *handle);

    /**
     * @brief Abort flasher transmitter
     * @param[in] handle transmitter handle
     * @return
     * - ESP_OK
     */
    esp_err_t (*abort)(sscma_client_flasher_t *handle);

    /**
     * @brief Delete flasher transmitter
     * @param[in] handle transmitter handle
     * @return
     * - ESP_OK
     */
    esp_err_t (*del)(sscma_client_flasher_t *handle);
};

/**
 * Start flasher transmitter
 * @param[in] handle transmitter handle
 * @param[in] offset offset
 * @return
 * - ESP_OK
 */
esp_err_t sscma_client_flasher_start(sscma_client_flasher_t *handle, size_t offset);

/**
 * Write data to flasher transmitter
 * @param[in] handle transmitter handle
 * @param[in] data data
 * @param[in] len length
 * @return
 * - ESP_OK
 */
esp_err_t sscma_client_flasher_write(sscma_client_flasher_t *handle, const void *data, size_t len);

/**
 * Finish flasher transmitter
 * @param[in] handle transmitter handle
 * @return
 * - ESP_OK
 */
esp_err_t sscma_client_flasher_finish(sscma_client_flasher_t *handle);

/**
 * Abort flasher transmitter
 * @param[in] handle transmitter handle
 * @return
 * - ESP_OK
 */
esp_err_t sscma_client_flasher_abort(sscma_client_flasher_t *handle);

/**
 * Delete flasher transmitter
 * @param[in] handle transmitter handle
 * @return
 * - ESP_OK
 */
esp_err_t sscma_client_flasher_delete(sscma_client_flasher_t *handle);

/**
 * Create xmodem flasher
 * @param[in] io io
 * @param[out] ret_handle handle
 * @return
 * - ESP_OK
 */
esp_err_t sscma_client_flasher_xmodem_create(sscma_client_io_t *io, sscma_client_flasher_t **ret_handle);

#ifdef __cplusplus
}
#endif