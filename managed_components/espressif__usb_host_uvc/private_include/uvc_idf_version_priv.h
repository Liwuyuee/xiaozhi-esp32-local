/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "sdkconfig.h"
#include "esp_idf_version.h"

// @todo fix the hard-coded number here: Should be taken from HAL FIFO config in future versions of esp-idf
#if (CONFIG_IDF_TARGET_ESP32P4 || CONFIG_IDF_TARGET_LINUX)
#define MAX_MPS_IN 4096
#else
// If FIFO is configured for bias IN, we have 608 bytes available.
// However, configuring MPS > 596 causes USB transfer failures,
// because end of the RX FIFO is used internally by the USB-OTG peripheral
#define MAX_MPS_IN 596
#endif

// Definition of USB_EP_DESC_GET_MULT for IDF versions that don't have it.
// It was introduced in IDF v5.3 and backported to v5.2.1 and v5.1.4
#if !(ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 1, 4) && ESP_IDF_VERSION != ESP_IDF_VERSION_VAL(5, 2, 0))
#define USB_EP_DESC_GET_MULT(desc_ptr) (((desc_ptr)->wMaxPacketSize & 0x1800) >> 11)
#endif
