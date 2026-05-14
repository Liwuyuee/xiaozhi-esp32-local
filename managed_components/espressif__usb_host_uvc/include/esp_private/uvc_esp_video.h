/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "usb/uvc_host.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This API provides access to advanced UVC features.
 * It is intended for use with esp_video component.
 */

typedef struct {
    uint32_t dwMaxVideoFrameSize; /**< Maximum frame size of current format */
} uvc_host_buf_info_t;

/**
 * @brief Get frame buffer information
 *
 * This function is intended for future use. Currently, it only returns the maximum frame size.
 *
 * @param[in]  stream_hdl UVC handle obtained from uvc_host_stream_open()
 * @param[out] buf_info   Pointer to frame information structure to be filled
 * @return
 *     - ESP_OK: Success
 *     - ESP_ERR_INVALID_ARG: Input parameter is NULL
 */
esp_err_t uvc_host_buf_info_get(uvc_host_stream_hdl_t stream_hdl, uvc_host_buf_info_t *buf_info);

#ifdef __cplusplus
}
#endif
