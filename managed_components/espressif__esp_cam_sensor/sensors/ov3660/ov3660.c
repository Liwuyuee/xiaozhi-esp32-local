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

#include "esp_cam_sensor.h"
#include "esp_cam_sensor_detect.h"
#include "ov3660.h"
#include "ov3660_settings.h"

typedef struct {
    uint32_t ae_target_level;
    uint32_t vflip_en : 1;
    uint32_t hmirror_en : 1;
    uint32_t binning_en : 1;
} ov3660_para_t;

struct ov3660_cam {
    ov3660_para_t ov3660_para;
};

#define OV3660_IO_MUX_LOCK(mux)
#define OV3660_IO_MUX_UNLOCK(mux)
#define OV3660_ENABLE_OUT_XCLK(pin,clk)
#define OV3660_DISABLE_OUT_XCLK(pin)

#define OV3660_PID         0x3660
#define OV3660_SENSOR_NAME "OV3660"
#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif
#define delay_ms(ms)  vTaskDelay((ms > portTICK_PERIOD_MS ? ms/ portTICK_PERIOD_MS : 1))
#define OV3660_SUPPORT_NUM CONFIG_CAMERA_OV3660_MAX_SUPPORT
#define OV3660_AE_LEVEL_DEFAULT (0x0)
#define OV3660_XCLK_DEFAULT       (20*1000*1000)

static const char *TAG = "ov3660";

static const esp_cam_sensor_format_t ov3660_format_info[] = {
    {
        .name = "DVP_8bit_20Minput_RGB565_240x240_24fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RGB565,
        .port = ESP_CAM_SENSOR_DVP,
        .xclk = 20000000,
        .width = 240,
        .height = 240,
        .regs = DVP_8bit_RGB565_240x240_XCLK_20_24fps,
        .regs_size = ARRAY_SIZE(DVP_8bit_RGB565_240x240_XCLK_20_24fps),
        .fps = 24,
        .isp_info = NULL,
        .mipi_info = {},
        .reserved = NULL,
    },
    {
        .name = "DVP_8bit_20Minput_YUV422_240x240_24fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_DVP,
        .xclk = 20000000,
        .width = 240,
        .height = 240,
        .regs = DVP_8bit_YUV422_240x240_XCLK_20_24fps,
        .regs_size = ARRAY_SIZE(DVP_8bit_YUV422_240x240_XCLK_20_24fps),
        .fps = 24,
        .isp_info = NULL,
        .mipi_info = {},
        .reserved = NULL,
    },
    {
        .name = "DVP_8bit_20Minput_RGB565_640x480_10fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RGB565,
        .port = ESP_CAM_SENSOR_DVP,
        .xclk = 20000000,
        .width = 640,
        .height = 480,
        .regs = DVP_8bit_RGB565_640x480_XCLK_20_10fps,
        .regs_size = ARRAY_SIZE(DVP_8bit_RGB565_640x480_XCLK_20_10fps),
        .fps = 10,
        .isp_info = NULL,
        .mipi_info = {},
        .reserved = NULL,
    },
    {
        .name = "DVP_8bit_20Minput_YUV422_640x480_10fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_DVP,
        .xclk = 20000000,
        .width = 640,
        .height = 480,
        .regs = DVP_8bit_YUV422_640x480_XCLK_20_10fps,
        .regs_size = ARRAY_SIZE(DVP_8bit_YUV422_640x480_XCLK_20_10fps),
        .fps = 10,
        .isp_info = NULL,
        .mipi_info = {},
        .reserved = NULL,
    },
    {
        .name = "DVP_8bit_20Minput_JPEG_1280x720_12fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_JPEG,
        .port = ESP_CAM_SENSOR_DVP,
        .xclk = 20000000,
        .width = 1280,
        .height = 720,
        .regs = DVP_8bit_JPEG_1280x720_XCLK_10_12fps,
        .regs_size = ARRAY_SIZE(DVP_8bit_JPEG_1280x720_XCLK_10_12fps),
        .fps = 12,
        .isp_info = NULL,
        .mipi_info = {},
        .reserved = NULL,
    }
};

