/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "esp_err.h"
#include "widget/gfx_img.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**
 * @brief Image format types
 */
typedef enum {
    GFX_IMAGE_FORMAT_UNKNOWN = 0,  /**< Unknown format */
    GFX_IMAGE_FORMAT_C_ARRAY = 1,  /**< C array format */
    GFX_IMAGE_FORMAT_AAF = 3,      /**< AAF animation format */
} gfx_image_format_t;

/* Image decoder descriptor - for internal use */
typedef struct {
    const void *src;            /**< Image source: file name or variable */
    gfx_image_header_t header;  /**< Image header information */
    const uint8_t *data;        /**< Decoded image data */
    uint32_t data_size;         /**< Size of decoded data */
    void *user_data;            /**< User data for decoder */
} gfx_image_decoder_dsc_t;

/* Forward declaration for image decoder structure */
typedef struct gfx_image_decoder_t gfx_image_decoder_t;

/* Image decoder structure - for internal use */
struct gfx_image_decoder_t {
    const char *name;           /**< Decoder name */

    /**
     * Get image information from source
     * @param decoder pointer to the decoder
     * @param dsc pointer to decoder descriptor
     * @param header store the info here
     * @return ESP_OK: no error; ESP_ERR_INVALID: can't get the info
     */
    esp_err_t (*info_cb)(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc, gfx_image_header_t *header);

    /**
     * Open and decode image
     * @param decoder pointer to the decoder
     * @param dsc pointer to decoder descriptor
     * @return ESP_OK: no error; ESP_ERR_INVALID: can't open the image
     */
    esp_err_t (*open_cb)(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc);

    /**
     * Close image and free resources
     * @param decoder pointer to the decoder
     * @param dsc pointer to decoder descriptor
     */
    void (*close_cb)(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc);
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Image format detection (internal)
 *====================*/

/**
 * @brief Detect image format from source data (internal)
 * @param src Source data pointer
 * @return Format type: GFX_IMAGE_FORMAT_UNKNOWN, GFX_IMAGE_FORMAT_C_ARRAY, or GFX_IMAGE_FORMAT_AAF
 */
gfx_image_format_t gfx_image_detect_format(const void *src);

/*=====================
 * Image decoder functions (internal)
 *====================*/

/**
 * @brief Register an image decoder (internal)
 * @param decoder Pointer to decoder structure
 * @return ESP_OK on success, otherwise error code
 */
esp_err_t gfx_image_decoder_register(gfx_image_decoder_t *decoder);

/**
 * @brief Get image information using registered decoders (internal)
 * @param dsc Decoder descriptor
 * @param header Output header structure
 * @return ESP_OK on success, otherwise error code
 */
esp_err_t gfx_image_decoder_info(gfx_image_decoder_dsc_t *dsc, gfx_image_header_t *header);

/**
 * @brief Open and decode image using registered decoders (internal)
 * @param dsc Decoder descriptor
 * @return ESP_OK on success, otherwise error code
 */
esp_err_t gfx_image_decoder_open(gfx_image_decoder_dsc_t *dsc);

/**
 * @brief Close image decoder and free resources (internal)
 * @param dsc Decoder descriptor
 */
void gfx_image_decoder_close(gfx_image_decoder_dsc_t *dsc);

/**
 * @brief Initialize image decoder system (internal)
 * @return ESP_OK on success, otherwise error code
 */
esp_err_t gfx_image_decoder_init(void);

/**
 * @brief Deinitialize image decoder system (internal)
 * @return ESP_OK on success, otherwise error code
 */
esp_err_t gfx_image_decoder_deinit(void);

#ifdef __cplusplus
}
#endif
