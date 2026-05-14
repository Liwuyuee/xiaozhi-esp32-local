/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/timers.h"

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_cam_motor.h"
#include "esp_cam_motor_detect.h"
#include "dw9714_settings.h"
#include "dw9714.h"

#define DW9714_DEFAULT_FOCUS_POS (0)
#define DW9714_MAX_FOCUS_POS     1023
#define DW9714_MIN_FOCUS_POS     DW9714_DEFAULT_FOCUS_POS

#define DW9714_IO_MUX_LOCK(mux)
#define DW9714_IO_MUX_UNLOCK(mux)
#define DW9714_MOVING_TEST_EN (0)

#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif

#define delay_ms(ms)  vTaskDelay((ms > portTICK_PERIOD_MS ? ms/ portTICK_PERIOD_MS : 1))
#define DW9714_SUPPORT_NUM CONFIG_CAMERA_DW9714_MAX_SUPPORT

static const char *TAG = "dw9714";

static const esp_cam_motor_format_t dw9714_format_info[] = {
    {
        .name = "LSC_mode_with_mclk01_src03",
        .mode = ESP_CAM_MOTOR_LSC_MODE,
        .step_period = {
            .period_in_us = 152,
            .codes_per_step = LSC_S32_CODES_PER_STEP, // Depends on LSC_SET_CODE
        },
        .init_position = DW9714_DEFAULT_FOCUS_POS,
        .regs = lsc_mode_mclk01_src03_init_list,
        .regs_size = ARRAY_SIZE(lsc_mode_mclk01_src03_init_list),
        .reserved = NULL,
    },
    {
        .name = "DLC_mode_with_mclk02_src17",
        .mode = ESP_CAM_MOTOR_DLC_MODE,
        .step_period = {
            .period_in_us = 4060,
            .codes_per_step = 1,
        },
        .init_position = DW9714_DEFAULT_FOCUS_POS,
        .regs = dlc_mode_mclk02_src17_init_list,
        .regs_size = ARRAY_SIZE(dlc_mode_mclk02_src17_init_list),
        .reserved = NULL,
    }
};

static esp_err_t dw9714_read(esp_sccb_io_handle_t sccb_handle, uint16_t *read_buf)
{
    return esp_sccb_receive_v16(sccb_handle, read_buf);
}

static esp_err_t dw9714_write(esp_sccb_io_handle_t sccb_handle, uint16_t data)
{
    return esp_sccb_transmit_v16(sccb_handle, data);
}

/* write a array of vals */
static esp_err_t dw9714_write_array(esp_sccb_io_handle_t sccb_handle, dw9714_data_type_t *data_array, size_t array_size)
{
    int i = 0;
    esp_err_t ret = ESP_OK;
    while ((ret == ESP_OK) && (i < array_size)) {
        ret = dw9714_write(sccb_handle, data_array[i].val);
        i++;
    }
    ESP_LOGD(TAG, "Set array done[i=%d]", i);
    return ret;
}

/* Set position code */
static esp_err_t dw9714_set_pos_code(esp_cam_motor_device_t *dev, int pos)
{
    esp_err_t ret = ESP_FAIL;
    dw9714_data_type_t w_data = {0};
    if (pos > DW9714_MAX_FOCUS_POS) {
        pos = DW9714_MAX_FOCUS_POS;
    } else if (pos < DW9714_MIN_FOCUS_POS) {
        pos = DW9714_MIN_FOCUS_POS;
    }

    switch (dev->cur_format->mode) {
    case ESP_CAM_MOTOR_DLC_MODE:
    case ESP_CAM_MOTOR_DIRECT_MODE:
        w_data.d = pos;
        ret = dw9714_write(dev->sccb_handle, w_data.val);
        break;
    case ESP_CAM_MOTOR_LSC_MODE:
        w_data.val = LSC_SET_CODE(pos);
        ret = dw9714_write(dev->sccb_handle, w_data.val);
        break;
    default:
        ret = ESP_ERR_INVALID_ARG;
        break;
    }
    if (ret == ESP_OK) {
        // This is not accurate, because moving to the designated position usually takes some times.
        dev->current_position = pos;
        dev->moving_start_time = esp_timer_get_time();
    }
    return ret;
}

#if DW9714_MOVING_TEST_EN
static int s_count = 0;
static void wb_timer_callback(TimerHandle_t timer)
{
    uint16_t read_v1 = 0;
    esp_cam_motor_device_t *dev = (esp_cam_motor_device_t *)pvTimerGetTimerID(timer);
    dw9714_set_pos_code(dev, s_count);
    s_count += 10;
    dw9714_read(dev->sccb_handle, &read_v1);
    ESP_LOGW(TAG, "Set array done[i=%d], read=0x%x", s_count, read_v1);
}
#endif

