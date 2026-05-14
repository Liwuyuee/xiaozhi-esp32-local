/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

// #undef LOG_LOCAL_LEVEL
// #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include <string.h>
#include "esp_log.h"
#include "esp_heap_caps.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "usb/usb_host.h"
#include "usb/uvc_host.h"
#include "esp_private/uvc_esp_video.h"

#include "esp_video.h"
#include "esp_video_device.h"
#include "esp_video_device_internal.h"
#include "esp_video_ioctl.h"

#define UVC_NAME_PREFIX    "USB-UVC"

#if CONFIG_SPIRAM
#define FRAME_MEM_CAPS                  MALLOC_CAP_SPIRAM
#else
#define FRAME_MEM_CAPS                  MALLOC_CAP_DEFAULT
#endif

#define UVC_DEVICE_INIT_TASK_STACK_SIZE (3 * 1024)
#define UVC_DEVICE_INIT_TASK_PRIORITY   5

#define UVC_DEVICE_FRAME_COUNT          3

#define UVC_DEVICE_URB_SIZE             (10 * 1024)
#define UVC_DEVICE_URB_NUM              (4)

#define UVC_INIT_TIMEOUT_MS             (10 * 1000)

#define UVC_INTERVAL_DENOMINATOR        (10 * 1000 * 1000)

struct uvc_video {
    uvc_host_stream_hdl_t stream_hdl;

    uint8_t dev_addr;
    uint8_t stream_index;
    uint32_t frame_info_num;
    uvc_host_frame_info_t *frame_info;
    uint8_t *frame_info_fmt_index;

    SemaphoreHandle_t ready_sem;
};

struct uvc_video_core {
    portMUX_TYPE lock;

    uint8_t uvc_video_num;
    struct uvc_video uvc_video[0];
};

struct uvc_device_init_task_args {
    const uvc_host_driver_event_data_t event;
    struct uvc_video_core *core;
};

static const char *TAG = "usb_uvc_device";
static struct uvc_video_core *s_uvc_video_core = NULL;

static uint32_t uvc_to_v4l2_format(enum uvc_host_stream_format uvc_format)
{
    switch (uvc_format) {
    case UVC_VS_FORMAT_YUY2:
        return V4L2_PIX_FMT_YUYV;
    case UVC_VS_FORMAT_MJPEG:
        return V4L2_PIX_FMT_JPEG;
    case UVC_VS_FORMAT_H264:
        return V4L2_PIX_FMT_H264;
    case UVC_VS_FORMAT_H265:
        return V4L2_PIX_FMT_HEVC;
    default:
        ESP_LOGE(TAG, "Unsupported pixel format %d", uvc_format);
        return 0; // Invalid format
    }
}

static esp_err_t v4l2_to_uvc_format(uint32_t v4l2_format, enum uvc_host_stream_format *uvc_format)
{
    switch (v4l2_format) {
    case V4L2_PIX_FMT_YUYV:
        *uvc_format = UVC_VS_FORMAT_YUY2;
        return ESP_OK;
    case V4L2_PIX_FMT_JPEG:
        *uvc_format = UVC_VS_FORMAT_MJPEG;
        return ESP_OK;
    case V4L2_PIX_FMT_H264:
        *uvc_format = UVC_VS_FORMAT_H264;
        return ESP_OK;
    case V4L2_PIX_FMT_HEVC:
        *uvc_format = UVC_VS_FORMAT_H265;
        return ESP_OK;
    default:
        ESP_LOGE(TAG, "Unsupported pixel format %" PRIu32, v4l2_format);
        return ESP_ERR_INVALID_ARG;
    }
}

static bool uvc_frame_callback(const uvc_host_frame_t *frame, void *user_ctx)
{
    struct esp_video *video = (struct esp_video *)user_ctx;
    struct esp_video_buffer_element *element;

    element = CAPTURE_VIDEO_GET_QUEUED_ELEMENT(video);
    if (element) {
        if (frame->data_len > ELEMENT_SIZE(element)) {
            CAPTURE_VIDEO_SKIP_BUF(video, ELEMENT_BUFFER(element));
            ESP_EARLY_LOGE(TAG, "Frame data length is greater than element buffer size");
            return false;
        }

        memcpy(ELEMENT_BUFFER(element), frame->data, frame->data_len);
        CAPTURE_VIDEO_DONE_BUF(video, ELEMENT_BUFFER(element), frame->data_len);
    }

    return true;
}

