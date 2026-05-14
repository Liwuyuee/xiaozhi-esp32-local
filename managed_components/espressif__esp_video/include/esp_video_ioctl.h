/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include "linux/videodev2.h"
#include "esp_cam_sensor_types.h"
#include "esp_cam_motor_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define V4L2_FMT_STR                    "%c%c%c%c"
#define V4L2_FMT_STR_ARG(fmt)           (uint8_t)(((fmt) >> 0)  & 0xFF), \
                                        (uint8_t)(((fmt) >> 8)  & 0xFF), \
                                        (uint8_t)(((fmt) >> 16) & 0xFF), \
                                        (uint8_t)(((fmt) >> 24) & 0xFF)

#define VIDIOC_S_SENSOR_FMT _IOWR('V',  BASE_VIDIOC_PRIVATE + 1, esp_cam_sensor_format_t)
#define VIDIOC_G_SENSOR_FMT _IOWR('V',  BASE_VIDIOC_PRIVATE + 2, esp_cam_sensor_format_t)

#define VIDIOC_SET_OWNER    _IOWR('V',  BASE_VIDIOC_PRIVATE + 3, int)

#define VIDIOC_S_MOTOR_FMT  _IOWR('V',  BASE_VIDIOC_PRIVATE + 4, esp_cam_motor_format_t)
#define VIDIOC_G_MOTOR_FMT  _IOWR('V',  BASE_VIDIOC_PRIVATE + 5, esp_cam_motor_format_t)

#define V4L2_CID_CAMERA_AE_LEVEL        (V4L2_CID_CAMERA_CLASS_BASE + 40)
#define V4L2_CID_CAMERA_STATS           (V4L2_CID_CAMERA_CLASS_BASE + 41)
#define V4L2_CID_CAMERA_GROUP           (V4L2_CID_CAMERA_CLASS_BASE + 42)
#define V4L2_CID_MOTOR_START_TIME       (V4L2_CID_CAMERA_CLASS_BASE + 43)

/**
 * @brief Use this class to call esp_cam_sensor ioctl commands directly, this is only
 * used for camera sensor, not for motor controller.
 *
 * @note Please note that this class only supports "p_u8" and "size" fields of v4l2_ext_control,
 * other fields are not supported.
 */
#define V4L2_CTRL_CLASS_ESP_CAM_IOCTL   (0x00a70000)

#ifdef __cplusplus
}
#endif
