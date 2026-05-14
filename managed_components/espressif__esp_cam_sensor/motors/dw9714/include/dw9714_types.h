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
 * DW9714 VCM actuator motor command type definition.
 */
typedef union {
    struct {
        uint16_t s    : 4;  /*!< Step and period control */
        uint16_t d    : 10; /*!< Code data */
        uint16_t flag : 1;  /*!< Flag must keep "L" at writing operation */
        uint16_t pd   : 1;  /*!< 0: Normal mode, 1: Power down mode */
    };
    struct {
        uint16_t byte2 : 8;
        uint16_t byte1 : 8;
    };
    uint16_t val;
} dw9714_data_type_t;

#ifdef __cplusplus
}
#endif
