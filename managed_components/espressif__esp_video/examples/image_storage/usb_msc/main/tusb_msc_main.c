/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

/* DESCRIPTION:
 * This example contains code to make ESP32 based device recognizable by USB-hosts as a USB Mass Storage Device.
 * It either allows the embedded application i.e. example to access the partition or Host PC accesses the partition over USB MSC.
 * They can't be allowed to access the partition at the same time.
 * For different scenarios and behaviour, Refer to README of this example.
 */

#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "sdkconfig.h"
#include "esp_check.h"
#include "driver/gpio.h"
#include "tinyusb.h"
#include "tusb_msc_storage.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "example_video_common.h"
#if SOC_SDMMC_IO_POWER_EXTERNAL
#include "sd_pwr_ctrl_by_on_chip_ldo.h"
#endif

#ifdef CONFIG_EXAMPLE_STORAGE_MEDIA_SDMMC
#include "diskio_impl.h"
#include "diskio_sdmmc.h"
#if CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_INTERNAL_IO
#include "sd_pwr_ctrl_by_on_chip_ldo.h"
#endif /* CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_INTERNAL_IO */
#endif
#if CONFIG_EXAMPLE_STORAGE_MEDIA_SPIFLASH
#include "esp_partition.h"
#endif

#if CONFIG_EXAMPLE_FORMAT_MJPEG
#define ENCODE_DEV_PATH        ESP_VIDEO_JPEG_DEVICE_NAME
#define STORAGE_IMAGE_FORMAT   V4L2_PIX_FMT_JPEG
#elif CONFIG_EXAMPLE_FORMAT_H264
#if CONFIG_EXAMPLE_H264_MAX_QP <= CONFIG_EXAMPLE_H264_MIN_QP
#error "CONFIG_EXAMPLE_H264_MAX_QP should larger than CONFIG_EXAMPLE_H264_MIN_QP"
#endif

#define ENCODE_DEV_PATH            ESP_VIDEO_H264_DEVICE_NAME
#define STORAGE_IMAGE_FORMAT       V4L2_PIX_FMT_H264
#define CAPTURE_SECONDS            3
#elif CONFIG_EXAMPLE_FORMAT_NON_ENCODE
#define STORAGE_IMAGE_FORMAT       V4L2_PIX_FMT_YUV422P
#endif

#define VIDEO_BUFFER_COUNT         2
#define VIDEO_ENCODER_BUFFER_COUNT 1
#define SKIP_STARTUP_FRAME_COUNT   2
#define BASE_PATH "/data" /* base path to mount the partition */

/**
 * @brief The format of the stored image data
 */
typedef enum {
    MSC_IMG_FORMAT_JPEG,            /*!< JPEG format */
    MSC_IMG_FORMAT_H264,            /*!< H264 format */
    MSC_IMG_FORMAT_NON_ENCODE,      /*!< Non-encoded format */
} usb_msc_image_format_t;

/**
 * @brief The framebuffer type
 */
typedef struct usb_msc_fb {
    uint8_t *buf;
    uint8_t buf_index;
    size_t buf_bytesused;
    usb_msc_image_format_t fmt; /*!< Data format of stored images */
    size_t width;               /*!< Width of the image frame in pixels */
    size_t height;              /*!< Height of the image frame in pixels */
    struct timeval timestamp;   /*!< Timestamp since boot of the frame */
} usb_msc_fb_t;

typedef struct usb_msc_storage {
    int cap_fd;
    uint32_t format;
    uint8_t *cap_buffer[VIDEO_BUFFER_COUNT];
#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    int m2m_fd;
    uint8_t *m2m_cap_buffer;
#endif
    usb_msc_fb_t um_fb;
    uint64_t storage_max_capacity;
} usb_msc_storage_t;

/* TinyUSB descriptors
   ********************************************************************* */
#define EPNUM_MSC       1
#define TUSB_DESC_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_MSC_DESC_LEN)