static esp_err_t dw9714_query_para_desc(esp_cam_motor_device_t *dev, esp_cam_motor_param_desc_t *qdesc)
{
    esp_err_t ret = ESP_OK;
    switch (qdesc->id) {
    case ESP_CAM_MOTOR_POSITION_CODE:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = 0;
        qdesc->number.maximum = DW9714_MAX_FOCUS_POS;
        qdesc->number.step = 1;
        qdesc->default_value = DW9714_DEFAULT_FOCUS_POS;
        break;
    case ESP_CAM_MOTOR_MOVING_START_TIME:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_U8;
        qdesc->u8.size = sizeof(int64_t);
        break;
    default: {
        ESP_LOGD(TAG, "id=%"PRIx32" is not supported", qdesc->id);
        ret = ESP_ERR_INVALID_ARG;
        break;
    }
    }
    return ret;
}

static esp_err_t dw9714_get_para_value(esp_cam_motor_device_t *dev, uint32_t id, void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;
    switch (id) {
    case ESP_CAM_MOTOR_POSITION_CODE: {
        ESP_RETURN_ON_FALSE(arg && size >= sizeof(uint16_t), ESP_ERR_INVALID_ARG, TAG, "Para size err");
        *(uint16_t *)arg = dev->current_position; // use dw9714_read() is a better choice.
        break;
    }
    case ESP_CAM_MOTOR_MOVING_START_TIME:
        ESP_RETURN_ON_FALSE(arg && size == sizeof(int64_t), ESP_ERR_INVALID_ARG, TAG, "Para size err");
        *(int64_t *)arg = dev->moving_start_time;
        break;
    default: {
        ret = ESP_ERR_NOT_SUPPORTED;
        break;
    }
    }
    return ret;
}

/*Most important is speed and position*/
static esp_err_t dw9714_set_para_value(esp_cam_motor_device_t *dev, uint32_t id, const void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;

    switch (id) {
    case ESP_CAM_MOTOR_POSITION_CODE: {
        ESP_RETURN_ON_FALSE(arg && size >= sizeof(int), ESP_ERR_INVALID_ARG, TAG, "Para size err");
        int *value = (int *)arg;

        ret = dw9714_set_pos_code(dev, *value);
        break;
    }
    default: {
        ESP_LOGE(TAG, "set id=%" PRIx32 " is not supported", id);
        ret = ESP_ERR_INVALID_ARG;
        break;
    }
    }

    return ret;
}

static esp_err_t dw9714_query_support_formats(esp_cam_motor_device_t *dev, esp_cam_motor_fmt_array_t *formats)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, formats);

    formats->count = ARRAY_SIZE(dw9714_format_info);
    formats->fmt_array = &dw9714_format_info[0];
    return ESP_OK;
}

/* Init cam motor para, you can change this function according your spec if it's necessary*/
static esp_err_t dw9714_set_format(esp_cam_motor_device_t *dev, const esp_cam_motor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);

    esp_err_t ret = ESP_OK;

    if (format == NULL) {
        format = &dw9714_format_info[CONFIG_DW9714_FORMAT_INDEX_DEFAULT];
    }

    ret = dw9714_write_array(dev->sccb_handle, (dw9714_data_type_t *)format->regs, format->regs_size);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Set format vals fail");
        return ESP_CAM_MOTOR_ERR_FAILED_SET_FORMAT;
    }

    dev->cur_format = format;
    dev->current_position = format->init_position;

    return ret;
}

static esp_err_t dw9714_get_format(esp_cam_motor_device_t *dev, esp_cam_motor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, format);

    esp_err_t ret = ESP_FAIL;

    if (dev->cur_format != NULL) {
        memcpy(format, dev->cur_format, sizeof(esp_cam_motor_format_t));
        ret = ESP_OK;
    }
    return ret;
}

static esp_err_t dw9714_soft_standby(esp_cam_motor_device_t *dev, bool en)
{
    esp_err_t ret = ESP_OK;
    dw9714_data_type_t w_data = {0};
    w_data.d = (uint16_t)(dev->current_position);

    if (en) {
        w_data.pd = 1;
    } else {
        w_data.pd = 0;
    }

    ESP_LOGD(TAG, "SW standby set val=0x%x", w_data.val);
    dw9714_write(dev->sccb_handle, w_data.val);

    delay_ms(DW9714_WAIT_STABLE_TIME);

    return ret;
}

