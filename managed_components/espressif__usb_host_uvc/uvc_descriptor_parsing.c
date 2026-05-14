/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <string.h> // strncmp for guid format parsing
#include <math.h>   // fabsf for float comparison
#include "usb/usb_helpers.h"
#include "usb/uvc_host.h"
#include "uvc_check_priv.h"
#include "uvc_descriptors_priv.h"

#define FLOAT_EQUAL(a, b) (fabsf(a - b) < 0.0001f) // For comparing float values with acceptable difference (epsilon value)

static const uvc_vs_input_header_desc_t *uvc_desc_get_streaming_input_header(const usb_config_desc_t *cfg_desc, uint8_t bInterfaceNumber)
{
    UVC_CHECK(cfg_desc, NULL);

    // Find Interface with alternate settings = 0. All Video Streaming descriptors should be after this descriptor.
    int offset = 0;
    const usb_intf_desc_t *intf_desc = usb_parse_interface_descriptor(cfg_desc, bInterfaceNumber, 0, &offset);
    UVC_CHECK(intf_desc, NULL);
    UVC_CHECK(intf_desc->bInterfaceClass == USB_CLASS_VIDEO, NULL);
    UVC_CHECK(intf_desc->bInterfaceSubClass == UVC_SC_VIDEOSTREAMING, NULL);

    // Find Video Input Header Descriptor
    const usb_standard_desc_t *std_desc = usb_parse_next_descriptor_of_type((const usb_standard_desc_t *)intf_desc, cfg_desc->wTotalLength, UVC_CS_INTERFACE, &offset);
    const uvc_vs_input_header_desc_t *input_header = (uvc_vs_input_header_desc_t *)std_desc;
    UVC_CHECK(input_header, NULL);
    UVC_CHECK(input_header->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_INPUT_HEADER, NULL);
    return input_header;
}

esp_err_t uvc_desc_get_streaming_intf_and_ep(
    const usb_config_desc_t *cfg_desc,
    uint8_t bInterfaceNumber,
    uint16_t dwMaxPayloadTransferSize,
    const usb_intf_desc_t **intf_desc_ret,
    const usb_ep_desc_t **ep_desc_ret)
{
    UVC_CHECK(cfg_desc && intf_desc_ret && ep_desc_ret, ESP_ERR_INVALID_ARG);

    esp_err_t ret = ESP_ERR_NOT_FOUND; // Default to error, in case we don't find and endpoint with supported MPS
    const usb_intf_desc_t *intf_desc = NULL;
    const usb_ep_desc_t *ep_desc = NULL;
    int offset = 0;

    const uint8_t num_of_alternate = usb_parse_interface_number_of_alternate(cfg_desc, bInterfaceNumber);
    uint16_t last_mps = 0; // Looking for maximum MPS: init to zero
    uint8_t last_mult = UINT8_MAX; // Looking for minimum: init to max
    for (int i = 0; i <= num_of_alternate; i++) {
        // Check Interface desc
        intf_desc = usb_parse_interface_descriptor(cfg_desc, bInterfaceNumber, i, &offset);
        UVC_CHECK(intf_desc, ESP_ERR_NOT_FOUND);
        UVC_CHECK(intf_desc->bInterfaceClass == USB_CLASS_VIDEO, ESP_ERR_NOT_FOUND);
        UVC_CHECK(intf_desc->bInterfaceSubClass == UVC_SC_VIDEOSTREAMING, ESP_ERR_NOT_FOUND);
        if (intf_desc->bNumEndpoints == 0 && i == 0) {
            continue; // This is Alternate setting 0 for ISOC cameras.
        }
        UVC_CHECK(intf_desc->bNumEndpoints == 1, ESP_ERR_NOT_FOUND); // Only 1 endpoint is expected

        // Check EP desc
        ep_desc = usb_parse_endpoint_descriptor_by_index(intf_desc, 0, cfg_desc->wTotalLength, &offset);
        UVC_CHECK(ep_desc, ESP_ERR_NOT_FOUND);

        // Here we look for an interface that offers the largest MPS with minimum multiple transactions in a microframe
        // and that is not bigger that max. requests MPS
        const uint16_t current_mps = USB_EP_DESC_GET_MPS(ep_desc);
        const uint8_t current_mult = USB_EP_DESC_GET_MULT(ep_desc);
        if (current_mps >= last_mps && current_mult <= last_mult && current_mps <= dwMaxPayloadTransferSize) {
            last_mps = current_mps;
            last_mult = current_mult;
            *ep_desc_ret = ep_desc;
            *intf_desc_ret = intf_desc;
            ret = ESP_OK;
        } else {
            break;
        }
    }

    return ret;
}

