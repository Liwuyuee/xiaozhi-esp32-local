/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <sys/param.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/timers.h"

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#include "esp_cam_sensor.h"
#include "esp_cam_sensor_detect.h"
#include "os02n10_settings.h"
#include "os02n10.h"

/*
 * OS02N10 camera sensor gain map control.
 */
typedef struct {
    uint8_t analog_gain;
    uint8_t dgain_msb;
    uint8_t dgain_lsb;
} os02n10_gain_t;

typedef struct {
    uint32_t exposure_val;
    uint32_t exposure_max;
    uint32_t gain_index; // current gain index

    uint32_t vflip_en : 1;
    uint32_t hmirror_en : 1;
} os02n10_para_t;

struct os02n10_cam {
    os02n10_para_t os02n10_para;
};

#define OS02N10_IO_MUX_LOCK(mux)
#define OS02N10_IO_MUX_UNLOCK(mux)
#define OS02N10_ENABLE_OUT_XCLK(pin,clk)
#define OS02N10_DISABLE_OUT_XCLK(pin)

#define OS02N10_EXP_MAX_OFFSET   0x09

#define OS02N10_FETCH_EXP_H(val)     (((val) >> 8) & 0xFF)
#define OS02N10_FETCH_EXP_L(val)     ((val) & 0xFF)

#define OS02N10_PID         0x534e
#define OS02N10_SENSOR_NAME "OS02N10"
#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif
#define delay_ms(ms)  vTaskDelay((ms > portTICK_PERIOD_MS ? ms/ portTICK_PERIOD_MS : 1))
#define OS02N10_SUPPORT_NUM CONFIG_CAMERA_OS02N10_MAX_SUPPORT

#define CAMERA_OS02N10_EXPOSURE_TEST_EN 0

static size_t s_limited_gain_index;
static const uint8_t s_os02n10_exp_min = 0x02;
static volatile os02n10_bank_t s_reg_bank = OS02N10_BANK_MAX; // current bank
static const char *TAG = "os02n10";

#define EXPOSURE_V4L2_UNIT_US                   100
#define EXPOSURE_V4L2_TO_OS02N10(v, sf)          \
    ((uint32_t)(((double)v) * EXPOSURE_V4L2_UNIT_US * 1000 / (((sf)->isp_info->isp_v1_info.tline_ns)) + 0.5))
#define EXPOSURE_OS02N10_TO_V4L2(v, sf)          \
    ((int32_t)(((double)v) * (((sf)->isp_info->isp_v1_info.tline_ns)) / EXPOSURE_V4L2_UNIT_US / 1000 + 0.5))

// total gain = analog_gain x digital_gain x 1000(To avoid decimal points, the final abs_gain is multiplied by 1000.)
static const uint32_t os02n10_total_gain_val_map[] = {
    1000, 1062, 1125, 1187, 1250, 1312, 1375, 1437, 1500, 1562, 1625, 1687, 1750, 1812, 1875, 1937,
    2000, 2125, 2250, 2375, 2500, 2625, 2750, 2875, 3000, 3125, 3250, 3375, 3500, 3625, 3750, 3875,
    4000, 4250, 4500, 4750, 5000, 5250, 5500, 5750, 6000, 6250, 6500, 6750, 7000, 7250, 7500,
    7750, 8000, 8500, 9000, 9500, 10000, 10500, 11000, 11500, 12000, 12500, 13000, 13500, 14000,
    14500, 15000, 15500, 15741, 15984, 16225, 16468
};

/*
 * OS02N10 Gain map format: [AGain, DGain_MSB, DGain_LSB]
 * AGain {P1:0x24}
 * 0x10~0xF8: 1x-15.5x
 *
 * DGain {P1:0x1F P1:0x20}
 * 1x: 0x1F=0x00;0x20=0x40
 * 32x:0x1F=0x07;0x20=0xFF
 * minimum step is 1/64
 */