static void uvc_event_callback(const uvc_host_stream_event_data_t *event, void *user_ctx)
{
    switch (event->type) {
    case UVC_HOST_TRANSFER_ERROR:
        ESP_LOGD(TAG, "USB error has occurred, err_no = %i", event->transfer_error.error);
        break;
    case UVC_HOST_DEVICE_DISCONNECTED: {
        struct esp_video *video = (struct esp_video *)user_ctx;
        struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);

        ESP_LOGD(TAG, "Device disconnected, dev_addr = %d, stream_index = %d", device->dev_addr, device->stream_index);

        device->dev_addr = 0;
        device->stream_index = 0;
        device->frame_info_num = 0;
        xSemaphoreTake(device->ready_sem, 0);
        break;
    }
    case UVC_HOST_FRAME_BUFFER_OVERFLOW:
        ESP_LOGD(TAG, "Frame buffer overflow");
        break;
    case UVC_HOST_FRAME_BUFFER_UNDERFLOW:
        ESP_LOGD(TAG, "Frame buffer underflow");
        break;
    default:
        abort();
        break;
    }
}

static void uvc_host_driver_event_callback(const uvc_host_driver_event_data_t *event, void *user_ctx)
{
    struct uvc_video_core *core = (struct uvc_video_core *)user_ctx;

    switch (event->type) {
    case UVC_HOST_DRIVER_EVENT_DEVICE_CONNECTED: {
        struct uvc_video *found_device = NULL;

        ESP_LOGD(TAG, "Device connected");

        /**
         * Active the video device with given stream parameters
         */

        portENTER_CRITICAL(&core->lock);
        for (int i = 0; i < core->uvc_video_num; i++) {
            struct uvc_video *device = &core->uvc_video[i];

            if (device->dev_addr == 0) {
                device->dev_addr = event->device_connected.dev_addr;
                device->stream_index = event->device_connected.uvc_stream_index;
                device->frame_info_num = event->device_connected.frame_info_num;
                found_device = device;
                break;
            }
        }
        portEXIT_CRITICAL(&core->lock);

        if (!found_device) {
            ESP_LOGD(TAG, "No free UVC device found");
            break;
        } else {
            xSemaphoreGive(found_device->ready_sem);
        }

        ESP_LOGD(TAG, "UVC device found, dev_addr = %d, stream_index = %d",
                 found_device->dev_addr, found_device->stream_index);
        break;
    }
    default:
        ESP_LOGD(TAG, "Unknown UVC host driver event type: %d", event->type);
        break;
    }
}

static esp_err_t uvc_video_init(struct esp_video *video)
{
    esp_err_t ret;
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);

    ESP_RETURN_ON_FALSE((xSemaphoreTake(device->ready_sem, UVC_INIT_TIMEOUT_MS / portTICK_PERIOD_MS) == pdPASS), ESP_ERR_NOT_FOUND,
                        TAG, "Failed to take UVC device ready semaphore");
    ESP_GOTO_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, fail0, TAG, "UVC device=%p is not connected", device);

    device->frame_info = malloc((sizeof(uvc_host_frame_info_t) + sizeof(uint8_t)) * device->frame_info_num);
    ESP_GOTO_ON_FALSE(device->frame_info, ESP_ERR_NO_MEM, fail0, TAG, "Failed to allocate memory for frame info");

    device->frame_info_fmt_index = (uint8_t *)device->frame_info + sizeof(uvc_host_frame_info_t) * device->frame_info_num;
    memset(device->frame_info_fmt_index, -1, sizeof(uint8_t) * device->frame_info_num);

    size_t list_size = device->frame_info_num;
    ESP_GOTO_ON_ERROR(uvc_host_get_frame_list(device->dev_addr, device->stream_index, (uvc_host_frame_info_t (*)[1])device->frame_info, &list_size),
                      fail1, TAG, "Failed to get frame info");

