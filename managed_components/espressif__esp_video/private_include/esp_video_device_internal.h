/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include "esp_err.h"
#include "esp_cam_sensor_types.h"
#include "esp_cam_motor_types.h"
#if CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE
#include "driver/jpeg_encode.h"
#endif
#include "esp_video_device.h"
#include "hal/cam_ctlr_types.h"
#include "esp_cam_ctlr_spi.h"
#include "linux/videodev2.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ISP video device configuration
 */
#if CONFIG_SOC_ISP_LSC_SUPPORTED && (CONFIG_ESP32P4_REV_MIN_FULL >= 100)
#define ESP_VIDEO_ISP_DEVICE_LSC    1       /*!< ISP video device enable LSC */
#endif

/**
 * @brief MIPI-CSI state
 */
typedef struct esp_video_csi_state {
    uint32_t lane_bitrate_mbps;             /*!< MIPI-CSI data lane bitrate in Mbps */
    uint8_t lane_num;                       /*!< MIPI-CSI data lane number */
    cam_ctlr_color_t in_color;              /*!< MIPI-CSI input(from camera sensor) data color format */
    cam_ctlr_color_t out_color;             /*!< MIPI-CSI output(based on ISP output) data color format */
    uint8_t out_bpp;                        /*!< MIPI-CSI output data color format bit per pixel */
    uint32_t in_fmt;                        /*!< MIPI-CSI input V4L2 format from sensor */
    bool line_sync;                         /*!< true: line has start and end packet; false. line has no start and end packet */
    bool bypass_isp;                        /*!< true: ISP directly output data from input port with processing. false: ISP output processed data by pipeline  */
    color_raw_element_order_t bayer_order;  /*!< Bayer order of raw data */
} esp_video_csi_state_t;

#ifdef CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
/**
 * @brief SPI video device configuration
 */
typedef struct esp_video_spi_device_config {
    spi_host_device_t spi_port;             /*!< SPI port */
    gpio_num_t spi_cs_pin;                  /*!< SPI CS pin */
    gpio_num_t spi_sclk_pin;                /*!< SPI SCLK pin */
    gpio_num_t spi_data0_io_pin;            /*!< SPI data0 I/O pin */
} esp_video_spi_device_config_t;
#endif

#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
/**
 * @brief USB UVC video device configuration
 */
typedef struct esp_video_usb_uvc_device_config {
    uint32_t uvc_dev_num;                   /*!< USB UVC devices number */

    uint32_t task_stack;                    /*!< USB UVC video device task stack size */
    uint8_t task_priority;                  /*!< USB UVC video device task priority */
    int8_t task_affinity;                   /*!< USB UVC video device task affinity, -1 means no affinity */
} esp_video_usb_uvc_device_config_t;
#endif

#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
/**
 * @brief Create MIPI CSI video device
 *
 * @param cam_dev camera sensor device
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_create_csi_video_device(esp_cam_sensor_device_t *cam_dev);

/**
 * @brief Destroy MIPI-CSI video device
 *
 * @param None
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_destroy_csi_video_device(void);

/**
 * @brief Get the sensor connected to MIPI-CSI video device
 *
 * @param None
 *
 * @return
 *      - Sensor pointer on success
 *      - NULL if failed
 */
esp_cam_sensor_device_t *esp_video_get_csi_video_device_sensor(void);

/**
 * @brief Add camera motor device to MIPI-CSI video device
 *
 * @param motor_dev camera motor device
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_csi_video_device_add_motor(esp_cam_motor_device_t *motor_dev);

/**
 * @brief Get the motor connected to MIPI-CSI video device
 *
 * @param None
 *
 * @return
 *      - Motor pointer on success
 *      - NULL if failed
 */
esp_cam_motor_device_t *esp_video_get_csi_video_device_motor(void);
#endif

