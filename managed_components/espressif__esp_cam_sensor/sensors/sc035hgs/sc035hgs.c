/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
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
#include "sc035hgs_settings.h"
#include "sc035hgs.h"

/*
 * SC035HGS camera sensor gain control.
 */
typedef struct {
    uint8_t again_fine; // analog gain fine
    uint8_t again_coarse; // analog gain coarse
    uint8_t dgain_fine; // digital gain fine
    uint8_t dgain_coarse; // digital gain coarse
} sc035hgs_gain_t;

typedef struct {
    uint32_t exposure_val;
    uint32_t exposure_max;
    uint32_t gain_index; // current gain index

    uint32_t vflip_en : 1;
    uint32_t hmirror_en : 1;
} sc035hgs_para_t;

struct sc035hgs_cam {
    sc035hgs_para_t sc035hgs_para;
};

#define SC035HGS_IO_MUX_LOCK(mux)
#define SC035HGS_IO_MUX_UNLOCK(mux)
#define SC035HGS_ENABLE_OUT_XCLK(pin,clk)
#define SC035HGS_DISABLE_OUT_XCLK(pin)

/*
* Line_exp_in_s = HTS * Time_of_PCLK
* PCLK = HTS * VTS * fps
* Exposure_step = 1/16 * Line_exp_in_s = 1/16 * HTS * Time_of_PCLK = 1/16 * HTS * 1/PCLK
* Exposure_step = 1/16 * HTS * 1/(HTS * VTS * fps) = 1/16 * 1/(VTS * fps)
*/
#define EXPOSURE_V4L2_UNIT_US                   100
#define EXPOSURE_V4L2_TO_SC035HGS(v, sf)          \
    ((uint32_t)(((double)v) * (sf)->fps * (sf)->isp_info->isp_v1_info.vts * 16 / (1000000 / EXPOSURE_V4L2_UNIT_US) + 0.5))
#define EXPOSURE_SC035HGS_TO_V4L2(v, sf)          \
    ((int32_t)(((double)v) * 1000000 / (sf)->fps / (sf)->isp_info->isp_v1_info.vts / 16 / EXPOSURE_V4L2_UNIT_US + 0.5))

#define SC035HGS_FETCH_EXP_H(val)     (((val) >> 4) & 0xFF)
#define SC035HGS_FETCH_EXP_L(val)     (((val) & 0xF) << 4)
#define SC035HGS_GROUP_HOLD_START   0X00
#define SC035HGS_GROUP_HOLD_LUNCH   0x30
#define SC035HGS_EXP_MAX_OFFSET     0x06

#define SC035HGS_PID         0x0031
#define SC035HGS_SENSOR_NAME "SC035HGS"
#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif
#define delay_ms(ms)  vTaskDelay((ms > portTICK_PERIOD_MS ? ms/ portTICK_PERIOD_MS : 1))
#define SC035HGS_SUPPORT_NUM CONFIG_CAMERA_SC035HGS_MAX_SUPPORT

static const uint8_t s_sc035hgs_exp_min = 0x08;
static const char *TAG = "sc035hgs";

// total gain = analog_gain x digital_gain x 1000(To avoid decimal points, the final abs_gain is multiplied by 1000.)
static const uint32_t sc035hgs_total_gain_val_map[] = {
    //1x
    1000,
    1062,
    1125,
    1187,
    1250,
    1312,
    1375,
    1437,
    1500,
    1562,
    1625,
    1687,
    1750,
    1812,
    1875,
    1937,
    //2x
    2000,
    2125,
    2250,
    2375,
    2500,
    2625,
    2750,
    2875,
    3000,
    3125,
    3250,
    3375,
    3500,
    3625,
    3750,
    3875,
    //4x
    4000,
    4250,
    4500,
    4750,
    5000,
    5250,
    5500,
    5750,
    6000,
    6250,
    6500,
    6750,
    7000,
    7250,
    7500,
    7750,
    //8x
    8000,
    8500,
    9000,
    9500,
    10000,
    10500,
    11000,
    11500,
    12000,
    12500,
    13000,
    13500,
    14000,
    14500,
    15000,
    15500,
    //16x
    16468,
    17437,
    18406,
    19375,
    20343,
    21312,
    22281,
    23250,
    24218,
    25187,
    26156,
    27125,
    28093,
    29062,
    30031,
    31000,
    32937,
};