/**
 * @brief Check if this descriptor is Format descriptor
 *
 * @param[in] _desc USB descriptor
 * @return true  Is format descriptor
 * @return false Is NOT format descriptor
 */
static bool uvc_desc_is_format_desc(const usb_standard_desc_t *_desc)
{
    assert(_desc);
    const uvc_format_desc_t *desc = (const uvc_format_desc_t *)_desc;
    const bool is_format_desc = desc->bDescriptorType == UVC_CS_INTERFACE && (
                                    desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FORMAT_UNCOMPRESSED ||
                                    desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FORMAT_MJPEG ||
                                    desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FORMAT_MPEG2TS ||
                                    desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FORMAT_DV ||
                                    desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FORMAT_FRAME_BASED ||
                                    desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FORMAT_STREAM_BASED
                                );

    return is_format_desc;
}

/**
 * @brief Check if this descriptor is Frame descriptor
 *
 * @param[in] _desc USB descriptor
 * @return true  Is frame descriptor
 * @return false Is NOT frame descriptor
 */
static bool uvc_desc_is_frame_desc(const usb_standard_desc_t *_desc)
{
    assert(_desc);
    const uvc_frame_desc_t *desc = (const uvc_frame_desc_t *)_desc;
    const bool is_frame_desc = desc->bDescriptorType == UVC_CS_INTERFACE && (
                                   desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FRAME_UNCOMPRESSED ||
                                   desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FRAME_MJPEG ||
                                   desc->bDescriptorSubType == UVC_VS_DESC_SUBTYPE_FRAME_FRAME_BASED
                               );

    return is_frame_desc;
}

int uvc_desc_parse_format(const uvc_format_desc_t *format_desc)
{
    // Input checks
    assert(format_desc);
    UVC_CHECK(uvc_desc_is_format_desc((const usb_standard_desc_t *)format_desc), -1);

    int ret = -1;
    switch (format_desc->bDescriptorSubType) {
    case UVC_VS_DESC_SUBTYPE_FORMAT_UNCOMPRESSED: {
        const char *guid = (const char *)(format_desc->uncompressed_frame_based.guidFormat);
        // We do not check full guid, but only the first 4 characters that show human readable format
        if (strncmp(guid, "YUY2", 4) == 0) {
            ret = UVC_VS_FORMAT_YUY2;
        }
        break;
    }
    case UVC_VS_DESC_SUBTYPE_FORMAT_MJPEG:
        ret = UVC_VS_FORMAT_MJPEG;
        break;
    case UVC_VS_DESC_SUBTYPE_FORMAT_FRAME_BASED: {
        const char *guid = (const char *)(format_desc->uncompressed_frame_based.guidFormat);
        // We do not check full guid, but only the first 4 characters that show human readable format
        if (strncmp(guid, "H265", 4) == 0) {
            ret = UVC_VS_FORMAT_H265;
        } else if (strncmp(guid, "H264", 4) == 0) {
            ret = UVC_VS_FORMAT_H264;
        }
        break;
    }
    case UVC_VS_DESC_SUBTYPE_UNDEFINED:
    default: break;
    }
    return ret;
}

