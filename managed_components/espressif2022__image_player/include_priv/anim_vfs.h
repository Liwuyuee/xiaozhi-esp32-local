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

typedef struct anim_vfs_t *anim_vfs_handle_t;

esp_err_t anim_vfs_init(const uint8_t *data, size_t data_len, anim_vfs_handle_t *ret_parser);

esp_err_t anim_vfs_deinit(anim_vfs_handle_t handle);

int anim_vfs_get_total_frames(anim_vfs_handle_t handle);

int anim_vfs_get_frame_size(anim_vfs_handle_t handle, int index);

const uint8_t *anim_vfs_get_frame_data(anim_vfs_handle_t handle, int index);

#ifdef __cplusplus
}
#endif