# Espressif Video Component

Espressif video component provides a solution to call POSIX API plus Linux V4L2 commands to capture data streams from multi camera sensors, and transform stream data pixel format according to Linux V4L2 M2M codec device.

[![Component Registry](https://components.espressif.com/components/espressif/esp_video/badge.svg)](https://components.espressif.com/components/espressif/esp_video)

Now we have implementations based on:

- esp_cam_sensor
- esp_h264
- esp_ipa
- usb_host_uvc

## Supported SoCs and Interfaces

| SoC | MIPI-CSI Video Device | DVP Video Device | SPI Video Device | JPEG Video Device | H.264 Video Device | ISP Video Device | USB Video Device |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| ESP32-P4 | Y   | Y   | Y | Y | Y | Y | Y |
| ESP32-S3 | N/A | Y   | Y | N/A | N/A | N/A | Y |
| ESP32-C3 | N/A | N/A | Y | N/A | N/A | N/A | N/A |
| ESP32-C5 | N/A | N/A | Y | N/A | N/A | N/A | N/A |
| ESP32-C6 | N/A | N/A | Y | N/A | N/A | N/A | N/A |
| ESP32-C61 | N/A | N/A | Y | N/A | N/A | N/A | N/A |

## Video Device

| Hardware | Video Device | Type | Input Format | Output Format |
|:-:|:-:|:-:|:-|:-|
| MIPI-CSI | /dev/video0 | Capture | / | camera output pixel format or ISP output format(1) |
| DVP | /dev/video2 | Capture  | / | camera output pixel format |
| SPI0 | /dev/video3 | Capture  | / | camera output pixel format |
| SPI1(2) | /dev/video4 | Capture  | / | camera output pixel format |
| USB | /dev/video40 | Capture  | / | camera output pixel format |
| JPEG encode | /dev/video10 | M2M | RGB565: V4L2_PIX_FMT_RGB565<br> RGB888: V4L2_PIX_FMT_RGB24<br> YUV422: V4L2_PIX_FMT_YUV422P<br> Gray8: V4L2_PIX_FMT_GREY | JPEG: V4L2_PIX_FMT_JPEG |
| H.264 encode | /dev/video11 | M2M | YUV420: V4L2_PIX_FMT_YUV420 | H.264: V4L2_PIX_FMT_H264 |
| ISP | /dev/video20 | Meta | camera output pixel format  | Metadata: V4L2_META_FMT_ESP_ISP_STATS |

- (1): if camera output pixel format is RAW8, ISP can transform it to other pixel format: RGB565, RGB888, YUV420 and YUV422
- (2): select option `ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE` to enable the second SPI video device

## V4L2 Control Classes

### 1. V4L2_CTRL_CLASS_ESP_CAM_IOCTL

This video control class allows users to call the camera sensor (excluding motor) ioctl commands of `esp_cam_sensor` directly,
enabling them to utilize the camera sensor's special actions. The following code is to read the camera sensor ID:

```c
esp_cam_sensor_id_t chip_id;
struct v4l2_ext_controls controls;
struct v4l2_ext_control control[1];

controls.ctrl_class = V4L2_CTRL_CLASS_ESP_CAM_IOCTL;
controls.count      = 1;
controls.controls   = control;
control[0].id       = ESP_CAM_SENSOR_IOC_G_CHIP_ID;
control[0].p_u8     = (uint8_t *)&chip_id;
control[0].size     = sizeof(chip_id);
ioctl(fd, VIDIOC_G_EXT_CTRLS, &controls);
```

Please note that this class only supports "p_u8" and "size" fields of v4l2_ext_control, other fields are not supported.

## V4L2 Control IDs

| ID | Class | Type | Permission | Description |
|:-:|:-:|:-:|:-:|:-|
| V4L2_CID_VFLIP | V4L2_CID_USER_CLASS | Bool | Read/Write | Mirror the picture vertically. |
| V4L2_CID_HFLIP | V4L2_CID_USER_CLASS | Bool | Read/Write | Mirror the picture horizontally. |
| V4L2_CID_GAIN | V4L2_CID_USER_CLASS | Menu | Read/Write | Picrure pixel gain value. |
| V4L2_CID_EXPOSURE | V4L2_CID_USER_CLASS | Integer | Read/Write | Camera sensor exposure time, value unit depends on sensor |
| V4L2_CID_EXPOSURE_ABSOLUTE | V4L2_CID_CAMERA_CLASS | Integer | Read/Write | Camera sensor exposure time, value unit is 100us. |
| V4L2_CID_TEST_PATTERN | V4L2_CID_IMAGE_PROC_CLASS | Menu | Write | Camera sensor test pattern mode. |
| V4L2_CID_JPEG_COMPRESSION_QUALITY | V4L2_CID_JPEG_CLASS | Integer | Read/Write | JPEG encoded picture quality |
| V4L2_CID_JPEG_CHROMA_SUBSAMPLING | V4L2_CID_JPEG_CLASS | Menu | Read/Write | The chroma subsampling factors describe how each component of an input image is sampled. |
| V4L2_CID_MPEG_VIDEO_H264_I_PERIOD | V4L2_CID_CODEC_CLASS | Integer | Read/Write | Period between I-frames. |
| V4L2_CID_MPEG_VIDEO_BITRATE | V4L2_CID_CODEC_CLASS | Integer | Read/Write | Video bitrate in bits per second. |
| V4L2_CID_MPEG_VIDEO_H264_MIN_QP | V4L2_CID_CODEC_CLASS | Integer | Read/Write | Minimum quantization parameter for H264. |
| V4L2_CID_MPEG_VIDEO_H264_MAX_QP | V4L2_CID_CODEC_CLASS | Integer | Read/Write | Maximum quantization parameter for H264. |
| V4L2_CID_RED_BALANCE | V4L2_CID_USER_CLASS | Integer | Read/Write | Red chroma balance. |
| V4L2_CID_BLUE_BALANCE | V4L2_CID_USER_CLASS | Integer | Read/Write | Blue chroma balance. |
| V4L2_CID_USER_ESP_ISP_BF | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP bayer filter parameters. |
| V4L2_CID_USER_ESP_ISP_CCM | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP color correction matrix parameters. |
| V4L2_CID_USER_ESP_ISP_SHARPEN | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP sharpen parameters. |
| V4L2_CID_USER_ESP_ISP_GAMMA | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP GAMMA parameters. |
| V4L2_CID_USER_ESP_ISP_DEMOSAIC | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP demosaic parameters. |
| V4L2_CID_BRIGHTNESS | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | Picture brightness. |
| V4L2_CID_CONTRAST | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | Picture contrast. |
| V4L2_CID_SATURATION | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | Picture color saturation. |
| V4L2_CID_HUE | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | Picture hue. |
|  V4L2_CID_CAMERA_STATS | V4L2_CID_CAMERA_CLASS | Array of uint8_t | Read | Camera sensor statistics. |
| V4L2_CID_CAMERA_AE_LEVEL | V4L2_CID_CAMERA_CLASS | Integer | Read/Write | Camera sensor AE target level. |
| V4L2_CID_CAMERA_GROUP | V4L2_CID_CAMERA_CLASS | Array of uint8_t | Read/Write | Camera exposure and gain group parameters |
| V4L2_CID_USER_ESP_ISP_AWB | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP auto white balance statistics parameters |
| V4L2_CID_USER_ESP_ISP_LSC | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP lens shading correction parameters |
| V4L2_CID_USER_ESP_ISP_AF | V4L2_CID_USER_CLASS | Array of uint8_t | Read/Write | ISP auto focus(AF) parameters |