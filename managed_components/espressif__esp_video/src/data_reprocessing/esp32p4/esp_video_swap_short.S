/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

/**
 * @brief Swap short data based on RISC-V instruction
 *
 * @param a0    Source buffer pointer
 * @param a1    Source buffer size
 * @param a2    Destination buffer pointer
 * @param a3    Destination buffer size
 *
 * @Note void esp_video_swap_short_riscv(void *src, size_t src_size, void *dst, size_t dst_size);
 */
    .text
    .section    .text.esp_video_swap_short_riscv, "ax"
    .global     esp_video_swap_short_riscv
    .type       esp_video_swap_short_riscv,@function
    .align      4
esp_video_swap_short_riscv:
    addi    sp,  sp, -16
    sw      s0,  12(sp)
    sw      s1,  8(sp)
    sw      s2,  4(sp)

    add     a1,  a0, a1 

esp_video_swap_short_riscv_loop:
    lw      a3,  0(a0)
    lw      a4,  4(a0)
    lw      a5,  8(a0)
    lw      a6,  12(a0)
    lw      a7,  16(a0)
    lw      s0,  20(a0)
    lw      s1,  24(a0)
    lw      s2,  28(a0)

    sh      a3,  2(a2)
    srli    a3,  a3, 16
    sh      a3,  0(a2)

    sh      a4,  6(a2)
    srli    a4,  a4, 16
    sh      a4,  4(a2)

    sh      a5,  10(a2)
    srli    a5,  a5, 16
    sh      a5,  8(a2)

    sh      a6,  14(a2)
    srli    a6,  a6, 16
    sh      a6,  12(a2)

    sh      a7,  18(a2)
    srli    a7,  a7, 16
    sh      a7,  16(a2)

    sh      s0,  22(a2)
    srli    s0,  s0, 16
    sh      s0,  20(a2)

    sh      s1,  26(a2)
    srli    s1,  s1, 16
    sh      s1,  24(a2)

    sh      s2,  30(a2)
    srli    s2,  s2, 16
    sh      s2,  28(a2)

    addi    a0, a0, 32
    addi    a2, a2, 32
    bltu    a0, a1, esp_video_swap_short_riscv_loop

    lw      s0,  12(sp)
    lw      s1,  8(sp)
    lw      s2,  4(sp)
    addi    sp,  sp, 16

    ret

/**
 * @brief Swap short data based on PIE
 *
 * @param a0    Source buffer pointer
 * @param a1    Source buffer size
 * @param a2    Destination buffer pointer
 * @param a3    Destination buffer size
 *
 * @Note void esp_video_swap_short_pie(void *src, size_t src_size, void *dst, size_t dst_size);
 */
    .text
    .section    .text.esp_video_swap_short_pie, "ax"
    .global     esp_video_swap_short_pie
    .type       esp_video_swap_short_pie,@function
    .align      4
esp_video_swap_short_pie:
    add     a1,  a0, a1

    li      a4,  16
    esp.movx.w.sar a4

esp_video_swap_short_pie_loop:
    esp.vld.128.ip q0, a0, 16
    esp.vld.128.ip q1, a0, 16

    esp.vsr.u32 q4, q0
    esp.vsl.32  q5, q0
    esp.orq     q0, q4, q5

    esp.vsr.u32 q4, q1
    esp.vsl.32  q5, q1
    esp.orq     q1, q4, q5

    esp.vst.128.ip q0, a2, 16
    esp.vst.128.ip q1, a2, 16

    bltu    a0, a1, esp_video_swap_short_pie_loop

    ret
