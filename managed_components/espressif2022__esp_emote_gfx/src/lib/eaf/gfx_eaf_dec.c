/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 * @file gfx_eaf_dec.c
 * @brief EAF (Emote Animation Format) decoder implementation
 */

#include <string.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "gfx_eaf_dec.h"
#include "esp_jpeg_dec.h"

static const char *TAG = "eaf";

/**********************
 *  STATIC VARIABLES
 **********************/
static eaf_block_decoder_cb_t g_eaf_decoders[EAF_ENCODING_MAX] = {0};

/**********************
 *  STATIC HELPER FUNCTIONS
 **********************/

static uint32_t eaf_calculate_checksum(const uint8_t *data, uint32_t length)
{
    uint32_t checksum = 0;
    for (uint32_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum;
}

/* Huffman Tree Helper Functions */
static eaf_huffman_node_t *eaf_huffman_node_create(void)
{
    eaf_huffman_node_t *node = (eaf_huffman_node_t *)calloc(1, sizeof(eaf_huffman_node_t));
    return node;
}

static void eaf_huffman_tree_free(eaf_huffman_node_t *node)
{
    if (!node) {
        return;
    }
    eaf_huffman_tree_free(node->left);
    eaf_huffman_tree_free(node->right);
    free(node);
}

static esp_err_t eaf_huffman_decode_data(const uint8_t *encoded_data, size_t encoded_len,
        const uint8_t *dict_data, size_t dict_len,
        uint8_t *decoded_data, size_t *decoded_len)
{
    if (!encoded_data || !dict_data || encoded_len == 0 || dict_len == 0) {
        *decoded_len = 0;
        return ESP_OK;
    }

    // Get padding bits from dictionary
    uint8_t padding_bits = dict_data[0];
    size_t dict_pos = 1;

    // Reconstruct Huffman Tree
    eaf_huffman_node_t *root = eaf_huffman_node_create();
    eaf_huffman_node_t *current_node = NULL;

    while (dict_pos < dict_len) {
        uint8_t symbol = dict_data[dict_pos++];
        uint8_t code_len = dict_data[dict_pos++];

        size_t code_byte_len = (code_len + 7) / 8;
        uint64_t code = 0;
        for (size_t i = 0; i < code_byte_len; ++i) {
            code = (code << 8) | dict_data[dict_pos++];
        }

        // Insert symbol into tree
        current_node = root;
        for (int bit_pos = code_len - 1; bit_pos >= 0; --bit_pos) {
            int bit_val = (code >> bit_pos) & 1;
            if (bit_val == 0) {
                if (!current_node->left) {
                    current_node->left = eaf_huffman_node_create();
                }
                current_node = current_node->left;
            } else {
                if (!current_node->right) {
                    current_node->right = eaf_huffman_node_create();
                }
                current_node = current_node->right;
            }
        }
        current_node->is_leaf = 1;
        current_node->symbol = symbol;
    }

    // Calculate total bits to decode
    size_t total_bits = encoded_len * 8;
    if (padding_bits > 0) {
        total_bits -= padding_bits;
    }

    current_node = root;
    size_t decoded_pos = 0;

    // Process each bit in the encoded data
    for (size_t bit_index = 0; bit_index < total_bits; bit_index++) {
        size_t byte_idx = bit_index / 8;
        int bit_offset = 7 - (bit_index % 8);  // Most significant bit first
        int bit_val = (encoded_data[byte_idx] >> bit_offset) & 1;

        if (bit_val == 0) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }

        if (current_node == NULL) {
            ESP_LOGE(TAG, "Invalid path in Huffman tree at bit %d", (int)bit_index);
            break;
        }

        if (current_node->is_leaf) {
            decoded_data[decoded_pos++] = current_node->symbol;
            current_node = root;
        }
    }

    *decoded_len = decoded_pos;
    eaf_huffman_tree_free(root);
    return ESP_OK;
}

/**********************
 *  HEADER FUNCTIONS
 **********************/

