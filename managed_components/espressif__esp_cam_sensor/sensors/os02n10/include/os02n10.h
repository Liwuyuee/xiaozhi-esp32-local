/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_cam_sensor_types.h"
#include "os02n10_types.h"

#if CONFIG_CAMERA_OS02N10_SID_HIGH
#define OS02N10_SCCB_ADDR 0x3d // SCCB ID select to 0x3d if SID pin set to 1
#else
#define OS02N10_SCCB_ADDR 0x3c // SCCB ID select to 0x3c if SID pin set to 0
#endif

/**
 * @brief Power on camera sensor device and detect the device connected to the designated sccb bus.
 *
 * @param[in] config Configuration related to device power-on and detection.
 * @return
 *      - Camera device handle on success, otherwise, failed.
 */
esp_cam_sensor_device_t *os02n10_detect(esp_cam_sensor_config_t *config);

#ifdef __cplusplus
}
#endif
