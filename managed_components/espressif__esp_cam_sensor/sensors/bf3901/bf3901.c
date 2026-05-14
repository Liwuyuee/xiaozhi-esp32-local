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
#include "bf3901_settings.h"
#include "bf3901.h"

#define BF3901_IO_MUX_LOCK(mux)
#define BF3901_IO_MUX_UNLOCK(mux)
#define BF3901_ENABLE_OUT_XCLK(pin,clk)
#define BF3901_DISABLE_OUT_XCLK(pin)

#define BF3901_FRAME_HEADER_SIZE 4
#define BF3901_LINE_HEADER_SIZE 6
#define BF3901_PID 0x3901
#define BF3901_SENSOR_NAME "BF3901"

#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif
#define delay_ms(ms) vTaskDelay((ms > portTICK_PERIOD_MS ? ms/ portTICK_PERIOD_MS : 1))
#define BF3901_SUPPORT_NUM CONFIG_CAMERA_BF3901_MAX_SUPPORT

static const char *TAG = "bf3901";

static const esp_cam_sensor_spi_frame_info bf3901_frame_info_spi[] = {
    {
        .frame_size = (240 * 2 + BF3901_LINE_HEADER_SIZE) * 320 + BF3901_FRAME_HEADER_SIZE,
        .line_size = (240 * 2 + BF3901_LINE_HEADER_SIZE),
        .frame_header_check = (uint8_t[]){0xff, 0xff, 0xff, 0x00},
        .line_header_check = (uint8_t[]){0xff, 0xff, 0xff, 0x40},
        .frame_header_size = BF3901_FRAME_HEADER_SIZE,
        .line_header_size = BF3901_LINE_HEADER_SIZE,
        .frame_header_check_size = 4,
        .line_header_check_size = 4,
        .drop_frame_count = 1, // The 1st SPI packet is not the image data, so we need to drop it
    },
    {
        .frame_size = (240 * 2 + BF3901_LINE_HEADER_SIZE) * 240 + BF3901_FRAME_HEADER_SIZE,
        .line_size = (240 * 2 + BF3901_LINE_HEADER_SIZE),
        .frame_header_check = (uint8_t[]){0xff, 0xff, 0xff, 0x00},
        .line_header_check = (uint8_t[]){0xff, 0xff, 0xff, 0x40},
        .frame_header_size = BF3901_FRAME_HEADER_SIZE,
        .line_header_size = BF3901_LINE_HEADER_SIZE,
        .frame_header_check_size = 4,
        .line_header_check_size = 4,
        .drop_frame_count = 1,
    },
    {
        .frame_size = (120 * 2 + BF3901_LINE_HEADER_SIZE) * 160 + BF3901_FRAME_HEADER_SIZE,
        .line_size = (120 * 2 + BF3901_LINE_HEADER_SIZE),
        .frame_header_check = (uint8_t[]){0xff, 0xff, 0xff, 0x00},
        .line_header_check = (uint8_t[]){0xff, 0xff, 0xff, 0x40},
        .frame_header_size = BF3901_FRAME_HEADER_SIZE,
        .line_header_size = BF3901_LINE_HEADER_SIZE,
        .frame_header_check_size = 4,
        .line_header_check_size = 4,
        .drop_frame_count = 1,
    },
};

