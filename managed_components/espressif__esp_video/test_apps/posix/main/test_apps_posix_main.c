/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#ifdef CONFIG_HEAP_TRACING
#include "esp_heap_trace.h"
#endif
#include "esp_timer.h"
#include "memory_checks.h"
#include "unity_test_utils_memory.h"
#include "unity.h"
#include "esp_log_buffer.h"

#include "example_video_common.h"

#define TEST_MEMORY_LEAK_THRESHOLD (-512)

#define VIDEO_BUFFER_NUM 2

#define TEST_APP_VIDEO_DEVICE EXAMPLE_CAM_DEV_PATH

#define HEAP_RECORD_NUM 32

void setUp(void);

static size_t before_free_8bit;
static size_t before_free_32bit;

#ifdef CONFIG_HEAP_TRACING
static void init_heap_record(void)
{
    static heap_trace_record_t record_buffer[HEAP_RECORD_NUM];
    static bool initialized = false;

    if (!initialized) {
        assert(heap_trace_init_standalone(record_buffer, HEAP_RECORD_NUM) == ESP_OK);
        initialized = true;
    }
}
#endif

TEST_CASE("V4L2 init/deinit", "[video]")
{
    int count = 20;

    for (int i = 0; i < count; i++) {
        TEST_ESP_OK(example_video_init());

        int fd = open(TEST_APP_VIDEO_DEVICE, O_RDWR);
        TEST_ASSERT_GREATER_OR_EQUAL(0, fd);
        close(fd);

        TEST_ESP_OK(example_video_deinit());
    }
}

TEST_CASE("V4L2 Command", "[video]")
{
    int fd;
    int ret;
    uint16_t width;
    uint16_t height;
    uint32_t pixelformat;
    struct v4l2_format format;
    struct v4l2_capability cap;

    setUp();

    TEST_ESP_OK(example_video_init());

    fd = open(TEST_APP_VIDEO_DEVICE, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, fd);

    memset(&cap, 0, sizeof(cap));
    ret = ioctl(fd, VIDIOC_QUERYCAP, &cap);
    TEST_ESP_OK(ret);
    TEST_ASSERT_EQUAL_INT(V4L2_CAP_VIDEO_CAPTURE, cap.capabilities & V4L2_CAP_VIDEO_CAPTURE);

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd, VIDIOC_G_FMT, &format);
    TEST_ESP_OK(ret);

    width = format.fmt.pix.width;
    height = format.fmt.pix.height;

#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
    pixelformat = V4L2_PIX_FMT_RGB565;
#else
    pixelformat = format.fmt.pix.pixelformat;
#endif

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height;
    format.fmt.pix.pixelformat = pixelformat;
    ret = ioctl(fd, VIDIOC_S_FMT, &format);
    TEST_ESP_OK(ret);

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = width - 1;
    format.fmt.pix.height = height;
    format.fmt.pix.pixelformat = pixelformat;
    ret = ioctl(fd, VIDIOC_S_FMT, &format);
    TEST_ASSERT_EQUAL_INT(-1, ret);

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height - 1;
    format.fmt.pix.pixelformat = pixelformat;
    ret = ioctl(fd, VIDIOC_S_FMT, &format);
    TEST_ASSERT_EQUAL_INT(-1, ret);

    close(fd);

    TEST_ESP_OK(example_video_deinit());
}