enum {
    ITF_NUM_MSC = 0,
    ITF_NUM_TOTAL
};

enum {
    EDPT_CTRL_OUT = 0x00,
    EDPT_CTRL_IN  = 0x80,

    EDPT_MSC_OUT  = 0x01,
    EDPT_MSC_IN   = 0x81,
};

static const char *TAG = "example_main";
static usb_msc_storage_t msc_ctrl;
static tusb_desc_device_t descriptor_config = {
    .bLength = sizeof(descriptor_config),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = TUSB_CLASS_MISC,
    .bDeviceSubClass = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor = 0x303A, // This is Espressif VID. This needs to be changed according to Users / Customers
    .idProduct = 0x4002,
    .bcdDevice = 0x100,
    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,
    .bNumConfigurations = 0x01
};

static uint8_t const msc_fs_configuration_desc[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, TUSB_DESC_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // Interface number, string index, EP Out & EP In address, EP size
    TUD_MSC_DESCRIPTOR(ITF_NUM_MSC, 0, EDPT_MSC_OUT, EDPT_MSC_IN, 64),
};

#if (TUD_OPT_HIGH_SPEED)
static const tusb_desc_device_qualifier_t device_qualifier = {
    .bLength = sizeof(tusb_desc_device_qualifier_t),
    .bDescriptorType = TUSB_DESC_DEVICE_QUALIFIER,
    .bcdUSB = 0x0200,
    .bDeviceClass = TUSB_CLASS_MISC,
    .bDeviceSubClass = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
    .bNumConfigurations = 0x01,
    .bReserved = 0
};

static uint8_t const msc_hs_configuration_desc[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, TUSB_DESC_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // Interface number, string index, EP Out & EP In address, EP size
    TUD_MSC_DESCRIPTOR(ITF_NUM_MSC, 0, EDPT_MSC_OUT, EDPT_MSC_IN, 512),
};
#endif // TUD_OPT_HIGH_SPEED

static char const *string_desc_arr[] = {
    (const char[]) { 0x09, 0x04 },  // 0: is supported language is English (0x0409)
    "TinyUSB",                      // 1: Manufacturer
    "TinyUSB Device",               // 2: Product
    "123456",                       // 3: Serials
    "Example MSC",                  // 4. MSC
};
/*********************************************************************** TinyUSB descriptors*/

static esp_err_t init_capture_video(usb_msc_storage_t *umsc)
{
    int fd;

    fd = open(EXAMPLE_CAM_DEV_PATH, O_RDONLY);
    assert(fd >= 0);

    umsc->cap_fd = fd;
    umsc->format = STORAGE_IMAGE_FORMAT;

    return 0;
}

#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
static esp_err_t set_codec_control(int fd, uint32_t ctrl_class, uint32_t id, int32_t value)
{
    struct v4l2_ext_controls controls;
    struct v4l2_ext_control control[1];

    controls.ctrl_class = ctrl_class;
    controls.count = 1;
    controls.controls = control;
    control[0].id = id;
    control[0].value = value;

    if (ioctl(fd, VIDIOC_S_EXT_CTRLS, &controls) != 0) {
        ESP_LOGW(TAG, "failed to set control: %" PRIu32, id);
        return ESP_FAIL;
    }
    return ESP_OK;
}

