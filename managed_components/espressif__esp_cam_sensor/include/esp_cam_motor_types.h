/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_cam_sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Camera AF motor error code
 */
#define ESP_CAM_MOTOR_ERR_OFFSET                    0x1000
#define ESP_CAM_MOTOR_ERR_BASE                      ESP_CAM_SENSOR_ERR_BASE + ESP_CAM_MOTOR_ERR_OFFSET
#define ESP_CAM_MOTOR_ERR_NOT_DETECTED             (ESP_CAM_MOTOR_ERR_BASE + 1)
#define ESP_CAM_MOTOR_ERR_NOT_SUPPORTED            (ESP_CAM_MOTOR_ERR_BASE + 2)
#define ESP_CAM_MOTOR_ERR_FAILED_SET_POS           (ESP_CAM_MOTOR_ERR_BASE + 3)
#define ESP_CAM_MOTOR_ERR_FAILED_SET_REG           (ESP_CAM_MOTOR_ERR_BASE + 4)
#define ESP_CAM_MOTOR_ERR_FAILED_GET_REG           (ESP_CAM_MOTOR_ERR_BASE + 5)
#define ESP_CAM_MOTOR_ERR_FAILED_RESET             (ESP_CAM_MOTOR_ERR_BASE + 6)
#define ESP_CAM_MOTOR_ERR_FAILED_SET_FORMAT        (ESP_CAM_MOTOR_ERR_BASE + 7)

/**
 * @brief Camera AF motor class's control ID
 */
#define ESP_CAM_MOTOR_POSITION_CODE                ESP_CAM_SENSOR_CLASS_ID(ESP_CAM_SENSOR_CID_CLASS_MOTOR, 0x01)   /*!< AF motor position code */
#define ESP_CAM_MOTOR_CODES_PER_STEP               ESP_CAM_SENSOR_CLASS_ID(ESP_CAM_SENSOR_CID_CLASS_MOTOR, 0x02)   /*!< AF motor position code */
#define ESP_CAM_MOTOR_PERIODE_PER_STEP             ESP_CAM_SENSOR_CLASS_ID(ESP_CAM_SENSOR_CID_CLASS_MOTOR, 0x03)   /*!< AF motor position code */
#define ESP_CAM_MOTOR_UPDATE_STEP                  ESP_CAM_SENSOR_CLASS_ID(ESP_CAM_SENSOR_CID_CLASS_MOTOR, 0x04)   /*!< AF motor position code */
#define ESP_CAM_MOTOR_FOCAL_LENGTH                 ESP_CAM_SENSOR_CLASS_ID(ESP_CAM_SENSOR_CID_CLASS_MOTOR, 0x05)   /*!< AF motor position code */
#define ESP_CAM_MOTOR_SETTLE_TIME                  ESP_CAM_SENSOR_CLASS_ID(ESP_CAM_SENSOR_CID_CLASS_MOTOR, 0x06)   /*!< Rising time */
#define ESP_CAM_MOTOR_MOVING_START_TIME            ESP_CAM_SENSOR_CLASS_ID(ESP_CAM_SENSOR_CID_CLASS_MOTOR, 0x07)   /*!< Moving start time */

/**
 * @brief Camera AF motor command
 */
#define ESP_CAM_MOTOR_IOC_NUM                      0x10
#define ESP_CAM_MOTOR_IOC_BASE                     ESP_CAM_SENSOR_IOC_MAX + 0x01
#define ESP_CAM_MOTOR_IOC_HW_POWER_ON              ESP_CAM_SENSOR_IOC(ESP_CAM_MOTOR_IOC_BASE, sizeof(int))           /*!< Hardware power on */
#define ESP_CAM_MOTOR_IOC_SW_STANDBY               ESP_CAM_SENSOR_IOC(ESP_CAM_MOTOR_IOC_BASE + 0x01, sizeof(int))    /*!< Software standby */
#define ESP_CAM_MOTOR_IOC_S_REG                    ESP_CAM_SENSOR_IOC(ESP_CAM_MOTOR_IOC_BASE + 0x02, sizeof(esp_cam_motor_reg_val_t))
#define ESP_CAM_MOTOR_IOC_G_REG                    ESP_CAM_SENSOR_IOC(ESP_CAM_MOTOR_IOC_BASE + 0x03, sizeof(esp_cam_motor_reg_val_t))
#define ESP_CAM_MOTOR_IOC_MAX                      ESP_CAM_SENSOR_IOC(ESP_CAM_MOTOR_IOC_BASE + ESP_CAM_MOTOR_IOC_NUM, 0)

