/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#include "linux/videodev2.h"
#include "esp_video_device.h"
#include "esp_video_init.h"
#include "esp_video_ioctl.h"
#include "example_video_common_board.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SCCB(I2C) pre-initialized port configuration
 */
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
#define EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP              CONFIG_EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */

/**
 * @brief MIPI-CSI camera sensor common configuration
 */
#if CONFIG_EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR
#define EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR              1
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
#define EXAMPLE_MIPI_CSI_SCCB_I2C_PORT                  EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP
#else /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
#define EXAMPLE_MIPI_CSI_SCCB_I2C_PORT                  CONFIG_EXAMPLE_MIPI_CSI_SCCB_I2C_PORT
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */

#define EXAMPLE_MIPI_CSI_SCCB_I2C_FREQ                  CONFIG_EXAMPLE_MIPI_CSI_SCCB_I2C_FREQ

#if CONFIG_EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR
#define EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR              1
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
#define EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_PORT       EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP
#else /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
#define EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_PORT       CONFIG_EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_PORT
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */

#define EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_FREQ       CONFIG_EXAMPLE_MIPI_CSI_CAM_MOTOR_SCCB_I2C_FREQ
#endif /* CONFIG_EXAMPLE_ENABLE_MIPI_CSI_CAM_MOTOR */
#endif /* CONFIG_EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR */

/**
 * @brief DVP camera sensor common configuration
 */
#if CONFIG_EXAMPLE_ENABLE_DVP_CAM_SENSOR
#define EXAMPLE_ENABLE_DVP_CAM_SENSOR                   1
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
#define EXAMPLE_DVP_SCCB_I2C_PORT                       EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP
#else /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
#define EXAMPLE_DVP_SCCB_I2C_PORT                       CONFIG_EXAMPLE_DVP_SCCB_I2C_PORT
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */

#define EXAMPLE_DVP_SCCB_I2C_FREQ                       CONFIG_EXAMPLE_DVP_SCCB_I2C_FREQ


/**
 * @brief DVP clock frequency configuration
 */
#if (defined(EXAMPLE_DVP_XCLK_PIN) && EXAMPLE_DVP_XCLK_PIN >= 0)
#define EXAMPLE_DVP_XCLK_FREQ                           CONFIG_EXAMPLE_DVP_XCLK_FREQ
#else
#define EXAMPLE_DVP_XCLK_FREQ                           0
#endif /* EXAMPLE_DVP_XCLK_PIN >= 0 */
#endif /* CONFIG_EXAMPLE_ENABLE_DVP_CAM_SENSOR */

/**
 * @brief SPI camera sensor common configuration
 */
#if CONFIG_EXAMPLE_ENABLE_SPI_CAM_0_SENSOR
#define EXAMPLE_ENABLE_SPI_CAM_SENSOR                   1
#define EXAMPLE_ENABLE_SPI_CAM_0_SENSOR                 1
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
#define EXAMPLE_SPI_CAM_0_SCCB_I2C_PORT                 EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP
#else /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
#define EXAMPLE_SPI_CAM_0_SCCB_I2C_PORT                 CONFIG_EXAMPLE_SPI_CAM_0_SCCB_I2C_PORT
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
#define EXAMPLE_SPI_CAM_0_SCCB_I2C_FREQ                 CONFIG_EXAMPLE_SPI_CAM_0_SCCB_I2C_FREQ

/**
 * @brief SPI camera sensor SPI port configuration
 */
#define EXAMPLE_SPI_CAM_0_SPI_PORT                      CONFIG_EXAMPLE_SPI_CAM_0_SPI_PORT

/**
 * @brief SPI camera sensor clock resource configuration
 */