static esp_err_t init_codec_video(usb_msc_storage_t *umsc)
{
    int fd;
    const char *devpath = ENCODE_DEV_PATH;

    fd = open(devpath, O_RDONLY);
    assert(fd >= 0);

#if CONFIG_EXAMPLE_FORMAT_MJPEG
    set_codec_control(fd, V4L2_CID_JPEG_CLASS, V4L2_CID_JPEG_COMPRESSION_QUALITY, CONFIG_EXAMPLE_JPEG_COMPRESSION_QUALITY);
#elif CONFIG_EXAMPLE_FORMAT_H264
    set_codec_control(fd, V4L2_CID_CODEC_CLASS, V4L2_CID_MPEG_VIDEO_H264_I_PERIOD, CONFIG_EXAMPLE_H264_I_PERIOD);
    set_codec_control(fd, V4L2_CID_CODEC_CLASS, V4L2_CID_MPEG_VIDEO_BITRATE, CONFIG_EXAMPLE_H264_BITRATE);
    set_codec_control(fd, V4L2_CID_CODEC_CLASS, V4L2_CID_MPEG_VIDEO_H264_MIN_QP, CONFIG_EXAMPLE_H264_MIN_QP);
    set_codec_control(fd, V4L2_CID_CODEC_CLASS, V4L2_CID_MPEG_VIDEO_H264_MAX_QP, CONFIG_EXAMPLE_H264_MAX_QP);
#endif

    umsc->m2m_fd = fd;

    return 0;
}
#endif

static esp_err_t example_write_file(FILE *f, const uint8_t *data, size_t len)
{
    size_t written;

    do {
        written = fwrite(data, 1, len, f);
        len -= written;
        data += written;
    } while ( written && len );
    fflush(f);

    return ESP_OK;
}

/* mount the partition and show all the files in BASE_PATH */
static void example_mount_msc(void)
{
    ESP_LOGI(TAG, "Mount storage...");
    ESP_ERROR_CHECK(tinyusb_msc_storage_mount(BASE_PATH));

    /* List all the files in this directory */
    ESP_LOGI(TAG, "\nls command output:");
    struct dirent *d;
    DIR *dh = opendir(BASE_PATH);
    if (!dh) {
        if (errno == ENOENT) {
            /* If the directory is not found */
            ESP_LOGE(TAG, "Directory doesn't exist %s", BASE_PATH);
        } else {
            /* If the directory is not readable then throw error and exit */
            ESP_LOGE(TAG, "Unable to read directory %s", BASE_PATH);
        }
        return;
    }
    /* While the next entry is not readable we will print directory files */
    while ((d = readdir(dh)) != NULL) {
        printf("%s\n", d->d_name);
    }
    return;
}

static esp_err_t example_video_start(usb_msc_storage_t *umsc)
{
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    struct v4l2_buffer buf;
    struct v4l2_format format;
    struct v4l2_requestbuffers req;
    struct v4l2_format init_format;
    uint32_t capture_fmt = 0;
    uint32_t width, height;

    ESP_LOGD(TAG, "Video start");

    memset(&init_format, 0, sizeof(struct v4l2_format));
    init_format.type = type;
    if (ioctl(umsc->cap_fd, VIDIOC_G_FMT, &init_format) != 0) {
        ESP_LOGE(TAG, "failed to get format");
        return ESP_FAIL;
    }
    /* Use default length and width, refer to the sensor format options in menuconfig. */
    width = init_format.fmt.pix.width;
    height = init_format.fmt.pix.height;

    if (umsc->format == V4L2_PIX_FMT_JPEG) {
        int fmt_index = 0;
        const uint32_t jpeg_input_formats[] = {
            V4L2_PIX_FMT_RGB565,
            V4L2_PIX_FMT_YUV422P,
            V4L2_PIX_FMT_RGB24,
            V4L2_PIX_FMT_GREY
        };
        int jpeg_input_formats_num = sizeof(jpeg_input_formats) / sizeof(jpeg_input_formats[0]);

        while (!capture_fmt) {
            struct v4l2_fmtdesc fmtdesc = {
                .index = fmt_index++,
                .type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
            };

            if (ioctl(umsc->cap_fd, VIDIOC_ENUM_FMT, &fmtdesc) != 0) {
                break;
            }

            for (int i = 0; i < jpeg_input_formats_num; i++) {
                if (jpeg_input_formats[i] == fmtdesc.pixelformat) {
                    capture_fmt = jpeg_input_formats[i];
                    break;
                }
            }
        }

        if (!capture_fmt) {
            ESP_LOGI(TAG, "The camera sensor output pixel format is not supported by JPEG encoder");
            return ESP_ERR_NOT_SUPPORTED;
        }
        umsc->um_fb.fmt = MSC_IMG_FORMAT_JPEG;
    } else if (umsc->format == V4L2_PIX_FMT_H264) {
        /* Todo, fix input format when h264 encoder supports other formats */
        capture_fmt = V4L2_PIX_FMT_YUV420;
        umsc->um_fb.fmt = MSC_IMG_FORMAT_H264;
    } else {
        /* Non-encode format */
        capture_fmt = umsc->format;
        umsc->um_fb.fmt = MSC_IMG_FORMAT_NON_ENCODE;
    }

    /* Configure camera interface capture stream */

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height;
    format.fmt.pix.pixelformat = capture_fmt;
    ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_S_FMT, &format));

    memset(&req, 0, sizeof(req));
    req.count  = VIDEO_BUFFER_COUNT;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_REQBUFS, &req));

    for (int i = 0; i < VIDEO_BUFFER_COUNT; i++) {
        memset(&buf, 0, sizeof(buf));
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;
        ESP_ERROR_CHECK (ioctl(umsc->cap_fd, VIDIOC_QUERYBUF, &buf));

        umsc->cap_buffer[i] = (uint8_t *)mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                                              MAP_SHARED, umsc->cap_fd, buf.m.offset);
        assert(umsc->cap_buffer[i]);

        ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_QBUF, &buf));
    }