static bool uvc_desc_format_is_equal(const uvc_frame_desc_t *frame_desc, const uvc_host_stream_format_t *vs_format)
{
    assert(frame_desc && vs_format);
    UVC_CHECK(uvc_desc_is_frame_desc((const usb_standard_desc_t *)frame_desc), false);

    if (frame_desc->wWidth == vs_format->h_res && frame_desc->wHeight == vs_format->v_res) {
        if (vs_format->fps == 0) {
            return true; // Default FPS requested
        }

        // Check if this frame descriptor supports requested FPS
        uint8_t bFrameIntervalType;
        uint32_t dwMinFrameInterval, dwMaxFrameInterval, dwFrameIntervalStep;

        switch (frame_desc->bDescriptorSubType) {
        case UVC_VS_DESC_SUBTYPE_FRAME_FRAME_BASED:
            bFrameIntervalType = frame_desc->frame_based.bFrameIntervalType;
            if (bFrameIntervalType == 0) {

                dwMinFrameInterval = frame_desc->frame_based.dwMinFrameInterval;
                dwMaxFrameInterval = frame_desc->frame_based.dwMaxFrameInterval;
                dwFrameIntervalStep = frame_desc->frame_based.dwFrameIntervalStep;
                // This stream does not support discrete Frame Interval. Check all supported intervals
                uint32_t current_frame_interval = dwMinFrameInterval;
                while (current_frame_interval <= dwMaxFrameInterval) {
                    if (FLOAT_EQUAL(vs_format->fps, UVC_DESC_DWFRAMEINTERVAL_TO_FPS(current_frame_interval))) {
                        return true;
                    }
                    current_frame_interval += dwFrameIntervalStep;
                }
            } else {
                // This stream support discrete Frame Intervals. Check supported intervals
                for (int i = 0; i < bFrameIntervalType; i++) {
                    if (FLOAT_EQUAL(vs_format->fps, UVC_DESC_DWFRAMEINTERVAL_TO_FPS(frame_desc->frame_based.dwFrameInterval[i]))) {
                        return true;
                    }
                }
            }
            break;
        case UVC_VS_DESC_SUBTYPE_FRAME_UNCOMPRESSED:
        case UVC_VS_DESC_SUBTYPE_FRAME_MJPEG:
            bFrameIntervalType = frame_desc->mjpeg_uncompressed.bFrameIntervalType;
            if (bFrameIntervalType == 0) {

                dwMinFrameInterval = frame_desc->mjpeg_uncompressed.dwMinFrameInterval;
                dwMaxFrameInterval = frame_desc->mjpeg_uncompressed.dwMaxFrameInterval;
                dwFrameIntervalStep = frame_desc->mjpeg_uncompressed.dwFrameIntervalStep;
                // This stream does not support discrete Frame Interval. Check all supported intervals
                uint32_t current_frame_interval = dwMinFrameInterval;
                while (current_frame_interval <= dwMaxFrameInterval) {
                    if (FLOAT_EQUAL(vs_format->fps, UVC_DESC_DWFRAMEINTERVAL_TO_FPS(current_frame_interval))) {
                        return true;
                    }
                    current_frame_interval += dwFrameIntervalStep;
                }
            } else {
                // This stream support discrete Frame Intervals. Check supported intervals
                for (int i = 0; i < bFrameIntervalType; i++) {
                    if (FLOAT_EQUAL(vs_format->fps, UVC_DESC_DWFRAMEINTERVAL_TO_FPS(frame_desc->mjpeg_uncompressed.dwFrameInterval[i]))) {
                        return true;
                    }
                }
            }
            break;
        default:
            return true; // Unknown frame type, assume it is equal;
        }
    }
    return false;
}