#if 0
    for (int i = 0; i < device->frame_info_num; i++) {
        ESP_LOGI(TAG, "Frame info %d: format=%d, h_res=%d, v_res=%d, default_interval=%d, interval_type=%d", i,
                 device->frame_info[i].format, device->frame_info[i].h_res, device->frame_info[i].v_res, device->frame_info[i].default_interval,
                 device->frame_info[i].interval_type);
        if (device->frame_info[i].interval_type == 0) {
            ESP_LOGI(TAG, "\tinterval_min = %d, interval_max = %d, interval_step = %d",
                     device->frame_info[i].interval_min, device->frame_info[i].interval_max, device->frame_info[i].interval_step);
        } else {
            int num = MIN(device->frame_info[i].interval_type, CONFIG_UVC_INTERVAL_ARRAY_SIZE);
            for (int j = 0; j < num; j++) {
                ESP_LOGI(TAG, "\tinterval[%d] = %d", j, device->frame_info[i].interval[j]);
            }
        }
    }
#endif

    uvc_host_stream_config_t stream_config = {
        .event_cb = uvc_event_callback,
        .frame_cb = uvc_frame_callback,
        .user_ctx = video,
        .usb = {
            .dev_addr = device->dev_addr,
            .vid = UVC_HOST_ANY_VID,
            .pid = UVC_HOST_ANY_PID,
            .uvc_stream_index = device->stream_index,
        },
        .vs_format = {
            .h_res = device->frame_info[0].h_res,
            .v_res = device->frame_info[0].v_res,
            .fps = 10 * 1000 * 1000 / device->frame_info[0].default_interval,
            .format = device->frame_info[0].format,
        },
        .advanced = {
            .number_of_frame_buffers = UVC_DEVICE_FRAME_COUNT,
            .frame_size = 0,
            .frame_heap_caps = FRAME_MEM_CAPS,
            .number_of_urbs = UVC_DEVICE_URB_NUM,
            .urb_size = UVC_DEVICE_URB_SIZE,
        },
    };

    uvc_host_stream_hdl_t stream_hdl = NULL;
    ESP_GOTO_ON_ERROR(uvc_host_stream_open(&stream_config, 0, &stream_hdl), fail1, TAG, "Failed to open UVC stream");

    uvc_host_stream_format_t uvc_format;
    uvc_host_buf_info_t uvc_buf_info;
    ESP_GOTO_ON_ERROR(uvc_host_stream_format_get(stream_hdl, &uvc_format), fail2, TAG, "Failed to get UVC format");
    ESP_GOTO_ON_ERROR(uvc_host_buf_info_get(stream_hdl, &uvc_buf_info), fail2, TAG, "Failed to get UVC buffer info");

    uint32_t v4l2_format = uvc_to_v4l2_format(uvc_format.format);

    CAPTURE_VIDEO_SET_FORMAT(video, uvc_format.h_res, uvc_format.v_res, v4l2_format);
    CAPTURE_VIDEO_SET_BUF_INFO(video, uvc_buf_info.dwMaxVideoFrameSize, 4, FRAME_MEM_CAPS);

    device->stream_hdl = stream_hdl;

    /*
     * Build a mapping table from UVC format index to V4L2 format index
     */
    int min_uvc_fmt_index = UVC_VS_FORMAT_MJPEG;
    int max_uvc_fmt_index = UVC_VS_FORMAT_H265;
    int v4l2_fmt_index = 0;
    for (int index = min_uvc_fmt_index; index <= max_uvc_fmt_index; index++) {
        int j;
        bool found = false;

        for (j = 0; j < device->frame_info_num; j++) {
            if (device->frame_info[j].format == index) {
                found = true;
                break;
            }
        }

        if (found) {
            for (; j < device->frame_info_num; j++) {
                if (device->frame_info[j].format == index) {
                    device->frame_info_fmt_index[j] = v4l2_fmt_index;
                }
            }
        }

        v4l2_fmt_index++;
    }

    return ESP_OK;

fail2:
    uvc_host_stream_close(stream_hdl);
fail1:
    free(device->frame_info);
    device->frame_info = NULL;
fail0:
    xSemaphoreGive(device->ready_sem);
    return ret;
}

static esp_err_t uvc_video_start(struct esp_video *video, uint32_t type)
{
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    ESP_RETURN_ON_ERROR(uvc_host_stream_start(device->stream_hdl), TAG, "Failed to start UVC stream");

    return ESP_OK;
}

