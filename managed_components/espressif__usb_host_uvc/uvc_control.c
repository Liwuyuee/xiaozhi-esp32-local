/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
// This file will contain all Class-Specific request from USB UVC specification chapter 4

#include <string.h> // For memset
#include <math.h>   // fabsf for float comparison

#include "esp_check.h"

#include "uvc_control.h"
#include "usb/usb_types_ch9.h"
#include "usb/usb_types_uvc.h"
#include "uvc_types_priv.h"
#include "uvc_descriptors_priv.h"
#include "uvc_check_priv.h"

#define FLOAT_EQUAL(a, b) (fabsf(a - b) < 0.0001f) // For comparing float values with acceptable difference (epsilon value)

static const char *TAG = "uvc-control";

static uint16_t uvc_vs_control_size(uint16_t uvc_version)
{
    if (uvc_version < UVC_VERSION_1_1) {
        return 26;
    } else if (uvc_version < UVC_VERSION_1_5) {
        return 34;
    } else {
        return 48;
    }
}

static esp_err_t uvc_host_stream_control(uvc_host_stream_hdl_t stream_hdl, uvc_vs_ctrl_t *vs_control, uvc_host_stream_format_t *vs_format, enum uvc_req_code req_code, bool commit)
{
    uvc_stream_t *uvc_stream = (uvc_stream_t *)stream_hdl;
    uint8_t bmRequestType, bRequest;
    uint16_t wValue, wIndex, wLength;
    const usb_config_desc_t *cfg_desc;
    ESP_ERROR_CHECK(usb_host_get_active_config_descriptor(uvc_stream->constant.dev_hdl, &cfg_desc));
    esp_err_t ret = ESP_OK;
    const bool set = (req_code == UVC_SET_CUR) ? true : false;

    bmRequestType = USB_BM_REQUEST_TYPE_TYPE_CLASS | USB_BM_REQUEST_TYPE_RECIP_INTERFACE;
    bmRequestType |= set ? USB_BM_REQUEST_TYPE_DIR_OUT : USB_BM_REQUEST_TYPE_DIR_IN;
    bRequest = (uint8_t)req_code;
    wValue = (commit ? UVC_VS_COMMIT_CONTROL : UVC_VS_PROBE_CONTROL) << 8;
    wIndex = uvc_stream->constant.bInterfaceNumber;
    wLength = uvc_vs_control_size(uvc_stream->constant.bcdUVC);

    if (set) {
        // Set Video Stream control parameters
        // see USB UVC specification ver 1.5, table 4-75
        const uvc_format_desc_t *format_desc;
        const uvc_frame_desc_t *frame_desc;

        ESP_RETURN_ON_ERROR(
            uvc_desc_get_frame_format_by_format(cfg_desc, uvc_stream->constant.bInterfaceNumber, vs_format, &format_desc, &frame_desc),
            TAG, "Could not find format that matches required format");
        UVC_CHECK(format_desc && frame_desc, ESP_ERR_NOT_FOUND);

        vs_control->bFormatIndex    = format_desc->bFormatIndex;
        vs_control->bFrameIndex     = frame_desc->bFrameIndex;

        // Load default FPS value in case requested FPS is 0
        if (vs_format->fps == 0) {
            switch (frame_desc->bDescriptorSubType) {
            case UVC_VS_DESC_SUBTYPE_FRAME_FRAME_BASED:
                vs_control->dwFrameInterval = frame_desc->frame_based.dwDefaultFrameInterval;
                break;
            case UVC_VS_DESC_SUBTYPE_FRAME_UNCOMPRESSED:
            case UVC_VS_DESC_SUBTYPE_FRAME_MJPEG:
                vs_control->dwFrameInterval = frame_desc->mjpeg_uncompressed.dwDefaultFrameInterval;
                break;
            default:
                vs_control->dwFrameInterval = 0; // Default value for unknown subtype
                break;
            }
        } else {
            vs_control->dwFrameInterval = UVC_DESC_FPS_TO_DWFRAMEINTERVAL(vs_format->fps); // Implicit conversion from float to uint32_t
        }
    }

    // Issue CTRL request
    ESP_RETURN_ON_ERROR(
        uvc_host_usb_ctrl(stream_hdl, bmRequestType, bRequest, wValue, wIndex, wLength, (uint8_t *)vs_control),
        TAG, "Control request failed");

    if (!set) {
        // Get Video Stream control parameters from the received data and parse it to user
        const uvc_format_desc_t *format_desc = NULL;
        const uvc_frame_desc_t *frame_desc = NULL;
        ESP_RETURN_ON_ERROR(
            uvc_desc_get_frame_format_by_index(cfg_desc, uvc_stream->constant.bInterfaceNumber, vs_control->bFormatIndex, vs_control->bFrameIndex, &format_desc, &frame_desc),
            TAG, "Could not find requested frame format");

        vs_format->format = uvc_desc_parse_format(format_desc);
        vs_format->h_res  = frame_desc->wWidth;
        vs_format->v_res  = frame_desc->wHeight;
        vs_format->fps    = UVC_DESC_DWFRAMEINTERVAL_TO_FPS(vs_control->dwFrameInterval);
    }
    return ret;
}

static inline esp_err_t uvc_control_probe_set(uvc_host_stream_hdl_t stream_hdl, uvc_vs_ctrl_t *vs_control, const uvc_host_stream_format_t *vs_format)
{
    return uvc_host_stream_control(stream_hdl, vs_control, (uvc_host_stream_format_t *)vs_format, UVC_SET_CUR, false);
}

