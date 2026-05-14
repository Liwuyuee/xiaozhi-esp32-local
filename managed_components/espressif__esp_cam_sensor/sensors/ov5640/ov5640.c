/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#include "esp_cam_sensor.h"
#include "esp_cam_sensor_detect.h"
#include "ov5640_settings.h"
#include "ov5640.h"

#define OV5640_IO_MUX_LOCK(mux)
#define OV5640_IO_MUX_UNLOCK(mux)
#define OV5640_ENABLE_OUT_XCLK(pin,clk)
#define OV5640_DISABLE_OUT_XCLK(pin)

#define OV5640_PID         0x5640
#define OV5640_SENSOR_NAME "OV5640"
#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif
#define delay_ms(ms)  vTaskDelay((ms > portTICK_PERIOD_MS ? ms/ portTICK_PERIOD_MS : 1))
#define OV5640_SUPPORT_NUM CONFIG_CAMERA_OV5640_MAX_SUPPORT

static const char *TAG = "ov5640";

#if CONFIG_SOC_MIPI_CSI_SUPPORTED
static const esp_cam_sensor_format_t ov5640_format_info_mipi[] = {
    {
        .name = "MIPI_2lane_24Minput_RGB565_1280x720_14fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RGB565,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 1280,
        .height = 720,
        .regs = ov5640_MIPI_2lane_rgb565_720p_14fps,
        .regs_size = ARRAY_SIZE(ov5640_MIPI_2lane_rgb565_720p_14fps),
        .fps = 14,
        .isp_info = NULL,
        .mipi_info = {
            .mipi_clk = OV5640_LINE_RATE_16BITS_1280x720_14FPS,
            .lane_num = 2,
            .line_sync_en = CONFIG_CAMERA_OV5640_CSI_LINESYNC_ENABLE ? true : false,
        },
        .reserved = NULL,
    }
};
#endif

#if CONFIG_SOC_LCDCAM_CAM_SUPPORTED
static const esp_cam_sensor_format_t ov5640_format_info_dvp[] = {
    /* For DVP */
    {
        .name = "DVP_8bit_24Minput_YUV422_800x600_10fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_DVP,
        .xclk = 24000000,
        .width = 800,
        .height = 600,
        .regs = ov5640_dvp_yuv422_svga_10fps,
        .regs_size = ARRAY_SIZE(ov5640_dvp_yuv422_svga_10fps),
        .fps = 10,
        .isp_info = NULL,
        .mipi_info = {0},
        .reserved = NULL,
    },
    {
        .name = "DVP_8bit_24Minput_RGB565_800x600_10fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RGB565,
        .port = ESP_CAM_SENSOR_DVP,
        .xclk = 24000000,
        .width = 800,
        .height = 600,
        .regs = ov5640_dvp_yuv422_svga_10fps,
        .regs_size = ARRAY_SIZE(ov5640_dvp_yuv422_svga_10fps),
        .fps = 10,
        .isp_info = NULL,
        .mipi_info = {0},
        .reserved = NULL,
    }
};
#endif

static esp_err_t ov5640_read(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t *read_buf)
{
    return esp_sccb_transmit_receive_reg_a16v8(sccb_handle, reg, read_buf);
}

static esp_err_t ov5640_write(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t data)
{
    return esp_sccb_transmit_reg_a16v8(sccb_handle, reg, data);
}

/* write a array of registers  */
static esp_err_t ov5640_write_array(esp_sccb_io_handle_t sccb_handle, const ov5640_reginfo_t *regarray)
{
    int i = 0;
    esp_err_t ret = ESP_OK;
    while ((ret == ESP_OK) && regarray[i].reg != OV5640_REG_END) {
        if (regarray[i].reg != OV5640_REG_DELAY) {
            ret = ov5640_write(sccb_handle, regarray[i].reg, regarray[i].val);
        } else {
            delay_ms(regarray[i].val);
        }
        i++;
    }
    ESP_LOGD(TAG, "count=%d", i);
    return ret;
}

static esp_err_t ov5640_set_reg_bits(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t offset, uint8_t length, uint8_t value)
{
    esp_err_t ret = ESP_OK;
    uint8_t reg_data = 0;

    ret = ov5640_read(sccb_handle, reg, &reg_data);
    if (ret != ESP_OK) {
        return ret;
    }
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (reg_data & ~mask) | ((value << offset) & mask);
    ret = ov5640_write(sccb_handle, reg, value);
    return ret;
}

static esp_err_t ov5640_set_test_pattern(esp_cam_sensor_device_t *dev, int enable)
{
    return ov5640_set_reg_bits(dev->sccb_handle, 0x503d, 7, 1, enable ? 1 : 0);
}