static const esp_cam_sensor_format_t bf3901_format_info_spi[] = {
    {
        .name = "SPI_1bit_24Minput_RGB565_240x320_15fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RGB565,
        .port = ESP_CAM_SENSOR_SPI,
        .xclk = 24000000,
        .width = 240,
        .height = 320,
        .regs = SPI_1bit_24Minput_240x320_rgb565_15fps,
        .regs_size = ARRAY_SIZE(SPI_1bit_24Minput_240x320_rgb565_15fps),
        .fps = 15,
        .isp_info = NULL,
        .spi_info = {
            .rx_lines = 1,
            .frame_info = &bf3901_frame_info_spi[0],
        },
        .reserved = NULL,
    },
    {
        .name = "SPI_1bit_24Minput_YUV422_240x320_15fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_SPI,
        .xclk = 24000000,
        .width = 240,
        .height = 320,
        .regs = SPI_1bit_24Minput_240x320_yuv422_15fps,
        .regs_size = ARRAY_SIZE(SPI_1bit_24Minput_240x320_yuv422_15fps),
        .fps = 15,
        .isp_info = NULL,
        .spi_info = {
            .rx_lines = 1,
            .frame_info = &bf3901_frame_info_spi[0],
        },
        .reserved = NULL,
    },
    {
        .name = "SPI_1bit_20Minput_YUV422_240x320_12fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_SPI,
        .xclk = 20000000,
        .width = 240,
        .height = 320,
        .regs = SPI_1bit_20Minput_240x320_yuv422_12fps,
        .regs_size = ARRAY_SIZE(SPI_1bit_20Minput_240x320_yuv422_12fps),
        .fps = 12,
        .isp_info = NULL,
        .spi_info = {
            .rx_lines = 1,
            .frame_info = &bf3901_frame_info_spi[0],
        },
        .reserved = NULL,
    },
    {
        .name = "SPI_1bit_24Minput_YUV422_240x240_10fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_SPI,
        .xclk = 24000000,
        .width = 240,
        .height = 240,
        .regs = SPI_1bit_24Minput_240x240_yuv422_10fps,
        .regs_size = ARRAY_SIZE(SPI_1bit_24Minput_240x240_yuv422_10fps),
        .fps = 10,
        .isp_info = NULL,
        .spi_info = {
            .rx_lines = 1,
            .frame_info = &bf3901_frame_info_spi[1],
        },
        .reserved = NULL,
    },
    {
        .name = "SPI_1bit_24Minput_YUV422_120x160_10fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_SPI,
        .xclk = 24000000,
        .width = 120,
        .height = 160,
        .regs = SPI_1bit_24Minput_120x160_yuv422_10fps,
        .regs_size = ARRAY_SIZE(SPI_1bit_24Minput_120x160_yuv422_10fps),
        .fps = 10,
        .isp_info = NULL,
        .spi_info = {
            .rx_lines = 1,
            .frame_info = &bf3901_frame_info_spi[2],
        },
        .reserved = NULL,
    },
    {
        .name = "SPI_1bit_20Minput_YUV422_120x160_5fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_SPI,
        .xclk = 20000000,
        .width = 120,
        .height = 160,
        .regs = SPI_1bit_20Minput_120x160_yuv422_5fps,
        .regs_size = ARRAY_SIZE(SPI_1bit_20Minput_120x160_yuv422_5fps),
        .fps = 5,
        .isp_info = NULL,
        .spi_info = {
            .rx_lines = 1,
            .frame_info = &bf3901_frame_info_spi[2],
        },
        .reserved = NULL,
    },
    {
        .name = "SPI_2bit_24Minput_YUV422_240x320_20fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422,
        .port = ESP_CAM_SENSOR_SPI,
        .xclk = 24000000,
        .width = 240,
        .height = 320,
        .regs = SPI_2bit_24Minput_240x320_yuv422_20fps,
        .regs_size = ARRAY_SIZE(SPI_2bit_24Minput_240x320_yuv422_20fps),
        .fps = 20,
        .isp_info = NULL,
        .spi_info = {
            .rx_lines = 2,
            .frame_info = &bf3901_frame_info_spi[0],
        },
        .reserved = NULL,
    }
};

static esp_err_t bf3901_read(esp_sccb_io_handle_t sccb_handle, uint8_t reg, uint8_t *read_buf)
{
    return esp_sccb_transmit_receive_reg_a8v8(sccb_handle, reg, read_buf);
}

static esp_err_t bf3901_write(esp_sccb_io_handle_t sccb_handle, uint8_t reg, uint8_t data)
{
    return esp_sccb_transmit_reg_a8v8(sccb_handle, reg, data);
}

/* write a array of registers */
static esp_err_t bf3901_write_array(esp_sccb_io_handle_t sccb_handle, bf3901_reginfo_t *regarray, size_t regs_size)
{
    int i = 0;
    esp_err_t ret = ESP_OK;
    while ((ret == ESP_OK) && (i < regs_size)) {
        if (regarray[i].reg != BF3901_REG_DELAY) {
            ret = bf3901_write(sccb_handle, regarray[i].reg, regarray[i].val);
        } else {
            delay_ms(regarray[i].val);
        }
        i++;
    }
    ESP_LOGD(TAG, "Set array done[i=%d]", i);
    return ret;
}

static esp_err_t bf3901_set_reg_bits(esp_sccb_io_handle_t sccb_handle, uint8_t reg, uint8_t offset, uint8_t length, uint8_t value)
{
    esp_err_t ret = ESP_OK;
    uint8_t reg_data = 0;

    ret = bf3901_read(sccb_handle, reg, &reg_data);
    if (ret != ESP_OK) {
        return ret;
    }
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (reg_data & ~mask) | ((value << offset) & mask);
    ret = bf3901_write(sccb_handle, reg, value);
    return ret;
}

