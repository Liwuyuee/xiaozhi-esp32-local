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
 * OV5640 camera sensor register type definition.
 */
typedef struct {
    uint16_t reg;
    uint8_t val;
} ov5640_reginfo_t;

#ifdef __cplusplus
}
#endif