static esp_err_t dw9714_hw_power_on(esp_cam_motor_device_t *dev, bool en)
{
    esp_err_t ret = ESP_OK;

    if (dev->pwdn_pin >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << dev->pwdn_pin;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);

        if (en) {
            gpio_set_level(dev->pwdn_pin, 1);
        } else {
            gpio_set_level(dev->pwdn_pin, 0);
        }
        delay_ms(DW9714_WAIT_STABLE_TIME);
    }

    return ret;
}

static esp_err_t dw9714_read_check(esp_cam_motor_device_t *dev)
{
    uint16_t temp = 0x0;
    esp_err_t ret = dw9714_write(dev->sccb_handle, temp);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ret, TAG, "write failed");
    ret = dw9714_read(dev->sccb_handle, &temp);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ret, TAG, "read failed");

    return ret;
}

static esp_err_t dw9714_priv_ioctl(esp_cam_motor_device_t *dev, uint32_t cmd, void *arg)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    esp_err_t ret = ESP_FAIL;

    DW9714_IO_MUX_LOCK(mux);

    switch (cmd) {
    case ESP_CAM_MOTOR_IOC_HW_POWER_ON:
        ret = dw9714_hw_power_on(dev, *(int *)arg);
        break;
    case ESP_CAM_MOTOR_IOC_SW_STANDBY:
        ret = dw9714_soft_standby(dev, *(int *)arg);
        break;
    default:
        ret = ESP_ERR_INVALID_ARG;
        break;
    }

    DW9714_IO_MUX_UNLOCK(mux);
    return ret;
}

static esp_err_t dw9714_delete(esp_cam_motor_device_t *dev)
{
    ESP_LOGD(TAG, "del dw9714 (%p)", dev);
    if (dev) {
        free(dev);
        dev = NULL;
    }

    return ESP_OK;
}

static const esp_cam_motor_ops_t dw9714_ops = {
    .query_para_desc = dw9714_query_para_desc,
    .get_para_value = dw9714_get_para_value,
    .set_para_value = dw9714_set_para_value,
    .query_support_formats = dw9714_query_support_formats,
    .set_format = dw9714_set_format,
    .get_format = dw9714_get_format,
    .priv_ioctl = dw9714_priv_ioctl,
    .del = dw9714_delete
};

esp_cam_motor_device_t *dw9714_detect(esp_cam_motor_config_t *config)
{
    esp_cam_motor_device_t *dev = NULL;
    if (config == NULL) {
        return NULL;
    }

    dev = calloc(1, sizeof(esp_cam_motor_device_t));
    if (dev == NULL) {
        ESP_LOGE(TAG, "No memory for motor");
        return NULL;
    }

    dev->name = (char *)TAG;
    dev->sccb_handle = config->sccb_handle;
    dev->reset_pin = config->reset_pin;
    dev->pwdn_pin = config->pwdn_pin;
    dev->signal_pin = -1;
    dev->ops = &dw9714_ops;
    dev->cur_format = &dw9714_format_info[CONFIG_DW9714_FORMAT_INDEX_DEFAULT];

    // Configure motor power
    if (dw9714_hw_power_on(dev, true) != ESP_OK) {
        ESP_LOGE(TAG, "Camera power on failed");
        goto err_free_handler;
    }

    /*
    * DW9714 always fails the first read and returns
    * zeroes for subsequent ones
    */
    if (dw9714_read_check(dev) != ESP_OK) {
        ESP_LOGE(TAG, "Read check failed");
        goto err_free_handler;
    }

    if (dw9714_set_format(dev, NULL) != ESP_OK) {
        ESP_LOGE(TAG, "Set motor default fmt failed");
        goto err_free_handler;
    }

#if DW9714_MOVING_TEST_EN
    TimerHandle_t wb_timer_handle = xTimerCreate("wb_t", 1000 / portTICK_PERIOD_MS, pdTRUE,
                                    (void *)dev, wb_timer_callback);
    if (pdTRUE != xTimerStart(wb_timer_handle, portMAX_DELAY)) {
        ESP_LOGE(TAG, "Timer start err");
    }
#endif

    ESP_LOGI(TAG, "Detected Cam motor");

    return dev;

err_free_handler:
    dw9714_hw_power_on(dev, false);
    free(dev);

    return NULL;
}

#if CONFIG_CAM_MOTOR_DW9714_AUTO_DETECT
ESP_CAM_MOTOR_DETECT_FN(dw9714_detect, NULL, DW9714_SCCB_ADDR)
{
    return dw9714_detect(config);
}
#endif