static const os02n10_gain_t os02n10_gain_map[] = {
    /* 1x */
    {0x10, 0x00, 0x40},
    {0x11, 0x00, 0x40},
    {0x12, 0x00, 0x40},
    {0x13, 0x00, 0x40},
    {0x14, 0x00, 0x40},
    {0x15, 0x00, 0x40},
    {0x16, 0x00, 0x40},
    {0x17, 0x00, 0x40},
    {0x18, 0x00, 0x40},
    {0x19, 0x00, 0x40},
    {0x1a, 0x00, 0x40},
    {0x1b, 0x00, 0x40},
    {0x1c, 0x00, 0x40},
    {0x1d, 0x00, 0x40},
    {0x1e, 0x00, 0x40},
    {0x1f, 0x00, 0x40},
    /* 2x */
    {0x20, 0x00, 0x40},
    {0x22, 0x00, 0x40},
    {0x24, 0x00, 0x40},
    {0x26, 0x00, 0x40},
    {0x28, 0x00, 0x40},
    {0x2a, 0x00, 0x40},
    {0x2c, 0x00, 0x40},
    {0x2e, 0x00, 0x40},
    /* 3x */
    {0x30, 0x00, 0x40},
    {0x32, 0x00, 0x40},
    {0x34, 0x00, 0x40},
    {0x36, 0x00, 0x40},
    {0x38, 0x00, 0x40},
    {0x3a, 0x00, 0x40},
    {0x3c, 0x00, 0x40},
    {0x3e, 0x00, 0x40},
    /* 4x */
    {0x40, 0x00, 0x40},
    {0x44, 0x00, 0x40},
    {0x48, 0x00, 0x40},
    {0x4c, 0x00, 0x40},
    /* 5x */
    {0x50, 0x00, 0x40},
    {0x54, 0x00, 0x40},
    {0x58, 0x00, 0x40},
    {0x5c, 0x00, 0x40},
    /* 6x */
    {0x60, 0x00, 0x40},
    {0x64, 0x00, 0x40},
    {0x68, 0x00, 0x40},
    {0x6c, 0x00, 0x40},
    /* 7x */
    {0x70, 0x00, 0x40},
    {0x74, 0x00, 0x40},
    {0x78, 0x00, 0x40},
    {0x7c, 0x00, 0x40},
    /* 8x */
    {0x80, 0x00, 0x40},
    {0x88, 0x00, 0x40},
    /* 9x */
    {0x90, 0x00, 0x40},
    {0x98, 0x00, 0x40},
    /* 10x */
    {0xa0, 0x00, 0x40},
    {0xa8, 0x00, 0x40},
    /* 11x */
    {0xb0, 0x00, 0x40},
    {0xb8, 0x00, 0x40},
    /* 12x */
    {0xc0, 0x00, 0x40},
    {0xc8, 0x00, 0x40},
    /* 13x */
    {0xd0, 0x00, 0x40},
    {0xd8, 0x00, 0x40},
    /* 14x */
    {0xe0, 0x00, 0x40},
    {0xe8, 0x00, 0x40},
    /* 15x */
    {0xf0, 0x00, 0x40},
    {0xf8, 0x00, 0x40},
    {0xf8, 0x00, 0x41}, // 15741
    {0xf8, 0x00, 0x42}, // 15984
    /* 16x */
    {0xf8, 0x00, 0x43}, // 16225
    {0xf8, 0x00, 0x40}, // 16468
};

#if CONFIG_SOC_MIPI_CSI_SUPPORTED
static const esp_cam_sensor_isp_info_t os02n10_isp_info_mipi[] = {
    /* For MIPI */
    {
        .isp_v1_info = {
            .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
            .pclk = 72000000,
            .vts = 1323,
            .hts = 544,
            .tline_ns = 30222,
            .gain_def = 16,
            .exp_def = 0x1c2,
            .bayer_type = ESP_CAM_SENSOR_BAYER_BGGR,
        }
    },
    {
        .isp_v1_info = {
            .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
            .pclk = 81600000,
            .vts = 750,
            .hts = 544,
            .tline_ns = 26666,
            .gain_def = 16,
            .exp_def = 0x1c2,
            .bayer_type = ESP_CAM_SENSOR_BAYER_BGGR,
        },
    },
    {
        .isp_v1_info = {
            .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
            .pclk = 72000000,
            .vts = 1323,
            .hts = 544,
            .tline_ns = 30222,
            .gain_def = 16,
            .exp_def = 0x1c2,
            .bayer_type = ESP_CAM_SENSOR_BAYER_BGGR,
        },
    }
};