// SC035HGS Gain map format: [ANG_FINE(0x3e09), ANG_COARSE(0x3e08), DIG_FINE(0x3e07), DIG_COARSE(0x3e06)]
static const sc035hgs_gain_t sc035hgs_gain_map[] = {
    // 1x
    {0x10, 0x00, 0x80, 0x00},
    {0x11, 0x00, 0x80, 0x00},
    {0x12, 0x00, 0x80, 0x00},
    {0x13, 0x00, 0x80, 0x00},
    {0x14, 0x00, 0x80, 0x00},
    {0x15, 0x00, 0x80, 0x00},
    {0x16, 0x00, 0x80, 0x00},
    {0x17, 0x00, 0x80, 0x00},
    {0x18, 0x00, 0x80, 0x00},
    {0x19, 0x00, 0x80, 0x00},
    {0x1a, 0x00, 0x80, 0x00},
    {0x1b, 0x00, 0x80, 0x00},
    {0x1c, 0x00, 0x80, 0x00},
    {0x1d, 0x00, 0x80, 0x00},
    {0x1e, 0x00, 0x80, 0x00},
    {0x1f, 0x00, 0x80, 0x00},
    // 2x
    {0x10, 0x01, 0x80, 0x00},
    {0x11, 0x01, 0x80, 0x00},
    {0x12, 0x01, 0x80, 0x00},
    {0x13, 0x01, 0x80, 0x00},
    {0x14, 0x01, 0x80, 0x00},
    {0x15, 0x01, 0x80, 0x00},
    {0x16, 0x01, 0x80, 0x00},
    {0x17, 0x01, 0x80, 0x00},
    {0x18, 0x01, 0x80, 0x00},
    {0x19, 0x01, 0x80, 0x00},
    {0x1a, 0x01, 0x80, 0x00},
    {0x1b, 0x01, 0x80, 0x00},
    {0x1c, 0x01, 0x80, 0x00},
    {0x1d, 0x01, 0x80, 0x00},
    {0x1e, 0x01, 0x80, 0x00},
    {0x1f, 0x01, 0x80, 0x00},
    // 4x
    {0x10, 0x03, 0x80, 0x00},
    {0x11, 0x03, 0x80, 0x00},
    {0x12, 0x03, 0x80, 0x00},
    {0x13, 0x03, 0x80, 0x00},
    {0x14, 0x03, 0x80, 0x00},
    {0x15, 0x03, 0x80, 0x00},
    {0x16, 0x03, 0x80, 0x00},
    {0x17, 0x03, 0x80, 0x00},
    {0x18, 0x03, 0x80, 0x00},
    {0x19, 0x03, 0x80, 0x00},
    {0x1a, 0x03, 0x80, 0x00},
    {0x1b, 0x03, 0x80, 0x00},
    {0x1c, 0x03, 0x80, 0x00},
    {0x1d, 0x03, 0x80, 0x00},
    {0x1e, 0x03, 0x80, 0x00},
    {0x1f, 0x03, 0x80, 0x00},
    // 8x
    {0x10, 0x07, 0x80, 0x00},
    {0x11, 0x07, 0x80, 0x00},
    {0x12, 0x07, 0x80, 0x00},
    {0x13, 0x07, 0x80, 0x00},
    {0x14, 0x07, 0x80, 0x00},
    {0x15, 0x07, 0x80, 0x00},
    {0x16, 0x07, 0x80, 0x00},
    {0x17, 0x07, 0x80, 0x00},
    {0x18, 0x07, 0x80, 0x00},
    {0x19, 0x07, 0x80, 0x00},
    {0x1a, 0x07, 0x80, 0x00},
    {0x1b, 0x07, 0x80, 0x00},
    {0x1c, 0x07, 0x80, 0x00},
    {0x1d, 0x07, 0x80, 0x00},
    {0x1e, 0x07, 0x80, 0x00},
    {0x1f, 0x07, 0x80, 0x00},
    // 16x
    {0x1f, 0x07, 0x88, 0x00}, // 16.46875
    {0x1f, 0x07, 0x90, 0x00}, // 17.4375
    {0x1f, 0x07, 0x98, 0x00}, // 18.40625
    {0x1f, 0x07, 0xa0, 0x00}, // 19.375
    {0x1f, 0x07, 0xa8, 0x00}, // 20.34375
    {0x1f, 0x07, 0xb0, 0x00}, // 21.3125
    {0x1f, 0x07, 0xb8, 0x00}, // 22.28125
    {0x1f, 0x07, 0xc0, 0x00}, // 23.25
    {0x1f, 0x07, 0xc8, 0x00}, // 24.21875
    {0x1f, 0x07, 0xd0, 0x00}, // 25.1875
    {0x1f, 0x07, 0xd8, 0x00}, // 26.15625
    {0x1f, 0x07, 0xe0, 0x00}, // 27.125
    {0x1f, 0x07, 0xe8, 0x00}, // 28.09375
    {0x1f, 0x07, 0xf0, 0x00}, // 29.0625
    {0x1f, 0x07, 0xf8, 0x00}, // 30.03125
    {0x1f, 0x07, 0x80, 0x01}, // 31.0000
    {0x1f, 0x07, 0x88, 0x01}, // 32.9375
};

