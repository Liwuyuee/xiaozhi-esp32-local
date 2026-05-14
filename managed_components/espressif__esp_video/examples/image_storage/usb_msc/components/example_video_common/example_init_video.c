/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#include <string.h>
#include "esp_log.h"
#include "esp_check.h"
#include "example_video_common.h"
#include "esp_cam_sensor_xclk.h"

#if EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR
static const esp_video_init_csi_config_t s_csi_config = {
    .sccb_config = {
#if !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
        .init_sccb = true,
        .i2c_config = {
            .port      = EXAMPLE_MIPI_CSI_SCCB_I2C_PORT,
            .scl_pin   = EXAMPLE_MIPI_CSI_SCCB_I2C_SCL_PIN,
            .sda_pin   = EXAMPLE_MIPI_CSI_SCCB_I2C_SDA_PIN,
        },
#endif /* !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
        .freq = EXAMPLE_MIPI_CSI_SCCB_I2C_FREQ,
    },
    .reset_pin = EXAMPLE_MIPI_CSI_CAM_SENSOR_RESET_PIN,
    .pwdn_pin  = EXAMPLE_MIPI_CSI_CAM_SENSOR_PWDN_PIN,
};

#if EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR
static const esp_video_init_cam_motor_config_t s_cam_motor_config = {
    .sccb_config = {
#if !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
        .init_sccb = true,
        .i2c_config = {
            .port      = EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_PORT,
            .scl_pin   = EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_SCL_PIN,
            .sda_pin   = EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_SDA_PIN,
        },
#endif /* !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
        .freq      = EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_FREQ,
    },
    .reset_pin = EXAMPLE_MIPI_CSI_CAM_MOTOR_RESET_PIN,
    .pwdn_pin  = EXAMPLE_MIPI_CSI_CAM_MOTOR_PWDN_PIN,
    .signal_pin = EXAMPLE_MIPI_CSI_CAM_MOTOR_SIGNAL_PIN,
};
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR */
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR */

#if EXAMPLE_ENABLE_DVP_CAM_SENSOR
static const esp_video_init_dvp_config_t s_dvp_config = {
    .sccb_config = {
#if !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
        .init_sccb = true,
        .i2c_config = {
            .port      = EXAMPLE_DVP_SCCB_I2C_PORT,
            .scl_pin   = EXAMPLE_DVP_SCCB_I2C_SCL_PIN,
            .sda_pin   = EXAMPLE_DVP_SCCB_I2C_SDA_PIN,
        },
#endif /* !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
        .freq      = EXAMPLE_DVP_SCCB_I2C_FREQ,
    },
    .reset_pin = EXAMPLE_DVP_CAM_SENSOR_RESET_PIN,
    .pwdn_pin  = EXAMPLE_DVP_CAM_SENSOR_PWDN_PIN,
    .dvp_pin = {
        .data_width = CAM_CTLR_DATA_WIDTH_8,
        .data_io = {
            EXAMPLE_DVP_D0_PIN, EXAMPLE_DVP_D1_PIN, EXAMPLE_DVP_D2_PIN, EXAMPLE_DVP_D3_PIN,
            EXAMPLE_DVP_D4_PIN, EXAMPLE_DVP_D5_PIN, EXAMPLE_DVP_D6_PIN, EXAMPLE_DVP_D7_PIN,
        },
        .vsync_io = EXAMPLE_DVP_VSYNC_PIN,
        .de_io = EXAMPLE_DVP_DE_PIN,
        .pclk_io = EXAMPLE_DVP_PCLK_PIN,
        .xclk_io = EXAMPLE_DVP_XCLK_PIN,
    },
    .xclk_freq = EXAMPLE_DVP_XCLK_FREQ,
};
#endif /* EXAMPLE_ENABLE_DVP_CAM_SENSOR */

