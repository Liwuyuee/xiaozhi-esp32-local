/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_private/esp_cache_private.h"
#include "esp_cam_ctlr_spi.h"
#include "esp_video.h"
#include "esp_video_device_internal.h"
#include "esp_video_cam.h"

#define SPI_NAME                        "SPI"

#if CONFIG_SPIRAM
#define SPI_MEM_CAPS                    (MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM | MALLOC_CAP_CACHE_ALIGNED)
#else
#define SPI_MEM_CAPS                    (MALLOC_CAP_8BIT | MALLOC_CAP_DMA)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)                   sizeof(x) / sizeof((x)[0])
#endif

struct spi_video {
    cam_ctlr_color_t in_color;
    esp_cam_ctlr_handle_t cam_ctrl_handle;
    esp_video_cam_t cam;
    esp_video_spi_device_config_t spi_config;
};

static const char *TAG = "spi_video";

static esp_err_t spi_get_input_frame_type(esp_cam_sensor_output_format_t sensor_format,
        cam_ctlr_color_t *in_color,
        uint32_t *v4l2_format,
        uint32_t *bpp)
{
    esp_err_t ret = ESP_OK;

    switch (sensor_format) {
    case ESP_CAM_SENSOR_PIXFORMAT_RGB565:
        *in_color = CAM_CTLR_COLOR_RGB565;
        *v4l2_format = V4L2_PIX_FMT_RGB565;
        *bpp = 16;
        break;
    case ESP_CAM_SENSOR_PIXFORMAT_YUV422:
        *in_color = CAM_CTLR_COLOR_YUV422;
        *v4l2_format = V4L2_PIX_FMT_YUV422P;
        *bpp = 16;
        break;
    case ESP_CAM_SENSOR_PIXFORMAT_RGB888:
        *in_color = CAM_CTLR_COLOR_RGB888;
        *v4l2_format = V4L2_PIX_FMT_RGB24;
        *bpp = 24;
        break;
    case ESP_CAM_SENSOR_PIXFORMAT_JPEG:
        *in_color = 0;
        *v4l2_format = V4L2_PIX_FMT_JPEG;
        *bpp = 8;
        break;
    case ESP_CAM_SENSOR_PIXFORMAT_RAW8:
        *in_color = CAM_CTLR_COLOR_RAW8;
        *v4l2_format = V4L2_PIX_FMT_SBGGR8;
        *bpp = 8;
        break;
    case ESP_CAM_SENSOR_PIXFORMAT_RAW10:
        *in_color = CAM_CTLR_COLOR_RAW10;
        *v4l2_format = V4L2_PIX_FMT_SBGGR10;
        *bpp = 10;
        break;
    case ESP_CAM_SENSOR_PIXFORMAT_RAW12:
        *in_color = CAM_CTLR_COLOR_RAW12;
        *v4l2_format = V4L2_PIX_FMT_SBGGR12;
        *bpp = 12;
        break;
    case ESP_CAM_SENSOR_PIXFORMAT_GRAYSCALE:
        *in_color = CAM_CTLR_COLOR_GRAY8;
        *v4l2_format = V4L2_PIX_FMT_GREY;
        *bpp = 8;
        break;
    default:
        ret = ESP_ERR_NOT_SUPPORTED;
        break;
    }

    return ret;
}

static bool IRAM_ATTR spi_video_on_trans_finished(esp_cam_ctlr_handle_t handle, esp_cam_ctlr_trans_t *trans, void *user_data)
{
    struct esp_video *video = (struct esp_video *)user_data;

    ESP_EARLY_LOGD(TAG, "size=%zu", trans->received_size);

    CAPTURE_VIDEO_DONE_BUF(video, trans->buffer, trans->received_size);

    return true;
}

static bool IRAM_ATTR spi_video_on_get_new_trans(esp_cam_ctlr_handle_t handle, esp_cam_ctlr_trans_t *trans, void *user_data)
{
    struct esp_video_buffer_element *element;
    struct esp_video *video = (struct esp_video *)user_data;

    element = CAPTURE_VIDEO_GET_QUEUED_ELEMENT(video);
    if (!element) {
        return false;
    }

    trans->buffer = element->buffer;
    trans->buflen = ELEMENT_SIZE(element);

    return true;
}

