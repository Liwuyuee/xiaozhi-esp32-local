/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>

#include "usb/usb_host.h"
#include "usb/uvc_host.h"
#include "uvc_types_priv.h"

#define TERMINAL_INPUT_CAMERA_TYPE      0x0201
#define TERMINAL_INPUT_COMPOSITE_TYPE   0x0401
#define ITT_MEDIA_TRANSPORT_INPUT       0x0202

static enum uvc_int_subclass_code interface_sub_class = UVC_SC_VIDEOCONTROL;

static void unknown_desc(const usb_standard_desc_t *header)
{
    printf(" *** Unknown Descriptor Length: %d Type: %d ***\n",
           header->bLength, header->bDescriptorType);
}

static void print_cs_endpoint_desc(const usb_standard_desc_t *_desc)
{
    uvc_vc_interrupt_ep_desc_t *class_desc = (uvc_vc_interrupt_ep_desc_t *)_desc;
    printf("\t\t*** Class-specific Interrupt Endpoint Descriptor ***\n");
    printf("\t\tbLength %u\n", class_desc->bLength);
    printf("\t\tbDescriptorType 0x%02X\n", class_desc->bDescriptorType);
    printf("\t\tbDescriptorSubType %d\n", class_desc->bDescriptorSubType);
    printf("\t\twMaxTransferSize %d\n", class_desc->wMaxTransferSize);
}

static void print_class_header_desc(const usb_standard_desc_t *_desc)
{
    if (interface_sub_class == UVC_SC_VIDEOCONTROL) {
        const uvc_vc_header_desc_t *desc = (const uvc_vc_header_desc_t *) _desc;
        printf("\t*** Class-specific VC Interface Descriptor ***\n");
        printf("\tbLength %u\n", desc->bLength);
        printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
        printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
        printf("\tbcdUVC %04x\n", desc->bcdUVC);
        printf("\twTotalLength %u\n", desc->wTotalLength);
        printf("\tdwClockFrequency %"PRIu32"\n", desc->dwClockFrequency);
        printf("\tbInCollection %u\n", desc->bInCollection);
        for (int i = 0; i < desc->bInCollection; i++) {
            printf("\tbaInterfaceNr[%i] %u\n", i, desc->baInterfaceNr[i]);
        }
    } else if (interface_sub_class == UVC_SC_VIDEOSTREAMING) {
        const uvc_vs_input_header_desc_t *desc = (const uvc_vs_input_header_desc_t *) _desc;
        printf("\t*** Class-specific VS Interface Descriptor ***\n");
        printf("\tbLength %u\n", desc->bLength);
        printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
        printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
        printf("\tbNumFormats 0x%X\n", desc->bNumFormats);
        printf("\twTotalLength %u\n", desc->wTotalLength);
        printf("\tbEndpointAddress 0x%02X\n", desc->bEndpointAddress);
        printf("\tbmInfo 0x%X\n", desc->bmInfo);
        printf("\tbTerminalLink %u\n", desc->bTerminalLink);
        printf("\tbStillCaptureMethod %u\n", desc->bStillCaptureMethod);
        printf("\tbTriggerSupport %u\n", desc->bTriggerSupport);
        printf("\tbTriggerUsage %u\n", desc->bTriggerUsage);
        printf("\tbControlSize %u\n", desc->bControlSize);
        for (int format = 0; format < desc->bNumFormats; format++) {
            printf("\tbmaControls[%d] 0x%X\n", format, desc->bmaControls[format * desc->bControlSize]);
        }
    }
}

