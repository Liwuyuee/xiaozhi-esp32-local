#pragma once

#include <stdbool.h>

#include "esp_err.h"
#include "esp_io_expander.h"
#include "soc/soc_caps.h"
#include "sscma_client_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *sscma_client_flasher_we2_handle_t; /*!< Type of SSCMA flasher WE2 handle */

/**
 * @brief Flasher configuration structure, for WE2
 */
typedef struct
{
    int reset_gpio_num;                   /* !< GPIO number of reset pin */
    void *user_ctx;                       /*!< User private data */
    esp_io_expander_handle_t io_expander; /*!< IO expander handle */
    struct
    {
        unsigned int reset_high_active : 1;  /*!< Reset line is high active */
        unsigned int reset_use_expander : 1; /*!< Reset line use IO expander */
    } flags;
} sscma_client_flasher_we2_config_t;

/**
 * @brief Create SSCMA flasher, for WE2
 *
 * @param[in] io IO handle
 * @param[in] flasher_config Flasher configuration, for WE2
 * @param[out] ret_io Returned flasher handle
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NO_MEM        if out of memory
 *          - ESP_OK                on success
 */

esp_err_t sscma_client_new_flasher_we2_uart(const sscma_client_io_handle_t io, const sscma_client_flasher_we2_config_t *flasher_config, sscma_client_flasher_handle_t *ret_flasher);

/**
 * @brief Create SSCMA flasher, for WE2
 *
 * @param[in] io IO handle
 * @param[in] flasher_config Flasher configuration, for WE2
 * @param[out] ret_io Returned flasher handle
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NO_MEM        if out of memory
 *          - ESP_OK                on success
 */
esp_err_t sscma_client_new_flasher_we2_spi(const sscma_client_io_handle_t io, const sscma_client_flasher_we2_config_t *config, sscma_client_flasher_handle_t *ret_flasher);

#ifdef __cplusplus
}
#endif