static const esp_cam_sensor_format_t os02n10_format_info_mipi[] = {
    /* For MIPI */
    {
        .name = "MIPI_2lane_24Minput_RAW10_1920x1080_25fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW10,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 1920,
        .height = 1080,
        .regs = os02n10_init_reglist_MIPI_2lane_raw10_1080p_25fps,
        .regs_size = ARRAY_SIZE(os02n10_init_reglist_MIPI_2lane_raw10_1080p_25fps),
        .fps = 25,
        .isp_info = &os02n10_isp_info_mipi[0],
        .mipi_info = {
            .mipi_clk = 360000000,
            .lane_num = 2,
            .line_sync_en = false,
        },
    },
    {
        .name = "MIPI_2lane_24Minput_RAW10_1280x720_50fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW10,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 1280,
        .height = 720,
        .regs = os02n10_init_reglist_MIPI_2lane_raw10_720p_50fps,
        .regs_size = ARRAY_SIZE(os02n10_init_reglist_MIPI_2lane_raw10_720p_50fps),
        .fps = 50,
        .isp_info = &os02n10_isp_info_mipi[1],
        .mipi_info = {
            .mipi_clk = 408000000,
            .lane_num = 2,
            .line_sync_en = false,
        },
    },
    {
        .name = "MIPI_2lane_24Minput_RAW8_1920x1080_25fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW8,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 1920,
        .height = 1080,
        .regs = os02n10_init_reglist_MIPI_2lane_raw8_1080p_25fps,
        .regs_size = ARRAY_SIZE(os02n10_init_reglist_MIPI_2lane_raw8_1080p_25fps),
        .fps = 25,
        .isp_info = &os02n10_isp_info_mipi[0],
        .mipi_info = {
            .mipi_clk = 288000000,
            .lane_num = 2,
            .line_sync_en = false,
        },
    },
    {
        .name = "MIPI_2lane_24Minput_RAW8_1280x720_50fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW8,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 1280,
        .height = 720,
        .regs = os02n10_init_reglist_MIPI_2lane_raw8_720p_50fps,
        .regs_size = ARRAY_SIZE(os02n10_init_reglist_MIPI_2lane_raw8_720p_50fps),
        .fps = 50,
        .isp_info = &os02n10_isp_info_mipi[1],
        .mipi_info = {
            .mipi_clk = 326000000,
            .lane_num = 2,
            .line_sync_en = false,
        },
    },
    {
        .name = "MIPI_2lane_24Minput_RAW8_960x540_25fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW8,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 960,
        .height = 540,
        .regs = os02n10_init_reglist_MIPI_2lane_raw8_binning_960x540_25fps,
        .regs_size = ARRAY_SIZE(os02n10_init_reglist_MIPI_2lane_raw8_binning_960x540_25fps),
        .fps = 25,
        .isp_info = &os02n10_isp_info_mipi[2],
        .mipi_info = {
            .mipi_clk = 180000000,
            .lane_num = 2,
            .line_sync_en = false,
        },
    }
};
#endif

static esp_err_t os02n10_set_bank(esp_sccb_io_handle_t sccb_handle, os02n10_bank_t bank)
{
    esp_err_t ret = ESP_OK;
    if (bank != s_reg_bank) {
        ret = esp_sccb_transmit_reg_a8v8(sccb_handle, OS02N10_REG_BANK_SEL, bank);
        if (ret == ESP_OK) {
            s_reg_bank = bank;
        } else {
            ESP_LOGE(TAG, "Bank update failed");
        }
    }
    return ret;
}

static esp_err_t os02n10_read(esp_sccb_io_handle_t sccb_handle, uint8_t reg, uint8_t *read_buf)
{
    return esp_sccb_transmit_receive_reg_a8v8(sccb_handle, reg, read_buf);
}

static esp_err_t os02n10_write(esp_sccb_io_handle_t sccb_handle, uint8_t reg, uint8_t data)
{
    return esp_sccb_transmit_reg_a8v8(sccb_handle, reg, data);
}