#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    /* Configure codec output stream */

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height;
    format.fmt.pix.pixelformat = capture_fmt;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_S_FMT, &format));

    memset(&req, 0, sizeof(req));
    req.count  = VIDEO_ENCODER_BUFFER_COUNT;
    req.type   = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    req.memory = V4L2_MEMORY_USERPTR;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_REQBUFS, &req));

    /* Configure codec capture stream */

    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height;
    format.fmt.pix.pixelformat = umsc->format;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_S_FMT, &format));

    memset(&req, 0, sizeof(req));
    req.count  = 1;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_REQBUFS, &req));

    memset(&buf, 0, sizeof(buf));
    buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory      = V4L2_MEMORY_MMAP;
    buf.index       = 0;
    ESP_ERROR_CHECK (ioctl(umsc->m2m_fd, VIDIOC_QUERYBUF, &buf));

    umsc->m2m_cap_buffer = (uint8_t *)mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                                           MAP_SHARED, umsc->m2m_fd, buf.m.offset);
    assert(umsc->m2m_cap_buffer);

    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_QBUF, &buf));

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_STREAMON, &type));
    type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_STREAMON, &type));
#endif
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_STREAMON, &type));

    /* Skip the first few frames of the image to get a stable image. */
    for (int i = 0; i < SKIP_STARTUP_FRAME_COUNT; i++) {
        memset(&buf, 0, sizeof(buf));
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_DQBUF, &buf));
        ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_QBUF, &buf));
    }

    /* Init frame buffer's basic info. */
    umsc->um_fb.width = width;
    umsc->um_fb.height = height;

    return ESP_OK;
}

static void example_video_stop(usb_msc_storage_t *umsc)
{
    int type;

    ESP_LOGD(TAG, "Video stop");

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(umsc->cap_fd, VIDIOC_STREAMOFF, &type);
#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    ioctl(umsc->m2m_fd, VIDIOC_STREAMOFF, &type);
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(umsc->m2m_fd, VIDIOC_STREAMOFF, &type);
#endif
}

