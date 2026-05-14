| Supported Targets | ESP32-P4 |
| ----------------- | -------- |

# Image storage on the SD card example

This sample demonstrates how to store camera images to an SD card, then export the data from the SD card to the computer and preview the images.

The FatFS file system formatted SD card can be connected to the host through SPI interface or SDMMC interface.This example uses SDMMC peripheral to communicate with SD card. 

(More information about SD card drivers can be found [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/sdmmc.html).)

__WARNING:__ This example can potentially delete all data from your SD card (when formatting is enabled). Back up your data first before proceeding.

## How to use example

### Hardware Required

* A development board with MIPI-CSI or DVP interface.
* A camera sensor that is already supported by the [esp_cam_sensor](https://github.com/espressif/esp-video-components/tree/master/esp_cam_sensor) component.

* A USB Type-C cable for power supply and programming.
* A USB SD card reader.

### Software Required

* `VLC media player` APP for PC to preview H.264 stream.

### Configure the Project

Please refer to the example video initialization configuration [document](../common_components/example_video_common/README.md) for more details about the board-level configuration, including the camera sensor interface, GPIO pins, clock frequency, and so on.

Select and configure camera sensor based on development kit:

#### MIPI-CSI Development Kit

```  
Component config  --->
    Espressif Camera Sensors Configurations  --->
        [*] SC2336  ---->
            Default format select for MIPI (RAW8 1280x720 30fps, MIPI 2lane 24M input)  --->
                (X) RAW8 1280x720 30fps, MIPI 2lane 24M input
```

#### DVP Development Kit

```
Component config  --->
    Espressif Camera Sensors Configurations  --->
        [*] OV2640  --->
            Default format select (RGB565 640x480 6fps, DVP 8bit 20M input)  --->
                (X) RGB565 640x480 6fps, DVP 8bit 20M input
```

#### JPEG Configuration

```
Example Configuration  --->
	Example Video Configuration  --->
		Image Encoding Format  --->
			(X) MJPEG
```

#### H.264 Configuration

```
Example Configuration  --->
	Example Video Configuration  --->
		Image Encoding Format  --->
			(X) H264
```

***Please note that the OV2640 doesn't support H.264 format, it only supports the JPEG format***.

#### SD/MMC Configuration

```
Example Configuration  --->
	Example SD/MMC Configuration --->
        (44) CMD GPIO number
        (43) CLK GPIO number
        (39) D0 GPIO number
```

Note: For custom development boards, please update the `I2C pins` and `SD card pins` configuration in the `Example Configuration` menu.

#### Enable ISP Pipeline

For sensors that output data in RAW format, the ISP controller needs to be enabled to improve image quality.

```
Component config  --->
	Espressif Video Configuration  --->
		Enable ISP based Video Device  --->
			[*] Enable ISP Pipeline Controller
```

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py set-target esp32p4

idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the [ESP-IDF Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32p4/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

Running this example, you will see the following log output on the serial monitor:

#### JPEG
<details><summary>Example log output:</summary>

```
...
I (1538) main_task: Calling app_main()
I (1538) sc2336: Detected Camera sensor PID=0xcb3a
I (1608) example: version: 0.8.0
I (1608) example: driver:  MIPI-CSI
I (1618) example: card:    MIPI-CSI
I (1618) example: bus:     esp32p4:MIPI-CSI
I (1618) example: capabilities:
I (1618) example:       VIDEO_CAPTURE
I (1618) example:       STREAMING
I (1628) example: device capabilities:
I (1628) example:       VIDEO_CAPTURE
I (1628) example:       STREAMING
I (1638) example: version: 0.8.0
I (1638) example: driver:  JPEG
I (1638) example: card:    JPEG
I (1638) example: bus:     esp32p4:JPEG
I (1648) example: capabilities:
I (1648) example:       STREAMING
I (1648) example: device capabilities:
I (1658) example:       STREAMING
I (1658) example: Initializing SD card
I (1658) example: Using SDMMC peripheral
I (1668) example: Mounting filesystem
I (1668) gpio: GPIO[43]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1678) gpio: GPIO[44]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1688) gpio: GPIO[39]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1858) example: Filesystem mounted
Name: SC16G
Type: SDHC
Speed: 20.00 MHz (limit: 20.00 MHz)
Size: 15193MB
CSD: ver=2, sector_size=512, capacity=31116288 read_bl_len=9
SSR: bus_width=1
I (1948) example: file name:/sdcard/0_466596.jpg
I (2048) example: File written
...
```
</details>

#### H.264
<details><summary>Example log output:</summary>

```
...
I (1533) main_task: Calling app_main()
I (1533) sc2336: Detected Camera sensor PID=0xcb3a
I (1603) example: version: 0.8.0
I (1603) example: driver:  MIPI-CSI
I (1603) example: card:    MIPI-CSI
I (1613) example: bus:     esp32p4:MIPI-CSI
I (1613) example: capabilities:
I (1613) example:       VIDEO_CAPTURE
I (1613) example:       STREAMING
I (1623) example: device capabilities:
I (1623) example:       VIDEO_CAPTURE
I (1623) example:       STREAMING
I (1623) example: version: 0.8.0
I (1633) example: driver:  H.264
I (1633) example: card:    H.264
I (1633) example: bus:     esp32p4:H.264
I (1643) example: capabilities:
I (1643) example:       STREAMING
I (1643) example: device capabilities:
I (1653) example:       STREAMING
I (1653) example: Initializing SD card
I (1653) example: Using SDMMC peripheral
I (1663) example: Mounting filesystem
I (1663) gpio: GPIO[43]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1673) gpio: GPIO[44]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1683) gpio: GPIO[39]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1863) example: Filesystem mounted
Name: SC16G
Type: SDHC
Speed: 20.00 MHz (limit: 20.00 MHz)
Size: 15193MB
CSD: ver=2, sector_size=512, capacity=31116288 read_bl_len=9
SSR: bus_width=1
I (1973) example: file name:/sdcard/0_496174_h264.bin
I (5003) example: File written
I (5003) main_task: Returned from app_main()
...
```
</details>

Open VLC media player APP and then open the `*.bin` file in the player to view the video stream.

## Troubleshooting

* If the console log shows as follows, it means your SOC chip version is v0.0, and it is not supported by default configuration, please configure the right version by menuconfig:

    ```txt
    A fatal error occurred: bootloader/bootloader.bin requires chip revision in range [v0.1 - v0.99] (this chip is revision v0.0). Use --force to flash anyway
    ```

    menuconfig:
    ```
    Component config  --->
        Hardware Settings  --->
            Chip revision  --->
                Minimum Supported ESP32-P4 Revision (Rev v0.1)  --->
                    (X) Rev v0.0
    ```

- if the console log shows as follows, It means that the number of files allowed in the current virtual file system is too small. Please update the maximum number of files supported by the virtual file system by menuconfig:

  ```
  E (1535) esp_video: Failed to register video VFS dev name=video0
  E (1545) esp_video_init: failed to create MIPI-CSI video device
  ```

  menuconfig:

  ```
  Component config  --->
  	Virtual file system  --->
  		(20)     Maximum Number of Virtual Filesystems
  ```

  