/* write a array of registers  */
static esp_err_t os02n10_write_array(esp_sccb_io_handle_t sccb_handle, const os02n10_reginfo_t *regs, size_t regs_size)
{
    int i = 0;
    esp_err_t ret = ESP_OK;
    while ((ret == ESP_OK) && i < regs_size) {
        if (regs[i].reg == OS02N10_REG_BANK_SEL) {
            ret = os02n10_set_bank(sccb_handle, regs[i].val);
        } else if (regs[i].reg == OS02N10_REG_DELAY) {
            delay_ms(regs[i].val);
        } else {
            ret = esp_sccb_transmit_reg_a8v8(sccb_handle, regs[i].reg, regs[i].val);
        }
        i++;
    }
    ESP_LOGD(TAG, "write regs cnt=%d", i);
    return ret;
}

static esp_err_t os02n10_set_reg_bits(esp_sccb_io_handle_t sccb_handle, uint8_t reg, uint8_t offset, uint8_t length, uint8_t value)
{
    esp_err_t ret = ESP_OK;
    uint8_t reg_data = 0;

    ret = os02n10_read(sccb_handle, reg, &reg_data);
    if (ret != ESP_OK) {
        return ret;
    }
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (reg_data & ~mask) | ((value << offset) & mask);
    ret = os02n10_write(sccb_handle, reg, value);
    return ret;
}

static esp_err_t os02n10_set_test_pattern(esp_cam_sensor_device_t *dev, int enable)
{
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANKI_ISP) != ESP_OK) {
        return ESP_FAIL;
    }
    // 0x03 is gradient mode
    return os02n10_write(dev->sccb_handle, OS02N10_REG_TP_EN, enable ? 0x01 : 0x00);
}

static esp_err_t os02n10_hw_reset(esp_cam_sensor_device_t *dev)
{
    if (dev->reset_pin >= 0) {
        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
    }
    return ESP_OK;
}

static esp_err_t os02n10_soft_reset(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = os02n10_write(dev->sccb_handle, 0xfc, 0x01);
    delay_ms(5);
    return ret;
}

static esp_err_t os02n10_get_sensor_id(esp_cam_sensor_device_t *dev, esp_cam_sensor_id_t *id)
{
    esp_err_t ret = ESP_FAIL;
    uint8_t pid_hh, pid_lh;
    esp_rom_delay_us(2000);
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANK_SYSTEM) != ESP_OK) {
        return ret;
    }

    ret = os02n10_read(dev->sccb_handle, OS02N10_REG_CHIP_ID_ADDR_HH, &pid_hh);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "ID read h failed");
        return ret;
    }

    ret |= os02n10_read(dev->sccb_handle, OS02N10_REG_CHIP_ID_ADDR_LH, &pid_lh);

    id->pid = (pid_hh << 8) | pid_lh;

    return ret;
}

static esp_err_t os02n10_set_stream(esp_cam_sensor_device_t *dev, int enable)
{
    esp_err_t ret = ESP_FAIL;
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANK_SYSTEM) != ESP_OK) {
        return ret;
    }

    ret = os02n10_write(dev->sccb_handle, OS02N10_REG_COMC03, enable ? 0x00 : 0x03);

    if (ret == ESP_OK) {
        dev->stream_status = enable;
    }

    ESP_LOGD(TAG, "Stream=%d", enable);
    return ret;
}

static esp_err_t os02n10_set_mirror(esp_cam_sensor_device_t *dev, int enable)
{
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANK_SENSOR) != ESP_OK) {
        return ESP_FAIL;
    }
    return os02n10_set_reg_bits(dev->sccb_handle, 0x12, 1, 1, enable ? 0x01 : 0x00);
}

static esp_err_t os02n10_set_vflip(esp_cam_sensor_device_t *dev, int enable)
{
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANK_SENSOR) != ESP_OK) {
        return ESP_FAIL;
    }
    return os02n10_set_reg_bits(dev->sccb_handle, 0x12, 0, 1, enable ? 0x01 : 0x00);
}

