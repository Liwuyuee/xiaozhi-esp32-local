/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_err.h"
#include "usb/uvc_host.h"

#pragma once

esp_err_t test_uvc_host_install(const uvc_host_driver_config_t *driver_config);
esp_err_t test_uvc_host_uninstall(void);
esp_err_t test_uvc_host_stream_open(const uvc_host_stream_config_t *stream_config, int timeout, uvc_host_stream_hdl_t *stream_hdl_ret, bool is_isoc);
esp_err_t test_uvc_host_stream_close(uvc_host_stream_hdl_t stream_hdl);