static esp_err_t init_config(struct esp_video *video)
{
    uint32_t in_bpp;
    uint32_t v4l2_format;
    esp_cam_sensor_format_t sensor_format;
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);
    esp_cam_sensor_device_t *cam_dev = spi_video->cam.sensor;

    ESP_RETURN_ON_ERROR(esp_cam_sensor_get_format(cam_dev, &sensor_format), TAG, "failed to get sensor format");
    ESP_RETURN_ON_ERROR(spi_get_input_frame_type(sensor_format.format, &spi_video->in_color, &v4l2_format, &in_bpp), TAG, "failed to get SPI input frame type");

    CAPTURE_VIDEO_SET_FORMAT(video,
                             sensor_format.width,
                             sensor_format.height,
                             v4l2_format);

    uint32_t buf_size;
    if (sensor_format.spi_info.frame_info) {
        buf_size = sensor_format.spi_info.frame_info->frame_size;
    } else {
        buf_size = CAPTURE_VIDEO_GET_FORMAT_WIDTH(video) * CAPTURE_VIDEO_GET_FORMAT_HEIGHT(video) * in_bpp / 8;
    }

    ESP_LOGD(TAG, "buffer size=%" PRIu32, buf_size);

    size_t alignments = 0;
#if CONFIG_SPIRAM
    ESP_RETURN_ON_ERROR(esp_cache_get_alignment(SPI_MEM_CAPS, &alignments), TAG, "failed to get cache alignment");
#else
    alignments = 4;
#endif
    ESP_LOGD(TAG, "alignments=%zu", alignments);

    CAPTURE_VIDEO_SET_BUF_INFO(video, buf_size, alignments, SPI_MEM_CAPS);

    return ESP_OK;
}

static esp_err_t spi_video_init(struct esp_video *video)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    ESP_RETURN_ON_ERROR(esp_cam_sensor_set_format(spi_video->cam.sensor, NULL), TAG, "failed to set basic format");
    ESP_RETURN_ON_ERROR(init_config(video), TAG, "failed to initialize config");

    return ESP_OK;
}

static esp_err_t spi_video_start(struct esp_video *video, uint32_t type)
{
    esp_err_t ret;
    esp_cam_sensor_format_t sensor_format;
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);
    esp_cam_sensor_device_t *cam_dev = spi_video->cam.sensor;

    ESP_RETURN_ON_ERROR(esp_cam_sensor_get_format(cam_dev, &sensor_format), TAG, "failed to get sensor format");

    esp_cam_ctlr_spi_config_t spi_config = {
        .spi_port = spi_video->spi_config.spi_port,
        .spi_cs_pin = spi_video->spi_config.spi_cs_pin,
        .spi_sclk_pin = spi_video->spi_config.spi_sclk_pin,
        .spi_data0_io_pin = spi_video->spi_config.spi_data0_io_pin,
        .input_data_color_type = spi_video->in_color,
        .h_res = CAPTURE_VIDEO_GET_FORMAT_WIDTH(video),
        .v_res = CAPTURE_VIDEO_GET_FORMAT_HEIGHT(video),
        .frame_info = sensor_format.spi_info.frame_info,
        .auto_decode_dis = 1,
    };

    ESP_RETURN_ON_ERROR(esp_cam_new_spi_ctlr(&spi_config, &spi_video->cam_ctrl_handle), TAG, "failed to create SPI");

    esp_cam_ctlr_evt_cbs_t cam_ctrl_cbs = {
        .on_get_new_trans = spi_video_on_get_new_trans,
        .on_trans_finished = spi_video_on_trans_finished
    };
    ESP_GOTO_ON_ERROR(esp_cam_ctlr_register_event_callbacks(spi_video->cam_ctrl_handle, &cam_ctrl_cbs, video), fail0, TAG, "failed to register CAM ctlr event callback");
    ESP_GOTO_ON_ERROR(esp_cam_ctlr_enable(spi_video->cam_ctrl_handle), fail0, TAG, "failed to enable SPI");
    ESP_GOTO_ON_ERROR(esp_cam_ctlr_start(spi_video->cam_ctrl_handle), fail1, TAG, "failed to start SPI camera");

    int flags = 1;
    ESP_GOTO_ON_ERROR(esp_cam_sensor_ioctl(cam_dev, ESP_CAM_SENSOR_IOC_S_STREAM, &flags), fail2, TAG, "failed to start sensor");

    return ESP_OK;

fail2:
    esp_cam_ctlr_stop(spi_video->cam_ctrl_handle);
fail1:
    esp_cam_ctlr_disable(spi_video->cam_ctrl_handle);
fail0:
    esp_cam_ctlr_del(spi_video->cam_ctrl_handle);
    spi_video->cam_ctrl_handle = NULL;
    return ret;
}