static esp_err_t ov5640_hw_reset(esp_cam_sensor_device_t *dev)
{
    if (dev->reset_pin >= 0) {
        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
    }
    return ESP_OK;
}

static esp_err_t ov5640_soft_reset(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ov5640_set_reg_bits(dev->sccb_handle, OV5640_REG_SYS_CTRL0, 7, 1, 0x01);
    delay_ms(5);
    return ret;
}

static esp_err_t ov5640_get_sensor_id(esp_cam_sensor_device_t *dev, esp_cam_sensor_id_t *id)
{
    uint8_t pid_h, pid_l;
    esp_err_t ret = ov5640_read(dev->sccb_handle, OV5640_REG_SENSOR_ID_H, &pid_h);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ret, TAG, "read pid_h failed");

    ret = ov5640_read(dev->sccb_handle, OV5640_REG_SENSOR_ID_L, &pid_l);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ret, TAG, "read pid_l failed");

    uint16_t pid = (pid_h << 8) | pid_l;
    if (pid) {
        id->pid = pid;
    }
    return ret;
}

static esp_err_t ov5640_set_stream_dvp(esp_cam_sensor_device_t *dev, bool on)
{
    return ov5640_write(dev->sccb_handle, OV5640_REG_SYS_CTRL0, on ?
                        OV5640_SOFT_POWER_DOWN_DIS :
                        OV5640_SOFT_POWER_DOWN_EN);
}

static esp_err_t ov5640_set_stream_mipi(esp_cam_sensor_device_t *dev, bool on)
{
    esp_err_t ret;

    /*
     * Enable/disable the MIPI interface
     *
     * 0x300e = on ? 0x45 : 0x40
     *
     * FIXME: the sensor manual (version 2.03) reports
     * [7:5] = 000  : 1 data lane mode
     * [7:5] = 001  : 2 data lanes mode
     * But this settings do not work, while the following ones
     * have been validated for 2 data lanes mode.
     *
     * [7:5] = 010  : 2 data lanes mode
     * [4] = 0  : Power up MIPI HS Tx
     * [3] = 0  : Power up MIPI LS Rx
     * [2] = 1/0    : MIPI interface enable/disable
     * [1:0] = 01/00: FIXME: 'debug'
     * ret = ov5640_write(dev->sccb_handle, OV5640_REG_IO_MIPI_CTRL00,
     *             on ? 0x45 : 0x40);

     * ret |= ov5640_write(dev->sccb_handle, OV5640_REG_FRAME_CTRL01,
     *          on ? 0x00 : 0x0f);
     */

    ret = ov5640_write(dev->sccb_handle, OV5640_REG_SYS_CTRL0,
                       on ? OV5640_SOFT_POWER_DOWN_DIS : OV5640_SOFT_POWER_DOWN_EN);

    return ret;
}

static esp_err_t ov5640_set_stream(esp_cam_sensor_device_t *dev, int enable)
{
    esp_err_t ret = ESP_FAIL;
    if (dev->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
        ret = ov5640_set_stream_mipi(dev, enable);
    } else {
        ret = ov5640_set_stream_dvp(dev, enable);
    }

    if (ret == ESP_OK) {
        dev->stream_status = (uint8_t)enable;
    }

    ESP_LOGD(TAG, "Stream=%d", enable);
    return ret;
}

static esp_err_t ov5640_set_hmirror(esp_cam_sensor_device_t *dev, int enable)
{
    return ov5640_set_reg_bits(dev->sccb_handle, 0x3821, 2, 1, enable ? 1 : 0);
}

static esp_err_t ov5640_set_vflip(esp_cam_sensor_device_t *dev, int enable)
{
    return ov5640_set_reg_bits(dev->sccb_handle, 0x3820, 2, 1, enable ? 1 : 0);
}

static esp_err_t ov5640_query_para_desc(esp_cam_sensor_device_t *dev, esp_cam_sensor_param_desc_t *qdesc)
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
    default: {
        ESP_LOGD(TAG, "id=%"PRIx32" is not supported", qdesc->id);
        ret = ESP_ERR_INVALID_ARG;
        break;
    }
    }
    return ret;
}

static esp_err_t ov5640_get_para_value(esp_cam_sensor_device_t *dev, uint32_t id, void *arg, size_t size)
{
    return ESP_ERR_NOT_SUPPORTED;
}

