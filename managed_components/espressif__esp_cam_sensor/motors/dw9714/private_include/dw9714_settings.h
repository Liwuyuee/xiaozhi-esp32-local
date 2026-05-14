/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "dw9714_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PROT_OFF (0xeca3)
#define PROT_ON (0xdc51)

#define DLC_MCLK (0x2)
#define DLC_TSRC (0x17)
#define LSC_MCLK (0x1)
#define LSC_S32 (0x3)
#define LSC_S32_CODES_PER_STEP (0x04)
#define LSC_TSRC (0x3)
#define LSC_SET_CODE(pos) ((pos << 4) | (LSC_S32 << 2) | LSC_MCLK)
#define DLC_SET_CODE(pos) ((pos << 4))

static const dw9714_data_type_t lsc_mode_mclk01_src03_init_list[] = {
    {.val = PROT_OFF},
    {.val = 0xA104 | LSC_MCLK},
    {.val = 0xF200 | (LSC_TSRC << 3)},
    {.val = PROT_ON},
};

static const dw9714_data_type_t dlc_mode_mclk02_src17_init_list[] = {
    {.val = PROT_OFF},
    {.val = 0xA10C | DLC_MCLK},
    {.val = 0xF200 | (DLC_TSRC << 3)},
    {.val = PROT_ON},
};

#ifdef __cplusplus
}
#endif
