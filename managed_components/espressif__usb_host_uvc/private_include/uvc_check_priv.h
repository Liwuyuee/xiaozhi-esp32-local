/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

// UVC check macros
#define UVC_CHECK(cond, ret_val) ({                                     \
            if (!(cond)) {                                              \
                return (ret_val);                                       \
            }                                                           \
})

#define UVC_CHECK_FROM_CRIT(cond, ret_val) ({                           \
            if (!(cond)) {                                              \
                UVC_EXIT_CRITICAL();                                    \
                return ret_val;                                         \
            }                                                           \
})