esp_err_t uvc_desc_get_frame_format_by_format(
    const usb_config_desc_t *cfg_desc,
    uint8_t bInterfaceNumber,
    const uvc_host_stream_format_t *vs_format,
    const uvc_format_desc_t **format_desc_ret,
    const uvc_frame_desc_t **frame_desc_ret)
{
    UVC_CHECK(cfg_desc && vs_format, ESP_ERR_INVALID_ARG);

    const uvc_vs_input_header_desc_t *input_header = uvc_desc_get_streaming_input_header(cfg_desc, bInterfaceNumber);
    UVC_CHECK(input_header, ESP_ERR_NOT_FOUND);

    // Find requested Format descriptors
    esp_err_t ret = ESP_ERR_NOT_FOUND;
    int format_offset = 0;
    const usb_standard_desc_t *current_desc = (const usb_standard_desc_t *) input_header;
    while ((current_desc = usb_parse_next_descriptor_of_type(current_desc, input_header->wTotalLength, UVC_CS_INTERFACE, &format_offset))) {
        if (uvc_desc_is_format_desc(current_desc)) {
            const uvc_format_desc_t *this_format = (const uvc_format_desc_t *)(current_desc);
            if (vs_format->format == uvc_desc_parse_format(this_format)) {
                if (format_desc_ret) {
                    *format_desc_ret = this_format;
                }
                // We found required Format Descriptor
                // Now we look for correct Frame Descriptors which should be directly after Format
                while ((current_desc = usb_parse_next_descriptor_of_type(current_desc, input_header->wTotalLength, UVC_CS_INTERFACE, &format_offset))) {
                    uvc_frame_desc_t *this_frame = (uvc_frame_desc_t *)current_desc;
                    if (uvc_desc_format_is_equal(this_frame, vs_format)) {
                        if (frame_desc_ret) {
                            *frame_desc_ret = this_frame;
                        }
                        ret = ESP_OK;
                        break;
                    }
                }
                break;
            }
        }
    }
    return ret;
}

static inline bool uvc_desc_is_format_supported(
    const usb_config_desc_t *cfg_desc,
    uint8_t bInterfaceNumber,
    const uvc_host_stream_format_t *vs_format)
{
    if (vs_format->format == UVC_VS_FORMAT_DEFAULT ||
            ESP_OK == uvc_desc_get_frame_format_by_format(cfg_desc, bInterfaceNumber, vs_format, NULL, NULL)) {
        return true;
    }
    return false;
}

static const uvc_vc_header_desc_t *uvc_desc_get_control_interface_header(const usb_config_desc_t *cfg_desc, unsigned uvc_idx)
{
    UVC_CHECK(cfg_desc, NULL);

    // Find IAD UVC descriptor with desired index
    const uvc_vc_header_desc_t *header_desc_ret = NULL;
    int offset = 0;
    int uvc_iad_idx = 0;
    const usb_standard_desc_t *current_desc = (const usb_standard_desc_t *)cfg_desc;
    while ((current_desc = usb_parse_next_descriptor_of_type(current_desc, cfg_desc->wTotalLength, USB_B_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION, &offset))) {
        const usb_iad_desc_t *iad_desc = (usb_iad_desc_t *)current_desc;
        if (iad_desc->bFunctionClass == USB_CLASS_VIDEO && iad_desc->bFunctionSubClass == UVC_SC_VIDEO_INTERFACE_COLLECTION) {
            if (uvc_idx == uvc_iad_idx) {
                // This is the IAD that we are looking for. Find its first Video Control interface header descriptor
                header_desc_ret = (const uvc_vc_header_desc_t *)usb_parse_next_descriptor_of_type(current_desc, cfg_desc->wTotalLength, UVC_CS_INTERFACE, &offset);
                UVC_CHECK(header_desc_ret->bDescriptorSubType == UVC_VC_DESC_SUBTYPE_HEADER, NULL);
                break;
            } else {
                // The user requires next UVC function
                uvc_iad_idx++;
            }
        }
    }
    return header_desc_ret;
}