#if CONFIG_SOC_MIPI_CSI_SUPPORTED
static const esp_cam_sensor_isp_info_t sc035hgs_isp_info_mipi[] = {
    {
        .isp_v1_info = {
            .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
            .pclk = 50056704,
            .vts = 0x394,
            .hts = 0x470,
            .tline_ns = 1421,
            .gain_def = 0,
            .exp_def = 0x18f,
            .bayer_type = ESP_CAM_SENSOR_BAYER_BGGR,
        }
    },
    {
        .isp_v1_info = {
            .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
            .pclk = 45000000,
            .vts = 0x210,
            .hts = 0x554,
            .tline_ns = 986,
            .gain_def = 0,
            .exp_def = 0x18f,
            .bayer_type = ESP_CAM_SENSOR_BAYER_BGGR,
        },
    },
    {
        .isp_v1_info = {
            .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
            .pclk = 72000000,
            .vts = 0x4f3,
            .hts = 0x470,
            .tline_ns = 986,
            .gain_def = 0,
            .exp_def = 0x18f,
            .bayer_type = ESP_CAM_SENSOR_BAYER_BGGR,
        },
    },
    {
        .isp_v1_info = {
            .version = SENSOR_ISP_INFO_VERSION_DEFAULT,
            .pclk = 72000000,
            .vts = 0x27a,
            .hts = 0x470,
            .tline_ns = 986,
            .gain_def = 0,
            .exp_def = 0x18f,
            .bayer_type = ESP_CAM_SENSOR_BAYER_BGGR,
        },
    }
};

static const esp_cam_sensor_format_t sc035hgs_format_info_mipi[] = {
    {
        .name = "MIPI_1lane_20Minput_raw10_640x480_48fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW10,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 20000000,
        .width = 640,
        .height = 480,
        .regs = mipi_20Minput_1lane_640x480_raw10_48fps,
        .regs_size = ARRAY_SIZE(mipi_20Minput_1lane_640x480_raw10_48fps),
        .fps = 48,
        .isp_info = &sc035hgs_isp_info_mipi[0],
        .mipi_info = {
            .mipi_clk = 500000000,
            .lane_num = 1,
            .line_sync_en = false,
        },
        .reserved = NULL,
    },
    {
        .name = "MIPI_1lane_20Minput_raw10_640x480_120fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW10,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 640,
        .height = 480,
        .regs = mipi_24Minput_1lane_640x480_raw10_linear_120fps,
        .regs_size = ARRAY_SIZE(mipi_24Minput_1lane_640x480_raw10_linear_120fps),
        .fps = 120,
        .isp_info = &sc035hgs_isp_info_mipi[1],
        .mipi_info = {
            .mipi_clk = 425000000,
            .lane_num = 1,
            .line_sync_en = false,
        },
        .reserved = NULL,
    },
    {
        .name = "MIPI_2lane_24Minput_raw8_640x480_50fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW8,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 640,
        .height = 480,
        .regs = mipi_24Minput_2lane_640x480_raw8_linear_50fps,
        .regs_size = ARRAY_SIZE(mipi_24Minput_2lane_640x480_raw8_linear_50fps),
        .fps = 50,
        .isp_info = &sc035hgs_isp_info_mipi[2],
        .mipi_info = {
            .mipi_clk = 288000000,
            .lane_num = 2,
            .line_sync_en = false,
        },
        .reserved = NULL,
    },
    {
        .name = "MIPI_2lane_24Minput_raw8_640x480_100fps",
        .format = ESP_CAM_SENSOR_PIXFORMAT_RAW8,
        .port = ESP_CAM_SENSOR_MIPI_CSI,
        .xclk = 24000000,
        .width = 640,
        .height = 480,
        .regs = mipi_24Minput_2lane_640x480_raw8_linear_100fps,
        .regs_size = ARRAY_SIZE(mipi_24Minput_2lane_640x480_raw8_linear_100fps),
        .fps = 100,
        .isp_info = &sc035hgs_isp_info_mipi[3],
        .mipi_info = {
            .mipi_clk = 288000000,
            .lane_num = 2,
            .line_sync_en = false,
        },
        .reserved = NULL,
    }
};
#endif