#if EXAMPLE_ENABLE_SPI_CAM_SENSOR
static const esp_video_init_spi_config_t s_spi_config[] = {
    {
        .sccb_config = {
#if !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
            .init_sccb = true,
            .i2c_config = {
                .port      = EXAMPLE_SPI_CAM_0_SCCB_I2C_PORT,
                .scl_pin   = EXAMPLE_SPI_CAM_0_SCCB_I2C_SCL_PIN,
                .sda_pin   = EXAMPLE_SPI_CAM_0_SCCB_I2C_SDA_PIN,
            },
#endif /* !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
            .freq      = EXAMPLE_SPI_CAM_0_SCCB_I2C_FREQ,
        },
        .reset_pin = EXAMPLE_SPI_CAM_0_SENSOR_RESET_PIN,
        .pwdn_pin  = EXAMPLE_SPI_CAM_0_SENSOR_PWDN_PIN,

        .spi_port = EXAMPLE_SPI_CAM_0_SPI_PORT,
        .spi_cs_pin = EXAMPLE_SPI_CAM_0_CS_PIN,
        .spi_sclk_pin = EXAMPLE_SPI_CAM_0_SCLK_PIN,
        .spi_data0_io_pin = EXAMPLE_SPI_CAM_0_DATA0_IO_PIN,

        .xclk_source = EXAMPLE_SPI_CAM_0_XCLK_RESOURCE,
        .xclk_pin = EXAMPLE_SPI_CAM_0_XCLK_PIN,
        .xclk_freq = EXAMPLE_SPI_CAM_0_XCLK_FREQ,
#if CONFIG_EXAMPLE_SPI_CAM_XCLK_USE_LEDC
        .xclk_ledc_cfg = {
            .timer = EXAMPLE_SPI_CAM_0_XCLK_TIMER,
            .clk_cfg = LEDC_AUTO_CLK,
            .channel = EXAMPLE_SPI_CAM_0_XCLK_TIMER_CHANNEL,
        },
#endif /* CONFIG_EXAMPLE_SPI_CAM_XCLK_USE_LEDC */
    },

#if EXAMPLE_ENABLE_SPI_CAM_1_SENSOR
    {
        .sccb_config = {
#if !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
            .init_sccb = true,
            .i2c_config = {
                .port = EXAMPLE_SPI_CAM_1_SCCB_I2C_PORT,
                .scl_pin = EXAMPLE_SPI_CAM_1_SCCB_I2C_SCL_PIN,
                .sda_pin = EXAMPLE_SPI_CAM_1_SCCB_I2C_SDA_PIN,
            },
#endif /* !CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
            .freq = EXAMPLE_SPI_CAM_1_SCCB_I2C_FREQ,
        },
        .reset_pin = EXAMPLE_SPI_CAM_1_SENSOR_RESET_PIN,
        .pwdn_pin = EXAMPLE_SPI_CAM_1_SENSOR_PWDN_PIN,

        .spi_port = EXAMPLE_SPI_CAM_1_SPI_PORT,
        .spi_cs_pin = EXAMPLE_SPI_CAM_1_CS_PIN,
        .spi_sclk_pin = EXAMPLE_SPI_CAM_1_SCLK_PIN,
        .spi_data0_io_pin = EXAMPLE_SPI_CAM_1_DATA0_IO_PIN,

        .xclk_source = EXAMPLE_SPI_CAM_1_XCLK_RESOURCE,
        .xclk_pin = EXAMPLE_SPI_CAM_1_XCLK_PIN,
        .xclk_freq = EXAMPLE_SPI_CAM_1_XCLK_FREQ,
#if CONFIG_EXAMPLE_SPI_CAM_1_XCLK_USE_LEDC
        .xclk_ledc_cfg = {
            .timer = EXAMPLE_SPI_CAM_1_XCLK_TIMER,
            .clk_cfg = LEDC_AUTO_CLK,
            .channel = EXAMPLE_SPI_CAM_1_XCLK_TIMER_CHANNEL,
        },
#endif /* CONFIG_EXAMPLE_SPI_CAM_1_XCLK_USE_LEDC */
    },
#endif /* EXAMPLE_ENABLE_SPI_CAM_1_SENSOR */
};
#endif /* EXAMPLE_ENABLE_SPI_CAM_SENSOR */

#if EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR
static const esp_video_init_usb_uvc_config_t s_usb_uvc_config = {
    .uvc = {
        .uvc_dev_num = CONFIG_EXAMPLE_USB_UVC_DEVICES_NUM,
        .task_stack = CONFIG_EXAMPLE_USB_UVC_TASK_STACK_SIZE,
        .task_priority = CONFIG_EXAMPLE_USB_UVC_TASK_PRIORITY,
        .task_affinity = CONFIG_EXAMPLE_USB_UVC_TASK_AFFINITY,
    },
    .usb = {
        .init_usb_host_lib = true,
        .task_stack = CONFIG_EXAMPLE_USB_LIB_TASK_STACK_SIZE,
        .task_priority = CONFIG_EXAMPLE_USB_LIB_TASK_PRIORITY,
        .task_affinity = CONFIG_EXAMPLE_USB_LIB_TASK_AFFINITY,
    },
};
#endif /* EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR */

