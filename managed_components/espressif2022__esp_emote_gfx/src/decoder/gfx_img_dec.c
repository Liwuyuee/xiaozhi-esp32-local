/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "core/gfx_core.h"
#include "core/gfx_obj.h"
#include "widget/gfx_img.h"
#include "decoder/gfx_img_dec.h"

static const char *TAG = "gfx_img_decoder";

/*********************
 *      DEFINES
 *********************/

#define MAX_DECODERS 8

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static esp_err_t image_format_info_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc, gfx_image_header_t *header);
static esp_err_t image_format_open_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc);
static void image_format_close_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc);

static esp_err_t aaf_format_info_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc, gfx_image_header_t *header);
static esp_err_t aaf_format_open_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc);
static void aaf_format_close_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc);

/**********************
 *  STATIC VARIABLES
 **********************/

static gfx_image_decoder_t *registered_decoders[MAX_DECODERS] = {NULL};
static uint8_t decoder_count = 0;

// Built-in decoders
static gfx_image_decoder_t image_decoder = {
    .name = "IMAGE",
    .info_cb = image_format_info_cb,
    .open_cb = image_format_open_cb,
    .close_cb = image_format_close_cb,
};

static gfx_image_decoder_t aaf_decoder = {
    .name = "AAF",
    .info_cb = aaf_format_info_cb,
    .open_cb = aaf_format_open_cb,
    .close_cb = aaf_format_close_cb,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*=====================
 * Image format detection
 *====================*/

gfx_image_format_t gfx_image_detect_format(const void *src)
{
    if (src == NULL) {
        return GFX_IMAGE_FORMAT_UNKNOWN;
    }

    uint8_t *byte_ptr = (uint8_t *)src;

    if (byte_ptr[0] == C_ARRAY_HEADER_MAGIC) {
        return GFX_IMAGE_FORMAT_C_ARRAY;
    }

    if (byte_ptr[0] == 0x89 && byte_ptr[1] == 'A' && byte_ptr[2] == 'A' && byte_ptr[3] == 'F') {
        return GFX_IMAGE_FORMAT_AAF;
    }

    return GFX_IMAGE_FORMAT_UNKNOWN;
}

/*=====================
 * Image decoder functions
 *====================*/

esp_err_t gfx_image_decoder_register(gfx_image_decoder_t *decoder)
{
    if (decoder == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (decoder_count >= MAX_DECODERS) {
        ESP_LOGE(TAG, "Too many decoders registered");
        return ESP_ERR_NO_MEM;
    }

    registered_decoders[decoder_count] = decoder;
    decoder_count++;

    ESP_LOGD(TAG, "Registered decoder: %s", decoder->name);
    return ESP_OK;
}

esp_err_t gfx_image_decoder_info(gfx_image_decoder_dsc_t *dsc, gfx_image_header_t *header)
{
    if (dsc == NULL || header == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    // Try each registered decoder
    for (int i = 0; i < decoder_count; i++) {
        gfx_image_decoder_t *decoder = registered_decoders[i];
        if (decoder && decoder->info_cb) {
            esp_err_t ret = decoder->info_cb(decoder, dsc, header);
            if (ret == ESP_OK) {
                ESP_LOGD(TAG, "Decoder %s found format", decoder->name);
                return ESP_OK;
            }
        }
    }

    ESP_LOGW(TAG, "No decoder found for image format");
    return ESP_ERR_INVALID_ARG;
}

esp_err_t gfx_image_decoder_open(gfx_image_decoder_dsc_t *dsc)
{
    if (dsc == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    // Try each registered decoder
    for (int i = 0; i < decoder_count; i++) {
        gfx_image_decoder_t *decoder = registered_decoders[i];
        if (decoder && decoder->open_cb) {
            esp_err_t ret = decoder->open_cb(decoder, dsc);
            if (ret == ESP_OK) {
                ESP_LOGD(TAG, "Decoder %s opened image", decoder->name);
                return ESP_OK;
            }
        }
    }

    ESP_LOGW(TAG, "No decoder could open image");
    return ESP_ERR_INVALID_ARG;
}

void gfx_image_decoder_close(gfx_image_decoder_dsc_t *dsc)
{
    if (dsc == NULL) {
        return;
    }

    // Try each registered decoder
    for (int i = 0; i < decoder_count; i++) {
        gfx_image_decoder_t *decoder = registered_decoders[i];
        if (decoder && decoder->close_cb) {
            decoder->close_cb(decoder, dsc);
        }
    }
}

/*=====================
 * Built-in decoder implementations
 *====================*/

// C_ARRAY format decoder
static esp_err_t image_format_info_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc, gfx_image_header_t *header)
{
    if (dsc->src == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    gfx_image_format_t format = gfx_image_detect_format(dsc->src);
    if (format != GFX_IMAGE_FORMAT_C_ARRAY) {
        return ESP_ERR_INVALID_ARG;
    }

    gfx_image_dsc_t *image_desc = (gfx_image_dsc_t *)dsc->src;
    memcpy(header, &image_desc->header, sizeof(gfx_image_header_t));

    return ESP_OK;
}

static esp_err_t image_format_open_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc)
{
    if (dsc->src == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    gfx_image_format_t format = gfx_image_detect_format(dsc->src);
    if (format != GFX_IMAGE_FORMAT_C_ARRAY) {
        return ESP_ERR_INVALID_ARG;
    }

    gfx_image_dsc_t *image_desc = (gfx_image_dsc_t *)dsc->src;
    dsc->data = image_desc->data;
    dsc->data_size = image_desc->data_size;

    return ESP_OK;
}

static void image_format_close_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc)
{
    // Nothing to do for C_ARRAY format
}

// AAF format decoder
static esp_err_t aaf_format_info_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc, gfx_image_header_t *header)
{
    if (dsc->src == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    gfx_image_format_t format = gfx_image_detect_format(dsc->src);
    if (format != GFX_IMAGE_FORMAT_AAF) {
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}

static esp_err_t aaf_format_open_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc)
{
    if (dsc->src == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    gfx_image_format_t format = gfx_image_detect_format(dsc->src);
    if (format != GFX_IMAGE_FORMAT_AAF) {
        return ESP_ERR_INVALID_ARG;
    }

    dsc->data = (const uint8_t *)dsc->src;
    dsc->data_size = 0;

    return ESP_OK;
}

static void aaf_format_close_cb(gfx_image_decoder_t *decoder, gfx_image_decoder_dsc_t *dsc)
{
    // Nothing to do for AAF format
}

/*=====================
 * Initialization
 *====================*/

esp_err_t gfx_image_decoder_init(void)
{
    // Register built-in decoders
    esp_err_t ret = gfx_image_decoder_register(&image_decoder);
    if (ret != ESP_OK) {
        return ret;
    }

    ret = gfx_image_decoder_register(&aaf_decoder);
    if (ret != ESP_OK) {
        return ret;
    }

    ESP_LOGD(TAG, "Image decoder system initialized with %d decoders", decoder_count);
    return ESP_OK;
}

esp_err_t gfx_image_decoder_deinit(void)
{
    for (int i = 0; i < decoder_count; i++) {
        registered_decoders[i] = NULL;
    }

    decoder_count = 0;

    ESP_LOGD(TAG, "Image decoder system deinitialized");
    return ESP_OK;
}
