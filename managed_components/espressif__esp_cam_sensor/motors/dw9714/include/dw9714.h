/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_cam_motor_types.h"

/**
 * @brief DW9714 7-bits Address(0x18>>1).
 */
#define DW9714_SCCB_ADDR   0x0c
#define DW9714_WAIT_STABLE_TIME  12    //ms

/**
 * @brief Power on VCM actuator motor device and detect the device connected to the designated sccb bus.
 *
 * @param[in] config Configuration related to device power-on and detection.
 * @return
 *      - Camera device handle on success, otherwise, failed.
 */
esp_cam_motor_device_t *dw9714_detect(esp_cam_motor_config_t *config);

#ifdef __cplusplus
}
#endif
