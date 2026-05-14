/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_sccb_intf.h"

void test_op(esp_sccb_io_handle_t handle)
{
    esp_sccb_transmit_reg_a8v8(handle, 0, 0);
    esp_sccb_del_i2c_io(handle);
}
