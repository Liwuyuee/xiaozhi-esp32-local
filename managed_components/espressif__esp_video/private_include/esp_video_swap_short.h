/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_cam_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Video swap short object
 */
typedef struct esp_video_swap_short {
    void *priv;                             /*!< Swap short private data */

#ifdef CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PERF_LOG
    /*!< Video swap short performance debug data */

    uint64_t prev_time_us;                  /*!< The time to print information */
    uint64_t total_time_us;                 /*!< Total time of video swap short runs */
    uint32_t count;                         /*!< Count of video swap short runs */
    uint32_t max_time_us;                   /*!< Maximum time of video swap short runs */
    uint32_t min_time_us;                   /*!< Minmium time of video swap short runs */
#endif
} esp_video_swap_short_t;

/**
 * @brief Create video swap short
 *
 * @param max_size      Video swap short maximum data size
 *
 * @return Swapping short pointer if success or NULL if failed
 */
esp_video_swap_short_t *esp_video_swap_short_create(size_t max_size);

/**
 * @brief Process video swap short
 *
 * @param swap_short    Video swap short object pointer
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
esp_err_t esp_video_swap_short_process(esp_video_swap_short_t *swap_short,  void *src, size_t src_size,
                                       void *dst, size_t dst_size, size_t *ret_size);

/**
 * @brief Free video swap short
 *
 * @param swap short    Video swap short object pointer
 *
 * @return None
 */
void esp_video_swap_short_free(esp_video_swap_short_t *swap_short);

#ifdef __cplusplus
}
#endif
