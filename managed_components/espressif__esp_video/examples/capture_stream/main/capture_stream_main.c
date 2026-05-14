/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
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
#include "esp_check.h"
#include "example_video_common.h"
#if CONFIG_EXAMPLE_VIDEO_BUFFER_TYPE_USER
#include "esp_heap_caps.h"

#define MEMORY_TYPE V4L2_MEMORY_USERPTR
#define MEMORY_ALIGN 64
#else
#define MEMORY_TYPE V4L2_MEMORY_MMAP
#endif

#define BUFFER_COUNT 2
#define CAPTURE_SECONDS 3

static const char *TAG = "example";

static esp_err_t camera_capture_stream_by_format(int fd, int type, uint32_t v4l2_format, uint32_t width, uint32_t height)
{
    uint8_t *buffer[BUFFER_COUNT];
#if CONFIG_EXAMPLE_VIDEO_BUFFER_TYPE_USER
    uint32_t buffer_size[BUFFER_COUNT];
#endif
    uint32_t frame_size;
    uint32_t frame_count;
    struct v4l2_buffer buf;
    struct v4l2_requestbuffers req;
    struct v4l2_format format = {
        .type = type,
        .fmt.pix.width = width,
        .fmt.pix.height = height,
        .fmt.pix.pixelformat = v4l2_format,
    };

    if (ioctl(fd, VIDIOC_S_FMT, &format) != 0) {
        return ESP_FAIL;
    }

    memset(&req, 0, sizeof(req));
    req.count  = BUFFER_COUNT;
    req.type   = type;
    req.memory = MEMORY_TYPE;
    if (ioctl(fd, VIDIOC_REQBUFS, &req) != 0) {
        ESP_LOGE(TAG, "failed to require buffer");
        return ESP_FAIL;
    }

    for (int i = 0; i < BUFFER_COUNT; i++) {
        struct v4l2_buffer buf;

        memset(&buf, 0, sizeof(buf));
        buf.type        = type;
        buf.memory      = MEMORY_TYPE;
        buf.index       = i;
        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) != 0) {
            ESP_LOGE(TAG, "failed to query buffer");
            return ESP_FAIL;
        }

#if CONFIG_EXAMPLE_VIDEO_BUFFER_TYPE_USER
        buffer[i] = heap_caps_aligned_alloc(MEMORY_ALIGN, buf.length, MALLOC_CAP_SPIRAM | MALLOC_CAP_CACHE_ALIGNED);
#else
        buffer[i] = (uint8_t *)mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, fd, buf.m.offset);
#endif
        if (!buffer[i]) {
            ESP_LOGE(TAG, "failed to map buffer");
            return ESP_FAIL;
        }
#if CONFIG_EXAMPLE_VIDEO_BUFFER_TYPE_USER
        else {
            buf.m.userptr = (unsigned long)buffer[i];
            buffer_size[i] = buf.length;
        }
#endif

        if (ioctl(fd, VIDIOC_QBUF, &buf) != 0) {
            ESP_LOGE(TAG, "failed to queue video frame");
            return ESP_FAIL;
        }
    }

    if (ioctl(fd, VIDIOC_STREAMON, &type) != 0) {
        ESP_LOGE(TAG, "failed to start stream");
        return ESP_FAIL;
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
            return ESP_FAIL;
        }

        /**
         * If no error, the flags has V4L2_BUF_FLAG_DONE. If error, the flags has V4L2_BUF_FLAG_ERROR.
         * We need to skip these frames, but we also need queue the buffer.
         */
        if (buf.flags & V4L2_BUF_FLAG_DONE) {
            frame_size += buf.bytesused;
            frame_count++;
        }

#if CONFIG_EXAMPLE_VIDEO_BUFFER_TYPE_USER
        buf.m.userptr = (unsigned long)buffer[buf.index];
        buf.length = buffer_size[buf.index];
#endif
        if (ioctl(fd, VIDIOC_QBUF, &buf) != 0) {
            ESP_LOGE(TAG, "failed to queue video frame");
            return ESP_FAIL;
        }
    }

    if (ioctl(fd, VIDIOC_STREAMOFF, &type) != 0) {
        ESP_LOGE(TAG, "failed to stop stream");
        return ESP_FAIL;
    }

#if CONFIG_EXAMPLE_VIDEO_BUFFER_TYPE_USER
    for (int i = 0; i < BUFFER_COUNT; i++) {
        heap_caps_free(buffer[i]);
    }