#if CONFIG_EXAMPLE_SPI_CAM_0_XCLK_USE_LEDC
#define EXAMPLE_SPI_CAM_0_XCLK_RESOURCE                 ESP_CAM_SENSOR_XCLK_LEDC
#elif CONFIG_EXAMPLE_SPI_CAM_0_XCLK_USE_CLOCK_ROUTER
#define EXAMPLE_SPI_CAM_0_XCLK_RESOURCE                 ESP_CAM_SENSOR_XCLK_ESP_CLOCK_ROUTER
#endif /* CONFIG_EXAMPLE_SPI_CAM_0_XCLK_USE_LEDC */

#if defined(EXAMPLE_SPI_CAM_0_XCLK_PIN) && EXAMPLE_SPI_CAM_0_XCLK_PIN >= 0
#define EXAMPLE_SPI_CAM_0_XCLK_FREQ                     CONFIG_EXAMPLE_SPI_CAM_0_XCLK_FREQ
#else
#define EXAMPLE_SPI_CAM_0_XCLK_FREQ                     0
#endif /* EXAMPLE_SPI_CAM_0_XCLK_PIN >= 0 */

#if CONFIG_EXAMPLE_SPI_CAM_0_XCLK_USE_LEDC
#define EXAMPLE_SPI_CAM_0_XCLK_TIMER                    CONFIG_EXAMPLE_SPI_CAM_0_XCLK_TIMER
#define EXAMPLE_SPI_CAM_0_XCLK_TIMER_CHANNEL            CONFIG_EXAMPLE_SPI_CAM_0_XCLK_TIMER_CHANNEL
#endif /* CONFIG_EXAMPLE_SPI_CAM_XCLK_USE_LEDC */

#if CONFIG_EXAMPLE_ENABLE_SPI_CAM_1_SENSOR
#define EXAMPLE_ENABLE_SPI_CAM_1_SENSOR                 1
#if CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP
#define EXAMPLE_SPI_CAM_1_SCCB_I2C_PORT                 EXAMPLE_SCCB_I2C_PORT_INIT_BY_APP
#else /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
#define EXAMPLE_SPI_CAM_1_SCCB_I2C_PORT                 CONFIG_EXAMPLE_SPI_CAM_1_SCCB_I2C_PORT
#endif /* CONFIG_EXAMPLE_SCCB_I2C_INIT_BY_APP */
#define EXAMPLE_SPI_CAM_1_SCCB_I2C_FREQ                 CONFIG_EXAMPLE_SPI_CAM_1_SCCB_I2C_FREQ

#define EXAMPLE_SPI_CAM_1_SPI_PORT                      CONFIG_EXAMPLE_SPI_CAM_1_SPI_PORT

#if CONFIG_EXAMPLE_SPI_CAM_1_XCLK_USE_LEDC
#define EXAMPLE_SPI_CAM_1_XCLK_RESOURCE                 ESP_CAM_SENSOR_XCLK_LEDC
#elif CONFIG_EXAMPLE_SPI_CAM_1_XCLK_USE_CLOCK_ROUTER
#define EXAMPLE_SPI_CAM_1_XCLK_RESOURCE                 ESP_CAM_SENSOR_XCLK_ESP_CLOCK_ROUTER
#endif /* CONFIG_EXAMPLE_SPI_CAM_1_XCLK_USE_LEDC */

#if defined(EXAMPLE_SPI_CAM_1_XCLK_PIN) && EXAMPLE_SPI_CAM_1_XCLK_PIN >= 0
#define EXAMPLE_SPI_CAM_1_XCLK_FREQ                     CONFIG_EXAMPLE_SPI_CAM_1_XCLK_FREQ
#else
#define EXAMPLE_SPI_CAM_1_XCLK_FREQ                     0
#endif /* EXAMPLE_SPI_CAM_1_XCLK_PIN >= 0 */