static esp_err_t sc035hgs_read(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t *read_buf)
{
    return esp_sccb_transmit_receive_reg_a16v8(sccb_handle, reg, read_buf);
}

static esp_err_t sc035hgs_write(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t data)
{
    return esp_sccb_transmit_reg_a16v8(sccb_handle, reg, data);
}

static esp_err_t sc035hgs_set_reg_bits(esp_sccb_io_handle_t sccb_handle, uint16_t reg, uint8_t offset, uint8_t length, uint8_t value)
{
    esp_err_t ret = ESP_OK;
    uint8_t reg_data = 0;

    ret = sc035hgs_read(sccb_handle, reg, &reg_data);
    if (ret != ESP_OK) {
        return ret;
    }
    uint8_t mask = ((1 << length) - 1) << offset;
    value = (reg_data & ~mask) | ((value << offset) & mask);
    ret = sc035hgs_write(sccb_handle, reg, value);
    return ret;
}

/* write a array of registers  */
static esp_err_t sc035hgs_write_array(esp_sccb_io_handle_t sccb_handle, sc035hgs_reginfo_t *regarray, size_t regs_size)
{
    int i = 0;
    esp_err_t ret = ESP_OK;
    while ((ret == ESP_OK) && (i < regs_size)) {
        if (regarray[i].reg != SC035HGS_REG_DELAY) {
            ret = sc035hgs_write(sccb_handle, regarray[i].reg, regarray[i].val);
        } else {
            delay_ms(regarray[i].val);
        }
        i++;
    }
    ESP_LOGD(TAG, "Set array done[i=%d]", i);
    return ret;
}

static esp_err_t sc035hgs_set_test_pattern(esp_cam_sensor_device_t *dev, int enable)
{
    return sc035hgs_set_reg_bits(dev->sccb_handle, 0X4501, 3, 1, enable ? 0x01 : 0x00);
}

static esp_err_t sc035hgs_hw_reset(esp_cam_sensor_device_t *dev)
{
    if (dev->reset_pin >= 0) {
        gpio_set_level(dev->reset_pin, 0);
        delay_ms(10);
        gpio_set_level(dev->reset_pin, 1);
        delay_ms(10);
    }
    return ESP_OK;
}

static esp_err_t sc035hgs_soft_reset(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = sc035hgs_set_reg_bits(dev->sccb_handle, 0x0103, 0, 1, 0x01);
    delay_ms(5);
    return ret;
}

static esp_err_t sc035hgs_get_sensor_id(esp_cam_sensor_device_t *dev, esp_cam_sensor_id_t *id)
{
    esp_err_t ret = ESP_FAIL;
    uint8_t pid_h, pid_l;

    ret = sc035hgs_read(dev->sccb_handle, SC035HGS_REG_ID_HIGH, &pid_h);
    if (ret != ESP_OK) {
        return ret;
    }
    ret = sc035hgs_read(dev->sccb_handle, SC035HGS_REG_ID_LOW, &pid_l);
    if (ret != ESP_OK) {
        return ret;
    }
    id->pid = (pid_h << 8) | pid_l;

    return ret;
}

