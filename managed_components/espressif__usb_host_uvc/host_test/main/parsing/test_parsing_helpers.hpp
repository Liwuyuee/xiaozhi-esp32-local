/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/**
 * @brief Define MJPEG formats with FPS 30-5 and 0 (default)
 */
#define FORMAT_MJPEG_30_5(x, y)      \
    {x, y, 30, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 25, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 20, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 15, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 10, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 5, UVC_VS_FORMAT_MJPEG},  \
    {x, y, 0, UVC_VS_FORMAT_MJPEG}

/**
 * @brief Define MJPEG formats with FPS 30-15 and 0 (default)
 */
#define FORMAT_MJPEG_30_25_15(x, y)  \
    {x, y, 30, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 25, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 15, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 0, UVC_VS_FORMAT_MJPEG}

/**
 * @brief Define MJPEG formats with FPS 30-15 and 0 (default)
 */
#define FORMAT_MJPEG_30_20_15(x, y)  \
    {x, y, 30, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 20, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 15, UVC_VS_FORMAT_MJPEG}, \
    {x, y, 0, UVC_VS_FORMAT_MJPEG}

/**
 * @brief Define YUY2 formats with FPS 30-5 and 0 (default)
 */
#define FORMAT_UNCOMPRESSED_30_5(x, y) \
    {x, y, 30, UVC_VS_FORMAT_YUY2},    \
    {x, y, 25, UVC_VS_FORMAT_YUY2},    \
    {x, y, 20, UVC_VS_FORMAT_YUY2},    \
    {x, y, 15, UVC_VS_FORMAT_YUY2},    \
    {x, y, 10, UVC_VS_FORMAT_YUY2},    \
    {x, y, 5, UVC_VS_FORMAT_YUY2},     \
    {x, y, 0, UVC_VS_FORMAT_YUY2}

/**
 * @brief Define YUY2 formats with FPS 30-15 and 0 (default)
 */
#define FORMAT_UNCOMPRESSED_30_25_15(x, y) \
    {x, y, 30, UVC_VS_FORMAT_YUY2},        \
    {x, y, 25, UVC_VS_FORMAT_YUY2},        \
    {x, y, 15, UVC_VS_FORMAT_YUY2},        \
    {x, y, 0, UVC_VS_FORMAT_YUY2}

/**
 * @brief Define YUY2 formats with FPS 30-15 and 0 (default)
 */
#define FORMAT_UNCOMPRESSED_30_20_15(x, y) \
    {x, y, 30, UVC_VS_FORMAT_YUY2},        \
    {x, y, 20, UVC_VS_FORMAT_YUY2},        \
    {x, y, 15, UVC_VS_FORMAT_YUY2},        \
    {x, y, 0, UVC_VS_FORMAT_YUY2}

/**
 * @brief Define YUY2 formats with FPS 20-5 and 0 (default)
 */
#define FORMAT_UNCOMPRESSED_20_5(x, y) \
    {x, y, 20, UVC_VS_FORMAT_YUY2},    \
    {x, y, 15, UVC_VS_FORMAT_YUY2},    \
    {x, y, 10, UVC_VS_FORMAT_YUY2},    \
    {x, y, 5, UVC_VS_FORMAT_YUY2},     \
    {x, y, 0, UVC_VS_FORMAT_YUY2}

/**
 * @brief Define h264 formats with FPS 30-15 and 0 (default)
 */
#define FORMAT_H264_30_25_15(x, y)  \
    {x, y, 30, UVC_VS_FORMAT_H264}, \
    {x, y, 25, UVC_VS_FORMAT_H264}, \
    {x, y, 15, UVC_VS_FORMAT_H264}, \
    {x, y, 0, UVC_VS_FORMAT_H264}

/**
 * @brief Define h264 formats with FPS 30-15 and 0 (default)
 */