static usb_msc_fb_t *example_video_fb_get(usb_msc_storage_t *umsc)
{
    struct v4l2_buffer cap_buf;
#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    struct v4l2_buffer m2m_out_buf;
    struct v4l2_buffer m2m_cap_buf;
#endif
    int64_t us;

    ESP_LOGD(TAG, "Video get");

    /*
     * V4L2 works in either “capture” (frames being read off a device e.g. camera or webcam) or “output” (frames being sent to a device e.g. a graphics card)
     * M2M combines “capture” and “output” into a single mode which allows arbitrary transformations of frames.
     * The data flow can be described as follows:
     *
     *****************               ********       *************
     * Capture Device* ------------> * V4L2 *-----> * Program   *
     * (e.g. camera) *               *      *       *           *
     *****************               ********       *************
     *
     ************************        ********       *************
     * Output Device        * <----- * V4L2 *-----> * Program   *
     * (e.g. graphics card) *        *      *       *           *
     ************************        ********       *************
     *
     **********************   RAW    ********       *************
     * Encoder            * <------- * V4L2 * <---- * Program   *
     * (e.g. jpeg, h.264) * -------> * M2M  * ----> *           *
     **********************  h264    ********       *************
     *
     *The process of obtaining the encoded data can be briefly described as follows:

     **********  DQBUF
     * cap_fd * -------------> Dequeue a filled (capturing) original image data buffer from the cap_fd’s receive queue.
     **********                                                                     |
     *                                                                              |
     *                                                                              v
     *                                                                      QBUF **********
     * Enqueue the original image buf to m2m_fd output buffer queue <----------- * m2m_fd *
     * |                                                                         **********
     * |
     * v
     **********  DQBUF
     * m2m_fd * -------> Dequeue a filled (capturing) buffer to get the encoded image data from m2m_fd's outgoing queue.
     **********
    */
    memset(&cap_buf, 0, sizeof(cap_buf));
    cap_buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    cap_buf.memory = V4L2_MEMORY_MMAP;
    ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_DQBUF, &cap_buf));
#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    memset(&m2m_out_buf, 0, sizeof(m2m_out_buf));
    m2m_out_buf.index  = 0;
    m2m_out_buf.type   = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    m2m_out_buf.memory = V4L2_MEMORY_USERPTR;
    m2m_out_buf.m.userptr = (unsigned long)umsc->cap_buffer[cap_buf.index];
    m2m_out_buf.length = cap_buf.bytesused;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_QBUF, &m2m_out_buf));

    memset(&m2m_cap_buf, 0, sizeof(m2m_cap_buf));
    m2m_cap_buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    m2m_cap_buf.memory = V4L2_MEMORY_MMAP;
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_DQBUF, &m2m_cap_buf));

    ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_QBUF, &cap_buf));
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_DQBUF, &m2m_out_buf));
    /* Notes: If multiple m2m buffers are used, 'm2m_cap_buf.index' can be used to get the actual address of buf.
    Here, only one m2m buffer is used, so the address of the m2m buffer is directly referenced.*/
    umsc->um_fb.buf = umsc->m2m_cap_buffer;
    umsc->um_fb.buf_bytesused = m2m_cap_buf.bytesused;
    umsc->um_fb.buf_index = m2m_cap_buf.index;
#else
    umsc->um_fb.buf = umsc->cap_buffer[cap_buf.index];
    umsc->um_fb.buf_bytesused = cap_buf.bytesused;
    umsc->um_fb.buf_index = cap_buf.index;
#endif
    us = esp_timer_get_time();
    umsc->um_fb.timestamp.tv_sec = us / 1000000UL;;
    umsc->um_fb.timestamp.tv_usec = us % 1000000UL;

    return &umsc->um_fb;
}

static void example_video_fb_return(usb_msc_storage_t *umsc)
{
    struct v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.index  = umsc->um_fb.buf_index;
    buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    ESP_LOGD(TAG, "Video return");
#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    ESP_ERROR_CHECK(ioctl(umsc->m2m_fd, VIDIOC_QBUF, &buf));
#else
    ESP_ERROR_CHECK(ioctl(umsc->cap_fd, VIDIOC_QBUF, &buf));
#endif
}