static esp_err_t sc035hgs_set_stream(esp_cam_sensor_device_t *dev, int enable)
{
    esp_err_t ret = ESP_FAIL;

    ret = sc035hgs_write(dev->sccb_handle, SC035HGS_REG_SLEEP_MODE, enable ? 0x01 : 0x00);
    if (enable) {
        ret |= sc035hgs_write(dev->sccb_handle, 0x4418, 0x0a);
        ret |= sc035hgs_write(dev->sccb_handle, 0x363d, 0x10);
        ret |= sc035hgs_write(dev->sccb_handle, 0x4419, 0x80);
    }

    dev->stream_status = enable;
    ESP_LOGD(TAG, "Stream=%d", enable);

    return ret;
}

static esp_err_t sc035hgs_set_mirror(esp_cam_sensor_device_t *dev, int enable)
{
    return sc035hgs_set_reg_bits(dev->sccb_handle, 0x3221, 1, 2, enable ? 0x03 : 0x00);
}

static esp_err_t sc035hgs_set_vflip(esp_cam_sensor_device_t *dev, int enable)
{
    return sc035hgs_set_reg_bits(dev->sccb_handle, 0x3221, 5, 2, enable ? 0x03 : 0x00);
}

static esp_err_t sc035hgs_set_exp_val(esp_cam_sensor_device_t *dev, uint32_t u32_val)
{
    esp_err_t ret;
    struct sc035hgs_cam *cam_sc035hgs = (struct sc035hgs_cam *)dev->priv;
    uint32_t value_buf = MAX(u32_val, s_sc035hgs_exp_min);
    value_buf = MIN(value_buf, cam_sc035hgs->sc035hgs_para.exposure_max);

    ESP_LOGD(TAG, "set exposure 0x%" PRIx32, value_buf);

    ret = sc035hgs_write(dev->sccb_handle, SC035HGS_REG_SHUTTER_TIME_H, SC035HGS_FETCH_EXP_H(u32_val));
    ret |= sc035hgs_write(dev->sccb_handle, SC035HGS_REG_SHUTTER_TIME_L, SC035HGS_FETCH_EXP_L(u32_val));
    if (ret == ESP_OK) {
        cam_sc035hgs->sc035hgs_para.exposure_val = value_buf;
    }
    return ret;
}

static esp_err_t sc035hgs_set_total_gain_val(esp_cam_sensor_device_t *dev, uint32_t u32_val)
{
    esp_err_t ret;
    struct sc035hgs_cam *cam_sc035hgs = (struct sc035hgs_cam *)dev->priv;

    ESP_LOGD(TAG, "again_fine %" PRIx8 ", again_coarse %" PRIx8 ", dgain_fine %" PRIx8 ", dgain_coarse %" PRIx8, sc035hgs_gain_map[u32_val].again_fine,
             sc035hgs_gain_map[u32_val].again_coarse,
             sc035hgs_gain_map[u32_val].dgain_fine,
             sc035hgs_gain_map[u32_val].dgain_coarse);

    ret = sc035hgs_write(dev->sccb_handle,
                         SC035HGS_REG_FINE_AGAIN,
                         sc035hgs_gain_map[u32_val].again_fine);

    ret |= sc035hgs_set_reg_bits(dev->sccb_handle,
                                 SC035HGS_REG_COARSE_AGAIN, 2, 3,
                                 sc035hgs_gain_map[u32_val].again_coarse);

    ret |= sc035hgs_write(dev->sccb_handle,
                          SC035HGS_REG_FINE_DGAIN,
                          sc035hgs_gain_map[u32_val].dgain_fine);

    ret |= sc035hgs_set_reg_bits(dev->sccb_handle,
                                 SC035HGS_REG_COARSE_DGAIN, 0, 2,
                                 sc035hgs_gain_map[u32_val].dgain_coarse);
    if (ret == ESP_OK) {
        cam_sc035hgs->sc035hgs_para.gain_index = u32_val;
    }
    return ret;
}