TEST_CASE("V4L2 Video Buffer Sequence", "[video]")
{
    int fd;
    int ret;
    int val;
    struct v4l2_buffer buf;
    struct v4l2_requestbuffers req;
    int buffer_count = 5;

    setUp();

    TEST_ESP_OK(example_video_init());

    fd = open(TEST_APP_VIDEO_DEVICE, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, fd);

    memset(&req, 0, sizeof(req));
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    req.count  = buffer_count;
    ret = ioctl(fd, VIDIOC_REQBUFS, &req);
    TEST_ESP_OK(ret);

    for (int test_count = 0; test_count < 4; test_count++) {
        for (int i = 0; i < buffer_count; i++) {
            memset(&buf, 0, sizeof(buf));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;
            ret = ioctl(fd, VIDIOC_QUERYBUF, &buf);
            TEST_ESP_OK(ret);

            ret = ioctl(fd, VIDIOC_QBUF, &buf);
            TEST_ESP_OK(ret);
        }

        val = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ret = ioctl(fd, VIDIOC_STREAMON, &val);
        TEST_ESP_OK(ret);

        for (int i = 0; i < buffer_count; i++) {
            memset(&buf, 0, sizeof(buf));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            ret = ioctl(fd, VIDIOC_DQBUF, &buf);
            TEST_ESP_OK(ret);

            TEST_ASSERT_EQUAL_INT(i, buf.index);

            ret = ioctl(fd, VIDIOC_QBUF, &buf);
            TEST_ESP_OK(ret);
        }

        val = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ret = ioctl(fd, VIDIOC_STREAMOFF, &val);
        TEST_ESP_OK(ret);
    }

    close(fd);

    TEST_ESP_OK(example_video_deinit());
}

#if CONFIG_ESP_VIDEO_ENABLE_JPEG_VIDEO_DEVICE
TEST_CASE("V4L2 M2M device", "[video]")
{
    int fd;
    int ret;
    int val;
    uint16_t width = 320;
    uint16_t height = 240;
    struct v4l2_buffer buf;
    struct v4l2_format format;
    struct v4l2_capability cap;
    struct v4l2_requestbuffers req;
    uint8_t *out_buf[VIDEO_BUFFER_NUM];
    uint8_t *cap_buf[VIDEO_BUFFER_NUM];

    setUp();

    TEST_ESP_OK(example_video_init());

    fd = open(ESP_VIDEO_JPEG_DEVICE_NAME, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, fd);

    memset(&cap, 0, sizeof(cap));
    ret = ioctl(fd, VIDIOC_QUERYCAP, &cap);
    TEST_ESP_OK(ret);
    TEST_ASSERT_EQUAL_INT(V4L2_CAP_VIDEO_M2M, cap.capabilities & V4L2_CAP_VIDEO_M2M);

    /* Initialize output buffer */

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB565;
    ret = ioctl(fd, VIDIOC_S_FMT, &format);
    TEST_ESP_OK(ret);

    memset(&req, 0, sizeof(req));
    req.type   = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    req.memory = V4L2_MEMORY_MMAP;
    req.count  = VIDEO_BUFFER_NUM;
    ret = ioctl(fd, VIDIOC_REQBUFS, &req);
    TEST_ESP_OK(ret);

    for (int i = 0; i < VIDEO_BUFFER_NUM; i++) {
        memset(&buf, 0, sizeof(buf));
        buf.type        = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;
        ret = ioctl(fd, VIDIOC_QUERYBUF, &buf);
        TEST_ESP_OK(ret);

        TEST_ASSERT_EQUAL_INT(width * height * 2, buf.length);

        out_buf[i] = mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, buf.m.offset);
        TEST_ASSERT_NOT_NULL(out_buf[i]);

        ret = ioctl(fd, VIDIOC_QBUF, &buf);
        TEST_ESP_OK(ret);
    }

    /* Initialize capture buffer */

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;
    ret = ioctl(fd, VIDIOC_S_FMT, &format);
    TEST_ESP_OK(ret);

    memset(&req, 0, sizeof(req));
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    req.count  = VIDEO_BUFFER_NUM;
    ret = ioctl(fd, VIDIOC_REQBUFS, &req);
    TEST_ESP_OK(ret);

    for (int i = 0; i < VIDEO_BUFFER_NUM; i++) {
        memset(&buf, 0, sizeof(buf));
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = i;
        ret = ioctl(fd, VIDIOC_QUERYBUF, &buf);
        TEST_ESP_OK(ret);

        cap_buf[i] = mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, buf.m.offset);
        TEST_ASSERT_NOT_NULL(cap_buf[i]);

        ret = ioctl(fd, VIDIOC_QBUF, &buf);
        TEST_ESP_OK(ret);
    }

    val = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    ret = ioctl(fd, VIDIOC_STREAMON, &val);
    TEST_ESP_OK(ret);

    val = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd, VIDIOC_STREAMON, &val);
    TEST_ESP_OK(ret);

    for (int i = 0; i < 100; i++) {
        memset(&buf, 0, sizeof(buf));
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        ret = ioctl(fd, VIDIOC_DQBUF, &buf);
        TEST_ESP_OK(ret);

        TEST_ASSERT_EQUAL_HEX8(0xff, cap_buf[buf.index][0]);
        TEST_ASSERT_EQUAL_HEX8(0xd8, cap_buf[buf.index][1]);

        ret = ioctl(fd, VIDIOC_QBUF, &buf);
        TEST_ESP_OK(ret);

        memset(&buf, 0, sizeof(buf));
        buf.type   = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        buf.memory = V4L2_MEMORY_MMAP;
        ret = ioctl(fd, VIDIOC_DQBUF, &buf);
        TEST_ESP_OK(ret);

        ret = ioctl(fd, VIDIOC_QBUF, &buf);
        TEST_ESP_OK(ret);
    }

    val = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    ret = ioctl(fd, VIDIOC_STREAMOFF, &val);
    TEST_ESP_OK(ret);

    val = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd, VIDIOC_STREAMOFF, &val);
    TEST_ESP_OK(ret);

    ret = close(fd);
    TEST_ESP_OK(ret);

    TEST_ESP_OK(example_video_deinit());
}
#endif /* CONFIG_ESP_VIDEO_ENABLE_JPEG_VIDEO_DEVICE */

