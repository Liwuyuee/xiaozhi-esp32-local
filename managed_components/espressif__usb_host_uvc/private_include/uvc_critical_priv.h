/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdatomic.h>

#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"

extern portMUX_TYPE uvc_lock;
#define UVC_ENTER_CRITICAL()              portENTER_CRITICAL(&uvc_lock)
#define UVC_EXIT_CRITICAL()               portEXIT_CRITICAL(&uvc_lock)

#define UVC_ATOMIC_LOAD(x)                __atomic_load_n(&x, __ATOMIC_SEQ_CST)
#define UVC_ATOMIC_SET_IF_NULL(x, new_x)  ({ \
                                              __typeof__(x) expected = NULL; \
                                              __atomic_compare_exchange_n(&(x), &expected, (new_x), false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
                                          })