static esp_err_t bf3901_set_test_pattern(esp_cam_sensor_device_t *dev, int enable)
{
    esp_err_t ret = ESP_OK;
    ret = bf3901_set_reg_bits(dev->sccb_handle, 0xb9, 0x07, 0x01, enable & 0xff);
    return ret;
}

static esp_err_t bf3901_hw_reset(esp_cam_sensor_device_t *dev)
{
    if (dev->reset_pin >= 0) {
        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
    }
    return ESP_OK;
}

static esp_err_t bf3901_soft_reset(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = bf3901_set_reg_bits(dev->sccb_handle, BF3901_REG_RESET_RELATED, 0x07, 0x01, 0x01);
    delay_ms(5);
    return ret;
}

static esp_err_t bf3901_get_sensor_id(esp_cam_sensor_device_t *dev, esp_cam_sensor_id_t *id)
{
    esp_err_t ret = ESP_FAIL;
    uint8_t pid_h, pid_l;
    delay_ms(5);

    ret = bf3901_read(dev->sccb_handle, BF3901_REG_CHIP_ID_H, &pid_h);
    if (ret != ESP_OK) {
        return ret;
    }
    ret = bf3901_read(dev->sccb_handle, BF3901_REG_CHIP_ID_L, &pid_l);
    if (ret != ESP_OK) {
        return ret;
    }
    id->pid = (pid_h << 8) | pid_l;

    return ret;
}

static esp_err_t bf3901_set_stream(esp_cam_sensor_device_t *dev, int enable)
{
    esp_err_t ret = bf3901_write(dev->sccb_handle, 0x09, enable ? 0x03 : 0x13);

    if (ret == ESP_OK) {
        dev->stream_status = enable;
    }
    ESP_LOGD(TAG, "Stream=%d", enable);
    return ret;
}

static esp_err_t bf3901_set_mirror(esp_cam_sensor_device_t *dev, int enable)
{
    esp_err_t ret = bf3901_set_reg_bits(dev->sccb_handle, 0x1e, 5, 0x01, enable != 0);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "Set h-mirror to: %d", enable);
    }
    return ret;
}

static esp_err_t bf3901_set_vflip(esp_cam_sensor_device_t *dev, int enable)
{
    esp_err_t ret = bf3901_set_reg_bits(dev->sccb_handle, 0x1e, 4, 0x01, enable != 0);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "Set vflip to: %d", enable);
    }

    return ret;
}

static esp_err_t bf3901_query_para_desc(esp_cam_sensor_device_t *dev, esp_cam_sensor_param_desc_t *qdesc)
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

static esp_err_t bf3901_get_para_value(esp_cam_sensor_device_t *dev, uint32_t id, void *arg, size_t size)
{
    return ESP_ERR_NOT_SUPPORTED;
}

static esp_err_t bf3901_set_para_value(esp_cam_sensor_device_t *dev, uint32_t id, const void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;

    switch (id) {
    case ESP_CAM_SENSOR_VFLIP: {
        int *value = (int *)arg;

        ret = bf3901_set_vflip(dev, *value);
        break;
    }
    case ESP_CAM_SENSOR_HMIRROR: {
        int *value = (int *)arg;

        ret = bf3901_set_mirror(dev, *value);
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

static esp_err_t bf3901_query_support_formats(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_array_t *formats)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, formats);

    formats->count = ARRAY_SIZE(bf3901_format_info_spi);
    formats->format_array = &bf3901_format_info_spi[0];
    return ESP_OK;
}

static esp_err_t bf3901_query_support_capability(esp_cam_sensor_device_t *dev, esp_cam_sensor_capability_t *sensor_cap)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, sensor_cap);

    sensor_cap->fmt_yuv = 1;
    sensor_cap->fmt_rgb565 = 1;
    return 0;
}

static esp_err_t bf3901_set_format(esp_cam_sensor_device_t *dev, const esp_cam_sensor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);

    esp_err_t ret = ESP_OK;
    /* Depending on the interface type, an available configuration is automatically loaded.
    You can set the output format of the sensor without using query_format().*/
    if (format == NULL) {
        format = &bf3901_format_info_spi[CONFIG_CAMERA_BF3901_SPI_IF_FORMAT_INDEX_DEFAULT];
    }

    /* Todo, I2C NACK error causes the I2C driver to fail(AEG-2481).
     * After fixing the error, re-enable the reset.*/
    // bf3901_write(dev->sccb_handle, 0x12, 0x80);//Reset
    // delay_ms(5);

    ret = bf3901_write_array(dev->sccb_handle, (bf3901_reginfo_t *)format->regs, format->regs_size);
    ESP_LOGD(TAG, "fmt=%s", format->name);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Set format regs fail");
        return ESP_CAM_SENSOR_ERR_FAILED_SET_FORMAT;
    }

    dev->cur_format = format;

    return ret;
}