static esp_err_t sc035hgs_query_para_desc(esp_cam_sensor_device_t *dev, esp_cam_sensor_param_desc_t *qdesc)
{
    esp_err_t ret = ESP_OK;
    switch (qdesc->id) {
    case ESP_CAM_SENSOR_EXPOSURE_VAL:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = s_sc035hgs_exp_min;
        qdesc->number.maximum = dev->cur_format->isp_info->isp_v1_info.vts - SC035HGS_EXP_MAX_OFFSET; // max = VTS-6 = height+vblank-6, so when update vblank, exposure_max must be updated
        qdesc->number.step = 1;
        qdesc->default_value = dev->cur_format->isp_info->isp_v1_info.exp_def;
        break;
    case ESP_CAM_SENSOR_EXPOSURE_US:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_NUMBER;
        qdesc->number.minimum = MAX(0x01, EXPOSURE_SC035HGS_TO_V4L2(s_sc035hgs_exp_min, dev->cur_format)); // The minimum value must be greater than 1
        qdesc->number.maximum = EXPOSURE_SC035HGS_TO_V4L2((dev->cur_format->isp_info->isp_v1_info.vts - SC035HGS_EXP_MAX_OFFSET), dev->cur_format);
        qdesc->number.step = MAX(0x01, EXPOSURE_SC035HGS_TO_V4L2(0x01, dev->cur_format));
        qdesc->default_value = EXPOSURE_SC035HGS_TO_V4L2((dev->cur_format->isp_info->isp_v1_info.exp_def), dev->cur_format);
        break;
    case ESP_CAM_SENSOR_GAIN:
        qdesc->type = ESP_CAM_SENSOR_PARAM_TYPE_ENUMERATION;
        qdesc->enumeration.count = ARRAY_SIZE(sc035hgs_total_gain_val_map);
        qdesc->enumeration.elements = sc035hgs_total_gain_val_map;
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

static esp_err_t sc035hgs_get_para_value(esp_cam_sensor_device_t *dev, uint32_t id, void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;
    struct sc035hgs_cam *cam_sc035hgs = (struct sc035hgs_cam *)dev->priv;
    switch (id) {
    case ESP_CAM_SENSOR_EXPOSURE_VAL: {
        *(uint32_t *)arg = cam_sc035hgs->sc035hgs_para.exposure_val;
        break;
    }
    case ESP_CAM_SENSOR_GAIN: {
        *(uint32_t *)arg = cam_sc035hgs->sc035hgs_para.gain_index;
        break;
    }
    default: {
        ret = ESP_ERR_NOT_SUPPORTED;
        break;
    }
    }
    return ret;
}

static esp_err_t sc035hgs_set_para_value(esp_cam_sensor_device_t *dev, uint32_t id, const void *arg, size_t size)
{
    esp_err_t ret = ESP_OK;

    switch (id) {
    case ESP_CAM_SENSOR_EXPOSURE_VAL: {
        uint32_t u32_val = *(uint32_t *)arg;
        ESP_LOGD(TAG, "set exposure 0x%" PRIx32, u32_val);
        ret = sc035hgs_set_exp_val(dev, u32_val);
        break;
    }
    case ESP_CAM_SENSOR_EXPOSURE_US: {
        uint32_t u32_val = *(uint32_t *)arg;
        uint32_t ori_exp = EXPOSURE_V4L2_TO_SC035HGS(u32_val, dev->cur_format);
        ret = sc035hgs_set_exp_val(dev, ori_exp);
        break;
    }
    case ESP_CAM_SENSOR_GAIN: {
        uint32_t u32_val = *(uint32_t *)arg;
        ret = sc035hgs_set_total_gain_val(dev, u32_val);
        break;
    }
    case ESP_CAM_SENSOR_GROUP_EXP_GAIN: {
        esp_cam_sensor_gh_exp_gain_t *value = (esp_cam_sensor_gh_exp_gain_t *)arg;
        uint32_t ori_exp = 0;
        if (value->exposure_us != 0) {
            ori_exp = EXPOSURE_V4L2_TO_SC035HGS(value->exposure_us, dev->cur_format);
        } else if (value->exposure_val != 0) {
            ori_exp = value->exposure_val;
        } else {
            ret = ESP_ERR_INVALID_ARG;
            break;
        }
        ret = sc035hgs_set_exp_val(dev, ori_exp);
        ret |= sc035hgs_set_total_gain_val(dev, value->gain_index);
        break;
    }
    case ESP_CAM_SENSOR_VFLIP: {
        int *value = (int *)arg;

        ret = sc035hgs_set_vflip(dev, *value);
        break;
    }
    case ESP_CAM_SENSOR_HMIRROR: {
        int *value = (int *)arg;

        ret = sc035hgs_set_mirror(dev, *value);
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

static esp_err_t sc035hgs_query_support_formats(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_array_t *formats)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, formats);
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
    if (dev->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
        formats->count = ARRAY_SIZE(sc035hgs_format_info_mipi);
        formats->format_array = &sc035hgs_format_info_mipi[0];
    }
#endif

    return ESP_OK;
}

static esp_err_t sc035hgs_query_support_capability(esp_cam_sensor_device_t *dev, esp_cam_sensor_capability_t *sensor_cap)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, sensor_cap);

    sensor_cap->fmt_yuv = 1;
    return 0;
}

static esp_err_t sc035hgs_set_format(esp_cam_sensor_device_t *dev, const esp_cam_sensor_format_t *format)
{
    ESP_CAM_SENSOR_NULL_POINTER_CHECK(TAG, dev);

    esp_err_t ret = ESP_OK;
    struct sc035hgs_cam *cam_sc035hgs = (struct sc035hgs_cam *)dev->priv;
    /* Depending on the interface type, an available configuration is automatically loaded.
    You can set the output format of the sensor without using query_format().*/
    if (format == NULL) {
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
        if (dev->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
            format = &sc035hgs_format_info_mipi[CONFIG_CAMERA_SC035HGS_MIPI_IF_FORMAT_INDEX_DEFAULT];
        }
#endif
    }

    ret = sc035hgs_write_array(dev->sccb_handle, (sc035hgs_reginfo_t *)format->regs, format->regs_size);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Set format regs fail");
        return ESP_CAM_SENSOR_ERR_FAILED_SET_FORMAT;
    }
    ESP_LOGD(TAG, "Set format %s", format->name);
    dev->cur_format = format;
    // init para
    cam_sc035hgs->sc035hgs_para.exposure_val = dev->cur_format->isp_info->isp_v1_info.exp_def;
    cam_sc035hgs->sc035hgs_para.gain_index = dev->cur_format->isp_info->isp_v1_info.gain_def;
    cam_sc035hgs->sc035hgs_para.exposure_max = dev->cur_format->isp_info->isp_v1_info.vts - SC035HGS_EXP_MAX_OFFSET;

    return ret;
}

