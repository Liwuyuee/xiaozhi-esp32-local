/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * OS02N10 register definitions.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define OS02N10_REG_DELAY    0xff

/* os02n10 registers */
#define OS02N10_REG_CHIP_ID_ADDR_HH     0x02
#define OS02N10_REG_CHIP_ID_ADDR_HL     0x03
#define OS02N10_REG_CHIP_ID_ADDR_LH     0x04
#define OS02N10_REG_CHIP_ID_ADDR_LL     0x05
#define OS02N10_REG_BANK_SEL            0xfd
#define OS02N10_REG_COMC03              0xba
#define OS02N10_REG_TP_EN               0xe8
#define OS02N10_REG_PAGE1_EXP_H         0x0e
#define OS02N10_REG_PAGE1_EXP_L         0x0f
#define OS02N10_REG_PAGE1_RPC_L         0x24
#define OS02N10_REG_PAGE1_DGAIN_H       0X1f
#define OS02N10_REG_PAGE1_DGAIN_L       0x20

#ifdef __cplusplus
}
#endif