static esp_err_t uvc_video_stop(struct esp_video *video, uint32_t type)
{
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    ESP_RETURN_ON_ERROR(uvc_host_stream_stop(device->stream_hdl), TAG, "Failed to stop UVC stream");

    return ESP_OK;
}

static esp_err_t uvc_video_deinit(struct esp_video *video)
{
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    ESP_RETURN_ON_ERROR(uvc_host_stream_close(device->stream_hdl), TAG, "Failed to close UVC stream");
    device->stream_hdl = NULL;

    free(device->frame_info);
    device->frame_info = NULL;

    xSemaphoreGive(device->ready_sem);

    return ESP_OK;
}

static esp_err_t uvc_video_enum_format(struct esp_video *video, uint32_t type, uint32_t index, uint32_t *pixel_format)
{
    esp_err_t ret = ESP_ERR_INVALID_ARG;
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    if (index >= device->frame_info_num) {
        ESP_LOGD(TAG, "Index %"PRIu32" is out of range", index);
        return ESP_ERR_INVALID_ARG;
    }

    for (int i = 0; i < device->frame_info_num; i++) {
        if (device->frame_info_fmt_index[i] == index) {
            *pixel_format = uvc_to_v4l2_format(device->frame_info[i].format);
            ret = ESP_OK;
            break;
        }
    }

    return ret;
}

static esp_err_t uvc_video_set_format(struct esp_video *video, const struct v4l2_format *format)
{
    enum uvc_host_stream_format uvc_stream_format;
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    ESP_RETURN_ON_ERROR(v4l2_to_uvc_format(GET_FORMAT_PIXEL_FORMAT(format), &uvc_stream_format), TAG, "Failed to convert V4L2 format to UVC format");

    uint32_t width = GET_FORMAT_WIDTH(format);
    uint32_t height = GET_FORMAT_HEIGHT(format);
    float fps = 0;
    for (int i = 0; i < device->frame_info_num; i++) {
        if (device->frame_info[i].format == uvc_stream_format) {
            if (device->frame_info[i].h_res == width && device->frame_info[i].v_res == height) {
                fps = (double)UVC_INTERVAL_DENOMINATOR / (double)device->frame_info[i].default_interval;
                break;
            }
        }
    }

    uvc_host_stream_format_t f = {
        .h_res = GET_FORMAT_WIDTH(format),
        .v_res = GET_FORMAT_HEIGHT(format),
        .fps = fps,
        .format = uvc_stream_format,
    };
    ESP_RETURN_ON_ERROR(uvc_host_stream_format_select(device->stream_hdl, &f), TAG, "Failed to set UVC format");

    uvc_host_buf_info_t uvc_buf_info;
    ESP_RETURN_ON_ERROR(uvc_host_buf_info_get(device->stream_hdl, &uvc_buf_info), TAG, "Failed to get UVC buffer info");

    CAPTURE_VIDEO_SET_FORMAT(video, f.h_res, f.v_res, GET_FORMAT_PIXEL_FORMAT(format));
    CAPTURE_VIDEO_SET_BUF_INFO(video, uvc_buf_info.dwMaxVideoFrameSize, 4, FRAME_MEM_CAPS);

    return ESP_OK;
}

static esp_err_t uvc_video_notify(struct esp_video *video, enum esp_video_event event, void *arg)
{
    return ESP_OK;
}

static esp_err_t uvc_video_set_parm(struct esp_video *video, struct v4l2_streamparm *stream_parm, struct esp_video_stream *stream)
{
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);
    struct v4l2_fract *time_per_frame = &stream_parm->parm.capture.timeperframe;
    float fps = (float)time_per_frame->denominator / (float)time_per_frame->numerator;

    ESP_RETURN_ON_FALSE(time_per_frame->numerator > 0 && time_per_frame->denominator > 0, ESP_ERR_INVALID_ARG, TAG, "Invalid time per frame");
    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    uvc_host_stream_format_t f = {
        .h_res = 0,  // 0 means do not change resolution
        .v_res = 0,
        .fps = fps,
        .format = 0, // 0 means do not change format
    };

    ESP_RETURN_ON_ERROR(uvc_host_stream_format_select(device->stream_hdl, &f), TAG, "Failed to set UVC format");

    return ESP_OK;
}

