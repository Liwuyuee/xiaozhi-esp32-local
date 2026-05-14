/*
 * SPDX-FileCopyrightText: 2022-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <string.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "anim_player.h"
#include "anim_vfs.h"
#include "anim_dec.h"

static const char *TAG = "anim_decoder";

uint16_t anim_dec_parse_palette(const image_header_t *header, uint8_t index, bool swap)
{
    const uint8_t *color = &header->palette[index * 4];
    // RGB888: R=color[2], G=color[1], B=color[0]
    // RGB565:
    // - R: (color[2] & 0xF8) << 8
    // - G: (color[1] & 0xFC) << 3
    // - B: (color[0] & 0xF8) >> 3
    return swap ? __builtin_bswap16(((color[2] & 0xF8) << 8) | ((color[1] & 0xFC) << 3) | ((color[0] & 0xF8) >> 3)) : \
           ((color[2] & 0xF8) << 8) | ((color[1] & 0xFC) << 3) | ((color[0] & 0xF8) >> 3);
}

image_format_t anim_dec_parse_header(const uint8_t *data, size_t data_len, image_header_t *header)
{
    // Initialize header fields
    memset(header, 0, sizeof(image_header_t));

    // Read format identifier
    memcpy(header->format, data, 2);
    header->format[2] = '\0';

    if (strncmp(header->format, "_S", 2) == 0) {
        // Parse format
        memcpy(header->version, data + 3, 6);

        // Read bit depth
        header->bit_depth = data[9];

        // Validate bit depth
        if (header->bit_depth != 4 && header->bit_depth != 8) {
            ESP_LOGE(TAG, "Invalid bit depth: %d", header->bit_depth);
            return IMAGE_FORMAT_INVALID;
        }

        header->width = *(uint16_t *)(data + 10);
        header->height = *(uint16_t *)(data + 12);
        header->splits = *(uint16_t *)(data + 14);
        header->split_height = *(uint16_t *)(data + 16);

        // Allocate and read split lengths
        header->split_lengths = (uint16_t *)malloc(header->splits * sizeof(uint16_t));
        if (header->split_lengths == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for split lengths");
            return IMAGE_FORMAT_INVALID;
        }

        for (int i = 0; i < header->splits; i++) {
            header->split_lengths[i] = *(uint16_t *)(data + 18 + i * 2);
        }

        // Calculate number of colors based on bit depth
        header->num_colors = 1 << header->bit_depth;

        // Allocate and read color palette
        header->palette = (uint8_t *)malloc(header->num_colors * 4);
        if (header->palette == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for palette");
            free(header->split_lengths);
            header->split_lengths = NULL;
            return IMAGE_FORMAT_INVALID;
        }

        // Read palette data
        memcpy(header->palette, data + 18 + header->splits * 2, header->num_colors * 4);

        header->data_offset = 18 + header->splits * 2 + header->num_colors * 4;
        return IMAGE_FORMAT_SBMP;

    } else if (strncmp(header->format, "_R", 2) == 0) {
        // Parse redirect format
        uint8_t file_length = *(uint8_t *)(data + 2);

        // For redirect format, we'll use the palette field to store the filename
        header->palette = (uint8_t *)malloc(file_length + 1);
        if (header->palette == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for redirect filename");
            return IMAGE_FORMAT_INVALID;
        }

        // Copy filename to palette buffer
        memcpy(header->palette, data + 3, file_length);
        header->palette[file_length] = '\0';  // Ensure null termination
        header->num_colors = file_length + 1;

        return IMAGE_FORMAT_REDIRECT;

    } else {
        ESP_LOGE(TAG, "Invalid format: %s", header->format);
        printf("%02X %02X %02X\r\n", header->format[0], header->format[1], header->format[2]);
        return IMAGE_FORMAT_INVALID;
    }
}

void anim_dec_calculate_offsets(const image_header_t *header, uint16_t *offsets)
{
    offsets[0] = header->data_offset;
    for (int i = 1; i < header->splits; i++) {
        offsets[i] = offsets[i - 1] + header->split_lengths[i - 1];
    }
}

void anim_dec_free_header(image_header_t *header)
{
    if (header->split_lengths != NULL) {
        free(header->split_lengths);
        header->split_lengths = NULL;
    }
    if (header->palette != NULL) {
        free(header->palette);
        header->palette = NULL;
    }
}

esp_err_t anim_dec_rte_decode(const uint8_t *input, size_t input_len, uint8_t *output, size_t output_len)
{
    size_t in_pos = 0;
    size_t out_pos = 0;

    while (in_pos + 1 <= input_len) {
        uint8_t count = input[in_pos++];
        uint8_t value = input[in_pos++];

        if (out_pos + count > output_len) {
            ESP_LOGE(TAG, "Output buffer overflow, %d > %d", out_pos + count, output_len);
            return ESP_FAIL;
        }

        for (uint8_t i = 0; i < count; i++) {
            output[out_pos++] = value;
        }
    }

    return ESP_OK;
}

static Node* create_node()
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    return node;
}

static void free_tree(Node* node)
{
    if (!node) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

static esp_err_t decode_huffman_data(const uint8_t* data, size_t data_len,
                                     const uint8_t* dict_bytes, size_t dict_len,
                                     uint8_t* output, size_t* output_len)
{
    if (!data || !dict_bytes || data_len == 0 || dict_len == 0) {
        *output_len = 0;
        return ESP_OK;
    }

    // Get padding
    uint8_t padding = dict_bytes[0];
    // printf("Padding bits: %u\n", padding);
    size_t dict_pos = 1;

    // Reconstruct Huffman Tree
    Node* root = create_node();
    Node* current = NULL;

    while (dict_pos < dict_len) {
        uint8_t byte_val = dict_bytes[dict_pos++];
        uint8_t code_len = dict_bytes[dict_pos++];

        size_t code_byte_len = (code_len + 7) / 8;
        uint64_t code = 0;
        for (size_t i = 0; i < code_byte_len; ++i) {
            code = (code << 8) | dict_bytes[dict_pos++];
        }

        // Insert into tree
        current = root;
        for (int bit = code_len - 1; bit >= 0; --bit) {
            int bit_val = (code >> bit) & 1;
            if (bit_val == 0) {
                if (!current->left) {
                    current->left = create_node();
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = create_node();
                }
                current = current->right;
            }
        }
        current->is_leaf = 1;
        current->value = byte_val;
    }

    // Convert bitstream
    size_t total_bits = data_len * 8;
    if (padding > 0) {
        total_bits -= padding;
    }

    current = root;
    size_t out_pos = 0;

    // Process each bit
    for (size_t bit_index = 0; bit_index < total_bits; bit_index++) {
        size_t byte_idx = bit_index / 8;
        int bit_offset = 7 - (bit_index % 8);  // Most significant bit first
        int bit = (data[byte_idx] >> bit_offset) & 1;

        if (bit == 0) {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current == NULL) {
            ESP_LOGE(TAG, "Invalid path in Huffman tree at bit %zu", bit_index);
            break;
        }

        if (current->is_leaf) {
            output[out_pos++] = current->value;
            current = root;
        }
    }

    *output_len = out_pos;
    free_tree(root);
    return ESP_OK;
}

esp_err_t anim_dec_huffman_decode(const uint8_t* buffer, size_t buflen, uint8_t* output, size_t* output_len)
{
    if (!buffer || buflen < 1 || !output || !output_len) {
        ESP_LOGE(TAG, "Invalid parameters: buffer=%p, buflen=%d, output=%p, output_len=%p",
                 buffer, buflen, output, output_len);
        return ESP_FAIL;
    }

    // First byte indicates encoding type (already checked in caller)
    // Next two bytes contain dictionary length (big endian)
    uint16_t dict_len = (buffer[2] << 8) | buffer[1];
    if (buflen < 3 + dict_len) {
        ESP_LOGE(TAG, "Buffer too short for dictionary");
        return ESP_FAIL;
    }

    // Calculate data length
    size_t data_len = buflen - 3 - dict_len;
    if (data_len == 0) {
        ESP_LOGE(TAG, "No data to decode");
        return ESP_FAIL;
    }

    // Decode data
    esp_err_t ret = decode_huffman_data(buffer + 3 + dict_len, data_len,
                                        buffer + 3, dict_len,
                                        output, output_len);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Huffman decoding failed: %d", ret);
        return ESP_FAIL;
    }

    return ESP_OK;
}