static void print_vc_input_terminal_desc(const usb_standard_desc_t *_desc)
{
    const uvc_input_terminal_camera_desc_t *desc = (const uvc_input_terminal_camera_desc_t *) _desc;

    const char *type = NULL;

    switch (desc->wTerminalType) {
    case TERMINAL_INPUT_CAMERA_TYPE: type = "Camera"; break;
    case TERMINAL_INPUT_COMPOSITE_TYPE: type = "Composite"; break;
    case ITT_MEDIA_TRANSPORT_INPUT: type = "Media"; break;
    default: printf("!!!!! Unknown Input terminal descriptor !!!!!\n"); return;
    }

    printf("\t*** Input Terminal Descriptor (%s) ***\n", type);
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbTerminalID 0x%X\n", desc->bTerminalID);
    printf("\twTerminalType 0x%X\n", desc->wTerminalType);
    printf("\tbAssocTerminal %u\n", desc->bAssocTerminal);
    printf("\tiTerminal %u\n", desc->iTerminal);

    if (desc->wTerminalType == TERMINAL_INPUT_COMPOSITE_TYPE) {
        return;
    } else if (desc->wTerminalType == TERMINAL_INPUT_CAMERA_TYPE) {
        printf("\twObjectiveFocalLengthMin %u\n", desc->wObjectiveFocalLengthMin);
        printf("\twObjectiveFocalLengthMax %u\n", desc->wObjectiveFocalLengthMax);
        printf("\twOcularFocalLength %u\n", desc->wOcularFocalLength);
        printf("\tbControlSize %u\n", desc->bControlSize);
        printf("\tbmControls 0x%X 0x%X 0x%X\n",
               desc->bmControls[0],
               desc->bmControls[1],
               desc->bmControls[2]);
    } else if (desc->wTerminalType == ITT_MEDIA_TRANSPORT_INPUT) {
        const uvc_input_terminal_media_desc_t *desc = (const uvc_input_terminal_media_desc_t *) _desc;
        printf("\tbControlSize %u\n", desc->bControlSize);
        printf("\tbmControls 0x%X\n", desc->bmControls);
        printf("\tbTransportModeSize %u\n", desc->bTransportModeSize);
        printf("\tbmTransportModes 0x%X 0x%X 0x%X 0x%X 0x%X\n",
               desc->bmTransportModes[0],
               desc->bmTransportModes[1],
               desc->bmTransportModes[2],
               desc->bmTransportModes[3],
               desc->bmTransportModes[4]);
    }
}

static void print_vc_output_terminal_desc(const usb_standard_desc_t *_desc)
{
    const uvc_output_terminal_desc_t *desc = (const uvc_output_terminal_desc_t *) _desc;
    printf("\t*** Output Terminal Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbTerminalID %u\n", desc->bTerminalID);
    printf("\twTerminalType 0x%X\n", desc->wTerminalType);
    printf("\tbAssocTerminal %u\n", desc->bAssocTerminal);
    printf("\tbSourceID %u\n", desc->bSourceID);
    printf("\tiTerminal %u\n", desc->iTerminal);
}

static void print_vc_selector_unit_desc(const usb_standard_desc_t *_desc)
{
    const uvc_selector_unit_desc_t *desc = (const uvc_selector_unit_desc_t *) _desc;
    printf("\t*** Selector Unit Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbUnitID %u\n", desc->bUnitID);
    printf("\tbNrInPins %u\n", desc->bNrInPins);
    printf("\tbaSourceID1 %u\n", desc->baSourceID1);
    printf("\tbaSourceID2 %u\n", desc->baSourceID2);
    printf("\tiSelector %u\n", desc->iSelector);
}

static void print_vc_processing_unit_desc(const usb_standard_desc_t *_desc)
{
    const uvc_processing_unit_desc_t *desc = (const uvc_processing_unit_desc_t *) _desc;
    printf("\t*** Processing Unit Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbUnitID %u\n", desc->bUnitID);
    printf("\tbSourceID %u\n", desc->bSourceID);
    printf("\twMaxMultiplier %u\n", desc->wMaxMultiplier);
    printf("\tbControlSize %u\n", desc->bControlSize);
    printf("\tbmControls 0x%X 0x%X 0x%X\n",
           desc->bmControls[0],
           desc->bmControls[1],
           desc->bmControls[2]);
    printf("\tiProcessing %u\n", desc->iProcessing);
    printf("\tbmVideoStandards 0x%X\n", desc->bmVideoStandards);
}

