/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include "esp_attr.h"

// Clamp the value between 0 and 255
static uint8_t clamp(int value)
{
    if (value < 0) {
        return 0;
    }
    if (value > 255) {
        return 255;
    }
    return (uint8_t)value;
}

// Convert YUV to RGB
void IRAM_ATTR yuy2_to_rgb565(const uint8_t *yuy2, uint16_t *rgb565, int width, int height)
{
    int size = width * height;

    for (int i = 0; i < size; i += 2) {
        int y0 = yuy2[i * 2 + 0];
        int u  = yuy2[i * 2 + 1];
        int y1 = yuy2[i * 2 + 2];
        int v  = yuy2[i * 2 + 3];

        // Convert YUV to RGB for the first pixel
        int c0 = y0 - 16;
        int c1 = y1 - 16;
        int d = u - 128;
        int e = v - 128;

        int r0 = clamp((298 * c0 + 409 * e + 128) >> 8);
        int g0 = clamp((298 * c0 - 100 * d - 208 * e + 128) >> 8);
        int b0 = clamp((298 * c0 + 516 * d + 128) >> 8);

        int r1 = clamp((298 * c1 + 409 * e + 128) >> 8);
        int g1 = clamp((298 * c1 - 100 * d - 208 * e + 128) >> 8);
        int b1 = clamp((298 * c1 + 516 * d + 128) >> 8);

        // Convert RGB888 to RGB565 for both pixels
        rgb565[i]     = ((r0 >> 3) << 11) | ((g0 >> 2) << 5) | (b0 >> 3);
        rgb565[i + 1] = ((r1 >> 3) << 11) | ((g1 >> 2) << 5) | (b1 >> 3);
    }
}
