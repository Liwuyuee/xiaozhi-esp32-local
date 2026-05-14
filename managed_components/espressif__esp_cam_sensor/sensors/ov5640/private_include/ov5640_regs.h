/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define OV5640_REG_END      0xffff
#define OV5640_REG_DELAY    0xfffe

/* OV5640 registers */
#define OV5640_REG_SYS_CTRL0               0x3008
#define OV5640_REG_SENSOR_ID_H             0x300a
#define OV5640_REG_SENSOR_ID_L             0x300b
#define OV5640_REG_IO_MIPI_CTRL00          0x300e
#define OV5640_REG_FRAME_CTRL01            0x4202

/**
 * Output format ISP control registers
 * Bit[2:0]:
 * 000: ISP YUV422
 * 001: ISP RGB
 * 010: ISP dither
 * 011: ISP RAW after DPC
 * 100: ISP RAW after SNR
 * 101: ISP RAW after CIP
 */
#define FORMAT_MUX_CTRL     0x501f

/**
 * Output format control00 registers
 * Bit[7:4]: Output format of formatter module
 * Bit[3:0]: Output sequence
 */
#define FORMAT_CTRL0        0x4300

#ifdef __cplusplus
}
#endif
