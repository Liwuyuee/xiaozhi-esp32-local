/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <inttypes.h>
#include <stdbool.h>
#include <sys/queue.h>

#include "usb/usb_host.h"
#include "usb/uvc_host.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef struct uvc_host_stream_s uvc_stream_t;

/**
 * @brief Enum for simple state machine of Bulk frame data processing
 */
typedef enum {
    UVC_STREAM_BULK_PACKET_SOF = 0,
    UVC_STREAM_BULK_PACKET_DATA,
    UVC_STREAM_BULK_PACKET_EOF,
} uvc_stream_bulk_packet_type_t;

struct uvc_host_stream_s {
    SLIST_ENTRY(uvc_host_stream_s) list_entry;

    struct {
        // UVC driver related members
        uvc_host_stream_callback_t stream_cb; // User's callback for stream events
        uvc_host_frame_callback_t frame_cb;   // User's frame callback
        void *cb_arg;                         // Common argument for user's callbacks
        QueueHandle_t empty_fb_queue;         // Queue of empty framebuffers

        // Constant USB descriptor values
        uint16_t bcdUVC;                      // Version of UVC specs this device implements
        uint8_t  bInterfaceNumber;            // USB Video Streaming interface claimed by this stream. Needed for ISOC Stream start and CTRL transfers
        uint8_t  bAlternateSetting;           // Alternate setting for selected interface. Needed for ISOC Stream start
        uint8_t  bEndpointAddress;            // Streaming endpoint address. Needed for BULK Stream stop

        // USB host related members
        usb_device_handle_t dev_hdl;          // USB device handle
        unsigned num_of_xfers;                // Number of USB transfers
        usb_transfer_t **xfers;               // Pointer to array of USB transfers. Accessible only by the UVC driver
    } constant; // Constant members do no change after installation thus do not require a critical section

    struct {
        uvc_host_stream_format_t vs_format;   // Format of the video stream
        uint32_t dwMaxVideoFrameSize;         // Maximum frame size of this vs_format
        uvc_host_frame_t *current_frame;      // Frame that is being written to
        bool streaming;                       // Flag whether stream is on/off
    } dynamic; // Dynamic members require a critical section

    struct {
        uvc_stream_bulk_packet_type_t next_bulk_packet; // Bulk only: next expected packet
        bool skip_current_frame;                        // Flag to skip current frame. An error has occurred in the stream
        uint8_t current_frame_id;                       // Frame ID can be only 0 or 1. But we also allow setting it to invalid value = 2.
    } single_thread; // Single thread members are only accessed from 1 thread, so they do not need protection
};