esp_err_t uvc_desc_get_frame_format_by_index(
    const usb_config_desc_t *cfg_desc,
    uint8_t bInterfaceNumber,
    uint8_t bFormatIndex,
    uint8_t bFrameIndex,
    const uvc_format_desc_t **format_desc_ret,
    const uvc_frame_desc_t **frame_desc_ret)
{
    UVC_CHECK(bFormatIndex > 0, ESP_ERR_INVALID_ARG); // Formats are indexed from 1
    UVC_CHECK(bFrameIndex > 0, ESP_ERR_INVALID_ARG); // Frames are indexed from 1
    UVC_CHECK(format_desc_ret && frame_desc_ret && cfg_desc, ESP_ERR_INVALID_ARG);

    const uvc_vs_input_header_desc_t *input_header = uvc_desc_get_streaming_input_header(cfg_desc, bInterfaceNumber);
    UVC_CHECK(input_header, ESP_ERR_NOT_FOUND);
    UVC_CHECK(input_header->bNumFormats >= bFormatIndex, ESP_ERR_NOT_FOUND);

    // Find requested Format and Frame descriptors
    esp_err_t ret = ESP_ERR_NOT_FOUND;
    int format_offset = 0;
    const usb_standard_desc_t *current_desc = (const usb_standard_desc_t *) input_header;
    while ((current_desc = usb_parse_next_descriptor_of_type(current_desc, input_header->wTotalLength, UVC_CS_INTERFACE, &format_offset))) {
        const uvc_format_desc_t *this_format = (const uvc_format_desc_t *)current_desc;
        if (uvc_desc_is_format_desc(current_desc)) {
            if (this_format->bFormatIndex == bFormatIndex) {
                UVC_CHECK(this_format->bNumFrameDescriptors >= bFrameIndex, ESP_ERR_NOT_FOUND);
                *format_desc_ret = (const uvc_format_desc_t *)this_format;
                // We found required Format Descriptor
                // Now we look for correct Frame Descriptors which should be directly after Format
                while ((current_desc = usb_parse_next_descriptor_of_type(current_desc, input_header->wTotalLength, UVC_CS_INTERFACE, &format_offset))) {
                    uvc_frame_desc_t *this_frame = (uvc_frame_desc_t *)current_desc;
                    if (this_frame->bFrameIndex == bFrameIndex) {
                        *frame_desc_ret = this_frame;
                        ret = ESP_OK;
                        break;
                    }
                }
                break;
            }
        }
    }
    return ret;
}

esp_err_t uvc_desc_get_streaming_interface_num(
    const usb_config_desc_t *cfg_desc,
    uint8_t uvc_index,
    const uvc_host_stream_format_t *vs_format,
    uint16_t *bcdUVC,
    uint8_t *bInterfaceNumber)
{
    UVC_CHECK(cfg_desc && vs_format && bcdUVC && bInterfaceNumber, ESP_ERR_INVALID_ARG);

    esp_err_t ret = ESP_ERR_NOT_FOUND;

    // Get Interface header with uvc_index
    const uvc_vc_header_desc_t *vc_header_desc = uvc_desc_get_control_interface_header(cfg_desc, uvc_index);
    if (!vc_header_desc) {
        return ESP_ERR_NOT_FOUND;
    }
    *bcdUVC = vc_header_desc->bcdUVC;

    // Find video streaming interface that offers the requested format
    for (int streaming_if = 0; streaming_if < vc_header_desc->bInCollection; streaming_if++) {
        uint8_t current_bInterfaceNumber = vc_header_desc->baInterfaceNr[streaming_if];
        if (uvc_desc_is_format_supported(cfg_desc, current_bInterfaceNumber, vs_format)) {
            *bInterfaceNumber = current_bInterfaceNumber;
            ret = ESP_OK;
            break;
        }
    }
    return ret;
}

bool uvc_desc_is_uvc_device(const usb_config_desc_t *cfg_desc)
{
    assert(cfg_desc);
    int offset = 0;
    int total_len = cfg_desc->wTotalLength;

    const usb_standard_desc_t *current_desc = (const usb_standard_desc_t *)cfg_desc;
    while ((current_desc = usb_parse_next_descriptor_of_type((const usb_standard_desc_t *)current_desc, total_len, USB_B_DESCRIPTOR_TYPE_INTERFACE, &offset))) {
        const usb_intf_desc_t *iface_desc = (const usb_intf_desc_t *)current_desc;
        if (USB_CLASS_VIDEO == iface_desc->bInterfaceClass) {
            return true;
        }
    }
    return false;
}

