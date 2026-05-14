| Supported Targets | ESP32-S2 | ESP32-S3 | ESP32-P4 |
| ----------------- | -------- | -------- | -------- |

# USB: UVC Class test application

## UVC driver

Target tests for USB Host UVC driver.

### Hardware Required

A USB camera and USB enabled ESP SoC is needed. Connect the camera to USB host port on ESP.
Format negotiation results are tested against values from Logitech C270 camera. These constants must be modified if different camera is used.

## Selecting the USB Component

To manually select which USB Component shall be used to build this test application, please refer to the following documentation page: [Manual USB component selection](../../../../../docs/host/usb_host_lib/usb_component_manual_selection.md).
