/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Camera data interface video device
 */
#define ESP_VIDEO_MIPI_CSI_DEVICE_ID        0
#define ESP_VIDEO_MIPI_CSI_DEVICE_NAME      "/dev/video0"

#define ESP_VIDEO_ISP_DVP_DEVICE_ID         1
#define ESP_VIDEO_ISP_DVP_DEVICE_NAME       "/dev/video1"

#define ESP_VIDEO_DVP_DEVICE_ID             2
#define ESP_VIDEO_DVP_DEVICE_NAME           "/dev/video2"

#define ESP_VIDEO_SPI_DEVICE_ID             3
#define ESP_VIDEO_SPI_DEVICE_NAME           "/dev/video3"

#define ESP_VIDEO_SPI_DEVICE_0_ID           ESP_VIDEO_SPI_DEVICE_ID
#define ESP_VIDEO_SPI_DEVICE_0_NAME         ESP_VIDEO_SPI_DEVICE_NAME

#define ESP_VIDEO_SPI_DEVICE_1_ID           4
#define ESP_VIDEO_SPI_DEVICE_1_NAME         "/dev/video4"

#if CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE
#define ESP_VIDEO_SPI_DEVICE_NUM            2
#elif CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
#define ESP_VIDEO_SPI_DEVICE_NUM            1
#else
#define ESP_VIDEO_SPI_DEVICE_NUM            0
#endif /* CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE */

/**
 * @brief USB UVC devices 40-49
 */
#define ESP_VIDEO_USB_UVC_DEVICE_ID_MIN     40
#define ESP_VIDEO_USB_UVC_DEVICE_ID_MAX     49
#define ESP_VIDEO_USB_UVC_DEVICE_ID_NUM     (ESP_VIDEO_USB_UVC_DEVICE_ID_MAX - ESP_VIDEO_USB_UVC_DEVICE_ID_MIN + 1)

#if CONFIG_ESP_VIDEO_CHECK_PARAMETERS
#define ESP_VIDEO_CHECK_USB_UVC_ID(_num) \
({ \
    assert((_num) >= 0 && (_num) < ESP_VIDEO_USB_UVC_DEVICE_ID_NUM); \
})
#else
#define ESP_VIDEO_CHECK_USB_UVC_ID(_num)
#endif

#define ESP_VIDEO_USB_UVC_NAME_PREFIX       "/dev/video4"
#define ESP_VIDEO_USB_UVC_NAME(_num)        (ESP_VIDEO_USB_UVC_NAME_PREFIX #_num)

#define ESP_VIDEO_USB_UVC_DEVICE_ID(_num)   ({ESP_VIDEO_CHECK_USB_UVC_ID(_num); ESP_VIDEO_USB_UVC_DEVICE_ID_MIN + (_num);})
#define ESP_VIDEO_USB_UVC_DEVICE_NAME(_num) ({extern const char *esp_video_usb_uvc_device_name[]; ESP_VIDEO_CHECK_USB_UVC_ID(_num); esp_video_usb_uvc_device_name[_num];})

/**
 * @brief Codec video device
 */
#define ESP_VIDEO_JPEG_DEVICE_ID            10
#define ESP_VIDEO_JPEG_DEVICE_NAME          "/dev/video10"

#define ESP_VIDEO_H264_DEVICE_ID            11
#define ESP_VIDEO_H264_DEVICE_NAME          "/dev/video11"

/**
 * @brief ISP video device
 */
#define ESP_VIDEO_ISP1_DEVICE_ID            20
#define ESP_VIDEO_ISP1_DEVICE_NAME          "/dev/video20"

#ifdef __cplusplus
}
#endif
