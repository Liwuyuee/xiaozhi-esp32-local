/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_cam_sensor.h"
#if CONFIG_ESP_VIDEO_ENABLE_SWAP_BYTE_BITSCRAMBLER
#include "driver/bitscrambler.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Video swap byte object
 */
typedef struct esp_video_swap_byte {
#if CONFIG_ESP_VIDEO_ENABLE_SWAP_BYTE_BITSCRAMBLER
    bitscrambler_handle_t bs;               /*!< Bitscrambler handle */
#else
    void *priv;                             /*!< Swap short byte data */
#endif
} esp_video_swap_byte_t;

/**
 * @brief Create video swap byte
 *
 * @return Swapping byte pointer if success or NULL if failed
 */
esp_video_swap_byte_t *esp_video_swap_byte_create(void);

/**
 * @brief Start video swap byte
 *
 * @param swap_byte    Video swap byte object pointer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_swap_byte_start(esp_video_swap_byte_t *swap_byte);

/**
 * @brief Free video swap byte
 *
 * @param swap byte    Video swap byte object pointer
 *
 * @return None
 */
void esp_video_swap_byte_free(esp_video_swap_byte_t *swap_byte);

/**
 * @brief Process video swap byte
 *
 * @param swap_byte     Video swap byte object pointer
 * @param src           Source buffer pointer
 * @param src_size      Source buffer size
 * @param dst           Destination buffer pointer
 * @param dst_size      Destination buffer size
 * @param ret_size      Result data size buffer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_swap_byte_process(esp_video_swap_byte_t *swap_byte,  void *src, size_t src_size,
                                      void *dst, size_t dst_size, size_t *ret_size);

#ifdef __cplusplus
}
#endif