static esp_err_t os02n10_trigger_gain(esp_cam_sensor_device_t *dev)
{
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANK_SENSOR) != ESP_OK) {
        return ESP_FAIL;
    }
    return os02n10_write(dev->sccb_handle, 0xfe, 0x02);
}

static esp_err_t os02n10_set_exp_val(esp_cam_sensor_device_t *dev, uint32_t u32_val)
{
    esp_err_t ret;
    struct os02n10_cam *cam_os02n10 = (struct os02n10_cam *)dev->priv;
    uint32_t value_buf = MAX(u32_val, s_os02n10_exp_min);
    value_buf = MIN(value_buf, cam_os02n10->os02n10_para.exposure_max);

    ESP_LOGD(TAG, "set exposure 0x%" PRIx32, value_buf);
    /* linear exposure reg range:
    * min : 2
    * max : vts - 9
    * step : 1
    * Set p1:0x0f = 0x02 to trigger the new exposure
    * enable auto prolong vts, see P1:0x18 = 0x01
    */
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANK_SENSOR) != ESP_OK) {
        return ESP_FAIL;
    }

    ret = os02n10_write(dev->sccb_handle,
                        OS02N10_REG_PAGE1_EXP_H,
                        OS02N10_FETCH_EXP_H(value_buf));
    ret |= os02n10_write(dev->sccb_handle,
                         OS02N10_REG_PAGE1_EXP_L,
                         OS02N10_FETCH_EXP_L(value_buf));

    if (ret == ESP_OK) {
        cam_os02n10->os02n10_para.exposure_val = value_buf;
    }
    return ret;
}

static esp_err_t os02n10_set_total_gain_val(esp_cam_sensor_device_t *dev, uint32_t u32_val)
{
    esp_err_t ret;
    struct os02n10_cam *cam_os02n10 = (struct os02n10_cam *)dev->priv;
    if (u32_val > s_limited_gain_index) {
        u32_val = s_limited_gain_index;
    }
    /* analog gain is p1:0x24, 1~15.5x, set p1:0xfe = 0x02 to trigger it */
    /* digital gain is p1:0x1f&0x20, 1~32x, min step is 1/64, */
    /* The exposure/gain will be valid form N + 2 frames when 0xfe=0x02 is written */
    if (os02n10_set_bank(dev->sccb_handle, OS02N10_BANK_SENSOR) != ESP_OK) {
        return ESP_FAIL;
    }

    ESP_LOGD(TAG, "a_gain %" PRIx8 ", dgain_m %" PRIx8 ", dgain_l %" PRIx8, os02n10_gain_map[u32_val].analog_gain, os02n10_gain_map[u32_val].dgain_msb, os02n10_gain_map[u32_val].dgain_lsb);
    ret = os02n10_write(dev->sccb_handle,
                        OS02N10_REG_PAGE1_RPC_L,
                        os02n10_gain_map[u32_val].analog_gain);
    ret |= os02n10_write(dev->sccb_handle,
                         OS02N10_REG_PAGE1_DGAIN_H,
                         os02n10_gain_map[u32_val].dgain_msb);
    ret |= os02n10_write(dev->sccb_handle,
                         OS02N10_REG_PAGE1_DGAIN_L,
                         os02n10_gain_map[u32_val].dgain_lsb);
    if (ret == ESP_OK) {
        cam_os02n10->os02n10_para.gain_index = u32_val;
    }
    return ret;
}