static esp_err_t ov3660_read(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t *read_buf)
{
    return esp_sccb_transmit_receive_reg_a16v8(sccb_handle, reg, read_buf);
}

static esp_err_t ov3660_write(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t data)
{
    return esp_sccb_transmit_reg_a16v8(sccb_handle, reg, data);
}

static esp_err_t ov3660_write_reg16(esp_sccb_io_handle_t sccb_handle, const uint16_t reg, uint16_t value)
{
    esp_err_t ret = ov3660_write(sccb_handle, reg, value >> 8);
    ret |= ov3660_write(sccb_handle, reg + 1, value & 0xff);

    return ret;
}

/* write a array of registers  */
static esp_err_t ov3660_write_array(esp_sccb_io_handle_t sccb_handle, const ov3660_reginfo_t *regarray)
{
    int i = 0;
    esp_err_t ret = ESP_OK;
    while ((ret == ESP_OK) && regarray[i].reg != OV3660_REGLIST_TAIL) {
        if (regarray[i].reg != OV3660_REG_DLY) {
            ret = ov3660_write(sccb_handle, regarray[i].reg, regarray[i].val);
        } else {
            delay_ms(regarray[i].val);
        }
        i++;
    }
    ESP_LOGD(TAG, "Set array done[i=%d]", i);
    return ret;
}

static esp_err_t ov3660_set_reg_bits(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t offset, uint8_t length, uint8_t value)
{
    esp_err_t ret = ESP_OK;
    uint8_t reg_data = 0;

    ret = ov3660_read(sccb_handle, reg, &reg_data);
    if (ret != ESP_OK) {
        return ret;
    }
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (reg_data & ~mask) | ((value << offset) & mask);
    ret = ov3660_write(sccb_handle, reg, value);
    return ret;
}

static esp_err_t ov3660_set_test_pattern(esp_cam_sensor_device_t *dev, int enable)
{
    return ov3660_set_reg_bits(dev->sccb_handle, 0x503d, 7, 1, enable ? 0x01 : 0x00);
}

static esp_err_t ov3660_set_jpeg_quality(esp_cam_sensor_device_t *dev, int qs)
{
    return ov3660_write(dev->sccb_handle, COMPRESSION_CTRL07, qs & 0x3f);
}

static esp_err_t ov3660_set_saturation(esp_cam_sensor_device_t *dev, int level)
{
    esp_err_t ret = ESP_OK;
    if (level > 2 || level < -2) {
        return ESP_ERR_INVALID_ARG;
    }

    const uint8_t *regs = (uint8_t *)sensor_saturation_levels[level + 4];
    for (int i = 0; i < 11; i++) {
        ret = ov3660_write(dev->sccb_handle, 0x5381 + i, regs[i]);
        if (ret != ESP_OK) {
            break;
        }
    }

    return ret;
}

static esp_err_t ov3660_set_contrast(esp_cam_sensor_device_t *dev, int level)
{
    esp_err_t ret = ESP_OK;
    if (level > 2 || level < -2) {
        return ESP_ERR_INVALID_ARG;
    }
    ret = ov3660_write(dev->sccb_handle, 0x5586, (level + 4) << 3);

    return ret;
}

static esp_err_t ov3660_set_special_effect(esp_cam_sensor_device_t *dev, int effect)
{
    esp_err_t ret = ESP_OK;
    if (effect < 0 || effect > 6) {
        return ESP_ERR_INVALID_ARG;
    }

    const uint8_t *regs = (uint8_t *)sensor_special_effects[effect];
    ret =  ov3660_write(dev->sccb_handle, 0x5580, regs[0])
           || ov3660_write(dev->sccb_handle, 0x5583, regs[1])
           || ov3660_write(dev->sccb_handle, 0x5584, regs[2])
           || ov3660_write(dev->sccb_handle, 0x5003, regs[3]);

    return ret;
}

