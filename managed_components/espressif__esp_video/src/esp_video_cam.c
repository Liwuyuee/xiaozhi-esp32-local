/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#include "esp_log.h"
#include "esp_cam_sensor.h"
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
#include "esp_cam_motor.h"
#endif
#include "esp_video_ioctl.h"
#include "esp_video_cam.h"

struct control_map {
    uint32_t esp_cam_priv_id;
    uint32_t v4l2_id;
};

typedef enum cam_dev_type {
    CAM_DEV_SENSOR = 0,
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
    CAM_DEV_MOTOR
#endif
} cam_dev_type_t;

static const char *TAG = "esp_video_cam";

/**
 * Todo: AEG-1094
 *
 * @note The order of the control map table is important, because the control map table is used to
 *       get the control ID map pointer based on V4L2 control ID. Put the control ID that is most
 *       frequently used at the beginning of the table which can improve the performance of the
 *       control ID map pointer lookup.
 */
static const struct control_map s_sensor_control_map_table[] = {
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_GAIN,
        .v4l2_id = V4L2_CID_GAIN,
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_EXPOSURE_VAL,
        .v4l2_id = V4L2_CID_EXPOSURE,
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_STATS,
        .v4l2_id = V4L2_CID_CAMERA_STATS
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_AE_LEVEL,
        .v4l2_id = V4L2_CID_CAMERA_AE_LEVEL
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_GROUP_EXP_GAIN,
        .v4l2_id = V4L2_CID_CAMERA_GROUP
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_EXPOSURE_US,
        .v4l2_id = V4L2_CID_EXPOSURE_ABSOLUTE,
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_JPEG_QUALITY,
        .v4l2_id = V4L2_CID_JPEG_COMPRESSION_QUALITY,
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_3A_LOCK,
        .v4l2_id = V4L2_CID_3A_LOCK,
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_FLASH_LED,
        .v4l2_id = V4L2_CID_FLASH_LED_MODE,
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_VFLIP,
        .v4l2_id = V4L2_CID_VFLIP,
    },
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_HMIRROR,
        .v4l2_id = V4L2_CID_HFLIP,
    },
};

static const struct control_map s_sensor_control_ioctl_table[] = {
    {
        .esp_cam_priv_id = ESP_CAM_SENSOR_IOC_S_TEST_PATTERN,
        .v4l2_id = V4L2_CID_TEST_PATTERN,
    },
};

#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
static const struct control_map s_motor_control_map_table[] = {
    {
        .esp_cam_priv_id = ESP_CAM_MOTOR_POSITION_CODE,
        .v4l2_id = V4L2_CID_FOCUS_ABSOLUTE,
    },
    {
        .esp_cam_priv_id = ESP_CAM_MOTOR_MOVING_START_TIME,
        .v4l2_id = V4L2_CID_MOTOR_START_TIME,
    }
};
#endif

/**
 * @brief Get control ID map pointer based on V4L2 control ID
 *
 * @param v4l2_id V4L2 control ID
 * @param ioctl   Camera device command type pointe, true: it is sensor ioctl command; false: it is sensor parameter ID command
 * @param type    Camera device type pointer
 *
 * @return
 *      - Control ID map pointer on success
 *      - NULL if failed
 */
static const struct control_map *get_v4l2_ext_control_map(uint32_t v4l2_id, bool *ioctl, cam_dev_type_t *type)
{
    for (int i = 0; i < ARRAY_SIZE(s_sensor_control_map_table); i++) {
        if (s_sensor_control_map_table[i].v4l2_id == v4l2_id) {
            *ioctl = false;
            *type = CAM_DEV_SENSOR;
            return &s_sensor_control_map_table[i];
        }
    }

#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
    for (int i = 0; i < ARRAY_SIZE(s_motor_control_map_table); i++) {
        if (s_motor_control_map_table[i].v4l2_id == v4l2_id) {
            *ioctl = false;
            *type = CAM_DEV_MOTOR;
            return &s_motor_control_map_table[i];
        }
    }
#endif

    for (int i = 0; i < ARRAY_SIZE(s_sensor_control_ioctl_table); i++) {
        if (s_sensor_control_ioctl_table[i].v4l2_id == v4l2_id) {
            *ioctl = true;
            *type = CAM_DEV_SENSOR;
            return &s_sensor_control_ioctl_table[i];
        }
    }

    return NULL;
}

