/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "usb/uvc_host.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Submit transfer to CTRL endpoint
 *
 * Sends Control transfer as described in USB specification chapter 9.
 * This function can be used by device drivers that use custom/vendor specific commands.
 *
 * @param        stream_hdl    UVC stream
 * @param[in]    bmRequestType Field of USB control request
 * @param[in]    bRequest      Field of USB control request
 * @param[in]    wValue        Field of USB control request
 * @param[in]    wIndex        Field of USB control request
 * @param[in]    wLength       Field of USB control request
 * @param[inout] data          Field of USB control request
 * @return
 *     - ESP_OK: Transfer succeeded
 *     - ESP_ERR_TIMEOUT: The transfer could not be completed in time
 *     - ESP_ERR_INVALID_SIZE: The transfer is too big
 *     - ESP_ERR_INVALID_ARG: stream_hdl is NULL, or data is not NULL and wValue is greater than zero
 *     - ESP_ERR_INVALID_RESPONSE: Reply corrupted or too short
 */
esp_err_t uvc_host_usb_ctrl(uvc_host_stream_hdl_t stream_hdl, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint16_t wLength, uint8_t *data);

/**
 * @brief Probe UVC stream format
 *
 * This function is use for obtaining format negotiation information
 * that are not in any descriptor, but in uvc_vs_ctrl_t
 *
 * @param         stream_hdl       UVC stream
 * @param[inout]  requested_format Requested Video Stream format. Negotiated format will be written here
 * @param[out]    vs_result_ret    Negotiation result. Can be NULL if result is not needed
 * @return
 *     - ESP_OK: Format negotiated and committed
 *     - ESP_ERR_INVALID_ARG: stream_hdl or vs_format is NULL
 *     - Else: USB Control transfer error
 */
esp_err_t uvc_host_stream_control_probe(uvc_host_stream_hdl_t stream_hdl, uvc_host_stream_format_t *requested_format, uvc_vs_ctrl_t *vs_result_ret);

/**
 * @brief Negotiate and commit UVC stream format
 *
 * @param      stream_hdl    UVC stream
 * @param[in]  vs_format     Requested Video Stream format
 * @return
 *     - ESP_OK: Format negotiated and committed
 *     - ESP_ERR_INVALID_ARG: stream_hdl or vs_format is NULL
 *     - ESP_ERR_NOT_FOUND: The requested format was not found
 *     - Else: USB Control transfer error
 */
esp_err_t uvc_host_stream_control_commit(uvc_host_stream_hdl_t stream_hdl, const uvc_host_stream_format_t *vs_format);

#ifdef __cplusplus
}
#endif