esp_err_t uvc_desc_get_frame_list(const usb_config_desc_t *config_desc, uint8_t uvc_index, uvc_host_frame_info_t (*frame_info_list)[], size_t *list_size)
{
    esp_err_t ret = ESP_OK;
    UVC_CHECK(config_desc && list_size, ESP_ERR_INVALID_ARG);
    size_t frame_index = 0;
    // Support frame number for VS Interface Header
    size_t num_frame = 0;

    const uvc_vc_header_desc_t *vc_header = uvc_desc_get_control_interface_header(config_desc, uvc_index);
    UVC_CHECK(vc_header, ESP_ERR_NOT_FOUND);

    // Find requested Format descriptors
    const usb_standard_desc_t *current_desc = (const usb_standard_desc_t *)vc_header;
    // Skip VC Interface Header and VC Interface Descriptor
    int format_offset = 0;
    const uvc_vs_input_header_desc_t *vs_header = uvc_desc_get_streaming_input_header(config_desc, vc_header->baInterfaceNr[0]);
    current_desc = (const usb_standard_desc_t *)vs_header;

    while ((current_desc = usb_parse_next_descriptor_of_type(current_desc, vs_header->wTotalLength, UVC_CS_INTERFACE, &format_offset))) {
        if (!uvc_desc_is_format_desc(current_desc)) {
            continue;
        }

        const uvc_format_desc_t *this_format = (const uvc_format_desc_t *)(current_desc);
        enum uvc_host_stream_format format_type = uvc_desc_parse_format(this_format);
        if (0 > format_type) { // Undefined format
            continue;
        }

        num_frame += this_format->bNumFrameDescriptors;

        /*!< Just Skip Skip populating `frame_info_list`. */
        if (!frame_info_list) {
            continue;
        }

        // We found required Format Descriptor
        // Now we look for correct Frame Descriptors which should be directly after Format
        while ((current_desc = usb_parse_next_descriptor_of_type(current_desc, vs_header->wTotalLength, UVC_CS_INTERFACE, &format_offset))) {
            if (!uvc_desc_is_frame_desc(current_desc)) {
                break;
            }
            uvc_frame_desc_t *this_frame = (uvc_frame_desc_t *)current_desc;

            if (frame_index > *list_size - 1) {
                break;
            }
            uvc_host_frame_info_t *frame_info = &(*frame_info_list)[frame_index];
            frame_info->format = format_type;
            frame_info->h_res = this_frame->wWidth;
            frame_info->v_res = this_frame->wHeight;
            switch (format_type) {
            case UVC_VS_FORMAT_YUY2:
            case UVC_VS_FORMAT_MJPEG:
                frame_info->default_interval = this_frame->mjpeg_uncompressed.dwDefaultFrameInterval;
                frame_info->interval_type = this_frame->mjpeg_uncompressed.bFrameIntervalType;
                if (frame_info->interval_type == 0) {
                    frame_info->interval_min = this_frame->mjpeg_uncompressed.dwMinFrameInterval;
                    frame_info->interval_max = this_frame->mjpeg_uncompressed.dwMaxFrameInterval;
                    frame_info->interval_step = this_frame->mjpeg_uncompressed.dwFrameIntervalStep;
                } else {
                    for (int i = 0; i < CONFIG_UVC_INTERVAL_ARRAY_SIZE; i ++) {
                        frame_info->interval[i] = this_frame->mjpeg_uncompressed.dwFrameInterval[i];
                    }
                }
                break;
            case UVC_VS_FORMAT_H265:
            case UVC_VS_FORMAT_H264:
                frame_info->default_interval = this_frame->frame_based.dwDefaultFrameInterval;
                frame_info->interval_type = this_frame->frame_based.bFrameIntervalType;
                if (frame_info->interval_type == 0) {
                    frame_info->interval_min = this_frame->frame_based.dwMinFrameInterval;
                    frame_info->interval_max = this_frame->frame_based.dwMaxFrameInterval;
                    frame_info->interval_step = this_frame->frame_based.dwFrameIntervalStep;
                } else {
                    for (int i = 0; i < CONFIG_UVC_INTERVAL_ARRAY_SIZE; i ++) {
                        frame_info->interval[i] = this_frame->frame_based.dwFrameInterval[i];
                    }
                }
                break;
            default:
                break;
            }

            frame_index++;
        }

        if (!current_desc) {
            break;
        }
    }

    *list_size = frame_info_list ? frame_index : num_frame;
    return ret;
}