static esp_err_t spi_video_stop(struct esp_video *video, uint32_t type)
{
    int flags = 0;
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);
    esp_cam_sensor_device_t *cam_dev = spi_video->cam.sensor;

    ESP_RETURN_ON_ERROR(esp_cam_sensor_ioctl(cam_dev, ESP_CAM_SENSOR_IOC_S_STREAM, &flags), TAG, "failed to disable sensor");

    ESP_RETURN_ON_ERROR(esp_cam_ctlr_stop(spi_video->cam_ctrl_handle), TAG, "failed to stop CAM ctlr");
    ESP_RETURN_ON_ERROR(esp_cam_ctlr_disable(spi_video->cam_ctrl_handle), TAG, "failed to disable CAM ctlr");
    ESP_RETURN_ON_ERROR(esp_cam_ctlr_del(spi_video->cam_ctrl_handle), TAG, "failed to delete cam ctlr");

    spi_video->cam_ctrl_handle = NULL;

    return ESP_OK;
}

static esp_err_t spi_video_deinit(struct esp_video *video)
{
    return ESP_OK;
}

static esp_err_t spi_video_enum_format(struct esp_video *video, uint32_t type, uint32_t index, uint32_t *pixel_format)
{
    if (index >= 1) {
        return ESP_ERR_INVALID_ARG;
    }

    *pixel_format = CAPTURE_VIDEO_GET_FORMAT_PIXEL_FORMAT(video);

    return ESP_OK;
}

static esp_err_t spi_video_set_format(struct esp_video *video, const struct v4l2_format *format)
{
    const struct v4l2_pix_format *pix = &format->fmt.pix;

    if (pix->width != CAPTURE_VIDEO_GET_FORMAT_WIDTH(video) ||
            pix->height != CAPTURE_VIDEO_GET_FORMAT_HEIGHT(video) ||
            pix->pixelformat != CAPTURE_VIDEO_GET_FORMAT_PIXEL_FORMAT(video)) {
        ESP_LOGE(TAG, "format is not supported");
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}

static esp_err_t spi_video_notify(struct esp_video *video, enum esp_video_event event, void *arg)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    if (event == ESP_VIDEO_DATA_PREPROCESSING) {
        struct esp_video_buffer_element *element = CAPTURE_VIDEO_GET_FIRST_DONE_ELEMENT_PTR(video);
        if (element) {
            uint32_t decoded_size;
            esp_err_t ret = esp_cam_spi_decode_frame(spi_video->cam_ctrl_handle, element->buffer, element->valid_size,
                            element->buffer, CAPTURE_VIDEO_BUF_SIZE(video), &decoded_size);
            if (ret == ESP_OK) {
                element->valid_size = decoded_size;
            } else {
                element->valid_size = 0;
            }
        }
    }

    return ESP_OK;
}

static esp_err_t spi_video_set_ext_ctrl(struct esp_video *video, const struct v4l2_ext_controls *ctrls)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    return esp_video_cam_set_ext_ctrls(&spi_video->cam, ctrls);
}

static esp_err_t spi_video_get_ext_ctrl(struct esp_video *video, struct v4l2_ext_controls *ctrls)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    return esp_video_cam_get_ext_ctrls(&spi_video->cam, ctrls);
}

static esp_err_t spi_video_query_ext_ctrl(struct esp_video *video, struct v4l2_query_ext_ctrl *qctrl)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    return esp_video_cam_query_ext_ctrls(&spi_video->cam, qctrl);
}

static esp_err_t spi_video_set_sensor_format(struct esp_video *video, const esp_cam_sensor_format_t *format)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    ESP_RETURN_ON_ERROR(esp_cam_sensor_set_format(spi_video->cam.sensor, format), TAG, "failed to set customer format");
    ESP_RETURN_ON_ERROR(init_config(video), TAG, "failed to initialize config");

    return ESP_OK;
}

static esp_err_t spi_video_get_sensor_format(struct esp_video *video, esp_cam_sensor_format_t *format)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    return esp_cam_sensor_get_format(spi_video->cam.sensor, format);
}

static esp_err_t spi_video_query_menu(struct esp_video *video, struct v4l2_querymenu *qmenu)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    return esp_video_cam_query_menu(&spi_video->cam, qmenu);
}