#endif

    if (frame_count > 0) {
        ESP_LOGI(TAG, "\twidth:  %" PRIu32, format.fmt.pix.width);
        ESP_LOGI(TAG, "\theight: %" PRIu32, format.fmt.pix.height);
        ESP_LOGI(TAG, "\tsize:   %" PRIu32, frame_size / frame_count);
        ESP_LOGI(TAG, "\tFPS:    %" PRIu32, frame_count / CAPTURE_SECONDS);
    } else {
        ESP_LOGW(TAG, "No frame captured");
    }

    return ESP_OK;
}

static esp_err_t camera_capture_stream(void)
{
    int fd;
    esp_err_t ret;
    esp_cam_sensor_id_t chip_id;
    struct v4l2_capability capability;
    struct v4l2_ext_controls controls;
    struct v4l2_ext_control control[1];
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
    if (capability.capabilities & V4L2_CAP_TIMEPERFRAME) {
        ESP_LOGI(TAG, "\tTIMEPERFRAME");
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
        if (capability.device_caps & V4L2_CAP_TIMEPERFRAME) {
            ESP_LOGI(TAG, "\tTIMEPERFRAME");
        }
    }

    controls.ctrl_class = V4L2_CTRL_CLASS_ESP_CAM_IOCTL;
    controls.count      = 1;
    controls.controls   = control;
    control[0].id       = ESP_CAM_SENSOR_IOC_G_CHIP_ID;
    control[0].p_u8     = (uint8_t *)&chip_id;
    control[0].size     = sizeof(chip_id);
    if (ioctl(fd, VIDIOC_G_EXT_CTRLS, &controls) != 0) {
        ESP_LOGE(TAG, "failed to get chip id");
    } else {
        ESP_LOGI(TAG, "chip id: 0x%" PRIx16, chip_id.pid);
    }

#if CONFIG_EXAMPLE_ENABLE_CAM_SENSOR_PIC_VFLIP
    controls.ctrl_class = V4L2_CTRL_CLASS_USER;
    controls.count      = 1;
    controls.controls   = control;
    control[0].id       = V4L2_CID_VFLIP;
    control[0].value    = 1;
    if (ioctl(fd, VIDIOC_S_EXT_CTRLS, &controls) != 0) {
        ESP_LOGW(TAG, "failed to mirror the frame horizontally and skip this step");
    }
#endif

#if CONFIG_EXAMPLE_ENABLE_CAM_SENSOR_PIC_HFLIP
    controls.ctrl_class = V4L2_CTRL_CLASS_USER;
    controls.count      = 1;
    controls.controls   = control;
    control[0].id       = V4L2_CID_HFLIP;
    control[0].value    = 1;
    if (ioctl(fd, VIDIOC_S_EXT_CTRLS, &controls) != 0) {
        ESP_LOGW(TAG, "failed to mirror the frame horizontally and skip this step");
    }
#endif

    for (int fmt_index = 0; ; fmt_index++) {
        struct v4l2_fmtdesc fmtdesc = {
            .index = fmt_index,
            .type = type,
        };

        if (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) != 0) {
            break;
        }

        struct v4l2_frmsizeenum frmsize = {
            .index = 0,
            .pixel_format = fmtdesc.pixelformat,
            .type = type,
        };
        if (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) == 0) {
            for (int fmt_frmsize_index = 0; ; fmt_frmsize_index++) {
                frmsize.index = fmt_frmsize_index;
                if (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) != 0) {
                    break;
                }

                struct v4l2_frmivalenum frmival = {
                    .index = 0,
                    .pixel_format = fmtdesc.pixelformat,
                    .type = type,
                    .width = frmsize.discrete.width,
                    .height = frmsize.discrete.height,
                };
                if (ioctl(fd, VIDIOC_ENUM_FRAMEINTERVALS, &frmival) == 0) {
                    for (int fmt_frmival_index = 0; ; fmt_frmival_index++) {
                        frmival.index = fmt_frmival_index;
                        if (ioctl(fd, VIDIOC_ENUM_FRAMEINTERVALS, &frmival) != 0) {
                            break;
                        }

                        /**
                         * Set format before setting stream parameter to avoid issues
                         */
                        struct v4l2_format format = {
                            .type = type,
                            .fmt.pix.width = frmsize.discrete.width,
                            .fmt.pix.height = frmsize.discrete.height,
                            .fmt.pix.pixelformat = fmtdesc.pixelformat,
                        };
                        if (ioctl(fd, VIDIOC_S_FMT, &format) != 0) {
                            ESP_LOGE(TAG, "failed to set format");
                            ret = ESP_FAIL;
                            goto exit_0;
                        }

                        struct v4l2_streamparm sparm = {
                            .type = type,
                            .parm.capture.capability = V4L2_CAP_TIMEPERFRAME,
                            .parm.capture.timeperframe.numerator = frmival.discrete.numerator,
                            .parm.capture.timeperframe.denominator = frmival.discrete.denominator,
                        };
                        if (ioctl(fd, VIDIOC_S_PARM, &sparm) != 0) {
                            ESP_LOGE(TAG, "failed to set stream parameter");
                            break;
                        }

                        ESP_LOGI(TAG, "Capture format: %s, frame size: %" PRIu32 "x%" PRIu32 ", FPS: %0.1f, for %d seconds:",
                                 (char *)fmtdesc.description, frmsize.discrete.width, frmsize.discrete.height,
                                 (double)frmival.discrete.denominator / (double)frmival.discrete.numerator,
                                 CAPTURE_SECONDS);

                        if (camera_capture_stream_by_format(fd, type, fmtdesc.pixelformat, frmsize.discrete.width,
                                                            frmsize.discrete.height) != ESP_OK) {
                            break;
                        }
                    }
                } else {
                    struct v4l2_streamparm sparm = {
                        .type = type,
                        .parm.capture.capability = V4L2_CAP_TIMEPERFRAME,
                    };
                    struct v4l2_captureparm *cparam = &sparm.parm.capture;

                    if (ioctl(fd, VIDIOC_G_PARM, &sparm) != 0) {
                        ESP_LOGE(TAG, "failed to get stream parameter");
                        ret = ESP_FAIL;
                        goto exit_0;
                    }

                    ESP_LOGI(TAG, "Capture format: %s, frame size: %" PRIu32 "x%" PRIu32 ", FPS: %0.1f, for %d seconds:",
                             (char *)fmtdesc.description, frmsize.discrete.width, frmsize.discrete.height,
                             (double)cparam->timeperframe.denominator / (double)cparam->timeperframe.numerator,
                             CAPTURE_SECONDS);

                    if (camera_capture_stream_by_format(fd, type, fmtdesc.pixelformat, frmsize.discrete.width,
                                                        frmsize.discrete.height) != ESP_OK) {
                        break;
                    }
                }
            }
        } else {
            struct v4l2_format format = {
                .type = type,
            };
            struct v4l2_streamparm sparm = {
                .type = type,
                .parm.capture.capability = V4L2_CAP_TIMEPERFRAME,
            };
            struct v4l2_captureparm *cparam = &sparm.parm.capture;

            if (ioctl(fd, VIDIOC_G_PARM, &sparm) != 0) {
                ESP_LOGE(TAG, "failed to get stream parameter");
                ret = ESP_FAIL;
                goto exit_0;
            }

            if (ioctl(fd, VIDIOC_G_FMT, &format) != 0) {
                ESP_LOGE(TAG, "failed to get format");
                ret = ESP_FAIL;
                goto exit_0;
            }

            ESP_LOGI(TAG, "Capture format: %s, frame size: %" PRIu32 "x%" PRIu32 ", FPS: %0.1f, for %d seconds:",
                     (char *)fmtdesc.description, format.fmt.pix.width, format.fmt.pix.height,
                     (double)cparam->timeperframe.denominator / (double)cparam->timeperframe.numerator,
                     CAPTURE_SECONDS);

            if (camera_capture_stream_by_format(fd, type, fmtdesc.pixelformat, format.fmt.pix.width,
                                                format.fmt.pix.height) != ESP_OK) {
                break;
            }
        }
    }

    ret = ESP_OK;

exit_0:
    close(fd);
    return ret;
}

void app_main(void)
{
    esp_err_t ret = ESP_OK;

    ret = example_video_init();
    ESP_GOTO_ON_ERROR(ret, clean1, TAG, "Camera init failed");

    ret = camera_capture_stream();
    ESP_GOTO_ON_ERROR(ret, clean0, TAG, "Camera capture stream failed");

clean0:
    ESP_ERROR_CHECK(example_video_deinit());
clean1:
    return;
}
