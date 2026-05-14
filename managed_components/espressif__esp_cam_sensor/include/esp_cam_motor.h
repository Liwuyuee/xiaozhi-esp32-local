/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_check.h"
#include "esp_cam_motor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Query the supported data types of extended control parameters.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @param[out] qdesc The pointer to hold the extended control parameters.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Error in the passed arguments.
 *      - ESP_ERR_NOT_SUPPORTED: The motor driver does not support this operation.
 */
esp_err_t esp_cam_motor_query_para_desc(esp_cam_motor_device_t *dev, esp_cam_motor_param_desc_t *qdesc);

/**
 * @brief Get the current value of the control parameter.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @param[in] id Camera motor parameter ID.
 * @param[out] arg Camera motor parameter setting data pointer.
 * @param[in] size Camera motor parameter setting data size.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Error in the passed arguments.
 *      - ESP_ERR_NOT_SUPPORTED: The motor driver does not support this operation.
 */
esp_err_t esp_cam_motor_get_para_value(esp_cam_motor_device_t *dev, uint32_t id, void *arg, size_t size);

/**
 * @brief Set the value of the control parameter.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @param[in] id Camera motor parameter ID.
 * @param[in] arg Camera motor parameter setting data pointer.
 * @param[in] size Camera motor parameter setting data size.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Error in the passed arguments.
 *      - ESP_ERR_NOT_SUPPORTED: The motor driver does not support this operation.
 */
esp_err_t esp_cam_motor_set_para_value(esp_cam_motor_device_t *dev, uint32_t id, const void *arg, size_t size);

/**
 * @brief Get driver information supported by the motor driver.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @param[out] format_arry The pointer to hold the description of the currently supported formats(configurations).
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Error in the passed arguments.
 *      - ESP_ERR_NOT_SUPPORTED: The motor driver does not support this operation.
 */
esp_err_t esp_cam_motor_query_formats(esp_cam_motor_device_t *dev, esp_cam_motor_fmt_array_t *format_array);

/**
 * @brief Set the working format of the camera motor.
 *
 * @note  If format is NULL, the camera motor will load the default format.
 *
 * @note  Query the currently supported formats by calling esp_cam_motor_query_format.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @param[in] format The pointer to hold the description of the currently supported format.
 *
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Error in the passed arguments.
 *      - ESP_ERR_NOT_SUPPORTED: The motor driver does not support this operation.
 *      - ESP_CAM_MOTOR_ERR_FAILED_SET_FORMAT: An error occurred while writing data over the SCCB bus
 */
esp_err_t esp_cam_motor_set_format(esp_cam_motor_device_t *dev, const esp_cam_motor_format_t *format);

/**
 * @brief Get the current camera motor Working format.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @param[out] format The pointer to hold the description of the currently format.
 * @return
 *      - ESP_OK: Success
 *      - ESP_FAIL: The motor driver has not been formatured the working format yet.
 *      - ESP_ERR_INVALID_ARG: Error in the passed arguments.
 *      - ESP_ERR_NOT_SUPPORTED: The motor driver does not support this operation.
 */
esp_err_t esp_cam_motor_get_format(esp_cam_motor_device_t *dev, esp_cam_motor_format_t *format);

/**
 * @brief Perform an ioctl request on the camera motor.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @param[in] cmd The ioctl command, see esp_cam_motor_types.h.
 * @param[in] arg The argument accompanying the ioctl command.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Error in the passed arguments.
 *      - ESP_ERR_NOT_SUPPORTED: The motor driver does not support this cmd or arg.
 */
esp_err_t esp_cam_motor_ioctl(esp_cam_motor_device_t *dev, uint32_t cmd, void *arg);

/**
 * @brief Get the module name of the current camera device.
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @return
 *      - Camera module name on success, or "NULL"
 */
const char *esp_cam_motor_get_name(esp_cam_motor_device_t *dev);

/**
 * @brief Delete camera device
 *
 * @param[in] dev Camera motor device handle that created by `motor_detect`.
 * @return
 *        - ESP_OK: If Camera motor is successfully deleted.
 */
esp_err_t esp_cam_motor_del_dev(esp_cam_motor_device_t *dev);

#ifdef __cplusplus
}
#endif
