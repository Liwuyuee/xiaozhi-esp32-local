/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * BF3901 register definitions.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* bf3901 registers */
#define BF3901_REG_DELAY               0xfe
#define BF3901_REG_CHIP_ID_H           0xfc
#define BF3901_REG_CHIP_ID_L           0xfd
#define BF3901_REG_RESET_RELATED       0x12

#ifdef __cplusplus
}
#endif
