/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/**
 * @file gfx.h
 * @brief Graphics Framework (GFX) - Main header file
 *
 * This header file includes all the public APIs for the GFX framework.
 * The framework provides:
 * - Object system for images and labels
 * - Drawing functions for rendering to buffers
 * - Color utilities and type definitions
 * - Software blending capabilities
 */

#include "core/gfx_types.h"
#include "core/gfx_core.h"
#include "core/gfx_timer.h"
#include "core/gfx_obj.h"
#include "widget/gfx_img.h"
#include "widget/gfx_label.h"
#include "widget/gfx_anim.h"
#include "widget/gfx_font_lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Main API
 *====================*/

#ifdef __cplusplus
}
#endif
