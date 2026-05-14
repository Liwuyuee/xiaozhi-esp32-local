## 2.3.1

- Added support for ESP32-H4

## 2.3.0

- Added `uvc_host_stream_format_get()` function that returns current stream's format
- Added `uvc_host_buf_info_get()` function for esp_video binding
- Added option to request default FPS by setting FPS = 0
- Fixed UVC driver re-installation
- Fixed abort on unexpected EoF flag in bulk transfers

## 2.2.0

- Added `uvc_host_stream_format_select()` function that allows change of format of an opened stream
- Fixed MPS limitation on FS targets from 600 to 596 bytes
- Fixed device opening procedure. Now the frame format is committed when the stream is started

## 2.1.0

- Added support for get frame list when device is inserted
- Added support for multiple cameras with USB hub

## 2.0.1

- Fixed negotiation for some non-conforming UVC devices (https://github.com/espressif/esp-idf/issues/9868)

## 2.0.0

- New version of the driver, native to Espressif's USB Host Library
- Removed libuvc dependency

## 1.0.4

- Support printf frame based descriptor

## 1.0.3

- Added support for ESP32-P4
- Bumped libuvc version to relax frame format negotiation
- Fixed crash on opening non-UVC devices
- Added `libuvc_get_usb_device_info` function

## 1.0.2

- Updated libuvc library to 0.0.7 https://github.com/libuvc/libuvc/tree/v0.0.7
- Added Software BoM information

## 1.0.1

- Fixed compatibility with IDF v4.4

## 1.0.0

- Initial version