eaf_format_type_t eaf_get_frame_info(eaf_format_handle_t handle, int frame_index, eaf_header_t *frame_info)
{
    if (!handle) {
        ESP_LOGE(TAG, "Invalid handle");
        return EAF_FORMAT_INVALID;
    }

    const uint8_t *file_data = eaf_get_frame_data(handle, frame_index);
    if (!file_data) {
        ESP_LOGE(TAG, "Failed to get frame data for frame %d", frame_index);
        return EAF_FORMAT_INVALID;
    }

    size_t file_size = eaf_get_frame_size(handle, frame_index);
    if (file_size <= 0) {
        ESP_LOGE(TAG, "Invalid frame size for frame %d", frame_index);
        return EAF_FORMAT_INVALID;
    }

    memset(frame_info, 0, sizeof(eaf_header_t));

    memcpy(frame_info->format, file_data, 2);
    frame_info->format[2] = '\0';

    if (strncmp(frame_info->format, "_S", 2) == 0) {
        memcpy(frame_info->version, file_data + 3, 6);

        frame_info->bit_depth = file_data[9];

        if (frame_info->bit_depth != 4 && frame_info->bit_depth != 8 && frame_info->bit_depth != 24) {
            ESP_LOGE(TAG, "Invalid bit depth: %d", frame_info->bit_depth);
            return EAF_FORMAT_INVALID;
        }

        frame_info->width = *(uint16_t *)(file_data + 10);
        frame_info->height = *(uint16_t *)(file_data + 12);
        frame_info->blocks = *(uint16_t *)(file_data + 14);
        frame_info->block_height = *(uint16_t *)(file_data + 16);

        frame_info->block_len = (uint32_t *)malloc(frame_info->blocks * sizeof(uint32_t));
        if (frame_info->block_len == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for split lengths");
            return EAF_FORMAT_INVALID;
        }

        for (int i = 0; i < frame_info->blocks; i++) {
            frame_info->block_len[i] = *(uint32_t *)(file_data + 18 + i * 4);
        }

        frame_info->num_colors = 1 << frame_info->bit_depth;

        if (frame_info->bit_depth == 24) {
            frame_info->num_colors = 0;
            frame_info->palette = NULL;
        } else {
            frame_info->palette = (uint8_t *)malloc(frame_info->num_colors * 4);
            if (frame_info->palette == NULL) {
                ESP_LOGE(TAG, "Failed to allocate memory for palette");
                free(frame_info->block_len);
                frame_info->block_len = NULL;
                return EAF_FORMAT_INVALID;
            }

            memcpy(frame_info->palette, file_data + 18 + frame_info->blocks * 4, frame_info->num_colors * 4);
        }
        frame_info->data_offset = 18 + frame_info->blocks * 4 + frame_info->num_colors * 4;
        return EAF_FORMAT_VALID;

    } else if (strncmp(frame_info->format, "_R", 2) == 0) {
        uint8_t file_length = *(uint8_t *)(file_data + 2);

        frame_info->palette = (uint8_t *)malloc(file_length + 1);
        if (frame_info->palette == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for redirect filename");
            return EAF_FORMAT_INVALID;
        }

        memcpy(frame_info->palette, file_data + 3, file_length);
        frame_info->palette[file_length] = '\0';
        frame_info->num_colors = file_length + 1;

        return EAF_FORMAT_REDIRECT;
    } else if (strncmp(frame_info->format, "_C", 2) == 0) {
        ESP_LOGE(TAG, "Invalid format: %s", frame_info->format);
        return EAF_FORMAT_FLAG;
    } else {
        ESP_LOGE(TAG, "Invalid format: %s", frame_info->format);
        return EAF_FORMAT_INVALID;
    }
}

void eaf_free_header(eaf_header_t *header)
{
    if (header->block_len != NULL) {
        free(header->block_len);
        header->block_len = NULL;
    }
    if (header->palette != NULL) {
        free(header->palette);
        header->palette = NULL;
    }
}

void eaf_calculate_offsets(const eaf_header_t *header, uint32_t *offsets)
{
    offsets[0] = header->data_offset;
    for (int i = 1; i < header->blocks; i++) {
        offsets[i] = offsets[i - 1] + header->block_len[i - 1];
    }
}

/**********************
 *  PALETTE FUNCTIONS
 **********************/

gfx_color_t eaf_palette_get_color(const eaf_header_t *header, uint8_t color_index, bool swap_bytes)
{
    const uint8_t *color_data = &header->palette[color_index * 4];
    // RGB888: R=color[2], G=color[1], B=color[0]
    // RGB565:
    // - R: (color[2] & 0xF8) << 8
    // - G: (color[1] & 0xFC) << 3
    // - B: (color[0] & 0xF8) >> 3
    gfx_color_t result;
    uint16_t rgb565_value = swap_bytes ? __builtin_bswap16(((color_data[2] & 0xF8) << 8) | ((color_data[1] & 0xFC) << 3) | ((color_data[0] & 0xF8) >> 3)) : \
                            ((color_data[2] & 0xF8) << 8) | ((color_data[1] & 0xFC) << 3) | ((color_data[0] & 0xF8) >> 3);
    result.full = rgb565_value;
    return result;
}