static esp_err_t bf3901_get_format(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_t *format)
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

static esp_err_t bf3901_priv_ioctl(esp_cam_sensor_device_t *dev, uint32_t cmd, void *arg)
{
    esp_err_t ret = ESP_OK;
    uint8_t regval;
    esp_cam_sensor_reg_val_t *sensor_reg;
    BF3901_IO_MUX_LOCK(mux);

    switch (cmd) {
    case ESP_CAM_SENSOR_IOC_HW_RESET:
        ret = bf3901_hw_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_SW_RESET:
        ret = bf3901_soft_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_S_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = bf3901_write(dev->sccb_handle, sensor_reg->regaddr, sensor_reg->value);
        break;
    case ESP_CAM_SENSOR_IOC_S_STREAM:
        ret = bf3901_set_stream(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_S_TEST_PATTERN:
        ret = bf3901_set_test_pattern(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_G_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = bf3901_read(dev->sccb_handle, sensor_reg->regaddr, &regval);
        if (ret == ESP_OK) {
            sensor_reg->value = regval;
        }
        break;
    case ESP_CAM_SENSOR_IOC_G_CHIP_ID:
        ret = bf3901_get_sensor_id(dev, arg);
        break;
    default:
        break;
    }

    BF3901_IO_MUX_UNLOCK(mux);
    return ret;
}

static esp_err_t bf3901_power_on(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        BF3901_ENABLE_OUT_XCLK(dev->xclk_pin, dev->xclk_freq_hz);
    }

    if (dev->pwdn_pin >= 0) {
        gpio_config_t conf = { 0 };
        conf.pin_bit_mask = 1LL << dev->pwdn_pin;
        conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&conf);

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
        gpio_config(&conf);

        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
    }

    return ret;
}

static esp_err_t bf3901_power_off(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        BF3901_DISABLE_OUT_XCLK(dev->xclk_pin);
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

static esp_err_t bf3901_delete(esp_cam_sensor_device_t *dev)
{
    ESP_LOGD(TAG, "del bf3901 (%p)", dev);
    if (dev) {
        free(dev);
        dev = NULL;
    }

    return ESP_OK;
}

static const esp_cam_sensor_ops_t bf3901_ops = {
    .query_para_desc = bf3901_query_para_desc,
    .get_para_value = bf3901_get_para_value,
    .set_para_value = bf3901_set_para_value,
    .query_support_formats = bf3901_query_support_formats,
    .query_support_capability = bf3901_query_support_capability,
    .set_format = bf3901_set_format,
    .get_format = bf3901_get_format,
    .priv_ioctl = bf3901_priv_ioctl,
    .del = bf3901_delete
};

esp_cam_sensor_device_t *bf3901_detect(esp_cam_sensor_config_t *config)
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

    dev->name = (char *)BF3901_SENSOR_NAME;
    dev->sccb_handle = config->sccb_handle;
    dev->xclk_pin = config->xclk_pin;
    dev->reset_pin = config->reset_pin;
    dev->pwdn_pin = config->pwdn_pin;
    dev->sensor_port = config->sensor_port;
    dev->ops = &bf3901_ops;
    dev->cur_format = &bf3901_format_info_spi[CONFIG_CAMERA_BF3901_SPI_IF_FORMAT_INDEX_DEFAULT];

// Configure sensor power, clock, and SCCB port
    if (bf3901_power_on(dev) != ESP_OK) {
        ESP_LOGE(TAG, "Camera power on failed");
        goto err_free_handler;
    }

    if (bf3901_get_sensor_id(dev, &dev->id) != ESP_OK) {
        ESP_LOGE(TAG, "Get sensor ID failed");
        goto err_free_handler;
    } else if (dev->id.pid != BF3901_PID) {
        ESP_LOGE(TAG, "Camera sensor is not BF3901, PID=0x%x", dev->id.pid);
        goto err_free_handler;
    }
    ESP_LOGI(TAG, "Detected Camera sensor PID=0x%x", dev->id.pid);

    return dev;

err_free_handler:
    bf3901_power_off(dev);
    free(dev);

    return NULL;
}

#if CONFIG_CAMERA_BF3901_AUTO_DETECT_SPI_INTERFACE_SENSOR
ESP_CAM_SENSOR_DETECT_FN(bf3901_detect, ESP_CAM_SENSOR_SPI, BF3901_SCCB_ADDR)
{
    ((esp_cam_sensor_config_t *)config)->sensor_port = ESP_CAM_SENSOR_SPI;
    return bf3901_detect(config);
}
#endif