static void print_vs_format_mjpeg_desc(const usb_standard_desc_t *_desc)
{
    const uvc_format_desc_t *desc = (const uvc_format_desc_t *) _desc;
    printf("\t*** VS Format Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbFormatIndex %u\n", desc->bFormatIndex);
    printf("\tbNumFrameDescriptors %u\n", desc->bNumFrameDescriptors);

    printf("\tbmFlags 0x%X\n",          desc->mjpeg.bmFlags);
    printf("\tbDefaultFrameIndex %u\n", desc->mjpeg.bDefaultFrameIndex);
    printf("\tbAspectRatioX %u\n",      desc->mjpeg.bAspectRatioX);
    printf("\tbAspectRatioY %u\n",      desc->mjpeg.bAspectRatioY);
    printf("\tbmInterlaceFlags 0x%X\n", desc->mjpeg.bmInterlaceFlags);
    printf("\tbCopyProtect %u\n",       desc->mjpeg.bCopyProtect);
}

static void print_vs_frame_mjpeg_desc(const usb_standard_desc_t *_desc)
{
    // Copy to local buffer due to potential misalignment issues.
    uint32_t raw_desc[25];
    uint32_t desc_size = ((const uvc_frame_desc_t *)_desc)->bLength;
    memcpy(raw_desc, _desc, desc_size);

    const uvc_frame_desc_t *desc = (const uvc_frame_desc_t *) raw_desc;
    printf("\t*** VS Frame Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbFrameIndex %u\n", desc->bFrameIndex);
    printf("\tbmCapabilities 0x%X\n", desc->bmCapabilities);
    printf("\twWidth %u\n", desc->wWidth);
    printf("\twHeigh %u\n", desc->wHeight);
    printf("\tdwMinBitRate %"PRIu32"\n", desc->dwMinBitRate);
    printf("\tdwMaxBitRate %"PRIu32"\n", desc->dwMaxBitRate);
    printf("\tdwMaxVideoFrameBufSize %"PRIu32"\n", desc->mjpeg_uncompressed.dwMaxVideoFrameBufferSize);
    printf("\tdwDefaultFrameInterval %"PRIu32"\n", desc->mjpeg_uncompressed.dwDefaultFrameInterval);
    printf("\tbFrameIntervalType %u\n", desc->mjpeg_uncompressed.bFrameIntervalType);

    if (desc->mjpeg_uncompressed.bFrameIntervalType == 0) {
        // Continuous Frame Intervals
        printf("\tdwMinFrameInterval %"PRIu32"\n",  desc->mjpeg_uncompressed.dwMinFrameInterval);
        printf("\tdwMaxFrameInterval %"PRIu32"\n",  desc->mjpeg_uncompressed.dwMaxFrameInterval);
        printf("\tdwFrameIntervalStep %"PRIu32"\n", desc->mjpeg_uncompressed.dwFrameIntervalStep);
    } else {
        // Discrete Frame Intervals
        for (int i = 0; i < desc->mjpeg_uncompressed.bFrameIntervalType; ++i) {
            printf("\tFrameInterval[%d] %"PRIu32"\n", i, desc->mjpeg_uncompressed.dwFrameInterval[i]);
        }
    }
}