/**********************
 *  DECODING FUNCTIONS
 **********************/

static esp_err_t eaf_decode_huffman_rle(const uint8_t *input_data, size_t input_size,
                                        uint8_t *output_buffer, size_t *out_size,
                                        bool swap_color)
{
    if (out_size == NULL || *out_size == 0) {
        ESP_LOGE(TAG, "Output size is invalid");
        return ESP_FAIL;
    }

    uint8_t *huffman_buffer = malloc(*out_size);
    if (huffman_buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for Huffman buffer");
        return ESP_FAIL;
    }

    size_t huffman_out_size = *out_size;
    esp_err_t ret = eaf_decode_huffman(input_data, input_size, huffman_buffer, &huffman_out_size, swap_color);
    if (ret == ESP_OK) {
        ret = eaf_decode_rle(huffman_buffer, huffman_out_size, output_buffer, out_size, swap_color);
        *out_size = huffman_out_size;
    }

    free(huffman_buffer);
    return ret;
}

static esp_err_t eaf_register_decoder(eaf_encoding_type_t type, eaf_block_decoder_cb_t decoder)
{
    if (type >= EAF_ENCODING_MAX) {
        ESP_LOGE(TAG, "Invalid encoding type: %d", type);
        return ESP_ERR_INVALID_ARG;
    }

    if (g_eaf_decoders[type] != NULL) {
        ESP_LOGW(TAG, "Decoder already registered for type: %d", type);
    }

    g_eaf_decoders[type] = decoder;
    return ESP_OK;
}

static esp_err_t eaf_init_decoders(void)
{
    esp_err_t ret = ESP_OK;

    ret |= eaf_register_decoder(EAF_ENCODING_RLE, eaf_decode_rle);
    ret |= eaf_register_decoder(EAF_ENCODING_HUFFMAN, eaf_decode_huffman_rle);
    ret |= eaf_register_decoder(EAF_ENCODING_HUFFMAN_DIRECT, eaf_decode_huffman);
    ret |= eaf_register_decoder(EAF_ENCODING_JPEG, eaf_decode_jpeg);

    return ret;
}