static esp_err_t uvc_video_get_parm(struct esp_video *video, struct v4l2_streamparm *stream_parm, struct esp_video_stream *stream)
{
    uvc_host_stream_format_t uvc_format;
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);
    struct v4l2_fract *time_per_frame = &stream_parm->parm.capture.timeperframe;

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    ESP_RETURN_ON_ERROR(uvc_host_stream_format_get(device->stream_hdl, &uvc_format), TAG, "Failed to get UVC format");
    ESP_RETURN_ON_FALSE(uvc_format.fps > 0.0, ESP_ERR_INVALID_ARG, TAG, "Invalid FPS");

    time_per_frame->numerator   = UVC_INTERVAL_DENOMINATOR;
    time_per_frame->denominator = UVC_INTERVAL_DENOMINATOR * uvc_format.fps;

    return ESP_OK;
}

static esp_err_t uvc_video_enum_framesizes(struct esp_video *video, struct v4l2_frmsizeenum *frmsize, struct esp_video_stream *stream)
{
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);
    esp_err_t ret = ESP_ERR_INVALID_ARG;

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    enum uvc_host_stream_format uvc_format;
    ESP_RETURN_ON_ERROR(v4l2_to_uvc_format(frmsize->pixel_format, &uvc_format), TAG, "Failed to convert V4L2 format to UVC format");

    int uvc_fmt_resolution_index = -1;
    for (int i = 0; i < device->frame_info_num; i++) {
        if (device->frame_info[i].format == uvc_format) {
            uvc_fmt_resolution_index++;

            if (uvc_fmt_resolution_index == frmsize->index) {
                frmsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
                frmsize->discrete.width = device->frame_info[i].h_res;
                frmsize->discrete.height = device->frame_info[i].v_res;
                ret = ESP_OK;
                break;
            }
        }
    }

    return ret;
}

static esp_err_t uvc_video_enum_frameintervals(struct esp_video *video, struct v4l2_frmivalenum *frmival, struct esp_video_stream *stream)
{
    struct uvc_video *device = VIDEO_PRIV_DATA(struct uvc_video *, video);
    esp_err_t ret = ESP_ERR_INVALID_ARG;

    ESP_RETURN_ON_FALSE(device->dev_addr, ESP_ERR_NOT_FOUND, TAG, "UVC device=%p is not connected", device);

    enum uvc_host_stream_format uvc_format;
    ESP_RETURN_ON_ERROR(v4l2_to_uvc_format(frmival->pixel_format, &uvc_format), TAG, "Failed to convert V4L2 format to UVC format");

    for (int i = 0; i < device->frame_info_num; i++) {
        if ((device->frame_info[i].format == uvc_format) &&
                (device->frame_info[i].h_res == frmival->width) &&
                (device->frame_info[i].v_res == frmival->height)) {
            if (!device->frame_info[i].interval_type) {
                if (frmival->index != 0) {
                    return ESP_ERR_INVALID_ARG;
                }

                frmival->type = V4L2_FRMIVAL_TYPE_STEPWISE;
                frmival->stepwise.min.numerator = device->frame_info[i].interval_min;
                frmival->stepwise.min.denominator = UVC_INTERVAL_DENOMINATOR;
                frmival->stepwise.max.numerator = device->frame_info[i].interval_max;
                frmival->stepwise.max.denominator = UVC_INTERVAL_DENOMINATOR;
                frmival->stepwise.step.numerator = device->frame_info[i].interval_step;
                frmival->stepwise.step.denominator = UVC_INTERVAL_DENOMINATOR;
                ret = ESP_OK;
                break;
            } else {
                if (frmival->index >= device->frame_info[i].interval_type) {
                    return ESP_ERR_INVALID_ARG;
                }

                frmival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
                frmival->discrete.numerator = device->frame_info[i].interval[frmival->index];
                frmival->discrete.denominator = UVC_INTERVAL_DENOMINATOR;
                ret = ESP_OK;
                break;
            }
        }
    }
    return ret;
}