static esp_err_t ov3660_set_wb_mode(esp_cam_sensor_device_t *dev, int mode)
{
    esp_err_t ret = ESP_OK;
    if (mode < 0 || mode > 4) {
        return ESP_ERR_INVALID_ARG;
    }

    ret = ov3660_write(dev->sccb_handle, 0x3406, (mode != 0)); // mode 0: auto
    if (ret != ESP_OK) {
        return ret;
    }

    switch (mode) {
    case 1://Sunny
        ret  = ov3660_write_reg16(dev->sccb_handle, 0x3400, 0x5e0) //AWB R GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3402, 0x410) //AWB G GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3404, 0x540);//AWB B GAIN
        break;
    case 2://Cloudy
        ret  = ov3660_write_reg16(dev->sccb_handle, 0x3400, 0x650) //AWB R GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3402, 0x410) //AWB G GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3404, 0x4f0);//AWB B GAIN
        break;
    case 3://Office
        ret  = ov3660_write_reg16(dev->sccb_handle, 0x3400, 0x520) //AWB R GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3402, 0x410) //AWB G GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3404, 0x660);//AWB B GAIN
        break;
    case 4://HOME
        ret  = ov3660_write_reg16(dev->sccb_handle, 0x3400, 0x420) //AWB R GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3402, 0x3f0) //AWB G GAIN
               || ov3660_write_reg16(dev->sccb_handle, 0x3404, 0x710);//AWB B GAIN
        break;
    default://AUTO
        break;
    }

    return ret;
}

static esp_err_t ov3660_set_ae_level(esp_cam_sensor_device_t *dev, int level)
{
    esp_err_t ret = ESP_OK;
    struct ov3660_cam *cam_ov3660 = (struct ov3660_cam *)dev->priv;
    if (level < -5 || level > 5) {
        return ESP_ERR_INVALID_ARG;
    }
    //good targets are between 5 and 115
    int target_level = ((level + 5) * 10) + 5;

    int level_high, level_low;
    int fast_high, fast_low;

    level_low = target_level * 23 / 25; //0.92 (0.46)
    level_high = target_level * 27 / 25; //1.08 (2.08)

    fast_low = level_low >> 1;
    fast_high = level_high << 1;

    if (fast_high > 255) {
        fast_high = 255;
    }

    ret =  ov3660_write(dev->sccb_handle, 0x3a0f, level_high)
           || ov3660_write(dev->sccb_handle, 0x3a10, level_low)
           || ov3660_write(dev->sccb_handle, 0x3a1b, level_high)
           || ov3660_write(dev->sccb_handle, 0x3a1e, level_low)
           || ov3660_write(dev->sccb_handle, 0x3a11, fast_high)
           || ov3660_write(dev->sccb_handle, 0x3a1f, fast_low);

    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "Set ae_level to: %d", level);
        cam_ov3660->ov3660_para.ae_target_level = level;
    }
    return ret;
}

static esp_err_t ov3660_hw_reset(esp_cam_sensor_device_t *dev)
{
    return ESP_OK;
}

static esp_err_t ov3660_soft_reset(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ov3660_write(dev->sccb_handle, SYSTEM_CTROL0, 0x82);
    delay_ms(20);
    return ret;
}

static esp_err_t ov3660_get_sensor_id(esp_cam_sensor_device_t *dev, esp_cam_sensor_id_t *id)
{
    esp_err_t ret = ESP_FAIL;
    uint8_t pid_h, pid_l;

    ret = ov3660_read(dev->sccb_handle, 0x300A, &pid_h);
    if (ret != ESP_OK) {
        return ret;
    }
    ret = ov3660_read(dev->sccb_handle, 0x300B, &pid_l);
    if (ret != ESP_OK) {
        return ret;
    }
    id->pid = (pid_h << 8) | pid_l;

    return ret;
}

static esp_err_t ov3660_set_stream(esp_cam_sensor_device_t *dev, int enable)
{
    /* OV3660 has no software standby or sleep mode */
    dev->stream_status = enable;
    ESP_LOGD(TAG, "Stream=%d", enable);
    return ESP_OK;
}

static esp_err_t ov3660_set_mirror(esp_cam_sensor_device_t *dev, int enable)
{
    return ov3660_set_reg_bits(dev->sccb_handle, 0x3821, 1, 2, enable ? 0x03 : 0x00);
}