static esp_err_t os02n10_query_para_desc(esp_cam_sensor_device_t *dev, esp_cam_sensor_param_desc_t *qdesc)
{
    esp_err_t ret = ESP_OK;
    switch (qdesc->id) {
    case ESP_CAM_SENSOR_EXPOSURE_VAL:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = s_os02n10_exp_min;
        qdesc->number.maximum = dev->cur_format->isp_info->isp_v1_info.vts - OS02N10_EXP_MAX_OFFSET;
        qdesc->number.step = 1;
        qdesc->default_value = dev->cur_format->isp_info->isp_v1_info.exp_def;
        break;
    case ESP_CAM_SENSOR_EXPOSURE_US:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = MAX(0x01, EXPOSURE_OS02N10_TO_V4L2(s_os02n10_exp_min, dev->cur_format)); // The minimum value must be greater than 1
        qdesc->number.maximum = EXPOSURE_OS02N10_TO_V4L2((dev->cur_format->isp_info->isp_v1_info.vts - OS02N10_EXP_MAX_OFFSET), dev->cur_format);
        qdesc->number.step = MAX(0x01, EXPOSURE_OS02N10_TO_V4L2(0x01, dev->cur_format));
        qdesc->default_value = EXPOSURE_OS02N10_TO_V4L2((dev->cur_format->isp_info->isp_v1_info.exp_def), dev->cur_format);
        ESP_LOGD(TAG, "exposure: minimum 0x%" PRIx32", maximum 0x%" PRIx32", step 0x%" PRIx32", default_value 0x%" PRIx32, qdesc->number.minimum, qdesc->number.maximum, qdesc->number.step, qdesc->default_value);
        break;
    case ESP_CAM_SENSOR_GAIN:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_ENUMERATION;
        qdesc->enumeration.count = s_limited_gain_index;
        qdesc->enumeration.elements = os02n10_total_gain_val_map;
        qdesc->default_value = dev->cur_format->isp_info->isp_v1_info.gain_def; // gain index
        break;
    case ESP_CAM_SENSOR_GROUP_EXP_GAIN:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_U8;
        qdesc->u8.size = sizeof(esp_cam_sensor_gh_exp_gain_t);
        break;
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

static esp_err_t os02n10_get_para_value(esp_cam_sensor_device_t *dev, uint32_t id, void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;
    struct os02n10_cam *cam_os02n10 = (struct os02n10_cam *)dev->priv;
    switch (id) {
    case ESP_CAM_SENSOR_EXPOSURE_VAL: {
        *(uint32_t *)arg = cam_os02n10->os02n10_para.exposure_val;
        break;
    }
    case ESP_CAM_SENSOR_GAIN: {
        *(uint32_t *)arg = cam_os02n10->os02n10_para.gain_index;
        break;
    }
    default: {
        ret = ESP_ERR_NOT_SUPPORTED;
        break;
    }
    }
    return ret;
}

static esp_err_t os02n10_set_para_value(esp_cam_sensor_device_t *dev, uint32_t id, const void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;

    switch (id) {
    case ESP_CAM_SENSOR_EXPOSURE_VAL: {
        uint32_t u32_val = *(uint32_t *)arg;
        ret = os02n10_set_exp_val(dev, u32_val);
        os02n10_trigger_gain(dev);
        break;
    }
    case ESP_CAM_SENSOR_EXPOSURE_US: {
        uint32_t u32_val = *(uint32_t *)arg;
        uint32_t ori_exp = EXPOSURE_V4L2_TO_OS02N10(u32_val, dev->cur_format);
        ret = os02n10_set_exp_val(dev, ori_exp);
        os02n10_trigger_gain(dev);
        break;
    }
    case ESP_CAM_SENSOR_GAIN: {
        uint32_t u32_val = *(uint32_t *)arg;
        ret = os02n10_set_total_gain_val(dev, u32_val);
        os02n10_trigger_gain(dev);
        break;
    }
    case ESP_CAM_SENSOR_GROUP_EXP_GAIN: {
        esp_cam_sensor_gh_exp_gain_t *value = (esp_cam_sensor_gh_exp_gain_t *)arg;
        uint32_t ori_exp = 0;
        if (value->exposure_us != 0) {
            ori_exp = EXPOSURE_V4L2_TO_OS02N10(value->exposure_us, dev->cur_format);
        } else if (value->exposure_val != 0) {
            ori_exp = value->exposure_val;
        } else {
            ret = ESP_ERR_INVALID_ARG;
            break;
        }
        ret = os02n10_set_exp_val(dev, ori_exp);
        ret |= os02n10_set_total_gain_val(dev, value->gain_index);
        os02n10_trigger_gain(dev);
        break;
    }
    case ESP_CAM_SENSOR_VFLIP: {
        int *value = (int *)arg;
        ret = os02n10_set_vflip(dev, *value);
        break;
    }
    case ESP_CAM_SENSOR_HMIRROR: {
        int *value = (int *)arg;
        ret = os02n10_set_mirror(dev, *value);
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

static esp_err_t os02n10_query_support_formats(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_array_t *formats)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, formats);
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
    if (dev->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
        formats->count = ARRAY_SIZE(os02n10_format_info_mipi);
        formats->format_array = &os02n10_format_info_mipi[0];
    }
#endif
    return ESP_OK;
}

static esp_err_t os02n10_query_support_capability(esp_cam_sensor_device_t *dev, esp_cam_sensor_capability_t *sensor_cap)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, sensor_cap);

    sensor_cap->fmt_raw = 1;
    return 0;
}

static esp_err_t os02n10_set_format(esp_cam_sensor_device_t *dev, const esp_cam_sensor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    struct os02n10_cam *cam_os02n10 = (struct os02n10_cam *)dev->priv;
    esp_err_t ret = ESP_OK;
    /* Depending on the interface type, an available configuration is automatically loaded.
    You can set the output format of the sensor without using query_format().*/
    if (format == NULL) {
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
        if (dev->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
            format = &os02n10_format_info_mipi[CONFIG_CAMERA_OS02N10_MIPI_IF_FORMAT_INDEX_DEFAULT];
        }
#endif
    }

    ret = os02n10_write_array(dev->sccb_handle, (os02n10_reginfo_t *)format->regs, format->regs_size);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Set format regs fail");
        return ESP_CAM_SENSOR_ERR_FAILED_SET_FORMAT;
    }
    ESP_LOGD(TAG, "Set format %s", format->name);

    dev->cur_format = format;

    // init para
    cam_os02n10->os02n10_para.exposure_val = dev->cur_format->isp_info->isp_v1_info.exp_def;
    cam_os02n10->os02n10_para.gain_index = dev->cur_format->isp_info->isp_v1_info.gain_def;
    cam_os02n10->os02n10_para.exposure_max = dev->cur_format->isp_info->isp_v1_info.vts - OS02N10_EXP_MAX_OFFSET;

    return ret;
}