#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
TEST_CASE("V4L2 set/get selection", "[video]")
{
    int fd;
    struct v4l2_selection in_selection;
    struct v4l2_selection out_selection;

    setUp();

    TEST_ESP_OK(example_video_init());

    fd = open(ESP_VIDEO_ISP1_DEVICE_NAME, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, fd);

    memset(&in_selection, 0, sizeof(in_selection));
    in_selection.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    TEST_ASSERT_EQUAL_INT(-1, ioctl(fd, VIDIOC_G_SELECTION, &in_selection));

    memset(&in_selection, 0, sizeof(in_selection));
    in_selection.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    TEST_ASSERT_EQUAL_INT(-1, ioctl(fd, VIDIOC_S_SELECTION, &in_selection));

    memset(&in_selection, 0, sizeof(in_selection));
    in_selection.type = V4L2_BUF_TYPE_META_CAPTURE;
    TEST_ESP_OK(ioctl(fd, VIDIOC_G_SELECTION, &in_selection));

    memset(&in_selection, 0, sizeof(in_selection));
    in_selection.type = V4L2_BUF_TYPE_META_CAPTURE;
    in_selection.r.left = 0;
    in_selection.r.width = 1080;
    in_selection.r.top = 0;
    in_selection.r.height = 720;
    TEST_ESP_OK(ioctl(fd, VIDIOC_S_SELECTION, &in_selection));

    memset(&out_selection, 0, sizeof(out_selection));
    out_selection.type = V4L2_BUF_TYPE_META_CAPTURE;
    TEST_ESP_OK(ioctl(fd, VIDIOC_G_SELECTION, &out_selection));

    TEST_ESP_OK(memcmp(&out_selection, &in_selection, sizeof(out_selection)));

    TEST_ESP_OK(close(fd));

    TEST_ESP_OK(example_video_deinit());
}