static const struct esp_video_ops s_uvc_video_ops = {
    .init          = uvc_video_init,
    .deinit        = uvc_video_deinit,
    .start         = uvc_video_start,
    .stop          = uvc_video_stop,
    .enum_format   = uvc_video_enum_format,
    .set_format    = uvc_video_set_format,
    .notify        = uvc_video_notify,
    .set_parm      = uvc_video_set_parm,
    .get_parm      = uvc_video_get_parm,
    .enum_framesizes = uvc_video_enum_framesizes,
    .enum_frameintervals = uvc_video_enum_frameintervals,
};

esp_err_t esp_video_install_usb_uvc_driver(const esp_video_usb_uvc_device_config_t *cfg)
{
    esp_err_t ret;
    struct uvc_video_core *core;
    struct esp_video *video[ESP_VIDEO_USB_UVC_DEVICE_ID_NUM] = {0};
    uint32_t device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_EXT_PIX_FORMAT | V4L2_CAP_STREAMING | V4L2_CAP_TIMEPERFRAME;
    uint32_t caps = device_caps | V4L2_CAP_DEVICE_CAPS;

    ESP_RETURN_ON_FALSE(cfg->uvc_dev_num > 0 && cfg->uvc_dev_num <= ESP_VIDEO_USB_UVC_DEVICE_ID_NUM, ESP_ERR_INVALID_ARG, TAG, "uvc_dev_num is out of range");

    core = heap_caps_calloc(1, sizeof(struct uvc_video_core) + sizeof(struct uvc_video) * cfg->uvc_dev_num, MALLOC_CAP_8BIT | MALLOC_CAP_INTERNAL);
    ESP_RETURN_ON_FALSE(core, ESP_ERR_NO_MEM, TAG, "Failed to allocate memory for uvc_video_core");

    core->uvc_video_num = cfg->uvc_dev_num;

    for (int i = 0; i < cfg->uvc_dev_num; i++) {
        char name[12];

        assert(snprintf(name, sizeof(name), UVC_NAME_PREFIX "%d", i) > 0);

        core->uvc_video[i].ready_sem = xSemaphoreCreateBinary();
        ESP_GOTO_ON_FALSE(core->uvc_video[i].ready_sem, ESP_ERR_NO_MEM, fail0, TAG, "Failed to create UVC device ready semaphore");

        video[i] = esp_video_create(name, ESP_VIDEO_USB_UVC_DEVICE_ID(i), &s_uvc_video_ops, &core->uvc_video[i], caps, device_caps);
        ESP_GOTO_ON_FALSE(video[i], ESP_ERR_NO_MEM, fail0, TAG, "Failed to create esp_video");
    }

    core->lock = (portMUX_TYPE)portMUX_INITIALIZER_UNLOCKED;

    const uvc_host_driver_config_t driver_config = {
        .driver_task_stack_size = cfg->task_stack,
        .driver_task_priority = cfg->task_priority,
        .xCoreID = cfg->task_affinity >= 0 ? cfg->task_affinity : tskNO_AFFINITY,
        .create_background_task = true,
        .event_cb = uvc_host_driver_event_callback,
        .user_ctx = core,
    };
    ESP_GOTO_ON_ERROR(uvc_host_install(&driver_config), fail0, TAG, "Failed to install UVC host driver");

    s_uvc_video_core = core;

    return ESP_OK;

fail0:
    for (int i = 0; i < cfg->uvc_dev_num; i++) {
        if (video[i]) {
            if (core->uvc_video[i].ready_sem) {
                vSemaphoreDelete(core->uvc_video[i].ready_sem);
            }

            esp_video_destroy(video[i]);
        }
    }
    free(core);
    return ret;
}

esp_err_t esp_video_uninstall_usb_uvc_driver(void)
{
    if (s_uvc_video_core) {
        struct uvc_video_core *core = s_uvc_video_core;

        for (int i = 0; i < core->uvc_video_num; i++) {
            struct esp_video *video;
            char name[12];

            assert(snprintf(name, sizeof(name), UVC_NAME_PREFIX "%d", i) > 0);

            video = esp_video_device_get_object(name);
            if (!video) {
                ESP_LOGW(TAG, "UVC device %s not found", name);
                return ESP_FAIL;
            }

            esp_video_destroy(video);

            if (core->uvc_video[i].ready_sem) {
                vSemaphoreDelete(core->uvc_video[i].ready_sem);
            }
        }

        free(s_uvc_video_core);
        s_uvc_video_core = NULL;
    }

    return uvc_host_uninstall();
}
