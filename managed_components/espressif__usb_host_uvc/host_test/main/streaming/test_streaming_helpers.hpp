/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <string>
#include <span>
#include <algorithm>
#include <cstdint>

#include "usb/usb_types_stack.h"
#include "usb/usb_types_uvc.h"

extern "C" {
#include "Mockusb_host.h"
    void bulk_transfer_callback(usb_transfer_t *transfer);
    void isoc_transfer_callback(usb_transfer_t *transfer);
}

#define HEADER_LEN (12)

/**
 * @brief Send bulk frame to the UVC driver
 *
 * Only the first and last transfer contains header
 */
inline void test_streaming_bulk_send_frame(size_t transfer_size, void *transfer_context, std::span<const uint8_t> data, uint8_t frame_id = 0, bool error_in_sof = false, bool error_in_eof = false, bool eof_in_sof = false)
{
    assert(transfer_size > HEADER_LEN);
    assert(!data.empty());
    uint8_t *data_buffer = new uint8_t[transfer_size];
    assert(data_buffer);
    usb_transfer_t _transfer = {
        .data_buffer = data_buffer,
        .data_buffer_size = transfer_size,
        .num_bytes = 0,
        .actual_num_bytes = 0,
        .flags = 0,
        .device_handle = nullptr,
        .bEndpointAddress = 0,
        .status = USB_TRANSFER_STATUS_COMPLETED,
        .timeout_ms = 0,
        .callback = nullptr,
        .context = transfer_context,
        .num_isoc_packets = 0,
    };
    usb_transfer_t *transfer = &_transfer;


    // Reinterpret transfer->data_buffer as a pointer to uvc_payload_header_t
    uvc_payload_header_t *header_sof = reinterpret_cast<uvc_payload_header_t *>(transfer->data_buffer);
    header_sof->bHeaderLength = HEADER_LEN;
    header_sof->bmHeaderInfo.val = 0;
    header_sof->bmHeaderInfo.end_of_header = 1;
    header_sof->bmHeaderInfo.frame_id = frame_id;
    header_sof->bmHeaderInfo.error = error_in_sof;
    header_sof->bmHeaderInfo.end_of_frame = eof_in_sof;


    // Add Frame data to first SoF transfer
    const size_t first_chunk_size = std::min(transfer->data_buffer_size - HEADER_LEN, data.size());
    std::copy_n(data.begin(), first_chunk_size, transfer->data_buffer + HEADER_LEN);
    transfer->actual_num_bytes = first_chunk_size + HEADER_LEN;
    usb_host_transfer_submit_ExpectAndReturn(transfer, ESP_OK); // Each must be re-submitted
    bulk_transfer_callback(transfer);

    // Loop through the large array in chunks with modern C++
    const size_t ChunkSize = transfer->data_buffer_size;
    for (size_t offset = first_chunk_size; offset < data.size(); offset += ChunkSize) {
        // Get a span representing the current chunk
        auto chunk = data.subspan(offset, std::min(ChunkSize, data.size() - offset));

        // Copy the chunk from the large array to the buffer
        std::copy(chunk.begin(), chunk.end(), transfer->data_buffer);

        // Process the chunk
        transfer->actual_num_bytes = chunk.size();
        usb_host_transfer_submit_ExpectAndReturn(transfer, ESP_OK); // Each must be re-submitted
        bulk_transfer_callback(transfer);
    }

    // Send EoF
    // Reinterpret transfer->data_buffer as a pointer to uvc_payload_header_t
    uvc_payload_header_t *header_eof = reinterpret_cast<uvc_payload_header_t *>(transfer->data_buffer);
    header_eof->bHeaderLength = HEADER_LEN;
    header_eof->bmHeaderInfo.val = 0;
    header_eof->bmHeaderInfo.end_of_frame = 1;
    header_eof->bmHeaderInfo.end_of_header = 1;
    header_eof->bmHeaderInfo.frame_id = frame_id;
    header_eof->bmHeaderInfo.error = error_in_eof;
    transfer->actual_num_bytes = HEADER_LEN;
    usb_host_transfer_submit_ExpectAndReturn(transfer, ESP_OK); // Each must be re-submitted
    bulk_transfer_callback(transfer);
    delete[] data_buffer;
}

/**
 * @brief Send isoc frame to the UVC driver
 *
 * Each ISOC packet contains header
 */