static const esp_video_init_config_t s_cam_config = {
#if EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR
    .csi      = &s_csi_config,
#if EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR
    .cam_motor = &s_cam_motor_config,
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR */
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR */
#if EXAMPLE_ENABLE_DVP_CAM_SENSOR
    .dvp      = &s_dvp_config,
#endif /* EXAMPLE_ENABLE_DVP_CAM_SENSOR */
#if EXAMPLE_ENABLE_SPI_CAM_SENSOR
    .spi      = s_spi_config,
#endif /* EXAMPLE_ENABLE_SPI_CAM_SENSOR */
#if EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR
    .usb_uvc  = &s_usb_uvc_config,
#endif /* EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR */
};

#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
static const i2c_master_bus_config_t s_bus_config = {
    .i2c_port = EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP,
    .sda_io_num = EXAMPLE_SCCB_I2C_SDA_PIN_INIT_BY_APP,
    .scl_io_num = EXAMPLE_SCCB_I2C_SCL_PIN_INIT_BY_APP,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
};

static i2c_master_bus_handle_t s_i2cbus_handle;
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */

#if defined(EXAMPLE_MIPI_CSI_XCLK_PIN) && EXAMPLE_MIPI_CSI_XCLK_PIN > 0
static esp_cam_sensor_xclk_handle_t s_xclk_handle;
#endif /* defined(EXAMPLE_MIPI_CSI_XCLK_PIN) && EXAMPLE_MIPI_CSI_XCLK_PIN > 0 */

static bool s_is_init = false;
static const char *TAG = "example_init_video";

/**
 * @brief Initialize the video system
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_video_init(void)
{
    esp_err_t ret;

    if (s_is_init) {
        return ESP_OK;
    }

    const esp_video_init_config_t *cam_config_ptr = &s_cam_config;

#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
    ESP_RETURN_ON_ERROR(i2c_new_master_bus(&s_bus_config, &s_i2cbus_handle), TAG, "failed to initialize i2c bus");

#if EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR
    esp_video_init_csi_config_t csi_config = s_csi_config;
    csi_config.sccb_config.init_sccb = false;
    csi_config.sccb_config.i2c_handle = s_i2cbus_handle;

#if EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR
    esp_video_init_cam_motor_config_t cam_motor_config = s_cam_motor_config;
    cam_motor_config.sccb_config.init_sccb = false;
    cam_motor_config.sccb_config.i2c_handle = s_i2cbus_handle;
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR */
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR */
#if EXAMPLE_ENABLE_DVP_CAM_SENSOR
    esp_video_init_dvp_config_t dvp_config = s_dvp_config;
    dvp_config.sccb_config.init_sccb = false;
    dvp_config.sccb_config.i2c_handle = s_i2cbus_handle;
#endif /* EXAMPLE_ENABLE_DVP_CAM_SENSOR */
#if EXAMPLE_ENABLE_SPI_CAM_0_SENSOR
    esp_video_init_spi_config_t spi_config[ESP_VIDEO_SPI_DEVICE_NUM];

    memcpy(spi_config, s_spi_config, sizeof(esp_video_init_spi_config_t) * ESP_VIDEO_SPI_DEVICE_NUM);
    for (int i = 0; i < ESP_VIDEO_SPI_DEVICE_NUM; i++) {
        spi_config[i].sccb_config.init_sccb = false;
        spi_config[i].sccb_config.i2c_handle = s_i2cbus_handle;
    }
#endif /* EXAMPLE_ENABLE_SPI_CAM_0_SENSOR */

    esp_video_init_config_t cam_config = {
#if EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR
        .csi      = &csi_config,
#if EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR
        .cam_motor = &cam_motor_config,
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR */
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR */
#if EXAMPLE_ENABLE_DVP_CAM_SENSOR
        .dvp      = &dvp_config,
#endif /* EXAMPLE_ENABLE_DVP_CAM_SENSOR */
#if EXAMPLE_ENABLE_SPI_CAM_SENSOR
        .spi      = spi_config,
#endif /* EXAMPLE_ENABLE_SPI_CAM_SENSOR */
#if EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR
        .usb_uvc  = &s_usb_uvc_config,
#endif /* EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR */
    };

    cam_config_ptr = &cam_config;
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */

#if defined(EXAMPLE_MIPI_CSI_XCLK_PIN) && EXAMPLE_MIPI_CSI_XCLK_PIN > 0
    esp_cam_sensor_xclk_config_t cam_xclk_config = {
        .esp_clock_router_cfg = {
            .xclk_pin = EXAMPLE_MIPI_CSI_XCLK_PIN,
            .xclk_freq_hz = EXAMPLE_MIPI_CSI_XCLK_FREQ,
        }
    };

    ESP_LOGI(TAG, "MIPI-CSI xclk pin=%d, freq=%d", EXAMPLE_MIPI_CSI_XCLK_PIN, EXAMPLE_MIPI_CSI_XCLK_FREQ);

    ESP_GOTO_ON_ERROR(esp_cam_sensor_xclk_allocate(ESP_CAM_SENSOR_XCLK_ESP_CLOCK_ROUTER, &s_xclk_handle), failed_0, TAG, "failed to allocate xclk");
    ESP_GOTO_ON_ERROR(esp_cam_sensor_xclk_start(s_xclk_handle, &cam_xclk_config), failed_1, TAG, "failed to start xclk");
