/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// Definitions from USB UVC specification

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "esp_assert.h"

#define UVC_VERSION_1_0 0x0100
#define UVC_VERSION_1_1 0x0110
#define UVC_VERSION_1_5 0x0150

#define USB_DESC_ATTR           __attribute__((packed))

/**
 * @brief UVC request code
 *
 * @see USB UVC specification ver 1.5, table A.8
 */
enum uvc_req_code {
    UVC_RC_UNDEFINED = 0x00,
    UVC_SET_CUR = 0x01,
    UVC_GET_CUR = 0x81,
    UVC_GET_MIN = 0x82,
    UVC_GET_MAX = 0x83,
    UVC_GET_RES = 0x84,
    UVC_GET_LEN = 0x85,
    UVC_GET_INFO = 0x86,
    UVC_GET_DEF = 0x87
};

/**
 * @brief VideoStreaming interface control selector
 *
 * @see USB UVC specification ver 1.5, table A.9.8
 */
enum uvc_vs_ctrl_selector {
    UVC_VS_CONTROL_UNDEFINED = 0x00,
    UVC_VS_PROBE_CONTROL = 0x01,
    UVC_VS_COMMIT_CONTROL = 0x02,
    UVC_VS_STILL_PROBE_CONTROL = 0x03,
    UVC_VS_STILL_COMMIT_CONTROL = 0x04,
    UVC_VS_STILL_IMAGE_TRIGGER_CONTROL = 0x05,
    UVC_VS_STREAM_ERROR_CODE_CONTROL = 0x06,
    UVC_VS_GENERATE_KEY_FRAME_CONTROL = 0x07,
    UVC_VS_UPDATE_FRAME_SEGMENT_CONTROL = 0x08,
    UVC_VS_SYNC_DELAY_CONTROL = 0x09
};

/**
 * @brief VideoControl interface descriptor subtype
 *
 * @see USB UVC specification ver 1.5, table A.5
 */
enum uvc_vc_desc_subtype {
    UVC_VC_DESC_SUBTYPE_DESCRIPTOR_UNDEFINED = 0x00,
    UVC_VC_DESC_SUBTYPE_HEADER = 0x01,
    UVC_VC_DESC_SUBTYPE_INPUT_TERMINAL = 0x02,
    UVC_VC_DESC_SUBTYPE_OUTPUT_TERMINAL = 0x03,
    UVC_VC_DESC_SUBTYPE_SELECTOR_UNIT = 0x04,
    UVC_VC_DESC_SUBTYPE_PROCESSING_UNIT = 0x05,
    UVC_VC_DESC_SUBTYPE_EXTENSION_UNIT = 0x06,
    UVC_VC_DESC_SUBTYPE_ENCODING_UNIT = 0x07
};

/**
 * @brief VideoStreaming interface descriptor subtype
 *
 * @see USB UVC specification ver 1.5, table A.6
 */
enum uvc_vs_desc_subtype {
    UVC_VS_DESC_SUBTYPE_UNDEFINED = 0x00,
    UVC_VS_DESC_SUBTYPE_INPUT_HEADER = 0x01,
    UVC_VS_DESC_SUBTYPE_OUTPUT_HEADER = 0x02,
    UVC_VS_DESC_SUBTYPE_STILL_IMAGE_FRAME = 0x03,
    UVC_VS_DESC_SUBTYPE_FORMAT_UNCOMPRESSED = 0x04,
    UVC_VS_DESC_SUBTYPE_FRAME_UNCOMPRESSED = 0x05,
    UVC_VS_DESC_SUBTYPE_FORMAT_MJPEG = 0x06,
    UVC_VS_DESC_SUBTYPE_FRAME_MJPEG = 0x07,
    UVC_VS_DESC_SUBTYPE_FORMAT_MPEG2TS = 0x0a,
    UVC_VS_DESC_SUBTYPE_FORMAT_DV = 0x0c,
    UVC_VS_DESC_SUBTYPE_COLORFORMAT = 0x0d,
    UVC_VS_DESC_SUBTYPE_FORMAT_FRAME_BASED = 0x10,
    UVC_VS_DESC_SUBTYPE_FRAME_FRAME_BASED = 0x11,
    UVC_VS_DESC_SUBTYPE_FORMAT_STREAM_BASED = 0x12
};

/**
 * @brief
 * @see USB UVC specification ver 1.5, table 4-75
 */
