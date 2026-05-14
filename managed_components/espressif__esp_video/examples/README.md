# ESP-Video Examples

## Example Layout
* [capture_stream](https://github.com/espressif/esp-video-components/tree/master/esp_video/examples/capture_stream) demonstrates how to open video device and capture image data from the device.

* [image_storage](https://github.com/espressif/esp-video-components/tree/master/esp_video/examples/image_storage) demonstrates how to store image data and video stream data to an SD card or flash.

* [simple_video_server](https://github.com/espressif/esp-video-components/tree/master/esp_video/examples/simple_video_server) shows how to set up a local server and then preview and download images through the server.

* [uvc](https://github.com/espressif/esp-video-components/tree/master/esp_video/examples/uvc) demonstrates how to implement a USB camera through the USB peripheral and camera drivers.

* [video_custom_format](https://github.com/espressif/esp-video-components/tree/master/esp_video/examples/video_custom_format) demonstrates how to initialize the video system using a custom format description.

* [Video LCD Display](https://github.com/espressif/esp-iot-solution/tree/master/examples/camera/video_lcd_display) demonstrates how to display images from the camera on an LCD screen.

* [esp-webrtc-solution](https://github.com/espressif/esp-webrtc-solution) provides everything needed to build a WebRTC application.

* [ESP-WHO](https://github.com/espressif/esp-who) is an image processing development platform based on Espressif chips. It contains development examples that may be applied in practical applications.

* [USB_camera_examples](https://github.com/espressif/esp-iot-solution/tree/master/examples/usb/host) contains some examples of using USB cameras.

## Hardware Required
* A ESP32-P4 development board with camera interface (e.g., ESP32-P4-Function-EV-Board).
* A camera sensor that has been supported, see the [esp_cam_sensor](https://github.com/espressif/esp-video-components/tree/master/esp_cam_sensor).
* A USB Type-C cable for power supply and programming.

## Enable ISP Pipelines
For sensors that output data in RAW format, the ISP controller needs to be enabled to improve image quality.
```
Component config  --->
    Espressif Video Configuration  --->
        Enable ISP based Video Device  --->
            [*] Enable ISP Pipeline Controller
```