static void print_vs_format_frame_based_desc(const usb_standard_desc_t *_desc)
{
    const uvc_format_desc_t *desc = (const uvc_format_desc_t *) _desc;
    printf("\t*** VS Format Frame-Based Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbFormatIndex %u\n", desc->bFormatIndex);
    printf("\tbNumFrameDescriptors %u\n", desc->bNumFrameDescriptors);
    printf("\tguidFormat %.*s\n", 16,     desc->uncompressed_frame_based.guidFormat);
    printf("\tbDefaultFrameIndex %u\n",   desc->uncompressed_frame_based.bDefaultFrameIndex);
    printf("\tbAspectRatioX %u\n",        desc->uncompressed_frame_based.bAspectRatioX);
    printf("\tbAspectRatioY %u\n",        desc->uncompressed_frame_based.bAspectRatioY);
    printf("\tbmInterlaceFlags 0x%X\n",   desc->uncompressed_frame_based.bmInterlaceFlags);
    printf("\tbCopyProtect %u\n",         desc->uncompressed_frame_based.bCopyProtect);
}

static void print_vs_frame_frame_based_desc(const usb_standard_desc_t *_desc)
{
    // Copy to local buffer due to potential misalignment issues.
    uint32_t raw_desc[25];
    uint32_t desc_size = ((const uvc_frame_desc_t *)_desc)->bLength;
    memcpy(raw_desc, _desc, desc_size);

    const uvc_frame_desc_t *desc = (const uvc_frame_desc_t *) raw_desc;
    printf("\t*** VS Frame Frame-Based Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbFrameIndex %u\n", desc->bFrameIndex);
    printf("\tbmCapabilities 0x%X\n", desc->bmCapabilities);
    printf("\twWidth %u\n", desc->wWidth);
    printf("\twHeight %u\n", desc->wHeight);
    printf("\tdwMinBitRate %"PRIu32"\n", desc->dwMinBitRate);
    printf("\tdwMaxBitRate %"PRIu32"\n", desc->dwMaxBitRate);
    printf("\tdwDefaultFrameInterval %"PRIu32"\n", desc->frame_based.dwDefaultFrameInterval);
    printf("\tbFrameIntervalType %u\n", desc->frame_based.bFrameIntervalType);
    printf("\tdwBytesPerLine %"PRIu32"\n", desc->frame_based.dwBytesPerLine);

    if (desc->frame_based.bFrameIntervalType == 0) {
        // Continuous Frame Intervals
        printf("\tdwMinFrameInterval %"PRIu32"\n",  desc->frame_based.dwMinFrameInterval);
        printf("\tdwMaxFrameInterval %"PRIu32"\n",  desc->frame_based.dwMaxFrameInterval);
        printf("\tdwFrameIntervalStep %"PRIu32"\n", desc->frame_based.dwFrameIntervalStep);
    } else {
        // Discrete Frame Intervals
        for (int i = 0; i < desc->frame_based.bFrameIntervalType; ++i) {
            printf("\tFrameInterval[%d] %"PRIu32"\n", i, desc->frame_based.dwFrameInterval[i]);
        }
    }
}

// Helper structs
typedef struct {
    uint16_t wWidth;
    uint16_t wHeight;
} USB_DESC_ATTR WidthHeight_t;
typedef struct {
    uint8_t  bNumCompressionPtn;
    uint8_t  bCompression;
} USB_DESC_ATTR Compression_t;

static void print_vs_still_frame_desc(const usb_standard_desc_t *_desc)
{
    const uvc_still_image_frame_desc_t *desc = (const uvc_still_image_frame_desc_t *) _desc;
    printf("\t*** VS Still Format Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbEndpointAddress 0x%02X\n", desc->bEndpointAddress);
    printf("\tbNumImageSizePatterns 0x%X\n", desc->bNumImageSizePatterns);

    WidthHeight_t *wh = (WidthHeight_t *)&desc->wWidth;
    for (int i = 0; i < desc->bNumImageSizePatterns; ++i, wh++) {
        printf("\t[%d]: wWidth: %u, wHeight: %u\n", i, wh->wWidth, wh->wHeight);
    }

    Compression_t *c = (Compression_t *)wh;
    printf("\tbNumCompressionPtn %u\n", c->bNumCompressionPtn);
    printf("\tbCompression %u\n", c->bCompression);
}