esp_err_t eaf_decode_block(const eaf_header_t *header, const uint8_t *block_data,
                           int block_len, uint8_t *decode_buffer, bool swap_color)
{
    uint8_t encoding_type = block_data[0];
    int width = header->width;
    int block_height = header->block_height;

    esp_err_t decode_result = ESP_FAIL;

    if (encoding_type >= sizeof(g_eaf_decoders) / sizeof(g_eaf_decoders[0])) {
        ESP_LOGE(TAG, "Unknown encoding type: %02X", encoding_type);
        return ESP_FAIL;
    }

    eaf_block_decoder_cb_t decoder = g_eaf_decoders[encoding_type];
    if (!decoder) {
        ESP_LOGE(TAG, "No decoder for encoding type: %02X", encoding_type);
        return ESP_FAIL;
    }

    size_t out_size;
    if (encoding_type == EAF_ENCODING_JPEG) {
        out_size = width * block_height * 2; // RGB565 = 2 bytes per pixel
    } else {
        out_size = width * block_height;
    }

    decode_result = decoder(block_data + 1, block_len - 1, decode_buffer, &out_size, swap_color);

    if (decode_result != ESP_OK) {
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t eaf_decode_rle(const uint8_t *input_data, size_t input_size,
                         uint8_t *output_buffer, size_t *out_size,
                         bool swap_color)
{
    (void)swap_color; // Unused parameter

    size_t in_pos = 0;
    size_t out_pos = 0;

    while (in_pos + 1 <= input_size) {
        uint8_t repeat_count = input_data[in_pos++];
        uint8_t repeat_value = input_data[in_pos++];

        if (out_pos + repeat_count > *out_size) {
            ESP_LOGE(TAG, "Decompressed buffer overflow, %d > %d", out_pos + repeat_count, *out_size);
            return ESP_FAIL;
        }

        uint32_t value_4bytes = repeat_value | (repeat_value << 8) | (repeat_value << 16) | (repeat_value << 24);
        while (repeat_count >= 4) {
            *((uint32_t *)(output_buffer + out_pos)) = value_4bytes;
            out_pos += 4;
            repeat_count -= 4;
        }

        while (repeat_count > 0) {
            output_buffer[out_pos++] = repeat_value;
            repeat_count--;
        }
    }

    *out_size = out_pos;
    return ESP_OK;
}

esp_err_t eaf_decode_jpeg(const uint8_t *jpeg_data, size_t jpeg_size,
                          uint8_t *decode_buffer, size_t *out_size, bool swap_color)
{
    uint32_t w, h;
    jpeg_dec_config_t config = {
        .output_type = swap_color ? JPEG_PIXEL_FORMAT_RGB565_BE : JPEG_PIXEL_FORMAT_RGB565_LE,
        .rotate = JPEG_ROTATE_0D,
    };

    jpeg_dec_handle_t jpeg_dec;
    if (jpeg_dec_open(&config, &jpeg_dec) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open JPEG decoder");
        return ESP_FAIL;
    }

    jpeg_dec_io_t *jpeg_io = malloc(sizeof(jpeg_dec_io_t));
    jpeg_dec_header_info_t *out_info = malloc(sizeof(jpeg_dec_header_info_t));
    if (!jpeg_io || !out_info) {
        if (jpeg_io) {
            free(jpeg_io);
        }
        if (out_info) {
            free(out_info);
        }
        jpeg_dec_close(jpeg_dec);
        ESP_LOGE(TAG, "Failed to allocate memory for JPEG decoder");
        return ESP_FAIL;
    }

    jpeg_io->inbuf = (unsigned char *)jpeg_data;
    jpeg_io->inbuf_len = jpeg_size;

    jpeg_error_t ret = jpeg_dec_parse_header(jpeg_dec, jpeg_io, out_info);
    if (ret == JPEG_ERR_OK) {
        w = out_info->width;
        h = out_info->height;

        size_t required_size = w * h * 2; // RGB565 = 2 bytes per pixel
        if (*out_size < required_size) {
            ESP_LOGE(TAG, "Output buffer too small: need %zu, got %zu", required_size, *out_size);
            free(jpeg_io);
            free(out_info);
            jpeg_dec_close(jpeg_dec);
            return ESP_ERR_INVALID_SIZE;
        }

        jpeg_io->outbuf = decode_buffer;
        ret = jpeg_dec_process(jpeg_dec, jpeg_io);
        if (ret != JPEG_ERR_OK) {
            free(jpeg_io);
            free(out_info);
            jpeg_dec_close(jpeg_dec);
            ESP_LOGE(TAG, "Failed to decode JPEG: %d", ret);
            return ESP_FAIL;
        }
        *out_size = required_size;
    } else {
        free(jpeg_io);
        free(out_info);
        jpeg_dec_close(jpeg_dec);
        ESP_LOGE(TAG, "Failed to parse JPEG header");
        return ESP_FAIL;
    }

    free(jpeg_io);
    free(out_info);
    jpeg_dec_close(jpeg_dec);
    return ESP_OK;
}

esp_err_t eaf_decode_huffman(const uint8_t *input_data, size_t input_size,
                             uint8_t *output_buffer, size_t *out_size,
                             bool swap_color)
{
    (void)swap_color; // Unused parameter
    size_t decoded_size = *out_size;

    if (!input_data || input_size < 3 || !output_buffer) {
        ESP_LOGE(TAG, "Invalid parameters: input_data=%p, input_size=%d, output_buffer=%p",
                 input_data, input_size, output_buffer);
        return ESP_FAIL;
    }

    uint16_t dict_size = (input_data[1] << 8) | input_data[0];
    if (input_size < 2 + dict_size) {
        ESP_LOGE(TAG, "Compressed data too short for dictionary");
        return ESP_FAIL;
    }

    size_t encoded_size = input_size - 2 - dict_size;
    esp_err_t ret = ESP_OK;

    // Special case: when the block is single color, the dictionary may contain only one symbol and the data length is 0
    if (encoded_size == 0) {

        size_t dict_pos = 1; // dict_bytes[0] is padding
        int symbol_count = 0;
        uint8_t single_symbol = 0;
        const uint8_t *dict_bytes = input_data + 2;

        while (dict_pos < dict_size) {
            uint8_t byte_val = dict_bytes[dict_pos++];
            uint8_t code_len = dict_bytes[dict_pos++];
            size_t code_byte_len = (size_t)((code_len + 7) / 8);
            if (dict_pos + code_byte_len > dict_size) {
                break;
            }
            dict_pos += code_byte_len;
            symbol_count++;
            single_symbol = byte_val;
            if (symbol_count > 1) {
                break;
            }
        }

        if (symbol_count == 1) {
            memset(output_buffer, single_symbol, decoded_size);
        }
    } else {
        ret = eaf_huffman_decode_data(input_data + 2 + dict_size, encoded_size,
                                      input_data + 2, dict_size,
                                      output_buffer, &decoded_size);
    }

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Huffman decoding failed: %d", ret);
        return ESP_FAIL;
    }

    if (decoded_size > *out_size) {
        ESP_LOGE(TAG, "Decoded data too large: %d > %d", decoded_size, *out_size);
        return ESP_FAIL;
    }
    *out_size = decoded_size;

    return ESP_OK;
}

/**********************
 *  FORMAT FUNCTIONS
 **********************/

esp_err_t eaf_init(const uint8_t *data, size_t data_len, eaf_format_handle_t *ret_parser)
{
    static bool decoders_initialized = false;

    if (!decoders_initialized) {
        esp_err_t ret = eaf_init_decoders();
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to initialize eaf_decoder");
            return ret;
        }
        decoders_initialized = true;
    }

    esp_err_t ret = ESP_OK;
    eaf_frame_entry_t *entries = NULL;

    eaf_format_ctx_t *parser = (eaf_format_ctx_t *)calloc(1, sizeof(eaf_format_ctx_t));
    ESP_GOTO_ON_FALSE(parser, ESP_ERR_NO_MEM, err, TAG, "no mem for parser handle");

    ESP_GOTO_ON_FALSE(data[EAF_FORMAT_OFFSET] == EAF_FORMAT_MAGIC, ESP_ERR_INVALID_CRC, err, TAG, "bad file format magic");

    const char *format_str = (const char *)(data + EAF_STR_OFFSET);
    bool is_valid = (memcmp(format_str, EAF_FORMAT_STR, 3) == 0) || (memcmp(format_str, AAF_FORMAT_STR, 3) == 0);
    ESP_GOTO_ON_FALSE(is_valid, ESP_ERR_INVALID_CRC, err, TAG, "bad file format string (expected EAF or AAF)");

    int total_frames = *(int *)(data + EAF_NUM_OFFSET);
    uint32_t stored_chk = *(uint32_t *)(data + EAF_CHECKSUM_OFFSET);
    uint32_t stored_len = *(uint32_t *)(data + EAF_TABLE_LEN);

    uint32_t calculated_chk = eaf_calculate_checksum((uint8_t *)(data + EAF_TABLE_OFFSET), stored_len);
    ESP_GOTO_ON_FALSE(calculated_chk == stored_chk, ESP_ERR_INVALID_CRC, err, TAG, "bad full checksum");

    entries = (eaf_frame_entry_t *)malloc(sizeof(eaf_frame_entry_t) * total_frames);

    eaf_frame_table_entry_t *table = (eaf_frame_table_entry_t *)(data + EAF_TABLE_OFFSET);
    for (int i = 0; i < total_frames; i++) {
        (entries + i)->table = (table + i);
        (entries + i)->frame_mem = (void *)(data + EAF_TABLE_OFFSET + total_frames * sizeof(eaf_frame_table_entry_t) + table[i].frame_offset);

        uint16_t *magic_ptr = (uint16_t *)(entries + i)->frame_mem;
        ESP_GOTO_ON_FALSE(*magic_ptr == EAF_MAGIC_HEAD, ESP_ERR_INVALID_CRC, err, TAG, "bad file magic header");
    }

    parser->entries = entries;
    parser->total_frames = total_frames;

    *ret_parser = (eaf_format_handle_t)parser;

    return ESP_OK;

err:
    if (entries) {
        free(entries);
    }
    if (parser) {
        free(parser);
    }
    *ret_parser = NULL;

    return ret;
}