static esp_err_t store_image_to_fat(usb_msc_storage_t *umsc)
{
    if (tinyusb_msc_storage_in_use_by_usb_host()) {
        ESP_LOGE(TAG, "storage exposed over USB. Application can't write to storage.");
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, "write to storage:");
    char string[32] = {0};
    char file_name_str[48] = {0};
    int current_time_us;
    struct timeval current_time;
    usb_msc_fb_t *image_fb = NULL;
    FILE *f = NULL;
    struct stat st;

    ESP_ERROR_CHECK(example_video_start(umsc));
    current_time_us = esp_timer_get_time();
    current_time.tv_sec = current_time_us / 1000000UL;;
    current_time.tv_usec = current_time_us % 1000000UL;
    /* Generate a file name based on the current time */
    itoa((int)current_time.tv_sec, string, 10);
    strcat(strcpy(file_name_str, BASE_PATH"/"), string);
    memset(string, 0x0, sizeof(string));
    itoa((int)current_time.tv_usec, string, 10);
    strcat(file_name_str, "_");
    strcat(file_name_str, string);
#if CONFIG_EXAMPLE_FORMAT_MJPEG
    strcat(file_name_str, ".jpg");
#elif CONFIG_EXAMPLE_FORMAT_H264
    strcat(file_name_str, "_h264.bin");
#elif CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    strcat(file_name_str, ".bin");
#endif

    ESP_LOGI(TAG, "file name:%s", file_name_str);

    if (stat(file_name_str, &st) == 0) {
        /* Delete it if it exists */
        ESP_LOGW(TAG, "Delete original file %s", file_name_str);
        unlink(file_name_str);
    }

#if (CONFIG_EXAMPLE_FORMAT_MJPEG || CONFIG_EXAMPLE_FORMAT_NON_ENCODE)
    f = fopen(file_name_str, "wb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }
    image_fb = example_video_fb_get(umsc);
    if (image_fb->buf_bytesused < umsc->storage_max_capacity) {
        example_write_file(f, image_fb->buf, image_fb->buf_bytesused);
    } else {
        ESP_LOGE(TAG, "Image size is too large, increase storage space");
    }

    example_video_fb_return(umsc);
    fclose(f);
#elif CONFIG_EXAMPLE_FORMAT_H264
    f = fopen(file_name_str, "ab");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }
    int64_t start_time_us = esp_timer_get_time();
    uint32_t bytes_written = 0;
    while (esp_timer_get_time() - start_time_us < (CAPTURE_SECONDS * 1000 * 1000)) {
        image_fb = example_video_fb_get(umsc);
        if ((bytes_written += image_fb->buf_bytesused) < umsc->storage_max_capacity) {
            example_write_file(f, image_fb->buf, image_fb->buf_bytesused);
        } else {
            ESP_LOGE(TAG, "Image size is too large, increase storage space");
        }

        example_video_fb_return(umsc);
    }
    fclose(f);
#endif
    ESP_LOGI(TAG, "File written");
    example_video_stop(umsc);

    return ESP_OK;
}

/* callback that is delivered when storage is mounted/unmounted by application. */
static void storage_mount_changed_cb(tinyusb_msc_event_t *event)
{
    ESP_LOGI(TAG, "Storage mounted to application: %s", event->mount_changed_data.is_mounted ? "Yes" : "No");
}