#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
/**
 * @brief Create DVP video device
 *
 * @param cam_dev camera sensor device
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_create_dvp_video_device(esp_cam_sensor_device_t *cam_dev);

/**
 * @brief Destroy DVP video device
 *
 * @param None
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_destroy_dvp_video_device(void);

/**
 * @brief Get the sensor connected to DVP video device
 *
 * @param None
 *
 * @return
 *      - Sensor pointer on success
 *      - NULL if failed
 */
esp_cam_sensor_device_t *esp_video_get_dvp_video_device_sensor(void);
#endif

#ifdef CONFIG_ESP_VIDEO_ENABLE_H264_VIDEO_DEVICE
/**
 * @brief Create H.264 video device
 *
 * @param hw_codec true: hardware H.264, false: software H.264(has not supported)
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_create_h264_video_device(bool hw_codec);

/**
 * @brief Destroy H.264 video device
 *
 * @param hw_codec true: hardware H.264, false: software H.264(has not supported)
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_destroy_h264_video_device(bool hw_codec);
#endif

#ifdef CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE
/**
 * @brief Create JPEG video device
 *
 * @param enc_handle JPEG encoder driver handle,
 *      - NULL, JPEG video device will create JPEG encoder driver handle by itself
 *      - Not null, JPEG video device will use this handle instead of creating JPEG encoder driver handle
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */

esp_err_t esp_video_create_jpeg_video_device(jpeg_encoder_handle_t enc_handle);

/**
 * @brief Destroy JPEG video device
 *
 * @param None
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_destroy_jpeg_video_device(void);
#endif

#if CONFIG_ESP_VIDEO_ENABLE_ISP
/**
 * @brief Start ISP process based on MIPI-CSI state
 *
 * @param state MIPI-CSI state object
 * @param state MIPI-CSI V4L2 capture format
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_isp_start_by_csi(const esp_video_csi_state_t *state, const struct v4l2_format *format);

/**
 * @brief Stop ISP process
 *
 * @param state MIPI-CSI state object
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_isp_stop(const esp_video_csi_state_t *state);

/**
 * @brief Enumerate ISP supported output pixel format
 *
 * @param state        MIPI-CSI state object
 * @param index        Enumerated number index
 * @param pixel_format Supported output pixel format
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_isp_enum_format(esp_video_csi_state_t *state, uint32_t index, uint32_t *pixel_format);

/**
 * @brief Check if input format is valid
 *
 * @param state  MIPI-CSI state object
 * @param format V4L2 format object
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_isp_check_format(esp_video_csi_state_t *state, const struct v4l2_format *format);

#if CONFIG_ESP_VIDEO_ENABLE_ISP_VIDEO_DEVICE
/**
 * @brief Create ISP video device
 *
 * @param None
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_create_isp_video_device(void);

/**
 * @brief Destroy ISP video device
 *
 * @param None
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_destroy_isp_video_device(void);
#endif
#endif

#ifdef CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
/**
 * @brief Create SPI video device
 *
 * @param cam_dev       Camera sensor device
 * @param config        SPI video device configuration
 * @param index         SPI video device index
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_create_spi_video_device(esp_cam_sensor_device_t *cam_dev, const esp_video_spi_device_config_t *config, uint8_t index);

/**
 * @brief Destroy SPI video device
 *
 * @param index         SPI video device index
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_destroy_spi_video_device(uint8_t index);

/**
 * @brief Get the sensor connected to SPI video device
 *
 * @param index         SPI video device index
 *
 * @return
 *      - Sensor pointer on success
 *      - NULL if failed
 */
esp_cam_sensor_device_t *esp_video_get_spi_video_device_sensor(uint8_t index);
#endif

#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
/**
 * @brief Install USB UVC video device driver
 *
 * @note USB Host Library must be initialized before calling this function.
 * @note This function will create a task to handle USB UVC video device.
 *
 * @param[in] cfg USB UVC video device configuration
 * @return esp_err_t
 */
esp_err_t esp_video_install_usb_uvc_driver(const esp_video_usb_uvc_device_config_t *cfg);

/**
 * @brief Uninstall USB UVC video device driver
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_uninstall_usb_uvc_driver(void);
#endif // CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE

#ifdef __cplusplus
}
#endif