typedef enum {
    ESP_CAM_MOTOR_NORM,
    ESP_CAM_MOTOR_SLEEP,
    ESP_CAM_MOTOR_START_MOVING,
    ESP_CAM_MOTOR_MOVING,
    ESP_CAM_MOTOR_MOVING_DONE,
    ESP_CAM_MOTOR_UPDATING,
} esp_cam_motor_status;

typedef struct {
    esp_sccb_io_handle_t sccb_handle;            /*!< the handle of the sccb bus bound to the motor, returned by sccb_new_i2c_io */
    gpio_num_t  reset_pin;                       /*!< Hardware reset pin, set to -1 if not used */
    gpio_num_t  pwdn_pin;                        /*!< Power down pin, set to -1 if not used */
    gpio_num_t  signal_pin;                      /*!< Signal output pin, set to -1 if not used */
    void *platform_data;                         /*!< Platform info */
} esp_cam_motor_config_t;

/**
 * @brief Set/get register value parameters.
 */
typedef struct {
    uint16_t regaddr;   /*!< Register address */
    uint16_t value;     /*!< Register value */
} esp_cam_motor_reg_val_t;

typedef enum {
    ESP_CAM_MOTOR_DIRECT_MODE = 0x1,    /*!< direct control */
    ESP_CAM_MOTOR_LSC_MODE = 0x2,       /*!< linear slope control */
    ESP_CAM_MOTOR_DLC_MODE = 0x3,       /*!< dual level control */
} esp_cam_motor_mode_t;

typedef struct {
    const char *name;                           /*!< String description for working format */
    esp_cam_motor_mode_t mode;
    struct {
        uint16_t period_in_us;
        uint16_t codes_per_step;
    } step_period;
    const void *regs;                           /*!< Regs to enable this format */
    int regs_size;
    int init_position;                          /*!< The init position related to the fmt regs */
    void *reserved;
} esp_cam_motor_format_t;

typedef struct _esp_cam_motor_ops esp_cam_motor_ops_t;

/**
 * @brief Type of camera motor device
 */
typedef struct {
    char *name;                                  /*!< String name of the motor */
    esp_cam_motor_status status;                 /*!< Motor status */
    esp_sccb_io_handle_t sccb_handle;            /*!< SCCB io handle that created by `sccb_new_i2c_io` */
    const esp_cam_motor_format_t *cur_format;    /*!< Current format */
    gpio_num_t  reset_pin;                       /*!< Hardware reset pin, set to -1 if not used */
    gpio_num_t  pwdn_pin;                        /*!< Power down pin, set to -1 if not used */
    gpio_num_t  signal_pin;                      /*!< Signal output pin, set to -1 if not used */
    int current_position;                        /*!< Current position */
    int requested_position;                      /*!< Requested position */

    int64_t moving_start_time;                   /*!< Time to start moving position */
    int64_t updating_start_time;                 /*!< Time to start updating configuration */
    const esp_cam_motor_ops_t *ops;              /*!< Pointer to the camera motor driver operation array. */
    void *priv;                                  /*!< Private data */
} esp_cam_motor_device_t;

/**
 * @brief Description of output formats supported by the camera motor driver
 */
typedef struct _cam_motor_fmt_array {
    uint8_t count;
    const esp_cam_motor_format_t *fmt_array;
} esp_cam_motor_fmt_array_t;

/**
 * @brief Description of automatically detecting camera motors
 */
typedef struct {
    esp_cam_motor_device_t *(*detect)(void *);   /*!< Pointer to the detect function */
    void *cam_info;
    uint16_t sccb_addr;
} esp_cam_motor_detect_fn_t;

typedef struct esp_cam_sensor_param_desc esp_cam_motor_param_desc_t;

/**
 * @brief camera motor driver operation array
 */
typedef struct _esp_cam_motor_ops {
    int (*query_para_desc)(esp_cam_motor_device_t *dev, esp_cam_motor_param_desc_t *qdesc);
    int (*get_para_value)(esp_cam_motor_device_t *dev, uint32_t id, void *arg, size_t size);
    int (*set_para_value)(esp_cam_motor_device_t *dev, uint32_t id, const void *arg, size_t size);

    int (*query_support_formats)(esp_cam_motor_device_t *dev, esp_cam_motor_fmt_array_t *parry);
    int (*set_format)(esp_cam_motor_device_t *dev, const esp_cam_motor_format_t *format);
    int (*get_format)(esp_cam_motor_device_t *dev, esp_cam_motor_format_t *format);

    int (*priv_ioctl)(esp_cam_motor_device_t *dev, uint32_t cmd, void *arg);
    int (*del)(esp_cam_motor_device_t *dev);
} esp_cam_motor_ops_t;

#ifdef __cplusplus
}
#endif
