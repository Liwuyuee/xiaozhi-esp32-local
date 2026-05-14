/*
 * SPDX-FileCopyrightText: 2022-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

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

typedef enum {
    IMAGE_FORMAT_SBMP = 0,  // Split BMP format
    IMAGE_FORMAT_REDIRECT = 1,  // Redirect format
    IMAGE_FORMAT_INVALID = 2
} image_format_t;

typedef enum {
    ENCODING_TYPE_RLE = 0,
    ENCODING_TYPE_HUFFMAN = 1,
    ENCODING_TYPE_INVALID = 2
} encoding_type_t;

// Image header structure
typedef struct {
    char format[3];        // Format identifier (e.g., "_S")
    char version[6];       // Version string
    uint8_t bit_depth;     // Bit depth (4 or 8)
    uint16_t width;        // Image width
    uint16_t height;       // Image height
    uint16_t splits;       // Number of splits
    uint16_t split_height; // Height of each split
    uint16_t *split_lengths; // Data length of each split
    uint16_t data_offset;  // Offset to data segment
    uint8_t *palette;      // Color palette (dynamically allocated)
    int num_colors;        // Number of colors in palette
} image_header_t;

// Huffman tree node structure
typedef struct huffman_node {
    uint8_t value;  // Character value for leaf nodes
    struct huffman_node *left;
    struct huffman_node *right;
} huffman_node_t;

typedef struct Node {
    uint8_t is_leaf;
    uint8_t value;
    struct Node* left;
    struct Node* right;
} Node;

/**
 * @brief Parse the header of an image file
 * @param data Pointer to the image data
 * @param data_len Length of the image data
 * @param header Pointer to store the parsed header information
 * @return Image format type (SBMP, REDIRECT, or INVALID)
 */
image_format_t anim_dec_parse_header(const uint8_t *data, size_t data_len, image_header_t *header);

uint16_t anim_dec_parse_palette(const image_header_t *header, uint8_t index, bool swap);

void anim_dec_calculate_offsets(const image_header_t *header, uint16_t *offsets);

void anim_dec_free_header(image_header_t *header);

esp_err_t anim_dec_huffman_decode(const uint8_t* buffer, size_t buflen, uint8_t* output, size_t* output_len);

esp_err_t anim_dec_rte_decode(const uint8_t *input, size_t input_len, uint8_t *output, size_t output_len);

#ifdef __cplusplus
}
#endif