esp_err_t eaf_deinit(eaf_format_handle_t handle)
{
    if (handle == NULL) {
        ESP_LOGW(TAG, "Handle is invalid");
        return ESP_ERR_INVALID_ARG;
    }

    eaf_format_ctx_t *parser = (eaf_format_ctx_t *)(handle);
    if (parser) {
        if (parser->entries) {
            free(parser->entries);
        }
        free(parser);
    }
    return ESP_OK;
}

int eaf_get_total_frames(eaf_format_handle_t handle)
{
    if (handle == NULL) {
        ESP_LOGE(TAG, "Handle is invalid");
        return -1;
    }

    eaf_format_ctx_t *parser = (eaf_format_ctx_t *)(handle);
    return parser->total_frames;
}

const uint8_t *eaf_get_frame_data(eaf_format_handle_t handle, int index)
{
    if (handle == NULL) {
        ESP_LOGE(TAG, "Handle is invalid");
        return NULL;
    }

    eaf_format_ctx_t *parser = (eaf_format_ctx_t *)(handle);

    if (parser->total_frames > index) {
        return (const uint8_t *)((parser->entries + index)->frame_mem + EAF_MAGIC_LEN);
    } else {
        ESP_LOGE(TAG, "Invalid index: %d. Maximum index is %d.", index, parser->total_frames);
        return NULL;
    }
}