static esp_err_t sc035hgs_get_format(esp_cam_sensor_device_t *dev, esp_cam_sensor_format_t *format)
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

static esp_err_t sc035hgs_priv_ioctl(esp_cam_sensor_device_t *dev, uint32_t cmd, void *arg)
{
    esp_err_t ret = ESP_OK;
    uint8_t regval;
    esp_cam_sensor_reg_val_t *sensor_reg;
    SC035HGS_IO_MUX_LOCK(mux);

    switch (cmd) {
    case ESP_CAM_SENSOR_IOC_HW_RESET:
        ret = sc035hgs_hw_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_SW_RESET:
        ret = sc035hgs_soft_reset(dev);
        break;
    case ESP_CAM_SENSOR_IOC_S_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = sc035hgs_write(dev->sccb_handle, sensor_reg->regaddr, sensor_reg->value);
        break;
    case ESP_CAM_SENSOR_IOC_S_STREAM:
        ret = sc035hgs_set_stream(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_S_TEST_PATTERN:
        ret = sc035hgs_set_test_pattern(dev, *(int *)arg);
        break;
    case ESP_CAM_SENSOR_IOC_G_REG:
        sensor_reg = (esp_cam_sensor_reg_val_t *)arg;
        ret = sc035hgs_read(dev->sccb_handle, sensor_reg->regaddr, &regval);
        if (ret == ESP_OK) {
            sensor_reg->value = regval;
        }
        break;
    case ESP_CAM_SENSOR_IOC_G_CHIP_ID:
        ret = sc035hgs_get_sensor_id(dev, arg);
        break;
    default:
        break;
    }

    SC035HGS_IO_MUX_UNLOCK(mux);
    return ret;
}

static esp_err_t sc035hgs_power_on(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        SC035HGS_ENABLE_OUT_XCLK(dev->xclk_pin, dev->xclk_freq_hz);
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

static esp_err_t sc035hgs_power_off(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = ESP_OK;

    if (dev->xclk_pin >= 0) {
        SC035HGS_DISABLE_OUT_XCLK(dev->xclk_pin);
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

static esp_err_t sc035hgs_delete(esp_cam_sensor_device_t *dev)
{
    ESP_LOGD(TAG, "del sc035hgs (%p)", dev);
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

static const esp_cam_sensor_ops_t sc035hgs_ops = {
    .query_para_desc = sc035hgs_query_para_desc,
    .get_para_value = sc035hgs_get_para_value,
    .set_para_value = sc035hgs_set_para_value,
    .query_support_formats = sc035hgs_query_support_formats,
    .query_support_capability = sc035hgs_query_support_capability,
    .set_format = sc035hgs_set_format,
    .get_format = sc035hgs_get_format,
    .priv_ioctl = sc035hgs_priv_ioctl,
    .del = sc035hgs_delete
};

esp_cam_sensor_device_t *sc035hgs_detect(esp_cam_sensor_config_t *config)
{
    esp_cam_sensor_device_t *dev = NULL;
    struct sc035hgs_cam *cam_sc035hgs;

    if (config == NULL) {
        return NULL;
    }

    dev = calloc(1, sizeof(esp_cam_sensor_device_t));
    if (dev == NULL) {
        ESP_LOGE(TAG, "No memory for camera");
        return NULL;
    }

    cam_sc035hgs = heap_caps_calloc(1, sizeof(struct sc035hgs_cam), MALLOC_CAP_DEFAULT);
    if (!cam_sc035hgs) {
        ESP_LOGE(TAG, "failed to calloc cam");
        free(dev);
        return NULL;
    }

    dev->name = (char *)SC035HGS_SENSOR_NAME;
    dev->sccb_handle = config->sccb_handle;
    dev->xclk_pin = config->xclk_pin;
    dev->reset_pin = config->reset_pin;
    dev->pwdn_pin = config->pwdn_pin;
    dev->sensor_port = config->sensor_port;
    dev->ops = &sc035hgs_ops;
    dev->priv = cam_sc035hgs;
#if CONFIG_SOC_MIPI_CSI_SUPPORTED
    if (config->sensor_port == ESP_CAM_SENSOR_MIPI_CSI) {
        dev->cur_format = &sc035hgs_format_info_mipi[CONFIG_CAMERA_SC035HGS_MIPI_IF_FORMAT_INDEX_DEFAULT];
    }
#endif

    // Configure sensor power, clock, and SCCB port
    if (sc035hgs_power_on(dev) != ESP_OK) {
        ESP_LOGE(TAG, "Camera power on failed");
        goto err_free_handler;
    }

    if (sc035hgs_get_sensor_id(dev, &dev->id) != ESP_OK) {
        ESP_LOGE(TAG, "Get sensor ID failed");
        goto err_free_handler;
    } else if (dev->id.pid != SC035HGS_PID) {
        ESP_LOGE(TAG, "Camera sensor is not SC035HGS, PID=0x%x", dev->id.pid);
        goto err_free_handler;
    }
    ESP_LOGI(TAG, "Detected Camera sensor PID=0x%x", dev->id.pid);

    return dev;

err_free_handler:
    sc035hgs_power_off(dev);
    free(dev->priv);
    free(dev);

    return NULL;
}

#if CONFIG_CAMERA_SC035HGS_AUTO_DETECT_MIPI_INTERFACE_SENSOR
ESP_CAM_SENSOR_DETECT_FN(sc035hgs_detect, ESP_CAM_SENSOR_MIPI_CSI, SC035HGS_SCCB_ADDR)
{
    ((esp_cam_sensor_config_t *)config)->sensor_port = ESP_CAM_SENSOR_MIPI_CSI;
    return sc035hgs_detect(config);
}
#endif