typedef struct {
    // Version 1.0
    uint16_t bmHint;
    uint8_t  bFormatIndex;
    uint8_t  bFrameIndex;
    uint32_t dwFrameInterval;
    uint16_t wKeyFrameRate;
    uint16_t wPFrameRate;
    uint16_t wCompQuality;
    uint16_t wCompWindowSize;
    uint16_t wDelay;
    uint32_t dwMaxVideoFrameSize;
    uint32_t dwMaxPayloadTransferSize;
    // Version 1.1 and above
    uint32_t dwClockFrequency;
    uint8_t  bmFramingInfo;
    uint8_t  bPreferredVersion;
    uint8_t  bMinVersion;
    uint8_t  bMaxVersion;
    // Version 1.5 and above
    uint8_t  bUsage;
    uint8_t  bBitDepthLuma;
    uint8_t  bmSettings;
    uint8_t  bMaxNumberOfRefFramesPlus1;
    uint16_t bmRateControlModes;
    uint8_t  bmLayoutPerStream[8];
} USB_DESC_ATTR uvc_vs_ctrl_t;
ESP_STATIC_ASSERT(sizeof(uvc_vs_ctrl_t) == 48, "Size of uvc_vs_ctrl_t incorrect");

/**
 * @brief Video Frame Descriptor
 *
 * Each format defines its own frame descriptor, but the first 9 fields are always the same.
 *
 * @see USB Device Class Definition for Video Devices: MJPEG Payload 1.5, table 3-2
 * @see USB Device Class Definition for Video Devices: Frame Based Payload 1.5, table 3-2
 * @see USB Device Class Definition for Video Devices: Uncompressed Payload 1.5, table 3-2
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bFrameIndex;
    uint8_t  bmCapabilities;
    uint16_t wWidth;
    uint16_t wHeight;
    uint32_t dwMinBitRate;
    uint32_t dwMaxBitRate;
    union {
        struct {
            uint32_t dwMaxVideoFrameBufferSize;
            uint32_t dwDefaultFrameInterval;
            uint8_t  bFrameIntervalType; /**< 0: Continuous frame interval, 1..255: The number of discrete frame intervals supported (n) */
            union {
                struct {
                    uint32_t dwMinFrameInterval;
                    uint32_t dwMaxFrameInterval;
                    uint32_t dwFrameIntervalStep;
                };
                uint32_t dwFrameInterval[3]; // We must put a fixed size here because of the union type. This is flexible size array though
            };
        } USB_DESC_ATTR mjpeg_uncompressed;
        struct {
            uint32_t dwDefaultFrameInterval;
            uint8_t  bFrameIntervalType; /**< 0: Continuous frame interval, 1..255: The number of discrete frame intervals supported (n) */
            uint32_t dwBytesPerLine;
            union {
                struct {
                    uint32_t dwMinFrameInterval;
                    uint32_t dwMaxFrameInterval;
                    uint32_t dwFrameIntervalStep;
                };
                uint32_t dwFrameInterval[3]; // We must put a fixed size here because of the union type. This is flexible size array though
            };
        } USB_DESC_ATTR frame_based;
    } USB_DESC_ATTR;
} USB_DESC_ATTR uvc_frame_desc_t;

/**
 * @brief Video Stream format descriptor
 *
 * Each format defines its own format descriptor, but the first 5 fields are always the same.
 *
 * @see USB Device Class Definition for Video Devices: MJPEG Payload 1.5, table 3-1
 * @see USB Device Class Definition for Video Devices: Uncompressed Payload 1.5, table 3-1
 * @see USB Device Class Definition for Video Devices: Frame Based Payload 1.5, table 3-1
 */
typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubType;
    uint8_t bFormatIndex;
    uint8_t bNumFrameDescriptors;
    union {
        struct {
            uint8_t guidFormat[16];        // Globally Unique Identifier used to identify stream-encoding format
            uint8_t bBitsPerPixel;         // Number of bits per pixel used to specify color in the decoded video frame
            uint8_t bDefaultFrameIndex;    // Optimum Frame Index (used to select resolution) for this stream
            uint8_t bAspectRatioX;         // The X dimension of the picture aspect ratio
            uint8_t bAspectRatioY;         // The Y dimension of the picture aspect ratio
            uint8_t bmInterlaceFlags;      // Specifies interlace information
            uint8_t bCopyProtect;          // Specifies whether duplication of the video stream is restricted
        } uncompressed_frame_based;
        struct {
            uint8_t bmFlags;
            uint8_t bDefaultFrameIndex;
            uint8_t bAspectRatioX;
            uint8_t bAspectRatioY;
            uint8_t bmInterlaceFlags;
            uint8_t bCopyProtect;
        } mjpeg;
    };
} USB_DESC_ATTR uvc_format_desc_t;

