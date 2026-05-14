/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "usb/uvc_host.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This API controls USB transfers to the streaming interface. It can be used to start/stop the stream
 * without any other CTRL requests (negotiation, interface setting, endpoint halting...).
 *
 * Usually, the UVC stream is started with uvc_host_stream_start() and stopped with uvc_host_stream_stop(),
 * which internally call this pause/unpause API.
 */

/**
 * @brief Pause UVC stream
 *
 * After this call, the USB transfers are not re-submitted and the user will stop getting new frame callbacks.
 * This function does not issue any CTRL request. In only stops receiving new data from streaming endpoint.
 *
 * @param[in] stream_hdl UVC handle obtained from uvc_host_stream_open()
 * @return
 *     - ESP_OK: Success - all USB transfers are paused
 *     - ESP_ERR_INVALID_ARG: stream_hdl is NULL
 */
esp_err_t uvc_host_stream_pause(uvc_host_stream_hdl_t stream_hdl);

/**
 * @brief Unpause UVC stream
 *
 * After this call, the user will be informed about new frames by frame callback.
 * This function does not issue any CTRL request. In only starts receiving new data from streaming endpoint.
 *
 * @param[in] stream_hdl UVC handle obtained from uvc_host_stream_open()
 * @return
 *     - ESP_OK: Success - all USB transfers were submitted
 *     - ESP_ERR_INVALID_ARG: stream_hdl is NULL
 *     - ESP_ERR_INVALID_STATE: Stream is not streaming
 *     - Others: Failed to submit USB transfer
 */
esp_err_t uvc_host_stream_unpause(uvc_host_stream_hdl_t stream_hdl);

#ifdef __cplusplus
}
#endif
