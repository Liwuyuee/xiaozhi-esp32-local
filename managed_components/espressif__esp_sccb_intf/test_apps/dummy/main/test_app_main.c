/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */


//This is a simple build test. Can't run actually.
//TODO: make it a target test
#include "esp_sccb_i2c.h"

extern void test_op(esp_sccb_io_handle_t handle);

void app_main(void)
{
    sccb_i2c_config_t config = {};
    esp_sccb_io_handle_t handle = NULL;
    sccb_new_i2c_io(NULL, &config, &handle);
    test_op(handle);
}