TEST_CASE("V4L2 set/get param", "[video]")
{
    int fd;
    int fps;
    int ret;
    struct v4l2_buffer buf;
    struct v4l2_streamparm sparm;
    struct v4l2_captureparm *cparam = &sparm.parm.capture;
    struct v4l2_fract *timeperframe = &cparam->timeperframe;
    struct v4l2_requestbuffers req;
    int buf_count = 3;
    int capture_seconds = 3;

    setUp();

    TEST_ESP_OK(example_video_init());

    fd = open(TEST_APP_VIDEO_DEVICE, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, fd);

    memset(&sparm, 0, sizeof(sparm));
    sparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd, VIDIOC_G_PARM, &sparm);
    TEST_ESP_OK(ret);

    TEST_ASSERT_EQUAL_INT(cparam->capability, V4L2_CAP_TIMEPERFRAME);
    TEST_ASSERT_GREATER_OR_EQUAL(1, timeperframe->numerator);
    TEST_ASSERT_GREATER_OR_EQUAL(1, timeperframe->denominator);
    printf("fps=%0.4f\n", (float)timeperframe->denominator / timeperframe->numerator);

    fps = timeperframe->denominator / timeperframe->numerator;
    for (int i = 2; i <= fps; i++) {
        if (fps % i != 0) {
            continue;
        }
        int div_fps = fps / i;

        memset(&sparm, 0, sizeof(sparm));
        sparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        cparam->capability = V4L2_CAP_TIMEPERFRAME;
        timeperframe->numerator = 1;
        timeperframe->denominator = div_fps;
        ret = ioctl(fd, VIDIOC_S_PARM, &sparm);
        TEST_ESP_OK(ret);

        memset(&req, 0, sizeof(req));
        req.count  = buf_count;
        req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        req.memory = V4L2_MEMORY_MMAP;
        ret = ioctl(fd, VIDIOC_REQBUFS, &req);
        TEST_ESP_OK(ret);

        for (int i = 0; i < buf_count; i++) {
            memset(&buf, 0, sizeof(buf));
            buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory      = V4L2_MEMORY_MMAP;
            buf.index       = i;
            ret = ioctl(fd, VIDIOC_QUERYBUF, &buf);
            TEST_ESP_OK(ret);

            ret = ioctl(fd, VIDIOC_QBUF, &buf);
            TEST_ESP_OK(ret);
        }

        int val = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ret = ioctl(fd, VIDIOC_STREAMON, &val);
        TEST_ESP_OK(ret);

        int frame_count = 0;
        int64_t start_time_us = esp_timer_get_time();
        while (esp_timer_get_time() - start_time_us < (capture_seconds * 1000 * 1000)) {
            memset(&buf, 0, sizeof(buf));
            buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            ret = ioctl(fd, VIDIOC_DQBUF, &buf);
            TEST_ESP_OK(ret);

            frame_count++;

            ret = ioctl(fd, VIDIOC_QBUF, &buf);
            TEST_ESP_OK(ret);
        }

        val = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ret = ioctl(fd, VIDIOC_STREAMOFF, &val);
        TEST_ESP_OK(ret);

        TEST_ASSERT_EQUAL_INT(div_fps, frame_count / capture_seconds);

        memset(&sparm, 0, sizeof(sparm));
        sparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ret = ioctl(fd, VIDIOC_G_PARM, &sparm);
        TEST_ESP_OK(ret);

        TEST_ASSERT_EQUAL_INT(cparam->capability, V4L2_CAP_TIMEPERFRAME);
        TEST_ASSERT_EQUAL_INT(timeperframe->numerator, 1);
        TEST_ASSERT_EQUAL_INT(timeperframe->denominator, div_fps);
    }

    close(fd);

    TEST_ESP_OK(example_video_deinit());
}
#endif /* CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE */

#if CONFIG_ESP_VIDEO_ENABLE_SWAP_BYTE_RISCV
TEST_CASE("RISCV swap byte", "[video]")
{
    int64_t c_time_us = 0;
    int64_t r_time_us = 0;
    int64_t total_bytes = 0;
    extern void esp_video_swap_byte_riscv(void *src, void *dst, uint32_t size);

    for (int i = 0; i < 100; i++) {
        uint8_t *src;
        uint8_t *dst;
        uint8_t *result;
        size_t size = (((size_t)rand() % 10240) / 32 + 1) * 32;
        /**
         * Add some bytes to the end of the buffer to check if the swap causes the buffer to be overflowed
         */
        size_t res = (size_t)rand() % 64 + 32;

        src = malloc(size + res);
        TEST_ASSERT_NOT_NULL(src);
        dst = malloc(size + res);
        TEST_ASSERT_NOT_NULL(dst);
        result = malloc(size + res);
        TEST_ASSERT_NOT_NULL(result);

        for (int j = 0; j < size + res; j++) {
            src[j] = rand() % 256;
        }

        int64_t t = esp_timer_get_time();
        for (int j = 0; j < size; j += 4) {
            result[j + 0] = src[j + 1];
            result[j + 1] = src[j + 0];

            result[j + 2] = src[j + 3];
            result[j + 3] = src[j + 2];
        }
        c_time_us += esp_timer_get_time() - t;

        for (int j = 0; j < res; j++) {
            result[size + j] = 0;
        }

        memset(dst, 0, size + res);
        t = esp_timer_get_time();
        esp_video_swap_byte_riscv(src, dst, size);
        r_time_us += esp_timer_get_time() - t;

        // ESP_LOG_BUFFER_HEX("src", src, size);
        // ESP_LOG_BUFFER_HEX("result", result, size);
        // ESP_LOG_BUFFER_HEX("dst", dst, size);

        TEST_ASSERT_EQUAL_INT(0, memcmp(result, dst, size));

        total_bytes += size;

        free(src);
        free(dst);
        free(result);
    }

    printf("c speed: %lld MB/s, riscv speed: %lld MB/s\n", total_bytes * 1000000 / c_time_us / 1024 / 1024, total_bytes * 1000000 / r_time_us / 1024 / 1024);
}
#endif

static void check_leak(size_t before_free, size_t after_free, const char *type)
{
    ssize_t delta = after_free - before_free;
    printf("MALLOC_CAP_%s: Before %u bytes free, After %u bytes free (delta %d)\n", type, before_free, after_free, delta);
    TEST_ASSERT_MESSAGE(delta >= TEST_MEMORY_LEAK_THRESHOLD, "memory leak");
}

void setUp(void)
{
#ifdef CONFIG_HEAP_TRACING
    init_heap_record();
    heap_trace_start(HEAP_TRACE_LEAKS);
#endif

    before_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    before_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
}

void tearDown(void)
{
    /* some FreeRTOS stuff is cleaned up by idle task */
    vTaskDelay(5);

    /* clean up some of the newlib's lazy allocations */
    esp_reent_cleanup();

#ifdef CONFIG_HEAP_TRACING
    heap_trace_stop();
    heap_trace_dump();
#endif

    size_t after_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t after_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    check_leak(before_free_8bit, after_free_8bit, "8BIT");
    check_leak(before_free_32bit, after_free_32bit, "32BIT");
}

void app_main(void)
{
    /**
     * \ \     /_ _| __ \  ____|  _ \
     *  \ \   /   |  |   | __|   |   |
     *   \ \ /    |  |   | |     |   |
     *    \_/   ___|____/ _____|\___/
    */

    printf("\r\n");
    printf("\\ \\     /_ _| __ \\  ____|  _ \\  \r\n");
    printf(" \\ \\   /   |  |   | __|   |   |\r\n");
    printf("  \\ \\ /    |  |   | |     |   | \r\n");
    printf("   \\_/   ___|____/ _____|\\___/  \r\n");

    unity_run_menu();
}