#if CONFIG_EXAMPLE_SPI_CAM_1_XCLK_USE_LEDC
#define EXAMPLE_SPI_CAM_1_XCLK_TIMER                    CONFIG_EXAMPLE_SPI_CAM_1_XCLK_TIMER
#define EXAMPLE_SPI_CAM_1_XCLK_TIMER_CHANNEL            CONFIG_EXAMPLE_SPI_CAM_1_XCLK_TIMER_CHANNEL
#endif /* CONFIG_EXAMPLE_SPI_CAM_1_XCLK_USE_LEDC */
#endif /* CONFIG_EXAMPLE_ENABLE_SPI_CAM_1_SENSOR */
#endif /* CONFIG_EXAMPLE_ENABLE_SPI_CAM_0_SENSOR */

/**
 * @brief USB-UVC camera sensor common configuration
 */
#if CONFIG_EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR
#define EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR               1
#endif

/**
 * @brief Example camera device path configuration
 */
#if EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR
#define EXAMPLE_CAM_DEV_PATH                            ESP_VIDEO_MIPI_CSI_DEVICE_NAME
#elif EXAMPLE_ENABLE_DVP_CAM_SENSOR
#define EXAMPLE_CAM_DEV_PATH                            ESP_VIDEO_DVP_DEVICE_NAME
#elif EXAMPLE_ENABLE_SPI_CAM_SENSOR
#define EXAMPLE_CAM_DEV_PATH                            ESP_VIDEO_SPI_DEVICE_NAME
#elif EXAMPLE_ENABLE_USB_UVC_CAM_SENSOR
#define EXAMPLE_CAM_DEV_PATH                            ESP_VIDEO_USB_UVC_DEVICE_NAME(0)
#else
#define EXAMPLE_CAM_DEV_PATH                            ESP_VIDEO_SPI_DEVICE_NAME
#endif /* CONFIG_EXAMPLE_ENABLE_MIPI_CSI_CAM_SENSOR */

/**
 * @brief Example encoder handle
 */
typedef void *example_encoder_handle_t;

/**
 * @brief Example encoder configuration
 */
typedef struct example_encoder_config {
    uint32_t width;             /**< Image width */
    uint32_t height;            /**< Image height */
    uint32_t pixel_format;      /**< Input image pixel format in V4L2 format */
    uint8_t quality;            /**< Image quality */
} example_encoder_config_t;

/**
 * @brief Initialize the video system
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_video_init(void);

/**
 * @brief Deinitialize the video system
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_video_deinit(void);

/**
 * @brief Initialize the encoder
 *
 * @param config Encoder configuration
 * @param ret_handle Encoder handle
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_encoder_init(example_encoder_config_t *config, example_encoder_handle_t *ret_handle);

/**
 * @brief Get the encoder output buffer
 *
 * @param handle Encoder handle
 * @param buf Output buffer
 * @param size Output buffer size
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_encoder_alloc_output_buffer(example_encoder_handle_t handle, uint8_t **buf, uint32_t *size);

/**
 * @brief Free the encoder output buffer
 *
 * @param handle Encoder handle
 * @param buf Output buffer
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_encoder_free_output_buffer(example_encoder_handle_t handle, uint8_t *buf);

/**
 * @brief Process the encoder
 *
 * @param handle Encoder handle
 * @param src_buf Source buffer
 * @param src_size Source buffer size
 * @param dst_buf Destination buffer
 * @param dst_size Destination buffer size
 * @param dst_size_out Output destination buffer size
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_encoder_process(example_encoder_handle_t handle, uint8_t *src_buf, uint32_t src_size, uint8_t *dst_buf, uint32_t dst_size, uint32_t *dst_size_out);

/**
 * @brief Set the JPEG quality
 *
 * @param handle Encoder handle
 * @param quality JPEG quality
 *
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_encoder_set_jpeg_quality(example_encoder_handle_t handle, uint8_t quality);

/**
 * @brief Deinitialize the encoder
 *
 * @param handle Encoder handle
 * @return ESP_OK on success or other value on failure
 */
esp_err_t example_encoder_deinit(example_encoder_handle_t handle);

#ifdef __cplusplus
}
#endif
