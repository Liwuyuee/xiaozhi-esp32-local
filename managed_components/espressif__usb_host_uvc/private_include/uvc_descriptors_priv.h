/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

// In this file we want to have clean interface for descriptor parsing
// So we include only files with USB specification definitions
// This interface is also used in host_tests
#include "usb/usb_types_ch9.h"
#include "usb/usb_types_uvc.h"

#define UVC_DESC_FPS_TO_DWFRAMEINTERVAL(fps) (((fps) != 0) ? 10000000.0f / (fps) : 0)
#define UVC_DESC_DWFRAMEINTERVAL_TO_FPS(dwFrameInterval) (((dwFrameInterval) != 0) ? 10000000.0f / ((float)(dwFrameInterval)) : 0)


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Helper to convert UVC format desc to this driver format
 *
 * @param[in] format_desc UVC format descriptor
 * @return enum uvc_host_stream_format Format enum
 */
int uvc_desc_parse_format(const uvc_format_desc_t *format_desc);

esp_err_t uvc_desc_get_streaming_interface_num(
    const usb_config_desc_t *cfg_desc,
    uint8_t uvc_index,
    const uvc_host_stream_format_t *vs_format,
    uint16_t *bcdUVC,
    uint8_t *bInterfaceNumber);

/**
 * @brief Get Streaming Interface and Endpoint descriptors
 *
 * We go through all alternate interfaces and pick the one that offers endpoint with MPS that:
 * * Is lower than or equal to dwMaxPayloadTransferSize
 * * Has as few as possible extra transactions per microframe (HS only)
 *
 * @note The caller is responsible for dwMaxPayloadTransferSize fitting in the IN FIFO
 *
 * @param[in] cfg_desc                 Configuration descriptor
 * @param[in] bInterfaceNumber         Index of Streaming interface
 * @param[in] dwMaxPayloadTransferSize Maximum requested MPS
 * @param[out] intf_desc_ret           Interface descriptor
 * @param[out] ep_desc_ret             Endpoint descriptor
 * @return
 *     - ESP_OK: Success
 *     - ESP_ERR_INVALID_ARG: cfg_desc, intf_desc_ret or ep_desc_ret is NULL
 *     - ESP_ERR_NOT_FOUND: Could not find interface with required parameters
 */
esp_err_t uvc_desc_get_streaming_intf_and_ep(
    const usb_config_desc_t *cfg_desc,
    uint8_t bInterfaceNumber,
    uint16_t dwMaxPayloadTransferSize,
    const usb_intf_desc_t **intf_desc_ret,
    const usb_ep_desc_t **ep_desc_ret);

esp_err_t uvc_desc_get_frame_format_by_index(
    const usb_config_desc_t *cfg_desc,
    uint8_t bInterfaceNumber,
    uint8_t bFormatIndex,
    uint8_t bFrameIndex,
    const uvc_format_desc_t **format_desc_ret,
    const uvc_frame_desc_t **frame_desc_ret);

esp_err_t uvc_desc_get_frame_format_by_format(
    const usb_config_desc_t *cfg_desc,
    uint8_t bInterfaceNumber,
    const uvc_host_stream_format_t *vs_format,
    const uvc_format_desc_t **format_desc_ret,
    const uvc_frame_desc_t **frame_desc_ret);

/**
 * @brief Check if the given USB configuration descriptor belongs to a UVC (USB Video Class) device.
 *
 * This function iterates through the descriptors in the provided configuration descriptor to determine
 * if there is any interface descriptor indicating the device is a UVC device.
 *
 * @param[in] cfg_desc Pointer to the USB configuration descriptor.
 *
 * @return
 *      - true: If the configuration descriptor contains a UVC interface.
 *      - false: Otherwise.
 */
bool uvc_desc_is_uvc_device(const usb_config_desc_t *cfg_desc);

/**
 * @brief Print UVC specific descriptor in human readable form
 *
 * This is a callback function that is called from USB Host library,
 * when it wants to print full configuration descriptor to stdout.
 *
 * @param[in] _desc UVC specific descriptor
 */
void uvc_print_desc(const usb_standard_desc_t *_desc);

/**
 * @brief Retrieve the list of frame descriptors for a specific streaming interface in a UVC device.
 *
 * This function extracts all frame descriptors associated with the given interface number
 * and organizes them into a list of `uvc_host_frame_info_t` structures.
 *
 * @param[in] config_desc         Pointer to the USB configuration descriptor.
 * @param[in] uvc_index           Index of UVC function you want to use.
 * @param[out] frame_info_list    Pointer to a list of frame info structures (allocated dynamically).
 * @param[inout] list_size          Pointer to store the number of frames in the list.
 *
 * @return
 *      - ESP_OK: Success.
 *      - ESP_ERR_INVALID_ARG: One or more invalid arguments.
 *      - ESP_ERR_NOT_FOUND: Input header descriptor not found.
 *      - ESP_ERR_NO_MEM: Memory allocation failure.
 */
esp_err_t uvc_desc_get_frame_list(
    const usb_config_desc_t *config_desc,
    uint8_t uvc_index,
    uvc_host_frame_info_t (*frame_info_list)[],
    size_t *list_size);

#ifdef __cplusplus
}
#endif
