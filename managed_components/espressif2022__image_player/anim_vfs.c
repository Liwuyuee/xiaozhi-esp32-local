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

static const char *TAG = "anim_vfs";

#define ASSETS_FILE_NUM_OFFSET  0
#define ASSETS_CHECKSUM_OFFSET  4
#define ASSETS_TABLE_LEN        8
#define ASSETS_TABLE_OFFSET     12

#define ASSETS_FILE_MAGIC_HEAD  0x5A5A
#define ASSETS_FILE_MAGIC_LEN   2

/**
 * @brief Asset table structure, contains detailed information for each asset.
 */
#pragma pack(1)

typedef struct {
    uint32_t asset_size;          /*!< Size of the asset */
    uint32_t asset_offset;        /*!< Offset of the asset */
} asset_table_entry_t;
#pragma pack()

typedef struct {
    const char *asset_mem;
    const asset_table_entry_t *table;
} asset_entry_t;

typedef struct {
    asset_entry_t *entries;
    int total_frames;
} anim_vfs_t;

esp_err_t anim_vfs_init(const uint8_t *data, size_t data_len, anim_vfs_handle_t *ret_parser)
{
    esp_err_t ret = ESP_OK;
    asset_entry_t *entries = NULL;

    anim_vfs_t *parser = (anim_vfs_t *)calloc(1, sizeof(anim_vfs_t));
    ESP_GOTO_ON_FALSE(parser, ESP_ERR_NO_MEM, err, TAG, "no mem for parser handle");

    int total_frames = *(int *)(data + ASSETS_FILE_NUM_OFFSET);
    // uint32_t stored_chksum = *(uint32_t *)(data + ASSETS_CHECKSUM_OFFSET);
    // uint32_t stored_len = *(uint32_t *)(data + ASSETS_TABLE_LEN);

    entries = (asset_entry_t *)malloc(sizeof(asset_entry_t) * total_frames);

    asset_table_entry_t *table = (asset_table_entry_t *)(data + ASSETS_TABLE_OFFSET);
    for (int i = 0; i < total_frames; i++) {
        (entries + i)->table = (table + i);
        (entries + i)->asset_mem = (void *)(data + ASSETS_TABLE_OFFSET + total_frames * sizeof(asset_table_entry_t) + table[i].asset_offset);

        uint16_t *magic_ptr = (uint16_t *)(entries + i)->asset_mem;
        ESP_GOTO_ON_FALSE(*magic_ptr == ASSETS_FILE_MAGIC_HEAD, ESP_ERR_INVALID_CRC, err, TAG, "bad file magic header");
    }

    parser->entries = entries;
    parser->total_frames = total_frames;

    *ret_parser = (anim_vfs_handle_t)parser;

    return ESP_OK;

err:
    if (entries) {
        free(entries);
    }
    if (parser) {
        free(parser);
    }

    return ret;
}

esp_err_t anim_vfs_deinit(anim_vfs_handle_t handle)
{
    assert(handle && "handle is invalid");
    anim_vfs_t *parser = (anim_vfs_t *)(handle);
    if (parser) {
        if (parser->entries) {
            free(parser->entries);
        }
        free(parser);
    }
    return ESP_OK;
}

int anim_vfs_get_total_frames(anim_vfs_handle_t handle)
{
    assert(handle && "handle is invalid");
    anim_vfs_t *parser = (anim_vfs_t *)(handle);

    return parser->total_frames;
}

const uint8_t *anim_vfs_get_frame_data(anim_vfs_handle_t handle, int index)
{
    assert(handle && "handle is invalid");

    anim_vfs_t *parser = (anim_vfs_t *)(handle);

    if (parser->total_frames > index) {
        return (const uint8_t *)((parser->entries + index)->asset_mem + ASSETS_FILE_MAGIC_LEN);
    } else {
        ESP_LOGE(TAG, "Invalid index: %d. Maximum index is %d.", index, parser->total_frames);
        return NULL;
    }
}

int anim_vfs_get_frame_size(anim_vfs_handle_t handle, int index)
{
    assert(handle && "handle is invalid");
    anim_vfs_t *parser = (anim_vfs_t *)(handle);

    if (parser->total_frames > index) {
        return ((parser->entries + index)->table->asset_size - ASSETS_FILE_MAGIC_LEN);
    } else {
        ESP_LOGE(TAG, "Invalid index: %d. Maximum index is %d.", index, parser->total_frames);
        return -1;
    }
}