inline void test_streaming_isoc_send_frame(size_t transfer_size, void *transfer_context, std::span<const uint8_t> data, uint8_t frame_id = 0, bool error_in_sof = false, bool error_in_eof = false, bool eof_in_sof = false)
{
    assert(transfer_size > HEADER_LEN);
    assert(!data.empty());
    uint8_t *data_buffer = new uint8_t[transfer_size];
    assert(data_buffer);
    // Define the number of isochronous packets
    constexpr int num_isoc_packets = 8;

    // Calculate the allocation size, including space for isoc_packet_desc
    size_t allocation_size = sizeof(usb_transfer_t) + num_isoc_packets * sizeof(usb_isoc_packet_desc_t);

    // Allocate memory for usb_transfer_s with extra space for isoc_packet_desc
    usb_transfer_t *transfer = static_cast<usb_transfer_t *>(operator new (allocation_size));

    // Initialize the struct using placement new
    new (transfer) usb_transfer_t{
        .data_buffer = data_buffer,
        .data_buffer_size = transfer_size,
        .num_bytes = 0,
        .actual_num_bytes = 0,
        .flags = 0,
        .device_handle = nullptr,
        .bEndpointAddress = 0,
        .status = USB_TRANSFER_STATUS_COMPLETED,
        .timeout_ms = 0,
        .callback = nullptr,
        .context = transfer_context,
        .num_isoc_packets = num_isoc_packets,
    };

    // Loop through the large array in chunks with modern C++
    size_t offset = 0;
    const size_t transfer_frame_data_size = transfer->data_buffer_size - (transfer->num_isoc_packets * HEADER_LEN); // Each packet contains its header
    // printf("frame data in each transfer %zu\n", transfer_frame_data_size);

    while (offset < data.size()) {
        // We have new USB transfer, init it to defaults
        transfer->actual_num_bytes = 0;
        uint8_t *write_ptr = transfer->data_buffer;

        for (int packet_idx = 0; packet_idx < transfer->num_isoc_packets; packet_idx++) { // All ISOC packets must be filled, even if data is empty
            transfer->isoc_packet_desc[packet_idx].actual_num_bytes = 0;
            transfer->isoc_packet_desc[packet_idx].status = USB_TRANSFER_STATUS_COMPLETED;
            transfer->isoc_packet_desc[packet_idx].num_bytes = transfer->data_buffer_size / transfer->num_isoc_packets;

            // **HEADER SECTION**
            // All ISOC packets must have its header
            // Reinterpret transfer->data_buffer as a pointer to uvc_payload_header_t
            uvc_payload_header_t *header = reinterpret_cast<uvc_payload_header_t *>(write_ptr);
            //printf("\tWriting @ %p\n", write_ptr);
            header->bHeaderLength = HEADER_LEN;
            header->bmHeaderInfo.val = 0;
            header->bmHeaderInfo.end_of_header = 1;
            header->bmHeaderInfo.frame_id = frame_id;

            // This is Start of Frame
            if (offset == 0) {
                //printf("SoF\n");
                uvc_payload_header_t *header = reinterpret_cast<uvc_payload_header_t *>(transfer->data_buffer);
                header->bmHeaderInfo.error = error_in_sof;
            }
            write_ptr += HEADER_LEN; // Move write pointer to start of data section
            transfer->isoc_packet_desc[packet_idx].actual_num_bytes += HEADER_LEN;
            transfer->actual_num_bytes += HEADER_LEN; // This is not actually checked by the UVC driver, leaving it here for completeness

            // **DATA SECTION**
            size_t packet_frame_data_size = std::min(transfer_frame_data_size / transfer->num_isoc_packets, data.size() - offset);

            // This is End of Frame
            if (packet_frame_data_size < (transfer_frame_data_size / transfer->num_isoc_packets)) {
                //printf("EoF\n");
                header->bmHeaderInfo.error = error_in_eof;
                header->bmHeaderInfo.end_of_frame = 1;
            }

            // Get a span representing the current chunk of frame data
            auto chunk = data.subspan(offset, packet_frame_data_size);

            // Copy the chunk from the large array to the buffer
            std::copy(chunk.begin(), chunk.end(), write_ptr);

            transfer->actual_num_bytes += chunk.size(); // This is not actually checked by the UVC driver, leaving it here for completeness
            transfer->isoc_packet_desc[packet_idx].actual_num_bytes += chunk.size();
            write_ptr += chunk.size();
            offset += chunk.size();
            //printf("\tcreating packet %d bytes\n", transfer->isoc_packet_desc[packet_idx].actual_num_bytes);
        }

        // Process the transfer
        //printf("\tsending transfer %d bytes\n", transfer->actual_num_bytes);
        usb_host_transfer_submit_ExpectAndReturn(transfer, ESP_OK); // Each must be re-submitted
        isoc_transfer_callback(transfer);
    }

    delete[] data_buffer;
}
