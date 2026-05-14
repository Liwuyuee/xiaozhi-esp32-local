/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include "esp_video.h"
#include "esp_cam_sensor_types.h"
#include "esp_cam_motor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_video_cam {
    esp_cam_sensor_device_t *sensor;
    esp_cam_motor_device_t *motor;
} esp_video_cam_t;

/**
 * @brief Set control value to camera device
 *
 * @param cam      Camera device pointer
 * @param controls V4L2 external controls pointer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_cam_set_ext_ctrls(esp_video_cam_t *cam, const struct v4l2_ext_controls *controls);

/**
 * @brief Get control value from camera device
 *
 * @param cam      Camera device pointer
 * @param controls V4L2 external controls pointer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_cam_get_ext_ctrls(esp_video_cam_t *cam, struct v4l2_ext_controls *controls);

/**
 * @brief Get control description from camera device
 *
 * @param cam      Camera device pointer
 * @param qctrl    V4L2 external controls query description pointer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_cam_query_ext_ctrls(esp_video_cam_t *cam, struct v4l2_query_ext_ctrl *qctrl);

/**
 * @brief Query menu value from camera device
 *
 * @param cam      Camera device pointer
 * @param qmenu    Menu value buffer pointer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_cam_query_menu(esp_video_cam_t *cam, struct v4l2_querymenu *qmenu);

#ifdef __cplusplus
}
#endif
