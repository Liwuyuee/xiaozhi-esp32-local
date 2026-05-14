/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <string.h> // For memcpy

#include "esp_log.h"

#include "uvc_stream.h" // For uvc_host_stream_pause()
#include "uvc_types_priv.h"
#include "uvc_check_priv.h"
#include "uvc_frame_priv.h"
#include "uvc_critical_priv.h"

static const char *TAG = "uvc-bulk";

/**
 * @brief Callback function for handling Bulk USB transfers from a UVC camera.
 *
 * This function processes Bulk transfer packets, managing frame data according to a state machine. The characteristics
 * and requirements of Bulk transfers are as follows:
 *
 * - **CRC Included**: Ensures no errors in frame data.
 * - **ACK Mechanism**: Missed packets are retransmitted, ensuring reliable data delivery.
 * - **Packet Headers**: Not all packets contain headers; the end of a transfer is indicated by a short packet
 *   (less than the maximum packet size), and the next packet usually contains a header.
 *
 * To process these packets, a state machine is implemented to track the next expected Bulk packet type:
 * - Start of Frame (SoF), usually followed by data packets in the same transfer
 * - Data packets (no header)
 * - End of Frame (EoF)
 *
 * The function handles USB transfer statuses, manages frame buffers, and invokes user-defined callbacks for
 * completed frames.
 *
 * @param[in] transfer Pointer to the completed USB transfer structure.
 */