static esp_err_t ov5640_set_para_value(esp_cam_sensor_device_t *dev, uint32_t id, const void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;

    switch (id) {
    case ESP_CAM_SENSOR_VFLIP: {
        int *value = (int *)arg;
        ret = ov5640_set_vflip(dev, *value);
        break;
    }
    case ESP_CAM_SENSOR_HMIRROR: {
        int *value = (int *)arg;
        ret = ov5640_set_hmirror(dev, *value);
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

static esp_err_t ov5640_query_support_formats(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_array_t *formats)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, formats);
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
    if (dev->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
        formats->count = ARRAY_SIZE(ov5640_format_info_mipi);
        formats->format_array = &ov5640_format_info_mipi[0];
    }
#endif

#if CONFIG_SOC_LCDCAM_CAM_SUPPORTED
    if (dev->sensor_port == ESP_CAM_SENSOR_DVP) {
        formats->count = ARRAY_SIZE(ov5640_format_info_dvp);
        formats->format_array = &ov5640_format_info_dvp[0];
    }
#endif
    return ESP_OK;
}

static esp_err_t ov5640_query_support_capability(esp_cam_sensor_device_t *dev, esp_cam_sensor_capability_t *sensor_cap)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, sensor_cap);

    sensor_cap->fmt_yuv = 1;
    return ESP_OK;
}

static esp_err_t ov5640_set_format(esp_cam_sensor_device_t *dev, const esp_cam_sensor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);

    esp_err_t ret = ESP_OK;
    ov5640_reginfo_t *reset_regs_list = NULL;
    /* Depending on the interface type, an available configuration is automatically loaded.
    You can set the output format of the sensor without using query_format().*/
    if (format == NULL) {
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
        if (dev->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
            reset_regs_list = (ov5640_reginfo_t *)ov5640_mipi_reset_regs;
            format = &ov5640_format_info_mipi[CONFIG_CAMERA_OV5640_MIPI_IF_FORMAT_INDEX_DEFAULT];
        }
#endif
#if CONFIG_SOC_LCDCAM_CAM_SUPPORTED
        if (dev->sensor_port == ESP_CAM_SENSOR_DVP) {
            reset_regs_list = (ov5640_reginfo_t *)ov5640_dvp_reset_regs;
            format = &ov5640_format_info_dvp[CONFIG_CAMERA_OV5640_DVP_IF_FORMAT_INDEX_DEFAULT];
        }
#endif
    }

    ret = ov5640_write_array(dev->sccb_handle, reset_regs_list);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ret, TAG, "write reset regs failed");

    ret = ov5640_write_array(dev->sccb_handle, (const ov5640_reginfo_t *)format->regs);
    ESP_RETURN_ON_FALSE(ret == ESP_OK, ESP_CAM_SENSOR_ERR_FAILED_SET_FORMAT, TAG, "write format regs failed");

    dev->cur_format = format;

    return ret;
}

static esp_err_t ov5640_get_format(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_t *format)
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