static esp_err_t ov3660_set_vflip(esp_cam_sensor_device_t *dev, int enable)
{
    return ov3660_set_reg_bits(dev->sccb_handle, 0x3820, 1, 2, enable ? 0x03 : 0x00);
}

static esp_err_t ov3660_query_para_desc(esp_cam_sensor_device_t *dev, esp_cam_sensor_param_desc_t *qdesc)
{
    esp_err_t ret = ESP_OK;
    switch (qdesc->id) {
    case ESP_CAM_SENSOR_VFLIP:
    case ESP_CAM_SENSOR_HMIRROR:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = 0;
        qdesc->number.maximum = 1;
        qdesc->number.step = 1;
        qdesc->default_value = 0;
        break;
    case ESP_CAM_SENSOR_AE_LEVEL:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = -5;
        qdesc->number.maximum = 5;
        qdesc->number.step = 1;
        qdesc->default_value = OV3660_AE_LEVEL_DEFAULT;
        break;
    case ESP_CAM_SENSOR_JPEG_QUALITY:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = 1;
        qdesc->number.maximum = 63;
        qdesc->number.step = 1;
        qdesc->default_value = 0x11;
        break;
    case ESP_CAM_SENSOR_CONTRAST:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = -2;
        qdesc->number.maximum = 2;
        qdesc->number.step = 1;
        qdesc->default_value = 0;
        break;
    case ESP_CAM_SENSOR_SATURATION:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = -2;
        qdesc->number.maximum = 2;
        qdesc->number.step = 1;
        qdesc->default_value = 0;
        break;
    case ESP_CAM_SENSOR_SPECIAL_EFFECT:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = 0;
        qdesc->number.maximum = 6;
        qdesc->number.step = 1;
        qdesc->default_value = 0;
        break;
    case ESP_CAM_SENSOR_WB:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = 0;
        qdesc->number.maximum = 4;
        qdesc->number.step = 1;
        qdesc->default_value = 0;
        break;
    default: {
        ESP_LOGD(TAG, "id=%"PRIx32" is not supported", qdesc->id);
        ret = ESP_ERR_INVALID_ARG;
        break;
    }
    }
    return ret;
}

static esp_err_t ov3660_get_para_value(esp_cam_sensor_device_t *dev, uint32_t id, void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;
    struct ov3660_cam *cam_ov3660 = (struct ov3660_cam *)dev->priv;

    switch (id) {
    case ESP_CAM_SENSOR_AE_LEVEL: {
        ESP_RETURN_ON_FALSE(size == 4, ESP_ERR_INVALID_ARG, TAG, "Para size err");
        *(uint32_t *)arg = cam_ov3660->ov3660_para.ae_target_level;
    }
    break;
    default: {
        ret = ESP_ERR_NOT_SUPPORTED;
        break;
    }
    }
    return ret;
}

static esp_err_t ov3660_set_para_value(esp_cam_sensor_device_t *dev, uint32_t id, const void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;
    int value = *(int *)arg;
    // The parameter types of this sensor are all 4 bytes.
    ESP_RETURN_ON_FALSE(size == 4, ESP_ERR_INVALID_ARG, TAG, "Para size err");

    switch (id) {
    case ESP_CAM_SENSOR_VFLIP: {
        ret = ov3660_set_vflip(dev, value);
        break;
    }
    case ESP_CAM_SENSOR_HMIRROR: {
        ret = ov3660_set_mirror(dev, value);
        break;
    }
    case ESP_CAM_SENSOR_JPEG_QUALITY: {
        if (dev->cur_format->format == ESP_CAM_SENSOR_PIXFORMAT_JPEG) {
            ret = ov3660_set_jpeg_quality(dev, value);
        } else {
            ret = ESP_ERR_INVALID_STATE;
        }
        break;
    }
    case ESP_CAM_SENSOR_AE_LEVEL: {
        ret = ov3660_set_ae_level(dev, value);
        break;
    }
    case ESP_CAM_SENSOR_CONTRAST: {
        ret = ov3660_set_contrast(dev, value);
        break;
    }
    case ESP_CAM_SENSOR_SATURATION: {
        ret = ov3660_set_saturation(dev, value);
        break;
    }
    case ESP_CAM_SENSOR_SPECIAL_EFFECT: {
        ret = ov3660_set_special_effect(dev, value);
        break;
    }
    case ESP_CAM_SENSOR_WB: {
        ret = ov3660_set_wb_mode(dev, value);
        break;
    }
    default: {
        ESP_LOGE(TAG, "set id=%"PRIx32" is not supported", id);
        ret = ESP_ERR_INVALID_ARG;
        break;
    }
    }

    return ret;
}