void bulk_transfer_callback(usb_transfer_t *transfer)
{
    ESP_LOGD(TAG, "%s", __FUNCTION__);
    uvc_stream_t *uvc_stream = (uvc_stream_t *)transfer->context;

    // Check USB transfer status
    switch (transfer->status) {
    case USB_TRANSFER_STATUS_COMPLETED:
        break;
    case USB_TRANSFER_STATUS_NO_DEVICE:
    case USB_TRANSFER_STATUS_CANCELED:
    case USB_TRANSFER_STATUS_ERROR:
    case USB_TRANSFER_STATUS_OVERFLOW:
    case USB_TRANSFER_STATUS_STALL:
        // On Bulk errors we stop the stream
        //@todo Stall, error and overflow errors should be propagated to the user
        ESP_ERROR_CHECK(uvc_host_stream_pause(uvc_stream)); // This should never fail
        break;
    case USB_TRANSFER_STATUS_TIMED_OUT:
    case USB_TRANSFER_STATUS_SKIPPED: // Should never happen to BULK transfer
    default:
        assert(false);
    }

    if (!UVC_ATOMIC_LOAD(uvc_stream->dynamic.streaming)) {
        return; // If the streaming was turned off, we don't have to do anything
    }

    // In BULK implementation, 'payload' is a constant pointer to constant data,
    // meaning both the pointer and the data it points to cannot be changed.
    // This contrasts with the ISOC implementation, where 'payload' is a variable
    // pointer and is increased after every ISOC packet processing
    const uint8_t *const payload = transfer->data_buffer;
    const uint8_t *payload_data  = payload;
    size_t payload_data_len      = transfer->actual_num_bytes;

    // Note for developers:
    // The order of SoF, Data, and EoF handling is intentional and represents a workaround for detecting EoF in the Bulk stream.
    // Normally, a complete Sample transfer includes two short packets: one marking the last data packet and another with the EoF header.
    // However, if the last data packet has a size equal to the Maximum Packet Size (MPS), there is no zero-length packet between the data and the EoF header.
    // Consequently, it becomes impossible to distinguish between the last data packet and the EoF header.
    // To address this, the hack discards all frames whose last data packet has the MPS size.
    switch (uvc_stream->single_thread.next_bulk_packet) {
    case UVC_STREAM_BULK_PACKET_EOF: {
        const uvc_payload_header_t *payload_header = (const uvc_payload_header_t *)payload;
        uvc_stream->single_thread.next_bulk_packet = UVC_STREAM_BULK_PACKET_SOF;

        if (payload_header->bmHeaderInfo.end_of_frame) {
            assert(payload_header->bmHeaderInfo.frame_id == uvc_stream->single_thread.current_frame_id);
            if (payload_header->bmHeaderInfo.error) {
                uvc_stream->single_thread.skip_current_frame = true;
            }

            // Get the current frame being processed and clear it from the stream,
            // so no more data is written to this frame after the end of frame
            UVC_ENTER_CRITICAL(); // Enter critical section to safely check and modify the stream state.
            uvc_host_frame_t *this_frame = uvc_stream->dynamic.current_frame;
            uvc_stream->dynamic.current_frame = NULL;

            // Determine if we should invoke the frame callback:
            // Only invoke the callback if streaming is active, a frame callback exists,
            // and we have a valid frame to pass to the user.
            const bool invoke_fb_callback = (uvc_stream->dynamic.streaming && uvc_stream->constant.frame_cb && this_frame && !uvc_stream->single_thread.skip_current_frame);
            UVC_EXIT_CRITICAL();

            bool return_frame = true; // Default to returning the frame in case streaming has been stopped
            if (invoke_fb_callback) {
                // Call the user's frame callback. If the callback returns false,
                // we do not return the frame to the empty queue (i.e., the user wants to keep it for processing)
                return_frame = uvc_stream->constant.frame_cb(this_frame, uvc_stream->constant.cb_arg);
            }
            if (return_frame) {
                // If the user has processed the frame (or the stream is stopped), return it to the empty frame queue
                uvc_host_frame_return(uvc_stream, this_frame);
            }
            break;
        }

        __attribute__((fallthrough));  // Fall through! This is not EoF but SoF!
    }
    case UVC_STREAM_BULK_PACKET_SOF: {
        const uvc_payload_header_t *payload_header = (const uvc_payload_header_t *)payload;

        // We detected start of new frame. Update Frame ID and start fetching this frame
        uvc_stream->single_thread.current_frame_id   = payload_header->bmHeaderInfo.frame_id;
        uvc_stream->single_thread.skip_current_frame = payload_header->bmHeaderInfo.error; // Check for error flag

        // Get free frame buffer for this new frame
        UVC_ENTER_CRITICAL();
        const bool need_new_frame = (uvc_stream->dynamic.streaming && !uvc_stream->dynamic.current_frame);
        if (need_new_frame) {
            UVC_EXIT_CRITICAL();
            uvc_stream->dynamic.current_frame = uvc_frame_get_empty(uvc_stream);
            if (uvc_stream->dynamic.current_frame == NULL) {
                // There is no free frame buffer now, skipping this frame
                uvc_stream->single_thread.skip_current_frame = true;

                // Inform the user about the underflow
                uvc_host_stream_callback_t stream_cb = uvc_stream->constant.stream_cb;
                if (stream_cb) {
                    const uvc_host_stream_event_data_t event = {
                        .type = UVC_HOST_FRAME_BUFFER_UNDERFLOW,
                    };
                    stream_cb(&event, uvc_stream->constant.cb_arg);
                }
            }
        } else {
            // We received SoF but current_frame is not NULL: We missed EoF - reset the frame buffer
            uvc_frame_reset(uvc_stream->dynamic.current_frame);
            UVC_EXIT_CRITICAL();
        }

        payload_data     += payload_header->bHeaderLength; // Pointer arithmetic!
        payload_data_len -= payload_header->bHeaderLength;
        uvc_stream->single_thread.next_bulk_packet = UVC_STREAM_BULK_PACKET_DATA;
        __attribute__((fallthrough));  // Fall through! There can be data after SoF!
    }
    case UVC_STREAM_BULK_PACKET_DATA: {
        // We got short packet in data section, next packet is EoF
        if (transfer->data_buffer_size > transfer->actual_num_bytes) {
            uvc_stream->single_thread.next_bulk_packet = UVC_STREAM_BULK_PACKET_EOF;
        }
        // Add received data to frame buffer
        if (!uvc_stream->single_thread.skip_current_frame) {
            uvc_host_frame_t *current_frame = UVC_ATOMIC_LOAD(uvc_stream->dynamic.current_frame);
            esp_err_t ret = uvc_frame_add_data(current_frame, payload_data, payload_data_len);
            if (ret != ESP_OK) {
                // Frame buffer overflow
                uvc_stream->single_thread.skip_current_frame = true;

                // Inform the user about the overflow
                uvc_host_stream_callback_t stream_cb = uvc_stream->constant.stream_cb;
                if (stream_cb) {
                    const uvc_host_stream_event_data_t event = {
                        .type = UVC_HOST_FRAME_BUFFER_OVERFLOW,
                    };
                    stream_cb(&event, uvc_stream->constant.cb_arg);
                }
            }
        }
        break;
    }
    default: abort();
    }

    if (UVC_ATOMIC_LOAD(uvc_stream->dynamic.streaming)) {
        usb_host_transfer_submit(transfer); // Restart the transfer
    }
}
