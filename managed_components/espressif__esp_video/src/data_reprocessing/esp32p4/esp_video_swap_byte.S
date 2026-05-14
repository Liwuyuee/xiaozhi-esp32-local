/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

/**
 * @brief Swap byte data based on RISC-V instruction
 *
 * @param a0    Source buffer pointer
 * @param a1    Destination buffer pointer
 * @param a2    Buffer size
 *
 * @Note void esp_video_swap_byte_riscv(void *src, void *dst, size_t size);
 */
    .text
    .section    .text.esp_video_swap_byte_riscv, "ax"
    .global     esp_video_swap_byte_riscv
    .type       esp_video_swap_byte_riscv,@function
    .align      4
esp_video_swap_byte_riscv:
    addi    sp,  sp, -32
    sw      s0,  0(sp)
    sw      s1,  4(sp)
    sw      s2,  8(sp)
    sw      s3,  12(sp)
    sw      s4,  16(sp)
    sw      s5,  20(sp)

    add     a2,  a0, a2
    li      s4,  0xff00ff00
    li      s5,  0x00ff00ff

esp_video_swap_byte_riscv_loop:
    lw      a3,  0(a0)
    lw      a4,  4(a0)
    lw      a5,  8(a0)
    lw      a6,  12(a0)
    lw      a7,  16(a0)
    lw      s0,  20(a0)
    lw      s1,  24(a0)
    lw      s2,  28(a0)

    srli    s3,  a3, 8
    and     s3,  s3, s5
    slli    a3,  a3, 8
    and     a3,  a3, s4
    or      a3,  a3, s3
    sw      a3,  0(a1)

    srli    s3,  a4, 8
    and     s3,  s3, s5
    slli    a4,  a4, 8
    and     a4,  a4, s4
    or      a4,  a4, s3
    sw      a4,  4(a1)

    srli    s3,  a5, 8
    and     s3,  s3, s5
    slli    a5,  a5, 8
    and     a5,  a5, s4
    or      a5,  a5, s3
    sw      a5,  8(a1)

    srli    s3,  a6, 8
    and     s3,  s3, s5
    slli    a6,  a6, 8
    and     a6,  a6, s4
    or      a6,  a6, s3
    sw      a6,  12(a1)

    srli    s3,  a7, 8
    and     s3,  s3, s5
    slli    a7,  a7, 8
    and     a7,  a7, s4
    or      a7,  a7, s3
    sw      a7,  16(a1)

    srli    s3,  s0, 8
    and     s3,  s3, s5
    slli    s0,  s0, 8
    and     s0,  s0, s4
    or      s0,  s0, s3
    sw      s0,  20(a1)

    srli    s3,  s1, 8
    and     s3,  s3, s5
    slli    s1,  s1, 8
    and     s1,  s1, s4
    or      s1,  s1, s3
    sw      s1,  24(a1)

    srli    s3,  s2, 8
    and     s3,  s3, s5
    slli    s2,  s2, 8
    and     s2,  s2, s4
    or      s2,  s2, s3
    sw      s2,  28(a1)

    addi    a0, a0, 32
    addi    a1, a1, 32
    bltu    a0, a2, esp_video_swap_byte_riscv_loop

    lw      s0,  0(sp)
    lw      s1,  4(sp)
    lw      s2,  8(sp)
    lw      s3,  12(sp)
    lw      s4,  16(sp)
    lw      s5,  20(sp)
    addi    sp,  sp, 32

    ret