static esp_err_t ov3660_query_support_formats(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_array_t *formats)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, formats);

    formats->count = ARRAY_SIZE(ov3660_format_info);
    formats->format_array = &ov3660_format_info[0];
    return ESP_OK;
}

static esp_err_t ov3660_query_support_capability(esp_cam_sensor_device_t *dev, esp_cam_sensor_capability_t *sensor_cap)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, sensor_cap);

    sensor_cap->fmt_raw = 1;
    return 0;
}

static esp_err_t ov3660_set_format(esp_cam_sensor_device_t *dev, const esp_cam_sensor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    esp_err_t ret = ESP_OK;
    /* Depending on the interface type, an available configuration is automatically loaded.
    You can set the output format of the sensor without using query_format().*/
    if (format == NULL) {
        format = &ov3660_format_info[CONFIG_CAMERA_OV3660_DVP_IF_FORMAT_INDEX_DEFAULT];
    }

    ret = ov3660_write_array(dev->sccb_handle, ov3660_sensor_default_regs);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ret, TAG, "Set common regs failed");
    ret = ov3660_set_ae_level(dev, OV3660_AE_LEVEL_DEFAULT);
    delay_ms(10);

    ret = ov3660_write_array(dev->sccb_handle, (ov3660_reginfo_t *)format->regs);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ret, TAG, "Set format regs failed");
    delay_ms(10);

    ESP_LOGD(TAG, "Set fmt done %s", format->name);

    dev->cur_format = format;

    return ret;
}

static esp_err_t ov3660_get_format(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, format);

    esp_err_t ret = ESP_FAIL;

    if (dev->cur_format != NULL) {
        memcpy(format, dev->cur_format, sizeof(esp_cam_sensor_format_t));
        ret = ESP_OK;
    }
    return ret;
}

static esp_err_t ov3660_priv_ioctl(esp_cam_sensor_device_t *dev, uint32_t cmd, void *arg)
{
    esp_err_t ret = ESP_OK;
    uint8_t regval;
    esp_cam_sensor_reg_val_t *sensor_reg;
    OV3660_IO_MUX_LOCK(mux);

    switch (cmd) {
    case ESP_CAM_SENSOR_IOC_HW_RESET:
        ret = ov3660_hw_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_SW_RESET:
        ret = ov3660_soft_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_S_REG:
        ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, arg);
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = ov3660_write(dev->sccb_handle, sensor_reg->regaddr, sensor_reg->value);
        break;
    case ESP_CAM_SENSOR_IOC_S_STREAM:
        ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, arg);
        ret = ov3660_set_stream(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_S_TEST_PATTERN:
        ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, arg);
        ret = ov3660_set_test_pattern(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_G_REG:
        ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, arg);
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = ov3660_read(dev->sccb_handle, sensor_reg->regaddr, &regval);
        if (ret == ESP_OK) {
            sensor_reg->value = regval;
        }
        break;
    case ESP_CAM_SENSOR_IOC_G_CHIP_ID:
        ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, arg);
        ret = ov3660_get_sensor_id(dev, arg);
        break;
    default:
        break;
    }

    OV3660_IO_MUX_UNLOCK(mux);
    return ret;
}

static esp_err_t ov3660_power_on(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        OV3660_ENABLE_OUT_XCLK(dev->xclk_pin, dev->xclk_freq_hz);
    }

    if (dev->pwdn_pin >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << dev->pwdn_pin;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);

        // carefully, logic is inverted compared to reset pin
        gpio_set_level(dev->pwdn_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->pwdn_pin, 1);
        delay_ms(10);
    }

    if (dev->reset_pin >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << dev->reset_pin;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);

        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
    }

    return ret;
}

