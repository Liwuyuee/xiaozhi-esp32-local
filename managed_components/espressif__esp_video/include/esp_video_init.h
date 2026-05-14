/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "driver/i2c_master.h"
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
#include "esp_cam_ctlr_dvp.h"
#endif
#if CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE
#include "driver/jpeg_encode.h"
#endif
#include "esp_cam_sensor_xclk.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE || \
    CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE || \
    CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
#define ESP_VIDEO_ENABLE_SCCB_DEVICE 1
#endif

/**
 * @brief SCCB initialization configuration
 */
#if ESP_VIDEO_ENABLE_SCCB_DEVICE
typedef struct esp_video_init_sccb_config {
    bool init_sccb;                             /*!< true:  SCCB I2C is not initialized and esp_video_init function will initialize SCCB I2C with given parameters i2c_config.
                                                     false: SCCB I2C is initialized and esp_video_init function can use i2c_handle directly */
    union {
        struct {
            uint8_t port;                       /*!< SCCB I2C port */
            gpio_num_t scl_pin;                 /*!< SCCB I2C SCL pin */
            gpio_num_t sda_pin;                 /*!< SCCB I2C SDA pin */
        } i2c_config;

        i2c_master_bus_handle_t i2c_handle;     /*!< SCCB I2C handle */
    };

    uint32_t freq;                              /*!< SCCB I2C frequency */
} esp_video_init_sccb_config_t;
#endif /* ESP_VIDEO_ENABLE_SCCB_DEVICE */

/**
 * @brief MIPI CSI initialization and camera sensor connection configuration
 */
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
typedef struct esp_video_init_csi_config {
    esp_video_init_sccb_config_t sccb_config;   /*!< Camera sensor SCCB configuration */

    gpio_num_t  reset_pin;                      /*!< Camera sensor reset pin, if hardware has no reset pin, set reset_pin to be -1 */
    gpio_num_t  pwdn_pin;                       /*!< Camera sensor power down pin, if hardware has no power down pin, set pwdn_pin to be -1 */
} esp_video_init_csi_config_t;
#endif /* CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE */

/**
 * @brief DVP initialization and camera sensor connection configuration
 */
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
typedef struct esp_video_init_dvp_config {
    esp_video_init_sccb_config_t sccb_config;   /*!< Camera sensor SCCB configuration */

    gpio_num_t  reset_pin;                      /*!< Camera sensor reset pin, if hardware has no reset pin, set reset_pin to be -1 */
    gpio_num_t  pwdn_pin;                       /*!< Camera sensor power down pin, if hardware has no power down pin, set pwdn_pin to be -1 */

    esp_cam_ctlr_dvp_pin_config_t dvp_pin;      /*!< DVP pin configuration */

    uint32_t xclk_freq;                         /*!< DVP hardware output clock frequency */
} esp_video_init_dvp_config_t;
#endif /* CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE */

/**
 * @brief SPI interface camera sensor connection configuration
 */
#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
typedef struct esp_video_init_spi_config {
    esp_video_init_sccb_config_t sccb_config;   /*!< Camera sensor SCCB configuration */

    uint8_t spi_port;                           /*!< SPI port */
    gpio_num_t spi_cs_pin;                      /*!< SPI CS pin */
    gpio_num_t spi_sclk_pin;                    /*!< SPI SCLK pin */
    gpio_num_t spi_data0_io_pin;                /*!< SPI data0 I/O pin */

    gpio_num_t  reset_pin;                      /*!< SPI interface camera sensor reset pin, if hardware has no reset pin, set reset_pin to be -1 */
    gpio_num_t  pwdn_pin;                       /*!< SPI interface camera sensor power down pin, if hardware has no power down pin, set pwdn_pin to be -1 */

    /* Output clock configuration for SPI interface camera sensor */

    esp_cam_sensor_xclk_source_t xclk_source;   /*!< Output clock resource for SPI interface camera sensor */
    uint32_t xclk_freq;                         /*!< Output clock frequency for SPI interface camera sensor */
    gpio_num_t xclk_pin;                        /*!< Output clock pin for SPI interface camera sensor */

#if CONFIG_CAMERA_XCLK_USE_LEDC
    /* This is used when xclk_source is ESP_CAM_SENSOR_XCLK_LEDC */

    struct {
        ledc_timer_t timer;                     /*!< The timer source of channel */
        ledc_clk_cfg_t clk_cfg;                 /*!< LEDC source clock from ledc_clk_cfg_t */
        ledc_channel_t channel;                 /*!< LEDC channel used for XCLK */
    } xclk_ledc_cfg;
#endif
} esp_video_init_spi_config_t;
#endif /* CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE */

/**
 * @brief UVC video device initialization configuration
 */
#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
typedef struct esp_video_init_usb_uvc_config {
    struct {
        uint8_t uvc_dev_num;                    /*!< USB UVC devices number */

        uint32_t task_stack;                    /*!< USB UVC video device task stack size */
        uint8_t task_priority;                  /*!< USB UVC video device task priority */
        int task_affinity;                      /*!< USB UVC video device task affinity, -1 means no affinity */
    } uvc;

    struct {
        bool init_usb_host_lib;                 /*!< Init USB Host Lib in esp_video */
        // USB Host Lib task configuration: Ignored if init_usb_host_lib is false
        uint32_t task_stack;                    /*!< USB Host Lib task stack size */
        uint8_t task_priority;                  /*!< USB Host Lib task priority */
        int task_affinity;                      /*!< USB Host Lib task affinity, -1 means no affinity */
    } usb;
} esp_video_init_usb_uvc_config_t;
#endif /* CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE */

/**
 * @brief JPEG initialization configuration
 */
#if CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE
typedef struct esp_video_init_jpeg_config {
    jpeg_encoder_handle_t enc_handle;           /*!< JPEG encoder driver handle:
                                                     - NULL, JPEG video device will create JPEG encoder driver handle by itself
                                                     - Not null, JPEG video device will use this handle instead of creating JPEG encoder driver handle */
} esp_video_init_jpeg_config_t;
#endif

/**
 * @brief Camera motor connection configuration
 */
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
typedef struct esp_video_init_cam_motor_config {
    esp_video_init_sccb_config_t sccb_config;   /*!< Camera motor SCCB configuration */

    gpio_num_t  reset_pin;                      /*!< Camera motor reset pin, if hardware has no reset pin, set reset_pin to be -1 */
    gpio_num_t  pwdn_pin;                       /*!< Camera motor power down pin, if hardware has no power down pin, set pwdn_pin to be -1 */
    gpio_num_t  signal_pin;                     /*!< Camera motor enable signal pin, if hardware has no signal pin, set signal to be -1 */
} esp_video_init_cam_motor_config_t;
#endif

/**
 * @brief Video hardware initialization configuration
 */
typedef struct esp_video_init_config {
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
    const esp_video_init_csi_config_t *csi;     /*!< MIPI CSI initialization configuration */
#endif
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
    const esp_video_init_dvp_config_t *dvp;     /*!< DVP initialization configuration array */
#endif
#if CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE
    const esp_video_init_jpeg_config_t *jpeg;   /*!< JPEG initialization configuration */
#endif
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
    const esp_video_init_cam_motor_config_t *cam_motor;     /*!< Camera motor initialization configuration */
#endif
#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
    const esp_video_init_spi_config_t *spi;     /*!< SPI initialization configuration */
#endif
#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
    const esp_video_init_usb_uvc_config_t *usb_uvc; /*!< USB UVC video device initialization configuration */
#endif
} esp_video_init_config_t;

/**
 * @brief Initialize video hardware and software, including I2C, MIPI CSI and so on.
 *
 * @param config video hardware configuration
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_init(const esp_video_init_config_t *config);

/**
 * @brief Deinitialize video hardware and software, including I2C, MIPI CSI and so on.
 *
 * @param None
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_deinit(void);

#ifdef __cplusplus
}
#endif
