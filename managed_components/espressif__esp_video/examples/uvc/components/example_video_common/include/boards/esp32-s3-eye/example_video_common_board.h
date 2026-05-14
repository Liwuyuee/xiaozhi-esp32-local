/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ESP32-S3-EYE configuration
 */

/**
 * @brief SCCB(I2C) pre-initialized port configuration
 */
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
#define EXAMPLE_SCCB_I2C_SCL_PIN_INIT_BY_APP            5
#define EXAMPLE_SCCB_I2C_SDA_PIN_INIT_BY_APP            4
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */

#if CONFIG_EXAMPLE_ENABLE_DVP_CAM_SENSOR
/**
 * @brief DVP camera sensor configuration
 */
#define EXAMPLE_DVP_SCCB_I2C_SCL_PIN                    5
#define EXAMPLE_DVP_SCCB_I2C_SDA_PIN                    4
#define EXAMPLE_DVP_CAM_SENSOR_RESET_PIN                -1
#define EXAMPLE_DVP_CAM_SENSOR_PWDN_PIN                 -1

/**
 * @brief DVP interface configuration
 */
#define EXAMPLE_DVP_XCLK_PIN                            15
#define EXAMPLE_DVP_PCLK_PIN                            13
#define EXAMPLE_DVP_VSYNC_PIN                           6
#define EXAMPLE_DVP_DE_PIN                              7
#define EXAMPLE_DVP_D0_PIN                              11
#define EXAMPLE_DVP_D1_PIN                              9
#define EXAMPLE_DVP_D2_PIN                              8
#define EXAMPLE_DVP_D3_PIN                              10
#define EXAMPLE_DVP_D4_PIN                              12
#define EXAMPLE_DVP_D5_PIN                              18
#define EXAMPLE_DVP_D6_PIN                              17
#define EXAMPLE_DVP_D7_PIN                              16
#endif /* CONFIG_EXAMPLE_ENABLE_DVP_CAM_SENSOR */

#if CONFIG_EXAMPLE_ENABLE_SPI_CAM_0_SENSOR
/**
 * @brief SPI camera sensor configuration
 */
#define EXAMPLE_SPI_CAM_0_SCCB_I2C_SCL_PIN              5
#define EXAMPLE_SPI_CAM_0_SCCB_I2C_SDA_PIN              4
#define EXAMPLE_SPI_CAM_0_SENSOR_RESET_PIN              -1
#define EXAMPLE_SPI_CAM_0_SENSOR_PWDN_PIN               -1

/**
 * @brief SPI camera sensor configuration
 */
#define EXAMPLE_SPI_CAM_0_CS_PIN                        6
#define EXAMPLE_SPI_CAM_0_SCLK_PIN                      13
#define EXAMPLE_SPI_CAM_0_DATA0_IO_PIN                  16

/**
 * @brief SPI camera sensor clock resource configuration
 */
#define EXAMPLE_SPI_CAM_0_XCLK_PIN                      15
#endif /* CONFIG_EXAMPLE_ENABLE_SPI_CAM_0_SENSOR */

#ifdef __cplusplus
}
#endif
