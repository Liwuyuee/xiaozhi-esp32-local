| Supported Targets | ESP32-P4 | ESP32-S3 | ESP32-C3 | ESP32-C6 | ESP32-C61 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- | -------- | --------- | -------- |

# Apply Custom Format In Video

(See the [README.md](../README.md) file in the upper level [examples](../) directory for more information about examples.)

This example demonstrates how to initialize the video system using a custom format description. There are three steps to implement this feature:

1. The camera sensor can only work properly when the developer provides the correct register configuration. Therefore, the correct initializer list needs to be provided:

   ```c
   const sc2336_reginfo_t init_reglist_custom_MIPI_2lane_800x800_raw8_30fps[] = {
       {0x0103, 0x01},
       {0x0100, 0x00}, // sleep en
       ...
   };
   ```

2. To use a custom register configuration, the corresponding description information needs to be provided so that the system can get the correct initialization parameters:

   ```c
   const esp_cam_sensor_format_t custom_format_info = {
       .name = "MIPI_2lane_24Minput_RAW8_800x800_30fps",
       .format = ESP_CAM_SENSOR_PIXFORMAT_RAW8,
       .port = ESP_CAM_SENSOR_MIPI_CSI,
       .xclk = 24000000,
       .width = 800,
       .height = 800,
       .regs = init_reglist_custom_MIPI_2lane_800x800_raw8_30fps,
       .regs_size = ARRAY_SIZE(init_reglist_custom_MIPI_2lane_800x800_raw8_30fps),
       .fps = 30,
       .isp_info = &custom_fmt_isp_info,
       .mipi_info = {
           .mipi_clk = 336000000,
           .lane_num = 2,
           .line_sync_en = false,
       },
       .reserved = NULL,
   };
   ```

   Note that if the camera sensor does not need to use the ISP module provided by the development board, then there is no need to provide ISP-related data.

3. The `ioctl()` is used to set a custom format for the sensor:

   ```c
   if (ioctl(fd, VIDIOC_S_SENSOR_FMT, &custom_format_info) != 0) {
   	ret = ESP_FAIL;
   	goto exit_0;
   }
   ```

​	Note that after executing the `VIDIOC_STREAMON` command, reconfiguring the output format is not allowed.

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
I (1627) main_task: Calling app_main()
I (1627) gpio: GPIO[22]| InputEn: 1| OutputEn: 1| OpenDrain: 1| Pullup: 1| Pulldown: 0| Intr:0 
I (1637) gpio: GPIO[23]| InputEn: 1| OutputEn: 1| OpenDrain: 1| Pullup: 1| Pulldown: 0| Intr:0 
I (1647) sc2336: Detected Camera sensor PID=0xcb3a
I (1727) example: version: 0.5.1
I (1727) example: driver:  MIPI-CSI
I (1727) example: card:    MIPI-CSI
I (1727) example: bus:     esp32p4:MIPI-CSI
I (1727) example: capabilities:
I (1737) example:       VIDEO_CAPTURE
I (1737) example:       STREAMING
I (1747) example: device capabilities:
I (1747) example:       VIDEO_CAPTURE
I (1747) example:       STREAMING
I (1827) example: Capture  format frames for 3 seconds:
I (4847) example:       width:  800
I (4847) example:       height: 800
I (4847) example:       size:   1280000
I (4857) example:       FPS:    30
I (4857) main_task: Returned from app_main()
```

#### SPI Development Kit

```
...
I (779) main_task: Calling app_main()
I (779) example_init_video: SPI camera sensor I2C port=1, scl_pin=5, sda_pin=4, freq=100000
I (799) bf3901: Detected Camera sensor PID=0x3901
I (859) example: version: 1.0.0
I (859) example: driver:  SPI
I (859) example: card:    SPI
I (859) example: bus:     esp32s3:SPI
I (859) example: capabilities:
I (869) example:        VIDEO_CAPTURE
I (869) example:        STREAMING
I (869) example: device capabilities:
I (869) example:        VIDEO_CAPTURE
I (879) example:        STREAMING
I (939) example: Capture RGB 5-6-5 format frames for 3 seconds:
I (3999) example:       width:  240
I (3999) example:       height: 320
I (3999) example:       size:   153600
I (3999) example:       FPS:    12
I (3999) main_task: Returned from app_main()
```