static inline esp_err_t uvc_control_probe_get(uvc_host_stream_hdl_t stream_hdl, uvc_vs_ctrl_t *vs_control, uvc_host_stream_format_t *vs_format)
{
    return uvc_host_stream_control(stream_hdl, vs_control, vs_format, UVC_GET_CUR, false);
}

static inline esp_err_t uvc_control_probe_get_max(uvc_host_stream_hdl_t stream_hdl, uvc_vs_ctrl_t *vs_control, uvc_host_stream_format_t *vs_format)
{
    return uvc_host_stream_control(stream_hdl, vs_control, vs_format, UVC_GET_MAX, false);
}

static inline esp_err_t uvc_control_probe_get_min(uvc_host_stream_hdl_t stream_hdl, uvc_vs_ctrl_t *vs_control, uvc_host_stream_format_t *vs_format)
{
    return uvc_host_stream_control(stream_hdl, vs_control, vs_format, UVC_GET_MIN, false);
}

static inline esp_err_t uvc_control_commit(uvc_host_stream_hdl_t stream_hdl, uvc_vs_ctrl_t *vs_control, const uvc_host_stream_format_t *vs_format)
{
    return uvc_host_stream_control(stream_hdl, vs_control, (uvc_host_stream_format_t *)vs_format, UVC_SET_CUR, true);
}

static inline bool uvc_is_vs_format_equal(const uvc_host_stream_format_t *a, const uvc_host_stream_format_t *b)
{
    if (a->h_res == b->h_res &&
            a->v_res == b->v_res &&
            FLOAT_EQUAL(a->fps, b->fps) &&
            a->format == b->format) {
        return true;
    }
    return false;
}

esp_err_t uvc_host_stream_control_probe(uvc_host_stream_hdl_t stream_hdl, uvc_host_stream_format_t *requested_format, uvc_vs_ctrl_t *vs_result_ret)
{
    UVC_CHECK(stream_hdl && requested_format, ESP_ERR_INVALID_ARG);

    esp_err_t ret;
    uvc_vs_ctrl_t vs_result = {0};
    uvc_host_stream_format_t default_format;

    // Notes: Some cameras require 'probe_get' to be the 1st negotiation call
    // It returns 'default' format and frame settings which will be used if requested format is UVC_VS_FORMAT_DEFAULT
    uvc_control_probe_get(stream_hdl, &vs_result, &default_format);
    if (requested_format->format == UVC_VS_FORMAT_DEFAULT) {
        memcpy(requested_format, &default_format, sizeof(uvc_host_stream_format_t));
    }

    uvc_control_probe_set(stream_hdl, &vs_result, requested_format); // Set the requested frame format
    ret = uvc_control_probe_get(stream_hdl, &vs_result, requested_format); // Get back the format

    // Pass the result to user
    if (vs_result_ret) {
        memcpy(vs_result_ret, &vs_result, sizeof(uvc_vs_ctrl_t));
    }

    return ret;
}

esp_err_t uvc_host_stream_control_commit(uvc_host_stream_hdl_t stream_hdl, const uvc_host_stream_format_t *vs_format)
{
    /*
    This is not a 'real' negotiation as we return OK only if set the format exactly as expected.
    In future, we can make vs_format parameter inout. This way we would return the real (close enough) set VS format.
    */
    UVC_CHECK(stream_hdl && vs_format, ESP_ERR_INVALID_ARG);
    esp_err_t ret = ESP_ERR_NOT_FOUND;
    uvc_vs_ctrl_t vs_result = {0};
    uvc_vs_ctrl_t vs_result_ignored = {0};
    uvc_host_stream_format_t format_set, format_ignored;

    // Try 2x. Some camera may return error on first try
    for (int i = 0; i < 2; i++) {
        // Notes: Some cameras require 'probe_get' to be the 1st negotiation call
        // It returns 'default' format and frame settings. It is ignored for now.
        // We can reuse the returned value, if we wanted to implement 'negotiate default frame format' feature.
        memcpy(&format_set, vs_format, sizeof(uvc_host_stream_format_t));
        uvc_host_stream_control_probe(stream_hdl, &format_set, NULL);

        // We do this to mimic Windows driver: The Min/Max values are ignored by this driver.
        // These values can be used if we wanted to negotiate advanced parameters, such as wCompQuality to select JPEG encoding quality
        uvc_control_probe_get_max(stream_hdl, &vs_result_ignored, &format_ignored);
        uvc_control_probe_get_min(stream_hdl, &vs_result_ignored, &format_ignored);

        // Probe that the camera accepts our format before committing
        ret = uvc_control_probe_set(stream_hdl, &vs_result, vs_format);
        ret |= uvc_control_probe_get(stream_hdl, &vs_result, &format_set);
        UVC_CHECK(ret == ESP_OK, ret);
        if (uvc_is_vs_format_equal(&format_set, vs_format)) {
            // If the 'set format' equals 'get format', the camera accepts our format and we can commit it
            break;
        }
    }

    ESP_LOGD(TAG, "Frame format negotiation:\n\tRequested: %dx%d@%2.1fFPS\n\tGot: %dx%d@%2.1fFPS",
             vs_format->h_res, vs_format->v_res, vs_format->fps, format_set.h_res, format_set.v_res, format_set.fps);

    // Commit the negotiated format
    return uvc_control_commit(stream_hdl, &vs_result, vs_format);
}