int eaf_get_frame_size(eaf_format_handle_t handle, int index)
{
    if (handle == NULL) {
        ESP_LOGE(TAG, "Handle is invalid");
        return -1;
    }

    eaf_format_ctx_t *parser = (eaf_format_ctx_t *)(handle);

    if (parser->total_frames > index) {
        return ((parser->entries + index)->table->frame_size - EAF_MAGIC_LEN);
    } else {
        ESP_LOGE(TAG, "Invalid index: %d. Maximum index is %d.", index, parser->total_frames);
        return -1;
    }
}

esp_err_t eaf_frame_decode(eaf_format_handle_t handle, int frame_index,
                           uint8_t *frame_buffer, size_t frame_buffer_size,
                           bool swap_bytes)
{
    if (!handle || !frame_buffer) {
        return ESP_ERR_INVALID_STATE;
    }

    const uint8_t *frame_data = eaf_get_frame_data(handle, frame_index);
    if (!frame_data) {
        ESP_LOGE(TAG, "Failed to get frame data for frame %d", frame_index);
        return ESP_FAIL;
    }

    eaf_header_t frame_header;
    eaf_format_type_t format = eaf_get_frame_info(handle, frame_index, &frame_header);
    if (format != EAF_FORMAT_VALID) {
        ESP_LOGE(TAG, "Failed to parse frame header");
        return ESP_FAIL;
    }

    size_t block_height = frame_header.block_height;
    size_t width = frame_header.width;
    size_t height = frame_header.height;
    uint8_t bit_depth = frame_header.bit_depth;

    size_t block_size = width * block_height;
    block_size = (bit_depth == 24) ? block_size * 2 : block_size;

    uint32_t *offsets = (uint32_t *)malloc(frame_header.blocks * sizeof(uint32_t));
    if (offsets == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for block offsets");
        eaf_free_header(&frame_header);
        return ESP_ERR_NO_MEM;
    }
    eaf_calculate_offsets(&frame_header, offsets);

    uint8_t *compressed_buffer = malloc(block_size);
    if (!compressed_buffer) {
        ESP_LOGE(TAG, "Failed to allocate compressed buffer");
        free(offsets);
        eaf_free_header(&frame_header);
        return ESP_ERR_NO_MEM;
    }

    uint32_t palette_cache[256];
    memset(palette_cache, 0xFF, sizeof(palette_cache));

    for (int block = 0; block < frame_header.blocks; block++) {
        const uint8_t *block_data = frame_data + offsets[block];
        int block_len = frame_header.block_len[block];
        esp_err_t ret = eaf_decode_block(&frame_header, block_data, block_len, compressed_buffer, swap_bytes);

        if (ret != ESP_OK) {
            ESP_LOGD(TAG, "Failed to decode block %d", block);
            continue;
        }

        uint16_t *block_buffer = (uint16_t *)frame_buffer + (block * block_height * width);

        size_t valid_size;
        if ((block + 1) * block_height > height) {
            valid_size = (height - block * block_height) * width;
            valid_size = (bit_depth == 24) ? valid_size * 2 : valid_size;
        } else {
            valid_size = block_size;
        }

        if (bit_depth == 8) {
            for (size_t i = 0; i < valid_size; i++) {
                uint8_t index = compressed_buffer[i];
                uint16_t color;

                if (palette_cache[index] == 0xFFFFFFFF) {
                    gfx_color_t eaf_color = eaf_palette_get_color(&frame_header, index, swap_bytes);
                    palette_cache[index] = eaf_color.full;
                    color = eaf_color.full;
                } else {
                    color = palette_cache[index];
                }
                block_buffer[i] = color;
            }
        } else if (bit_depth == 4) {
            ESP_LOGI(TAG, "4 bit depth not supported");
        } else if (bit_depth == 24) {
            memcpy(block_buffer, compressed_buffer, valid_size);
        }
    }

    free(compressed_buffer);
    free(offsets);
    eaf_free_header(&frame_header);

    return ESP_OK;
}