/**
 * @brief Get control internal operation parameters
 *
 * @param cam      Camera device pointer
 * @param controls V4L2 external control class pointer
 * @param ctrl     V4L2 external control pointer
 * @param qdesc    Camera sensor device query description pointer
 * @param buf_ptr  Actual data buffer pointer
 * @param buf_size Actual size buffer pointer
 * @param ioctl    Sensor command type pointe, true: it is sensor ioctl command; false: it is sensor parameter ID command
 * @param type     Camera device type pointer
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
static esp_err_t get_opt_value_desc(esp_video_cam_t *cam, const struct v4l2_ext_controls *controls, struct v4l2_ext_control *ctrl,
                                    esp_cam_sensor_param_desc_t *qdesc, void **buf_ptr, size_t *buf_size, bool *ioctl, cam_dev_type_t *dev_type)
{
    esp_err_t ret;
    const struct control_map *control_map;

    if (controls->ctrl_class == V4L2_CTRL_CLASS_ESP_CAM_IOCTL) {
        *ioctl = true;
        *dev_type = CAM_DEV_SENSOR;

        qdesc->id = ctrl->id;

        *buf_ptr = ctrl->p_u8;
        *buf_size = ctrl->size;

        return ESP_OK;
    } else {
        control_map = get_v4l2_ext_control_map(ctrl->id, ioctl, dev_type);
        if (!control_map) {
            ESP_LOGE(TAG, "ctrl id=%" PRIx32 " is not supported", ctrl->id);
            return ESP_ERR_NOT_SUPPORTED;
        }

        qdesc->id = control_map->esp_cam_priv_id;
    }

    if (*ioctl == false) {
        if (*dev_type == CAM_DEV_SENSOR) {
            ret = esp_cam_sensor_query_para_desc(cam->sensor, qdesc);
        } else {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
            ret = esp_cam_motor_query_para_desc(cam->motor, qdesc);
#else
            ret = ESP_ERR_NOT_SUPPORTED;
#endif
        }
        if (ret == ESP_ERR_NOT_SUPPORTED) {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
            const char *name = *dev_type == CAM_DEV_SENSOR ? cam->sensor->name : cam->motor->name;
#else
            const char *name = cam->sensor->name;
#endif
            ESP_LOGD(TAG, "sensor %s doesn't support to query parameter description", name);

            *buf_ptr = &ctrl->value;
            *buf_size = sizeof(ctrl->value);

            qdesc->type = UINT32_MAX;
        } else if (ret == ESP_OK) {
            switch (qdesc->type) {
            case ESP_CAM_SENSOR_PARAM_TYPE_NUMBER:
            case ESP_CAM_SENSOR_PARAM_TYPE_ENUMERATION:
            case ESP_CAM_SENSOR_PARAM_TYPE_BITMASK:
                *buf_ptr = &ctrl->value;
                *buf_size = sizeof(ctrl->value);
                break;
            case ESP_CAM_SENSOR_PARAM_TYPE_U8:
                *buf_ptr = ctrl->p_u8;
                *buf_size = ctrl->size;
                break;
            default:
                ESP_LOGE(TAG, "sensor description type=%" PRIu32 " is not supported", qdesc->type);
                return ESP_ERR_NOT_SUPPORTED;
            }
        } else {
            ESP_LOGE(TAG, "failed to query ctrl id=%" PRIx32, ctrl->id);
            return ret;
        }
    } else {
        switch (qdesc->id) {
        case ESP_CAM_SENSOR_IOC_S_TEST_PATTERN: {
            *buf_ptr = &ctrl->value;
            *buf_size = sizeof(ctrl->value);
            break;
        }
        default: {
            ESP_LOGE(TAG, "sensor command=%" PRIu32 " is not supported", qdesc->id);
            return ESP_ERR_NOT_SUPPORTED;
        }
        }
    }

    return ESP_OK;
}

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
esp_err_t esp_video_cam_set_ext_ctrls(esp_video_cam_t *cam, const struct v4l2_ext_controls *controls)
{
    esp_err_t ret = ESP_ERR_INVALID_ARG;

    for (int i = 0; i < controls->count; i++) {
        bool ioctl;
        void *value_ptr;
        size_t value_size;
        cam_dev_type_t dev_type;
        esp_cam_sensor_param_desc_t qdesc;
        struct v4l2_ext_control *ctrl = &controls->controls[i];

        ret = get_opt_value_desc(cam, controls, ctrl, &qdesc, &value_ptr, &value_size, &ioctl, &dev_type);
        if (ret != ESP_OK) {
            break;
        }

        if (ioctl) {
            if (dev_type == CAM_DEV_SENSOR) {
                ret = esp_cam_sensor_ioctl(cam->sensor, qdesc.id, value_ptr);
            } else {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
                ret = esp_cam_motor_ioctl(cam->motor, qdesc.id, value_ptr);
#else
                ret = ESP_ERR_NOT_SUPPORTED;
#endif
            }
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "failed to set ioctl id=%" PRIx32, ctrl->id);
                break;
            }
        } else {
            int32_t value_buf = ctrl->value;

            switch (qdesc.type) {
            case ESP_CAM_SENSOR_PARAM_TYPE_NUMBER:
                if ((value_buf > qdesc.number.maximum) || (value_buf < qdesc.number.minimum) ||
                        (value_buf % qdesc.number.step)) {
                    ESP_LOGE(TAG, "number: ctrl id=%" PRIx32 " value=%" PRIi32 " is out of range(max=%" PRIi32 ", min=%" PRIi32 ", step=%"PRIu32")",
                             ctrl->id, value_buf, (int32_t)qdesc.number.maximum, (int32_t)qdesc.number.minimum, (uint32_t)qdesc.number.step);
                    return ESP_ERR_INVALID_ARG;
                }
                break;
            case ESP_CAM_SENSOR_PARAM_TYPE_ENUMERATION: {
                if (value_buf < 0 || value_buf >= qdesc.enumeration.count) {
                    ESP_LOGE(TAG, "enum: ctrl id=%" PRIx32 " value=%" PRIu32 " is out of range(from 0 to %" PRIu32 ")",
                             ctrl->id, value_buf, qdesc.enumeration.count);
                    return ESP_ERR_INVALID_ARG;
                }
                break;
            }
            case ESP_CAM_SENSOR_PARAM_TYPE_BITMASK:
                if (value_buf & (~qdesc.bitmask.value)) {
                    ESP_LOGE(TAG, "mask: ctrl id=%" PRIx32 " value=%" PRIx32 " is out of range(%" PRIx32 ")",
                             ctrl->id, value_buf, qdesc.bitmask.value);
                    return ESP_ERR_INVALID_ARG;
                }
                break;
            case ESP_CAM_SENSOR_PARAM_TYPE_U8:
                if (value_size != qdesc.u8.size) {
                    ESP_LOGE(TAG, "mask: ctrl id=%" PRIx32 " size=%zu is not equal to sensor data size(%" PRIu32 ")",
                             ctrl->id, value_size, qdesc.u8.size);
                    return ESP_ERR_INVALID_ARG;
                }
                break;
            case UINT32_MAX:
                ESP_LOGD(TAG, "can't check ctrl id=%" PRIx32, ctrl->id);
                break;
            default:
                ESP_LOGE(TAG, "sensor description type=%" PRIx32 " is not supported", qdesc.type);
                return ESP_ERR_NOT_SUPPORTED;
            }

            if (dev_type == CAM_DEV_SENSOR) {
                ret = esp_cam_sensor_set_para_value(cam->sensor, qdesc.id, value_ptr, value_size);
            } else {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
                ret = esp_cam_motor_set_para_value(cam->motor, qdesc.id, value_ptr, value_size);
#else
                ret = ESP_ERR_NOT_SUPPORTED;
#endif
            }
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "failed to set ctrl id=%" PRIx32, ctrl->id);
                break;
            }
        }
    }

    return ret;
}

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
esp_err_t esp_video_cam_get_ext_ctrls(esp_video_cam_t *cam, struct v4l2_ext_controls *controls)
{
    esp_err_t ret = ESP_ERR_INVALID_ARG;

    for (int i = 0; i < controls->count; i++) {
        bool ioctl;
        void *value_ptr;
        size_t value_size;
        cam_dev_type_t dev_type;
        esp_cam_sensor_param_desc_t qdesc;
        struct v4l2_ext_control *ctrl = &controls->controls[i];

        ret = get_opt_value_desc(cam, controls, ctrl, &qdesc, &value_ptr, &value_size, &ioctl, &dev_type);
        if (ret != ESP_OK) {
            break;
        }

        if (ioctl) {
            if (dev_type == CAM_DEV_SENSOR) {
                ret = esp_cam_sensor_ioctl(cam->sensor, qdesc.id, value_ptr);
            } else {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
                ret = esp_cam_motor_ioctl(cam->motor, qdesc.id, value_ptr);
#else
                ret = ESP_ERR_NOT_SUPPORTED;
#endif
            }
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "failed to get ioctl id=%" PRIx32, ctrl->id);
                break;
            }
        } else {
            if (dev_type == CAM_DEV_SENSOR) {
                ret = esp_cam_sensor_get_para_value(cam->sensor, qdesc.id, value_ptr, value_size);
            } else {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
                ret = esp_cam_motor_get_para_value(cam->motor, qdesc.id, value_ptr, value_size);
#else
                ret = ESP_ERR_NOT_SUPPORTED;
#endif
            }
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "failed to get ctrl id=%" PRIx32, ctrl->id);
                break;
            }
        }
    }

    return ret;
}

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
esp_err_t esp_video_cam_query_ext_ctrls(esp_video_cam_t *cam, struct v4l2_query_ext_ctrl *qctrl)
{
    bool ioctl;
    esp_err_t ret;
    cam_dev_type_t dev_type;
    const struct control_map *control_map;
    esp_cam_sensor_param_desc_t qdesc;

    control_map = get_v4l2_ext_control_map(qctrl->id, &ioctl, &dev_type);
    if (!control_map) {
        ESP_LOGE(TAG, "ctrl id=%" PRIx32 " is not supported", qctrl->id);
        return ESP_ERR_NOT_SUPPORTED;
    }

    qdesc.id = control_map->esp_cam_priv_id;
    if (dev_type == CAM_DEV_SENSOR) {
        ret = esp_cam_sensor_query_para_desc(cam->sensor, &qdesc);
    } else {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
        ret = esp_cam_motor_query_para_desc(cam->motor, &qdesc);
#else
        ret = ESP_ERR_NOT_SUPPORTED;
#endif
    }
    if (ret != ESP_OK) {
        ESP_LOGD(TAG, "failed to query sensor id=%" PRIx32, qdesc.id);
        return ret;
    }

    /**
     * Todo: AEG-1095
     */
    switch (qdesc.type) {
    case ESP_CAM_SENSOR_PARAM_TYPE_NUMBER:
        qctrl->type = V4L2_CTRL_TYPE_INTEGER;
        qctrl->maximum = qdesc.number.maximum;
        qctrl->minimum = qdesc.number.minimum;
        qctrl->step = qdesc.number.step;;
        qctrl->elems = 1;
        qctrl->nr_of_dims = 0;
        qctrl->default_value = qdesc.default_value;
        break;
    case ESP_CAM_SENSOR_PARAM_TYPE_ENUMERATION:
        qctrl->type = V4L2_CTRL_TYPE_INTEGER_MENU;
        qctrl->maximum = qdesc.enumeration.count - 1;
        qctrl->minimum = 0;
        qctrl->step = 1;
        qctrl->elem_size = sizeof(uint32_t);
        qctrl->elems = 1;
        qctrl->nr_of_dims = 0;
        qctrl->dims[0] = qctrl->elem_size;
        qctrl->default_value = qdesc.default_value;
        break;
    case ESP_CAM_SENSOR_PARAM_TYPE_BITMASK:
        qctrl->type = V4L2_CTRL_TYPE_BITMASK;
        qctrl->minimum = 0;
        qctrl->maximum = qdesc.bitmask.value;
        qctrl->step = 1;
        qctrl->elems = 1;
        qctrl->nr_of_dims = 0;
        qctrl->default_value = qdesc.default_value;
        break;
    case ESP_CAM_SENSOR_PARAM_TYPE_U8:
        qctrl->type = V4L2_CTRL_TYPE_U8;
        qctrl->minimum = 0;
        qctrl->maximum = UINT8_MAX;
        qctrl->step = 1;
        qctrl->elem_size = qdesc.u8.size;
        qctrl->elems = 1;
        qctrl->nr_of_dims = 0;
        qctrl->dims[0] = 1;
        qctrl->default_value = 0;
        break;
    default:
        ESP_LOGD(TAG, "sensor type=%" PRIu32 " is not supported", qdesc.type);
        return ESP_ERR_NOT_SUPPORTED;
    }

    return ESP_OK;
}

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
esp_err_t esp_video_cam_query_menu(esp_video_cam_t *cam, struct v4l2_querymenu *qmenu)
{
    bool ioctl;
    esp_err_t ret;
    cam_dev_type_t dev_type;
    const struct control_map *control_map;
    esp_cam_sensor_param_desc_t qdesc;

    control_map = get_v4l2_ext_control_map(qmenu->id, &ioctl, &dev_type);
    if (!control_map) {
        ESP_LOGE(TAG, "ctrl id=%" PRIx32 " is not supported", qmenu->id);
        return ESP_ERR_NOT_SUPPORTED;
    }

    if (ioctl) {
        ESP_LOGE(TAG, "ctrl id=%" PRIx32 " is ioctl type", qmenu->id);
        return ESP_ERR_NOT_SUPPORTED;
    }

    qdesc.id = control_map->esp_cam_priv_id;
    if (dev_type == CAM_DEV_SENSOR) {
        ret = esp_cam_sensor_query_para_desc(cam->sensor, &qdesc);
    } else {
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
        ret = esp_cam_motor_query_para_desc(cam->motor, &qdesc);
#else
        ret = ESP_ERR_NOT_SUPPORTED;
#endif
    }
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "failed to query sensor id=%" PRIx32, qdesc.id);
        return ret;
    }

    if (qdesc.type != ESP_CAM_SENSOR_PARAM_TYPE_ENUMERATION) {
        ESP_LOGE(TAG, "ctrl id=%" PRIx32 " is not menu type", qmenu->id);
        return ESP_ERR_INVALID_ARG;
    }

    if (qmenu->index >= qdesc.enumeration.count) {
        ESP_LOGE(TAG, "ctrl id=%" PRIx32 " is out of range(max=" PRIx32 ")", qdesc.enumeration.count - 1);
        return ESP_ERR_INVALID_ARG;
    }

    qmenu->value = qdesc.enumeration.elements[qmenu->index];

    return ESP_OK;
}