static esp_err_t spi_video_get_parm(struct esp_video *video, struct v4l2_streamparm *stream_parm, struct esp_video_stream *stream)
{
    struct spi_video *spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);
    struct v4l2_captureparm *cp = &stream_parm->parm.capture;
    esp_cam_sensor_format_t sensor_format;

    ESP_RETURN_ON_ERROR(esp_cam_sensor_get_format(spi_video->cam.sensor, &sensor_format), TAG, "failed to get sensor format");
    cp->capability |= V4L2_CAP_TIMEPERFRAME;
    cp->timeperframe.numerator = 1;
    cp->timeperframe.denominator = sensor_format.fps;

    return ESP_OK;
}

static const struct esp_video_ops s_spi_video_ops = {
    .init           = spi_video_init,
    .deinit         = spi_video_deinit,
    .start          = spi_video_start,
    .stop           = spi_video_stop,
    .enum_format    = spi_video_enum_format,
    .set_format     = spi_video_set_format,
    .notify         = spi_video_notify,
    .set_ext_ctrl   = spi_video_set_ext_ctrl,
    .get_ext_ctrl   = spi_video_get_ext_ctrl,
    .query_ext_ctrl = spi_video_query_ext_ctrl,
    .set_sensor_format = spi_video_set_sensor_format,
    .get_sensor_format = spi_video_get_sensor_format,
    .query_menu    = spi_video_query_menu,
    .get_parm      = spi_video_get_parm,
};

/**
 * @brief Create SPI video device
 *
 * @param cam_dev       Camera sensor device
 * @param config        SPI video device configuration
 * @param index         SPI video device index
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_create_spi_video_device(esp_cam_sensor_device_t *cam_dev, const esp_video_spi_device_config_t *config, uint8_t index)
{
    const char *name;
    uint8_t id;
    struct esp_video *video;
    struct spi_video *spi_video;
    uint32_t device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_EXT_PIX_FORMAT | V4L2_CAP_STREAMING;
    uint32_t caps = device_caps | V4L2_CAP_DEVICE_CAPS;

    if (index == 0) {
        name = ESP_VIDEO_SPI_DEVICE_0_NAME;
        id = ESP_VIDEO_SPI_DEVICE_0_ID;
    } else if (index == 1) {
        name = ESP_VIDEO_SPI_DEVICE_1_NAME;
        id = ESP_VIDEO_SPI_DEVICE_1_ID;
    } else {
        return ESP_ERR_INVALID_ARG;
    }

    spi_video = heap_caps_calloc(1, sizeof(struct spi_video), MALLOC_CAP_8BIT | MALLOC_CAP_INTERNAL);
    if (!spi_video) {
        return ESP_ERR_NO_MEM;
    }

    spi_video->cam.sensor = cam_dev;
    spi_video->spi_config = *config;

    video = esp_video_create(name, id, &s_spi_video_ops, spi_video, caps, device_caps);
    if (!video) {
        heap_caps_free(spi_video);
        return ESP_FAIL;
    }

    return ESP_OK;
}

/**
 * @brief Destroy SPI video device
 *
 * @param index         SPI video device index
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_destroy_spi_video_device(uint8_t index)
{
    esp_err_t ret;
    const char *name;
    struct esp_video *video;
    struct spi_video *spi_video;

    if (index == 0) {
        name = ESP_VIDEO_SPI_DEVICE_0_NAME;
    } else if (index == 1) {
        name = ESP_VIDEO_SPI_DEVICE_1_NAME;
    } else {
        return ESP_ERR_INVALID_ARG;
    }

    video = esp_video_device_get_object(name);
    if (!video) {
        return ESP_ERR_NOT_FOUND;
    }

    spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    ret = esp_video_destroy(video);
    if (ret != ESP_OK) {
        return ret;
    }

    heap_caps_free(spi_video);

    return ESP_OK;
}

/**
 * @brief Get the sensor connected to SPI video device
 *
 * @param index         SPI video device index
 *
 * @return
 *      - Sensor pointer on success
 *      - NULL if failed
 */
esp_cam_sensor_device_t *esp_video_get_spi_video_device_sensor(uint8_t index)
{
    const char *name;
    struct esp_video *video;
    struct spi_video *spi_video;

    if (index == 0) {
        name = ESP_VIDEO_SPI_DEVICE_0_NAME;
    } else if (index == 1) {
        name = ESP_VIDEO_SPI_DEVICE_1_NAME;
    } else {
        return NULL;
    }

    video = esp_video_device_get_object(name);
    if (!video) {
        return NULL;
    }

    spi_video = VIDEO_PRIV_DATA(struct spi_video *, video);

    return spi_video->cam.sensor;
}
