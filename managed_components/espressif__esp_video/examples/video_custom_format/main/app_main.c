/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/errno.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "example_video_common.h"
#if CONFIG_CAMERA_BF3901
#include "app_bf3901_custom_settings.h"
#elif CONFIG_CAMERA_SC2336
#include "app_sc2336_custom_settings.h"
#else
#error "No supported camera sensor selected, only support BF3901(SPI interface), SC2336(MIPI-CSI interface)"
#endif

#define MEMORY_TYPE V4L2_MEMORY_MMAP
#define BUFFER_COUNT 2
#define CAPTURE_SECONDS 3

static const char *TAG = "example";

static esp_err_t camera_capture_stream(void)
{
    int fd;
    esp_err_t ret;
    int fmt_index = 0;
    uint32_t frame_size;
    uint32_t frame_count;
    struct v4l2_buffer buf;
    uint8_t *buffer[BUFFER_COUNT];
    struct v4l2_format init_format;
    struct v4l2_requestbuffers req;
    struct v4l2_capability capability;

    const int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    fd = open(EXAMPLE_CAM_DEV_PATH, O_RDONLY);
    if (fd < 0) {
        ESP_LOGE(TAG, "failed to open device");
        return ESP_FAIL;
    }

    if (ioctl(fd, VIDIOC_QUERYCAP, &capability)) {
        ESP_LOGE(TAG, "failed to get capability");
        ret = ESP_FAIL;
        goto exit_0;
    }

    ESP_LOGI(TAG, "version: %d.%d.%d", (uint16_t)(capability.version >> 16),
             (uint8_t)(capability.version >> 8),
             (uint8_t)capability.version);
    ESP_LOGI(TAG, "driver:  %s", capability.driver);
    ESP_LOGI(TAG, "card:    %s", capability.card);
    ESP_LOGI(TAG, "bus:     %s", capability.bus_info);
    ESP_LOGI(TAG, "capabilities:");
    if (capability.capabilities & V4L2_CAP_VIDEO_CAPTURE) {
        ESP_LOGI(TAG, "\tVIDEO_CAPTURE");
    }
    if (capability.capabilities & V4L2_CAP_READWRITE) {
        ESP_LOGI(TAG, "\tREADWRITE");
    }
    if (capability.capabilities & V4L2_CAP_ASYNCIO) {
        ESP_LOGI(TAG, "\tASYNCIO");
    }
    if (capability.capabilities & V4L2_CAP_STREAMING) {
        ESP_LOGI(TAG, "\tSTREAMING");
    }
    if (capability.capabilities & V4L2_CAP_META_OUTPUT) {
        ESP_LOGI(TAG, "\tMETA_OUTPUT");
    }
    if (capability.capabilities & V4L2_CAP_DEVICE_CAPS) {
        ESP_LOGI(TAG, "device capabilities:");
        if (capability.device_caps & V4L2_CAP_VIDEO_CAPTURE) {
            ESP_LOGI(TAG, "\tVIDEO_CAPTURE");
        }
        if (capability.device_caps & V4L2_CAP_READWRITE) {
            ESP_LOGI(TAG, "\tREADWRITE");
        }
        if (capability.device_caps & V4L2_CAP_ASYNCIO) {
            ESP_LOGI(TAG, "\tASYNCIO");
        }
        if (capability.device_caps & V4L2_CAP_STREAMING) {
            ESP_LOGI(TAG, "\tSTREAMING");
        }
        if (capability.device_caps & V4L2_CAP_META_OUTPUT) {
            ESP_LOGI(TAG, "\tMETA_OUTPUT");
        }
    }

    /* Set custom register configuration */
    if (ioctl(fd, VIDIOC_S_SENSOR_FMT, &custom_format_info) != 0) {
        ret = ESP_FAIL;
        goto exit_0;
    }

    memset(&init_format, 0, sizeof(struct v4l2_format));
    init_format.type = type;
    if (ioctl(fd, VIDIOC_G_FMT, &init_format) != 0) {
        ESP_LOGE(TAG, "failed to get format");
        ret = ESP_FAIL;
        goto exit_0;
    }

    struct v4l2_fmtdesc fmtdesc = {
        .index = fmt_index++,
        .type = type,
    };

    if (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) != 0) {
        ESP_LOGE(TAG, "failed to enum format");
        ret = ESP_FAIL;
        goto exit_0;
    }

    ESP_LOGI(TAG, "Capture %s format frames for %d seconds:", (char *)fmtdesc.description, CAPTURE_SECONDS);

    memset(&req, 0, sizeof(req));
    req.count  = BUFFER_COUNT;
    req.type   = type;
    req.memory = MEMORY_TYPE;
    if (ioctl(fd, VIDIOC_REQBUFS, &req) != 0) {
        ESP_LOGE(TAG, "failed to require buffer");
        ret = ESP_FAIL;
        goto exit_0;
    }

    for (int i = 0; i < BUFFER_COUNT; i++) {
        struct v4l2_buffer buf;

        memset(&buf, 0, sizeof(buf));
        buf.type        = type;
        buf.memory      = MEMORY_TYPE;
        buf.index       = i;
        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) != 0) {
            ESP_LOGE(TAG, "failed to query buffer");
            ret = ESP_FAIL;
            goto exit_0;
        }

        buffer[i] = (uint8_t *)mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, fd, buf.m.offset);
        if (!buffer[i]) {
            ESP_LOGE(TAG, "failed to map buffer");
            ret = ESP_FAIL;
            goto exit_0;
        }

        if (ioctl(fd, VIDIOC_QBUF, &buf) != 0) {
            ESP_LOGE(TAG, "failed to queue video frame");
            ret = ESP_FAIL;
            goto exit_0;
        }
    }

    if (ioctl(fd, VIDIOC_STREAMON, &type) != 0) {
        ESP_LOGE(TAG, "failed to start stream");
        ret = ESP_FAIL;
        goto exit_0;
    }

    frame_count = 0;
    frame_size = 0;
    int64_t start_time_us = esp_timer_get_time();
    while (esp_timer_get_time() - start_time_us < (CAPTURE_SECONDS * 1000 * 1000)) {
        memset(&buf, 0, sizeof(buf));
        buf.type   = type;
        buf.memory = MEMORY_TYPE;
        if (ioctl(fd, VIDIOC_DQBUF, &buf) != 0) {
            ESP_LOGE(TAG, "failed to receive video frame");
            ret = ESP_FAIL;
            goto exit_0;
        }

        /**
         * If no error, the flags has V4L2_BUF_FLAG_DONE. If error, the flags has V4L2_BUF_FLAG_ERROR.
         * We need to skip these frames, but we also need queue the buffer.
         */
        if (buf.flags & V4L2_BUF_FLAG_DONE) {
            frame_size += buf.bytesused;
            frame_count++;
        }

        if (ioctl(fd, VIDIOC_QBUF, &buf) != 0) {
            ESP_LOGE(TAG, "failed to queue video frame");
            ret = ESP_FAIL;
            goto exit_0;
        }
    }

    if (ioctl(fd, VIDIOC_STREAMOFF, &type) != 0) {
        ESP_LOGE(TAG, "failed to stop stream");
        ret = ESP_FAIL;
        goto exit_0;
    }

    if (frame_count > 0) {
        ESP_LOGI(TAG, "\twidth:  %" PRIu32, init_format.fmt.pix.width);
        ESP_LOGI(TAG, "\theight: %" PRIu32, init_format.fmt.pix.height);
        ESP_LOGI(TAG, "\tsize:   %" PRIu32, frame_size / frame_count);
        ESP_LOGI(TAG, "\tFPS:    %" PRIu32, frame_count / CAPTURE_SECONDS);
    } else {
        ESP_LOGW(TAG, "No frame captured");
    }

    ret = ESP_OK;

exit_0:
    close(fd);
    return ret;
}

void app_main(void)
{
    ESP_ERROR_CHECK(example_video_init());
    ESP_ERROR_CHECK(camera_capture_stream());
    ESP_ERROR_CHECK(example_video_deinit());
}