/**
 * @brief Video Control Interface Header Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-3
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint16_t bcdUVC;
    uint16_t wTotalLength;
    uint32_t dwClockFrequency;
    uint8_t  bInCollection;
    uint8_t  baInterfaceNr[];
} USB_DESC_ATTR uvc_vc_header_desc_t;

/**
 * @brief Input Terminal Camera Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-6
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bTerminalID;
    uint16_t wTerminalType;
    uint8_t  bAssocTerminal;
    uint8_t  iTerminal;
    uint16_t wObjectiveFocalLengthMin;
    uint16_t wObjectiveFocalLengthMax;
    uint16_t wOcularFocalLength;
    uint8_t  bControlSize; // Typically == 3. From UVC v1.5 must == 3
    uint8_t  bmControls[3];
} USB_DESC_ATTR uvc_input_terminal_camera_desc_t;

/**
 * @brief Media Transport Input Terminal Descriptor
 *
 * @see USB UVC Video Media Transport Terminal specification ver 1.5, table 3-1
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bTerminalID;
    uint16_t wTerminalType;
    uint8_t  bAssocTerminal;
    uint8_t  iTerminal;
    uint8_t  bControlSize;
    uint8_t  bmControls;
    uint8_t  bTransportModeSize;
    uint8_t  bmTransportModes[5];
} USB_DESC_ATTR uvc_input_terminal_media_desc_t;

/**
 * @brief Output Terminal Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-5
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bTerminalID;
    uint16_t wTerminalType;
    uint8_t  bAssocTerminal;
    uint8_t  bSourceID;
    uint8_t  iTerminal;
} USB_DESC_ATTR uvc_output_terminal_desc_t;

/**
 * @brief Selector Unit Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-7
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bUnitID;
    uint8_t  bNrInPins;
    uint8_t  baSourceID1;
    uint8_t  baSourceID2;
    uint8_t  iSelector;
} USB_DESC_ATTR uvc_selector_unit_desc_t;

/**
 * @brief Processing Unit Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-8
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bUnitID;
    uint8_t  bSourceID;
    uint16_t wMaxMultiplier;
    uint8_t  bControlSize; // Typically == 3. From UVC v1.5 must == 3
    uint8_t  bmControls[3];
    uint8_t  iProcessing;
    uint8_t  bmVideoStandards;
} USB_DESC_ATTR uvc_processing_unit_desc_t;

/**
 * @brief Video Streaming Interface Input Header Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-14
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bNumFormats;
    uint16_t wTotalLength;
    uint8_t  bEndpointAddress;
    uint8_t  bmInfo;
    uint8_t  bTerminalLink;
    uint8_t  bStillCaptureMethod;
    uint8_t  bTriggerSupport;
    uint8_t  bTriggerUsage;
    uint8_t  bControlSize;  // Typically == 1
    uint8_t  bmaControls[]; // This field is an array with size bNumFormats x bControlSize bytes
} USB_DESC_ATTR uvc_vs_input_header_desc_t;

/**
 * @brief Still Image Frame Descriptor
 *
 * Please note that this descriptor can have multiple sizes and compressions
 *
 * @see USB UVC specification ver 1.5, table 3-18
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bEndpointAddress;
    uint8_t  bNumImageSizePatterns;
    uint16_t wWidth;
    uint16_t wHeight;
    uint8_t  bNumCompressionPtn;
    uint8_t  bCompression;
} USB_DESC_ATTR uvc_still_image_frame_desc_t;

/**
 * @brief Color Matching Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-19
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint8_t  bColorPrimaries;
    uint8_t  bTransferCharacteristics;
    uint8_t  bMatrixCoefficients;
} USB_DESC_ATTR uvc_color_matching_desc_t;

/**
 * @brief Video Interface Subclass Codes
 *
 * @see USB UVC specification ver 1.5, table A.2
 */
enum uvc_int_subclass_code {
    UVC_SC_UNDEFINED = 0x00,
    UVC_SC_VIDEOCONTROL = 0x01,
    UVC_SC_VIDEOSTREAMING = 0x02,
    UVC_SC_VIDEO_INTERFACE_COLLECTION = 0x03
};

/**
 * @brief Video Class-Specific Descriptor Types
 *
 * @see USB UVC specification ver 1.5, table A.4
 */
enum uvc_descriptor_type {
    UVC_CS_UNDEFINED = 0x20,
    UVC_CS_DEVICE = 0x21,
    UVC_CS_CONFIGURATION = 0x22,
    UVC_CS_STRING = 0x23,
    UVC_CS_INTERFACE = 0x24,
    UVC_CS_ENDPOINT = 0x25
};

/**
 * @brief Video and Still Image Payload Header
 *
 * The extended fields from table 2-6 are not listed here because this driver does not use them
 * and they can be extended in next UVC specification versions
 *
 * @see USB UVC specification ver 1.5, table 2-5
 */
typedef struct {
    uint8_t bHeaderLength;
    union {
        struct {
            uint8_t frame_id: 1;
            uint8_t end_of_frame: 1;
            uint8_t presentation_time: 1;
            uint8_t source_clock_reference: 1;
            uint8_t payload_specific: 1;
            uint8_t still_image: 1;
            uint8_t error: 1 ;
            uint8_t end_of_header: 1;
        };
        uint8_t val;
    } bmHeaderInfo;
} USB_DESC_ATTR uvc_payload_header_t;

/**
 * @brief Class-specific VC Interrupt Endpoint Descriptor
 *
 * @see USB UVC specification ver 1.5, table 3-12
 */
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubType;
    uint16_t wMaxTransferSize;
} USB_DESC_ATTR uvc_vc_interrupt_ep_desc_t;
