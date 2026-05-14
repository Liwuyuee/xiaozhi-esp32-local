/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * OS02N10 camera sensor register type definition.
 */
typedef struct {
    uint8_t reg;
    uint8_t val;
} os02n10_reginfo_t;

/*
 * OS02N10 camera sensor register banks definition.
 */
typedef enum {
    OS02N10_BANK_SYSTEM = 0x0,  // When register 0xFD=0x00, System register bank is available
    OS02N10_BANK_SENSOR = 0x01, // When register 0xFD=0x01, Sensor register bank is available
    OS02N10_BANKI_ISP = 0x03,   // When register 0xFD=0x03, ISP register bank is available
    OS02N10_BANKI_DPC = 0x04,   // When register 0xFD=0x04, DPC register bank is available
    OS02N10_BANKI_OTP = 0x06,   // When register 0xFD=0x06, OTP register bank is available
    OS02N10_BANK_MAX
} os02n10_bank_t;

#ifdef __cplusplus
}
#endif