#define FORMAT_H264_30_20_15(x, y)  \
    {x, y, 30, UVC_VS_FORMAT_H264}, \
    {x, y, 20, UVC_VS_FORMAT_H264}, \
    {x, y, 15, UVC_VS_FORMAT_H264}, \
    {x, y, 0, UVC_VS_FORMAT_H264}

/**
 * @brief Define h265 formats with FPS 30-15 and 0 (default)
 */
#define FORMAT_H265_30_20_15(x, y)  \
    {x, y, 30, UVC_VS_FORMAT_H265}, \
    {x, y, 20, UVC_VS_FORMAT_H265}, \
    {x, y, 15, UVC_VS_FORMAT_H265}, \
    {x, y, 0, UVC_VS_FORMAT_H265}

/**
 * @brief Helper that check if required format is supported
 */
#define REQUIRE_FORMAT_SUPPORTED(cfg, format, expected_intf_num)                                                           \
    do {                                                                                                                   \
        uint8_t bInterfaceNumber = 0;                                                                                      \
        uint16_t bcdUVC = 0;                                                                                               \
        REQUIRE(ESP_OK == uvc_desc_get_streaming_interface_num(cfg, 0, &format, &bcdUVC, &bInterfaceNumber));              \
        REQUIRE(bInterfaceNumber == expected_intf_num);                                                                    \
        const usb_intf_desc_t *intf_desc = nullptr;                                                                        \
        const usb_ep_desc_t *ep_desc = nullptr;                                                                            \
        REQUIRE(ESP_OK == uvc_desc_get_streaming_intf_and_ep(cfg, bInterfaceNumber, 1024, &intf_desc, &ep_desc));          \
        REQUIRE(intf_desc != nullptr);                                                                                     \
        REQUIRE(ep_desc != nullptr);                                                                                       \
        const uvc_format_desc_t *format_desc = nullptr;                                                                    \
        const uvc_frame_desc_t *frame_desc = nullptr;                                                                      \
        REQUIRE(ESP_OK == uvc_desc_get_frame_format_by_format(cfg, bInterfaceNumber, &format, &format_desc, &frame_desc)); \
        REQUIRE(format_desc != nullptr);                                                                                   \
        REQUIRE(frame_desc != nullptr);                                                                                    \
    } while (0)

/**
 * @brief Helper that check if required format is NOT supported
 */
#define REQUIRE_FORMAT_NOT_SUPPORTED(cfg, format)                                                                        \
    do {                                                                                                                 \
        uint8_t bInterfaceNumber = 0;                                                                                    \
        uint16_t bcdUVC = 0;                                                                                             \
        REQUIRE_FALSE(ESP_OK == uvc_desc_get_streaming_interface_num(cfg, 0, &this_format, &bcdUVC, &bInterfaceNumber)); \
    } while (0)

/**
 * @brief Helper that check if default format is supported
 */
#define REQUIRE_FORMAT_DEFAULT(cfg, expected_intf_num)                                                                     \
    do {                                                                                                                   \
        uvc_host_stream_format_t format;                                                                                   \
        format.format = UVC_VS_FORMAT_DEFAULT;                                                                             \
        uint8_t bInterfaceNumber = 0;                                                                                      \
        uint16_t bcdUVC = 0;                                                                                               \
        REQUIRE(ESP_OK == uvc_desc_get_streaming_interface_num(cfg, 0, &format, &bcdUVC, &bInterfaceNumber));              \
        REQUIRE(bInterfaceNumber == expected_intf_num);                                                                    \
        const usb_intf_desc_t *intf_desc = nullptr;                                                                        \
        const usb_ep_desc_t *ep_desc = nullptr;                                                                            \
        REQUIRE(ESP_OK == uvc_desc_get_streaming_intf_and_ep(cfg, bInterfaceNumber, 1024, &intf_desc, &ep_desc));          \
        REQUIRE(intf_desc != nullptr);                                                                                     \
        REQUIRE(ep_desc != nullptr);                                                                                       \
    } while (0)