static esp_err_t ov5640_priv_ioctl(esp_cam_sensor_device_t *dev, uint32_t cmd, void *arg)
{
    esp_err_t ret = ESP_OK;
    uint8_t regval;
    esp_cam_sensor_reg_val_t *sensor_reg;
    OV5640_IO_MUX_LOCK(mux);

    switch (cmd) {
    case ESP_CAM_SENSOR_IOC_HW_RESET:
        ret = ov5640_hw_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_SW_RESET:
        ret = ov5640_soft_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_S_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = ov5640_write(dev->sccb_handle, sensor_reg->regaddr, sensor_reg->value);
        break;
    case ESP_CAM_SENSOR_IOC_S_STREAM:
        ret = ov5640_set_stream(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_S_TEST_PATTERN:
        ret = ov5640_set_test_pattern(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_G_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = ov5640_read(dev->sccb_handle, sensor_reg->regaddr, &regval);
        if (ret == ESP_OK) {
            sensor_reg->value = regval;
        }
        break;
    case ESP_CAM_SENSOR_IOC_G_CHIP_ID:
        ret = ov5640_get_sensor_id(dev, arg);
        break;
    default:
        ESP_LOGE(TAG, "cmd=%" PRIx32 " is not supported", cmd);
        ret = ESP_ERR_INVALID_ARG;
        break;
    }

    OV5640_IO_MUX_UNLOCK(mux);
    return ret;
}

static esp_err_t ov5640_power_on(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        OV5640_ENABLE_OUT_XCLK(dev->xclk_pin, dev->xclk_freq_hz);
    }

    if (dev->pwdn_pin >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << dev->pwdn_pin;
        conf.mode = GPIO_MODE_OUTPUT;
        ret = gpio_config(&conf);

        // carefully, logic is inverted compared to reset pin
        gpio_set_level(dev->pwdn_pin, 1);
        delay_ms(10);
        gpio_set_level(dev->pwdn_pin, 0);
        delay_ms(10);
    }

    if (dev->reset_pin >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << dev->reset_pin;
        conf.mode = GPIO_MODE_OUTPUT;
        ret = gpio_config(&conf);

        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
    }

    return ret;
}

static esp_err_t ov5640_power_off(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        OV5640_DISABLE_OUT_XCLK(dev->xclk_pin);
    }

    if (dev->pwdn_pin >= 0) {
        gpio_set_level(dev->pwdn_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->pwdn_pin, 1);
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

static esp_err_t ov5640_delete(esp_cam_sensor_device_t *dev)
{
    ESP_LOGD(TAG, "del ov5640 (%p)", dev);
    if (dev) {
        free(dev);
        dev = NULL;
    }

    return ESP_OK;
}

static const esp_cam_sensor_ops_t ov5640_ops = {
    .query_para_desc = ov5640_query_para_desc,
    .get_para_value = ov5640_get_para_value,
    .set_para_value = ov5640_set_para_value,
    .query_support_formats = ov5640_query_support_formats,
    .query_support_capability = ov5640_query_support_capability,
    .set_format = ov5640_set_format,
    .get_format = ov5640_get_format,
    .priv_ioctl = ov5640_priv_ioctl,
    .del = ov5640_delete
};

esp_cam_sensor_device_t *ov5640_detect(esp_cam_sensor_config_t *config)
{
    esp_cam_sensor_device_t *dev = NULL;

    if (config == NULL) {
        return NULL;
    }

    dev = calloc(1, sizeof(esp_cam_sensor_device_t));
    if (dev == NULL) {
        ESP_LOGE(TAG, "No memory for camera");
        return NULL;
    }

    dev->name = (char *)OV5640_SENSOR_NAME;
    dev->ops = &ov5640_ops;
    dev->sccb_handle = config->sccb_handle;
    dev->xclk_pin = config->xclk_pin;
    dev->reset_pin = config->reset_pin;
    dev->pwdn_pin = config->pwdn_pin;
    dev->sensor_port = config->sensor_port;

#if CONFIG_SOC_MIPI_CSI_SUPPORTED
    if (config->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
        dev->cur_format = &ov5640_format_info_mipi[CONFIG_CAMERA_OV5640_MIPI_IF_FORMAT_INDEX_DEFAULT];
    }
#endif

#if CONFIG_SOC_LCDCAM_CAM_SUPPORTED
    if (config->sensor_port == ESP_CAM_SENSOR_DVP) {
        dev->cur_format = &ov5640_format_info_dvp[CONFIG_CAMERA_OV5640_DVP_IF_FORMAT_INDEX_DEFAULT];
    }
#endif

    // Configure sensor power, clock, and SCCB port
    if (ov5640_power_on(dev) != ESP_OK) {
        ESP_LOGE(TAG, "Camera power on failed");
        goto err_free_handler;
    }

    if (ov5640_get_sensor_id(dev, &dev->id) != ESP_OK) {
        ESP_LOGE(TAG, "Camera get sensor ID failed");
        goto err_free_handler;
    } else if (dev->id.pid != OV5640_PID) {
        ESP_LOGE(TAG, "Camera sensor is not OV5640, PID=0x%x", dev->id.pid);
        goto err_free_handler;
    }
    ESP_LOGI(TAG, "Detected Camera sensor PID=0x%x", dev->id.pid);

    return dev;

err_free_handler:
    ov5640_power_off(dev);
    free(dev);

    return NULL;
}

#if CONFIG_CAMERA_OV5640_AUTO_DETECT_MIPI_INTERFACE_SENSOR
ESP_CAM_SENSOR_DETECT_FN(ov5640_detect, ESP_CAM_SENSOR_MIPI_CSI, OV5640_SCCB_ADDR)
{
    ((esp_cam_sensor_config_t *)config)->sensor_port = ESP_CAM_SENSOR_MIPI_CSI;
    return ov5640_detect(config);
}
#endif

#if CONFIG_CAMERA_OV5640_AUTO_DETECT_DVP_INTERFACE_SENSOR
ESP_CAM_SENSOR_DETECT_FN(ov5640_detect, ESP_CAM_SENSOR_DVP, OV5640_SCCB_ADDR)
{
    ((esp_cam_sensor_config_t *)config)->sensor_port = ESP_CAM_SENSOR_DVP;
    return ov5640_detect(config);
}
#endif