static void print_vs_color_format_desc(const usb_standard_desc_t *_desc)
{
    const uvc_color_matching_desc_t *desc = (const uvc_color_matching_desc_t *) _desc;
    printf("\t*** VS Color Format Descriptor ***\n");
    printf("\tbLength %u\n", desc->bLength);
    printf("\tbDescriptorType 0x%02X\n", desc->bDescriptorType);
    printf("\tbDescriptorSubType 0x%02X\n", desc->bDescriptorSubType);
    printf("\tbColorPrimaries 0x%X\n", desc->bColorPrimaries);
    printf("\tbTransferCharacteristics %u\n", desc->bTransferCharacteristics);
    printf("\tbMatrixCoefficients 0x%X\n", desc->bMatrixCoefficients);
}

static void print_class_specific_desc(const usb_standard_desc_t *_desc)
{
    switch (((uvc_vc_header_desc_t *)_desc)->bDescriptorSubType) {
    case UVC_VC_DESC_SUBTYPE_HEADER:
        print_class_header_desc(_desc);
        break;
    case UVC_VC_DESC_SUBTYPE_INPUT_TERMINAL:
        print_vc_input_terminal_desc(_desc);
        break;
    case UVC_VC_DESC_SUBTYPE_SELECTOR_UNIT:
        print_vc_selector_unit_desc(_desc);
        break;
    case UVC_VC_DESC_SUBTYPE_PROCESSING_UNIT:
        print_vc_processing_unit_desc(_desc);
        break;
    case UVC_VS_DESC_SUBTYPE_FORMAT_MJPEG:
        if (interface_sub_class == UVC_SC_VIDEOCONTROL) {
            printf("\t*** Extension Unit Descriptor unsupported, skipping... ***\n");;
            return;
        }
        print_vs_format_mjpeg_desc(_desc);
        break;
    case UVC_VS_DESC_SUBTYPE_FRAME_MJPEG:
        print_vs_frame_mjpeg_desc(_desc);
        break;
    case UVC_VS_DESC_SUBTYPE_FORMAT_FRAME_BASED:
        print_vs_format_frame_based_desc(_desc);
        break;
    case UVC_VS_DESC_SUBTYPE_FRAME_FRAME_BASED:
        print_vs_frame_frame_based_desc(_desc);
        break;
    case UVC_VS_DESC_SUBTYPE_COLORFORMAT:
        print_vs_color_format_desc(_desc);
        break;
    case UVC_VC_DESC_SUBTYPE_OUTPUT_TERMINAL: // same as UVC_VS_DESC_SUBTYPE_STILL_FRAME
        if (interface_sub_class == UVC_SC_VIDEOCONTROL) {
            print_vc_output_terminal_desc(_desc);
        } else {
            print_vs_still_frame_desc(_desc);
        }
        break;
    default:
        unknown_desc(_desc);
        break;
    }
}

void uvc_print_desc(const usb_standard_desc_t *_desc)
{
    switch (_desc->bDescriptorType) {
    case UVC_CS_INTERFACE:
        print_class_specific_desc(_desc);
        break;
    case UVC_CS_ENDPOINT:
        print_cs_endpoint_desc(_desc);
        break;
    default:
        unknown_desc(_desc);
        break;
    }
}

void uvc_host_desc_print(uvc_host_stream_hdl_t stream_hdl)
{
    assert(stream_hdl);
    uvc_stream_t *uvc_stream = (uvc_stream_t *)stream_hdl;

    const usb_device_desc_t *device_desc;
    const usb_config_desc_t *config_desc;
    ESP_ERROR_CHECK_WITHOUT_ABORT(usb_host_get_device_descriptor(uvc_stream->constant.dev_hdl, &device_desc));
    ESP_ERROR_CHECK_WITHOUT_ABORT(usb_host_get_active_config_descriptor(uvc_stream->constant.dev_hdl, &config_desc));
    usb_print_device_descriptor(device_desc);
    usb_print_config_descriptor(config_desc, &uvc_print_desc);
}
