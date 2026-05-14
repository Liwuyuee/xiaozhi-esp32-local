/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#include <assert.h>
#include <sys/param.h>
#include "esp_err.h"
#include "esp_heap_caps.h"
#include "esp_video_swap_short.h"
#if CONFIG_ESP_VIDEO_ENABLE_BITSCRAMBLER
#include "driver/bitscrambler_loopback.h"
#endif
#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PERF_LOG
#include "esp_timer.h"
#endif

#define ESP_VIDEO_SWAP_SHORT_PERF_LOG_INTERVAL_US    CONFIG_ESP_VIDEO_SWAP_SHORT_PERF_LOG_INTERVAL_US

#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT
#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER
#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PARL_IO
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_PARL_IO
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_LCD_CAM
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_LCD_CAM
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_GPSPI2
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_GPSPI2
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_GPSPI3
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_GPSPI3
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_AES
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_AES
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_SHA
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_SHA
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_ADC
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_ADC
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_I2S0
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_I2S0
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_I2S1
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_I2S1
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_I2S2
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_I2S2
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_I3C_MST
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_I3C_MST
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_UHCI
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_UHCI
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_RMT
#define ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL SOC_BITSCRAMBLER_ATTACH_RMT
#endif
BITSCRAMBLER_PROGRAM(esp_video_swap_short, "esp_video_swap_short");
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_RISCV
extern void esp_video_swap_short_riscv(void *src, uint32_t src_size, void *dst, uint32_t dst_size);
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PIE
extern void esp_video_swap_short_pie(void *src, uint32_t src_size, void *dst, uint32_t dst_size);
#endif /* CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER */
#endif /* CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT */

static const char *TAG = "swap_short";

/**
 * @brief Create video swap short
 *
 * @param max_size      Video swap short maximum data size
 *
 * @return Swapping short pointer if success or NULL if failed
 */
esp_video_swap_short_t *esp_video_swap_short_create(size_t max_size)
{
    esp_video_swap_short_t *swap_short;

    ESP_LOGD(TAG, "max_size=%zu", max_size);

    swap_short = heap_caps_calloc(1, sizeof(esp_video_swap_short_t), MALLOC_CAP_8BIT | MALLOC_CAP_8BIT);
    if (!swap_short) {
        return NULL;
    }

#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER
    esp_err_t ret;
    bitscrambler_handle_t bs;

    ESP_LOGD(TAG, "Swap short bitscrambler peripheral=%d", ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL);

    ESP_GOTO_ON_ERROR(bitscrambler_loopback_create(&bs, ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER_PERIPHERAL, max_size),
                      exit_0, TAG, "Failed to create loopback bitscrambler");

    ESP_GOTO_ON_ERROR(bitscrambler_load_program(bs, esp_video_swap_short), exit_1, TAG,
                      "Failed to load bitscrambler program");

    swap_short->priv = bs;
    (void)ret;
#endif

#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PERF_LOG
    swap_short->prev_time_us = 0;
    swap_short->total_time_us = 0;
    swap_short->count = 0;
    swap_short->max_time_us = 0;
    swap_short->min_time_us = UINT32_MAX;
#endif

    return swap_short;

#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER
exit_1:
    bitscrambler_free(bs);
exit_0:
    heap_caps_free(swap_short);
    return NULL;
#endif
}

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
                                       void *dst, size_t dst_size, size_t *ret_size)
{
    esp_err_t ret = ESP_OK;
#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PERF_LOG
    int64_t start_time_us = esp_timer_get_time();
#endif

#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER
    ret = bitscrambler_loopback_run((bitscrambler_handle_t)swap_short->priv, src, src_size, dst, dst_size, ret_size);
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_RISCV
    esp_video_swap_short_riscv(src, src_size, dst, dst_size);
    *ret_size = dst_size;
#elif CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PIE
    esp_video_swap_short_pie(src, src_size, dst, dst_size);
    *ret_size = dst_size;
#endif /* CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER */

#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PERF_LOG
    if (ret == ESP_OK) {
        int64_t end_time_us = esp_timer_get_time();
        uint32_t time_us = (uint32_t)(end_time_us - start_time_us);

        swap_short->total_time_us += time_us;
        swap_short->count++;
        swap_short->max_time_us = MAX(time_us, swap_short->max_time_us);
        swap_short->min_time_us = MIN(time_us, swap_short->min_time_us);

        if ((end_time_us - swap_short->prev_time_us) >= ESP_VIDEO_SWAP_SHORT_PERF_LOG_INTERVAL_US) {
            swap_short->prev_time_us = end_time_us;

            ESP_LOGI(TAG, "Swap short cost time(us):");
            ESP_LOGI(TAG, "\tMax: %"PRIu32"us", swap_short->max_time_us);
            ESP_LOGI(TAG, "\tMin: %"PRIu32"us", swap_short->min_time_us);
            ESP_LOGI(TAG, "\tAvg: %"PRIu32"us", (uint32_t)(swap_short->total_time_us / swap_short->count));
        }
    }
#endif

    return ret;
}

/**
 * @brief Free video swap short
 *
 * @param swap short    Video swap short object pointer
 *
 * @return None
 */
void esp_video_swap_short_free(esp_video_swap_short_t *swap_short)
{
#if CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_BITSCRAMBLER
    bitscrambler_free((bitscrambler_handle_t)swap_short->priv);
#endif

    heap_caps_free(swap_short);
}