static esp_err_t ov3660_power_off(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        OV3660_DISABLE_OUT_XCLK(dev->xclk_pin);
    }

    if (dev->pwdn_pin >= 0) {
        gpio_set_level(dev->pwdn_pin, 1);
        delay_ms(10);
        gpio_set_level(dev->pwdn_pin, 0);
        delay_ms(10);
    }

    if (dev->reset_pin >= 0) {
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
    }

    return ret;
}

static esp_err_t ov3660_delete(esp_cam_sensor_device_t *dev)
{
    ESP_LOGD(TAG, "del ov3660 (%p)", dev);
    if (dev) {
        if (dev->priv) {
            free(dev->priv);
            dev->priv = NULL;
        }
        free(dev);
        dev = NULL;
    }

    return ESP_OK;
}

static const esp_cam_sensor_ops_t ov3660_ops = {
    .query_para_desc = ov3660_query_para_desc,
    .get_para_value = ov3660_get_para_value,
    .set_para_value = ov3660_set_para_value,
    .query_support_formats = ov3660_query_support_formats,
    .query_support_capability = ov3660_query_support_capability,
    .set_format = ov3660_set_format,
    .get_format = ov3660_get_format,
    .priv_ioctl = ov3660_priv_ioctl,
    .del = ov3660_delete
};

esp_cam_sensor_device_t *ov3660_detect(esp_cam_sensor_config_t *config)
{
    esp_cam_sensor_device_t *dev = NULL;
    struct ov3660_cam *cam_ov3660;

    if (config == NULL) {
        return NULL;
    }

    dev = calloc(1, sizeof(esp_cam_sensor_device_t));
    if (dev == NULL) {
        ESP_LOGE(TAG, "No memory for camera");
        return NULL;
    }

    cam_ov3660 = heap_caps_calloc(1, sizeof(struct ov3660_cam), MALLOC_CAP_DEFAULT);
    if (!cam_ov3660) {
        ESP_LOGE(TAG, "failed to calloc cam");
        free(dev);
        return NULL;
    }
    memset(cam_ov3660, 0x0, sizeof(struct ov3660_cam));

    dev->name = (char *)OV3660_SENSOR_NAME;
    dev->sccb_handle = config->sccb_handle;
    dev->xclk_pin = config->xclk_pin;
    dev->reset_pin = config->reset_pin;
    dev->pwdn_pin = config->pwdn_pin;
    dev->sensor_port = config->sensor_port;
    dev->ops = &ov3660_ops;
    dev->priv = cam_ov3660;

    dev->cur_format = &ov3660_format_info[CONFIG_CAMERA_OV3660_DVP_IF_FORMAT_INDEX_DEFAULT];

    // Configure sensor power, clock, and SCCB port
    if (ov3660_power_on(dev) != ESP_OK) {
        ESP_LOGE(TAG, "Camera power on failed");
        goto err_free_handler;
    }

    if (ov3660_get_sensor_id(dev, &dev->id) != ESP_OK) {
        ESP_LOGE(TAG, "Get sensor ID failed");
        goto err_free_handler;
    } else if (dev->id.pid != OV3660_PID) {
        ESP_LOGW(TAG, "Camera sensor is not OV3660, PID=0x%x", dev->id.pid);
        goto err_free_handler;
    }
    ESP_LOGI(TAG, "Detected Camera sensor PID=0x%x", dev->id.pid);

    return dev;

err_free_handler:
    ov3660_power_off(dev);
    free(dev->priv);
    free(dev);

    return NULL;
}

#if CONFIG_CAMERA_OV3660_AUTO_DETECT_DVP_INTERFACE_SENSOR
ESP_CAM_SENSOR_DETECT_FN(ov3660_detect, ESP_CAM_SENSOR_DVP, OV3660_SCCB_ADDR)
{
    ((esp_cam_sensor_config_t *)config)->sensor_port = ESP_CAM_SENSOR_DVP;
    return ov3660_detect(config);
}
#endif