static esp_err_t os02n10_get_format(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_t *format)
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

static esp_err_t os02n10_priv_ioctl(esp_cam_sensor_device_t *dev, uint32_t cmd, void *arg)
{
    esp_err_t ret = ESP_OK;
    uint8_t regval;
    esp_cam_sensor_reg_val_t *sensor_reg;
    OS02N10_IO_MUX_LOCK(mux);

    switch (cmd) {
    case ESP_CAM_SENSOR_IOC_HW_RESET:
        ret = os02n10_hw_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_SW_RESET:
        ret = os02n10_soft_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_S_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = os02n10_write(dev->sccb_handle, sensor_reg->regaddr, sensor_reg->value);
        break;
    case ESP_CAM_SENSOR_IOC_S_STREAM:
        ret = os02n10_set_stream(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_S_TEST_PATTERN:
        ret = os02n10_set_test_pattern(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_G_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = os02n10_read(dev->sccb_handle, sensor_reg->regaddr, &regval);
        if (ret == ESP_OK) {
            sensor_reg->value = regval;
        }
        break;
    case ESP_CAM_SENSOR_IOC_G_CHIP_ID:
        ret = os02n10_get_sensor_id(dev, arg);
        break;
    default:
        break;
    }

    OS02N10_IO_MUX_UNLOCK(mux);
    return ret;
}

static esp_err_t os02n10_power_on(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        OS02N10_ENABLE_OUT_XCLK(dev->xclk_pin, dev->xclk_freq_hz);
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

static esp_err_t os02n10_power_off(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        OS02N10_DISABLE_OUT_XCLK(dev->xclk_pin);
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

static esp_err_t os02n10_delete(esp_cam_sensor_device_t *dev)
{
    ESP_LOGD(TAG, "del os02n10 (%p)", dev);
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

static const esp_cam_sensor_ops_t os02n10_ops = {
    .query_para_desc = os02n10_query_para_desc,
    .get_para_value = os02n10_get_para_value,
    .set_para_value = os02n10_set_para_value,
    .query_support_formats = os02n10_query_support_formats,
    .query_support_capability = os02n10_query_support_capability,
    .set_format = os02n10_set_format,
    .get_format = os02n10_get_format,
    .priv_ioctl = os02n10_priv_ioctl,
    .del = os02n10_delete
};

#if CAMERA_OS02N10_EXPOSURE_TEST_EN
static uint32_t exp_v = 2;
TimerHandle_t ae_timer_handle;
static void ae_timer_callback(TimerHandle_t timer)
{
    esp_cam_sensor_device_t *dev = (esp_cam_sensor_device_t *)pvTimerGetTimerID(timer);
    os02n10_set_total_gain_val(dev, exp_v);
    os02n10_trigger_gain(dev);
    exp_v++;
}
#endif

esp_cam_sensor_device_t *os02n10_detect(esp_cam_sensor_config_t *config)
{
    esp_cam_sensor_device_t *dev = NULL;
    struct os02n10_cam *cam_os02n10;
    s_limited_gain_index = ARRAY_SIZE(os02n10_total_gain_val_map);
    if (config == NULL) {
        return NULL;
    }

    dev = calloc(1, sizeof(esp_cam_sensor_device_t));
    if (dev == NULL) {
        ESP_LOGE(TAG, "No memory for camera");
        return NULL;
    }

    cam_os02n10 = heap_caps_calloc(1, sizeof(struct os02n10_cam), MALLOC_CAP_DEFAULT);
    if (!cam_os02n10) {
        ESP_LOGE(TAG, "failed to calloc cam");
        free(dev);
        return NULL;
    }

    dev->name = (char *)OS02N10_SENSOR_NAME;
    dev->sccb_handle = config->sccb_handle;
    dev->xclk_pin = config->xclk_pin;
    dev->reset_pin = config->reset_pin;
    dev->pwdn_pin = config->pwdn_pin;
    dev->sensor_port = config->sensor_port;
    dev->ops = &os02n10_ops;
    dev->priv = cam_os02n10;
    for (size_t i = 0; i < ARRAY_SIZE(os02n10_total_gain_val_map); i++) {
        if (os02n10_total_gain_val_map[i] > CONFIG_CAMERA_OS02N10_ABSOLUTE_GAIN_LIMIT) {
            s_limited_gain_index = i - 1;
            ESP_LOGD(TAG, "Limit gain index is %d", s_limited_gain_index);
            break;
        }
    }
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
    if (config->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
        dev->cur_format = &os02n10_format_info_mipi[CONFIG_CAMERA_OS02N10_MIPI_IF_FORMAT_INDEX_DEFAULT];
    }
#endif
    // Configure sensor power, clock, and SCCB port
    if (os02n10_power_on(dev) != ESP_OK) {
        ESP_LOGE(TAG, "Camera power on failed");
        goto err_free_handler;
    }

    if (os02n10_get_sensor_id(dev, &dev->id) != ESP_OK) {
        ESP_LOGE(TAG, "Get sensor ID failed");
        goto err_free_handler;
    } else if (dev->id.pid != OS02N10_PID) {
        ESP_LOGE(TAG, "Camera sensor is not OS02N10, PID=0x%x", dev->id.pid);
        goto err_free_handler;
    }
    ESP_LOGI(TAG, "Detected Camera sensor PID=0x%x", dev->id.pid);

#if CAMERA_OS02N10_EXPOSURE_TEST_EN
    ae_timer_handle = xTimerCreate("AE_t", 100 / portTICK_PERIOD_MS, pdTRUE,
                                   (void *)dev, ae_timer_callback);
    xTimerStart(ae_timer_handle, portMAX_DELAY);
#endif

    return dev;

err_free_handler:
    os02n10_power_off(dev);
    free(dev->priv);
    free(dev);

    return NULL;
}

#if CONFIG_CAMERA_OS02N10_AUTO_DETECT_MIPI_INTERFACE_SENSOR
ESP_CAM_SENSOR_DETECT_FN(os02n10_detect, ESP_CAM_SENSOR_MIPI_CSI, OS02N10_SCCB_ADDR)
{
    ((esp_cam_sensor_config_t *)config)->sensor_port = ESP_CAM_SENSOR_MIPI_CSI;
    return os02n10_detect(config);
}
#endif