#ifdef CONFIG_EXAMPLE_STORAGE_MEDIA_SPIFLASH
static esp_err_t storage_init_spiflash(wl_handle_t *wl_handle)
{
    ESP_LOGI(TAG, "Initializing wear levelling");

    const esp_partition_t *data_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, NULL);
    if (data_partition == NULL) {
        ESP_LOGE(TAG, "Failed to find FATFS partition. Check the partition table.");
        return ESP_ERR_NOT_FOUND;
    }

    return wl_mount(data_partition, wl_handle);
}
#else  /* CONFIG_EXAMPLE_STORAGE_MEDIA_SPIFLASH */
static esp_err_t storage_init_sdmmc(sdmmc_card_t **card)
{
    esp_err_t ret = ESP_OK;
    bool host_init = false;
    sdmmc_card_t *sd_card;

    ESP_LOGI(TAG, "Initializing SDCard");

    /* By default, SD card frequency is initialized to SDMMC_FREQ_DEFAULT (20MHz)
     * For setting a specific frequency, use host.max_freq_khz (range 400kHz - 40MHz for SDMMC)
     * Example: for fixed frequency of 10MHz, use host.max_freq_khz = 10000;*/
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    /* For SoCs where the SD power can be supplied both via an internal or external (e.g. on-board LDO) power supply.
     * When using specific IO pins (which can be used for ultra high-speed SDMMC) to connect to the SD card
     * and the internal LDO power supply, we need to initialize the power supply first.*/
#if CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_INTERNAL_IO
    sd_pwr_ctrl_ldo_config_t ldo_config = {
        .ldo_chan_id = CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_IO_ID,
    };
    sd_pwr_ctrl_handle_t pwr_ctrl_handle = NULL;

    ret = sd_pwr_ctrl_new_on_chip_ldo(&ldo_config, &pwr_ctrl_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create a new on-chip LDO power control driver");
        return ret;
    }
    host.pwr_ctrl_handle = pwr_ctrl_handle;
#endif

    /* This initializes the slot without card detect (CD) and write protect (WP) signals.
     * Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.*/
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    /* For SD Card, set bus width to use */
#ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
    slot_config.width = 4;
#else
    slot_config.width = 1;
#endif  /* CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4 */

    /* On chips where the GPIOs used for SD card can be configured, set the user defined values */
#ifdef CONFIG_SOC_SDMMC_USE_GPIO_MATRIX
    slot_config.clk = CONFIG_EXAMPLE_PIN_CLK;
    slot_config.cmd = CONFIG_EXAMPLE_PIN_CMD;
    slot_config.d0 = CONFIG_EXAMPLE_PIN_D0;
#ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
    slot_config.d1 = CONFIG_EXAMPLE_PIN_D1;
    slot_config.d2 = CONFIG_EXAMPLE_PIN_D2;
    slot_config.d3 = CONFIG_EXAMPLE_PIN_D3;
#endif  /* CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4 */

#endif  /* CONFIG_SOC_SDMMC_USE_GPIO_MATRIX */

    /* Enable internal pullups on enabled pins. The internal pullups
     * are insufficient however, please make sure 10k external pullups are
     * connected on the bus. This is for debug / example purpose only.*/
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    /* not using ff_memalloc here, as allocation in internal RAM is preferred */
    sd_card = (sdmmc_card_t *)malloc(sizeof(sdmmc_card_t));
    ESP_GOTO_ON_FALSE(sd_card, ESP_ERR_NO_MEM, clean, TAG, "could not allocate new sdmmc_card_t");

    ESP_GOTO_ON_ERROR((*host.init)(), clean, TAG, "Host Config Init fail");
    host_init = true;

    ESP_GOTO_ON_ERROR(sdmmc_host_init_slot(host.slot, (const sdmmc_slot_config_t *) &slot_config),
                      clean, TAG, "Host init slot fail");

    while (sdmmc_card_init(&host, sd_card)) {
        ESP_LOGE(TAG, "The detection pin of the slot is disconnected(Insert uSD card). Retrying...");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    /* Card has been initialized, print its properties */
    sdmmc_card_print_info(stdout, sd_card);
    *card = sd_card;

    return ESP_OK;

clean:
    if (host_init) {
        if (host.flags & SDMMC_HOST_FLAG_DEINIT_ARG) {
            host.deinit_p(host.slot);
        } else {
            (*host.deinit)();
        }
    }
    if (sd_card) {
        free(sd_card);
        sd_card = NULL;
    }
#if CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_INTERNAL_IO
    /* We don't need to duplicate error here as all error messages are handled via sd_pwr_* call */
    sd_pwr_ctrl_del_on_chip_ldo(pwr_ctrl_handle);
#endif /* CONFIG_EXAMPLE_SD_PWR_CTRL_LDO_INTERNAL_IO */
    return ret;
}
#endif  /* CONFIG_EXAMPLE_STORAGE_MEDIA_SPIFLASH */

static esp_err_t init_usb_msc(usb_msc_storage_t *umsc)
{
    uint32_t sec_count;
    uint32_t sec_size;
    ESP_LOGI(TAG, "Initializing storage...");

#ifdef CONFIG_EXAMPLE_STORAGE_MEDIA_SPIFLASH
    static wl_handle_t wl_handle = WL_INVALID_HANDLE;
    ESP_ERROR_CHECK(storage_init_spiflash(&wl_handle));

    const tinyusb_msc_spiflash_config_t config_spi = {
        .wl_handle = wl_handle,
        .callback_mount_changed = storage_mount_changed_cb,  /* First way to register the callback. This is while initializing the storage. */
        .mount_config.max_files = 5,
    };
    ESP_ERROR_CHECK(tinyusb_msc_storage_init_spiflash(&config_spi));
    ESP_ERROR_CHECK(tinyusb_msc_register_callback(TINYUSB_MSC_EVENT_MOUNT_CHANGED, storage_mount_changed_cb)); /* Other way to register the callback i.e. registering using separate API. If the callback had been already registered, it will be overwritten. */
#else /* CONFIG_EXAMPLE_STORAGE_MEDIA_SPIFLASH */
    static sdmmc_card_t *card = NULL;
    ESP_ERROR_CHECK(storage_init_sdmmc(&card));

    const tinyusb_msc_sdmmc_config_t config_sdmmc = {
        .card = card,
        .callback_mount_changed = storage_mount_changed_cb,  /* First way to register the callback. This is while initializing the storage. */
        .mount_config.max_files = 5,
    };
    ESP_ERROR_CHECK(tinyusb_msc_storage_init_sdmmc(&config_sdmmc));
    ESP_ERROR_CHECK(tinyusb_msc_register_callback(TINYUSB_MSC_EVENT_MOUNT_CHANGED, storage_mount_changed_cb)); /* Other way to register the callback i.e. registering using separate API. If the callback had been already registered, it will be overwritten. */
#endif  /* CONFIG_EXAMPLE_STORAGE_MEDIA_SPIFLASH */

    /* Mounted in the app by default */
    example_mount_msc();

    ESP_LOGI(TAG, "USB MSC initialization");
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = &descriptor_config,
        .string_descriptor = string_desc_arr,
        .string_descriptor_count = sizeof(string_desc_arr) / sizeof(string_desc_arr[0]),
        .external_phy = false,
#if (TUD_OPT_HIGH_SPEED)
        .fs_configuration_descriptor = msc_fs_configuration_desc,
        .hs_configuration_descriptor = msc_hs_configuration_desc,
        .qualifier_descriptor = &device_qualifier,
#else
        .configuration_descriptor = msc_fs_configuration_desc,
#endif /* TUD_OPT_HIGH_SPEED */
    };
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
    sec_count = tinyusb_msc_storage_get_sector_count();
    sec_size = tinyusb_msc_storage_get_sector_size();
    umsc->storage_max_capacity = ((uint64_t) sec_count) * sec_size;
    ESP_LOGI(TAG, "USB MSC initialization DONE, storage capacity %lluKB\n", umsc->storage_max_capacity / 1024);
    return ESP_OK;
}

void app_main(void)
{
    ESP_ERROR_CHECK(example_video_init());
    ESP_ERROR_CHECK(init_capture_video(&msc_ctrl));
#if !CONFIG_EXAMPLE_FORMAT_NON_ENCODE
    ESP_ERROR_CHECK(init_codec_video(&msc_ctrl));
#endif
    ESP_ERROR_CHECK(init_usb_msc(&msc_ctrl));
    ESP_ERROR_CHECK(store_image_to_fat(&msc_ctrl));
}