#endif /* defined(EXAMPLE_MIPI_CSI_XCLK_PIN) && EXAMPLE_MIPI_CSI_XCLK_PIN > 0 */

#if EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR
    ESP_LOGI(TAG, "MIPI-CSI camera sensor I2C port=%d, scl_pin=%d, sda_pin=%d, freq=%d",
             EXAMPLE_MIPI_CSI_SCCB_I2C_PORT,
             EXAMPLE_MIPI_CSI_SCCB_I2C_SCL_PIN,
             EXAMPLE_MIPI_CSI_SCCB_I2C_SDA_PIN,
             EXAMPLE_MIPI_CSI_SCCB_I2C_FREQ);
#endif /* EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR */

#if EXAMPLE_ENABLE_DVP_CAM_SENSOR
    ESP_LOGI(TAG, "DVP camera sensor I2C port=%d, scl_pin=%d, sda_pin=%d, freq=%d",
             EXAMPLE_DVP_SCCB_I2C_PORT,
             EXAMPLE_DVP_SCCB_I2C_SCL_PIN,
             EXAMPLE_DVP_SCCB_I2C_SDA_PIN,
             EXAMPLE_DVP_SCCB_I2C_FREQ);
#endif /* EXAMPLE_ENABLE_DVP_CAM_SENSOR */

#if EXAMPLE_ENABLE_SPI_CAM_0_SENSOR
    ESP_LOGI(TAG, "SPI camera sensor 0 I2C port=%d, scl_pin=%d, sda_pin=%d, freq=%d",
             EXAMPLE_SPI_CAM_0_SCCB_I2C_PORT,
             EXAMPLE_SPI_CAM_0_SCCB_I2C_SCL_PIN,
             EXAMPLE_SPI_CAM_0_SCCB_I2C_SDA_PIN,
             EXAMPLE_SPI_CAM_0_SCCB_I2C_FREQ);
#if EXAMPLE_ENABLE_SPI_CAM_1_SENSOR
    ESP_LOGI(TAG, "SPI camera sensor 1 I2C port=%d, scl_pin=%d, sda_pin=%d, freq=%d",
             EXAMPLE_SPI_CAM_1_SCCB_I2C_PORT,
             EXAMPLE_SPI_CAM_1_SCCB_I2C_SCL_PIN,
             EXAMPLE_SPI_CAM_1_SCCB_I2C_SDA_PIN,
             EXAMPLE_SPI_CAM_1_SCCB_I2C_FREQ);
#endif /* EXAMPLE_ENABLE_SPI_CAM_1_SENSOR */
#endif /* EXAMPLE_ENABLE_SPI_CAM_0_SENSOR */

    ESP_GOTO_ON_ERROR(esp_video_init(cam_config_ptr), failed_2, TAG, "failed to initialize video");

    s_is_init = true;

    return ESP_OK;


failed_2:
#if EXAMPLE_MIPI_CSI_XCLK_PIN > 0
    esp_cam_sensor_xclk_stop(s_xclk_handle);
failed_1:
    esp_cam_sensor_xclk_free(s_xclk_handle);
    s_xclk_handle = NULL;
failed_0:
#endif
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
    i2c_del_master_bus(s_i2cbus_handle);
    s_i2cbus_handle = NULL;
#endif
    return ret;
}

/**
 * @brief Deinitialize the video system
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_video_deinit(void)
{
    esp_err_t ret = ESP_OK;

    if (!s_is_init) {
        return ESP_OK;
    }

    ESP_RETURN_ON_ERROR(esp_video_deinit(), TAG, "failed to deinitialize video");

#if EXAMPLE_MIPI_CSI_XCLK_PIN > 0
    ESP_RETURN_ON_ERROR(esp_cam_sensor_xclk_stop(s_xclk_handle), TAG, "failed to stop xclk");
    ESP_RETURN_ON_ERROR(esp_cam_sensor_xclk_free(s_xclk_handle), TAG, "failed to free xclk");
    s_xclk_handle = NULL;
#endif

#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
    ESP_RETURN_ON_ERROR(i2c_del_master_bus(s_i2cbus_handle), TAG, "failed to delete i2c bus");
    s_i2cbus_handle = NULL;
#endif

    s_is_init = false;

    return ret;
}
