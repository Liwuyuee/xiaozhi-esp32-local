| Supported Targets | ESP32-P4 | ESP32-S3 | ESP32-C3 | ESP32-C6 | ESP32-C61 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- | -------- | --------- | -------- |


# Capture Stream Example

(See the [README.md](../README.md) file in the upper level [examples](../) directory for more information about examples.)

This example demonstrates the following:

- How to initialize esp_video with specific parameters
- How to open video device and capture data stream from this device

## How to use example

### Configure the Project

Please refer to the example video initialization configuration [document](../common_components/example_video_common/README.md) for more details about the board-level configuration, including the camera sensor interface, GPIO pins, clock frequency, and so on.

Select and configure camera sensor based on development kit:

#### MIPI-CSI Development Kit

```
Component config  --->
    Espressif Camera Sensors Configurations  --->
        [ ] OV2640  --->
        [*] SC2336  ----
```

#### DVP Development Kit

```
Component config  --->
    Espressif Camera Sensors Configurations  --->
        [*] OV2640  --->
        [ ] SC2336  ----
```

#### SPI Development Kit

```
Component config  --->
    Espressif Camera Sensors Configurations  --->
        [*] BF3901  --->
            Auto detect BF3901  --->
                [*] Detect for SPI interface sensor
```

### Build and Flash
Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the [ESP-IDF Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32p4/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

Running this example, you will see the following log output on the serial monitor:

#### MIPI-CSI Development Kit

```
...
I (1075) main_task: Calling app_main()
I (1085) gpio: GPIO[31]| InputEn: 1| OutputEn: 1| OpenDrain: 1| Pullup: 1| Pulldown: 0| Intr:0 
I (1095) gpio: GPIO[34]| InputEn: 1| OutputEn: 1| OpenDrain: 1| Pullup: 1| Pulldown: 0| Intr:0 
I (1105) sc2336: Detected Camera sensor PID=0xcb3a with index 0
I (1175) example: version: 0.1.0
I (1175) example: driver:  MIPI-CSI
I (1175) example: card:    MIPI-CSI
I (1175) example: bus:     esp32p4:MIPI-CSI
I (1185) example: capabilities:
I (1185) example:       VIDEO_CAPTURE
I (1195) example:       READWRITE
I (1195) example:       STREAMING
I (1195) example: device capabilities:
I (1205) example:       VIDEO_CAPTURE
I (1205) example:       READWRITE
I (1215) example:       STREAMING
I (1215) example: Capture RAW8 BGGR format frames for 3 seconds:
I (4235) example:       width:  1280
I (4235) example:       height: 720
I (4235) example:       size:   921600
I (4245) example:       FPS:    30
I (4245) example: Capture RGB 5-6-5 format frames for 3 seconds:
I (7265) example:       width:  1280
I (7265) example:       height: 720
I (7265) example:       size:   1843200
I (7265) example:       FPS:    30
I (7275) example: Capture RGB 8-8-8 format frames for 3 seconds:
I (10295) example:      width:  1280
I (10295) example:      height: 720
I (10295) example:      size:   2764800
I (10295) example:      FPS:    30
I (10305) example: Capture YUV 4:2:0 format frames for 3 seconds:
I (13325) example:      width:  1280
I (13325) example:      height: 720
I (13325) example:      size:   1382400
I (13325) example:      FPS:    30
I (13325) example: Capture YVU 4:2:2 planar format frames for 3 seconds:
I (16355) example:      width:  1280
I (16355) example:      height: 720
I (16355) example:      size:   1843200
I (16355) example:      FPS:    30
I (16355) main_task: Returned from app_main()
...
```

#### DVP Development Kit

```
...
I (867) main_task: Calling app_main()
I (867) gpio: GPIO[32]| InputEn: 1| OutputEn: 1| OpenDrain: 1| Pullup: 1| Pulldown: 0| Intr:0 
I (867) gpio: GPIO[33]| InputEn: 1| OutputEn: 1| OpenDrain: 1| Pullup: 1| Pulldown: 0| Intr:0 
I (877) ov2640: Detected Camera sensor PID=0x26 with index 0
I (957) example: version: 0.3.0
I (957) example: driver:  DVP
I (957) example: card:    DVP
I (957) example: bus:     esp32p4:DVP
I (957) example: capabilities:
I (957) example:        VIDEO_CAPTURE
I (957) example:        READWRITE
I (957) example:        STREAMING
I (957) example: device capabilities:
I (957) example:        VIDEO_CAPTURE
I (957) example:        READWRITE
I (957) example:        STREAMING
I (957) example: Capture RGB 5-6-5 format frames for 3 seconds:
I (4367) example:       width:  640
I (4367) example:       height: 480
I (4367) example:       size:   614400
I (4367) example:       FPS:    6
I (4367) main_task: Returned from app_main()
...
```

#### SPI Development Kit

```
...
I (1483) main_task: Calling app_main()
I (1483) example_init_video: SPI camera sensor I2C port=1, scl_pin=8, sda_pin=7, freq=100000
I (1513) bf3901: Detected Camera sensor PID=0x3901
I (1573) example: version: 1.0.0
I (1573) example: driver:  SPI
I (1573) example: card:    SPI
I (1573) example: bus:     esp32p4:SPI
I (1573) example: capabilities:
I (1573) example:       VIDEO_CAPTURE
I (1573) example:       STREAMING
I (1583) example: device capabilities:
I (1583) example:       VIDEO_CAPTURE
I (1583) example:       STREAMING
I (1593) example: Capture YVU 4:2:2 planar format frames for 3 seconds:
I (4613) example:       width:  240
I (4613) example:       height: 320
I (4613) example:       size:   153600
I (4613) example:       FPS:    10
I (4613) main_task: Returned from app_main()
...
```
