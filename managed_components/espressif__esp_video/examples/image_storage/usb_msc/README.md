| Supported Targets | ESP32-P4 |
| ----------------- | -------- |

# Image storage on USB MSC

(See the [README.md](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/usb/device/tusb_msc) file in the `esp-idf/examples/peripherals/usb/device
/tusb_msc/` directory for more information about USB Mass Storage Device.)

This example demonstrates how to store an image file in SPI flash or SD card storage media and then access the image file through a USB cable.

__WARNING:__ This example can potentially delete all data from your SD card (when formatting is enabled). Back up your data first before proceeding.

## How to use example

### Hardware Required

* A development board with MIPI-CSI or DVP interface.
* A camera sensor that is already supported by the [esp_cam_sensor](https://github.com/espressif/esp-video-components/tree/master/esp_cam_sensor) component.
* A USB Type-C cable for power supply and programming.
* A cable for connecting the USB port of the PC to the USB-OTG peripherals of the development board.
* If the storage media is SPI Flash, any ESP board that have USB-OTG is supported.
* If the storage media is SD MMC Card, any ESP board with SD MMC card slot and an SD card is required.

### Software Required

* `VLC media player`. Open `VLC media player` APP and then open the `*.bin` file in the player to view the h.264 video stream.

### Configure the Project

Please refer to the example video initialization configuration [document](../common_components/example_video_common/README.md) for more details about the board-level configuration, including the camera sensor interface, GPIO pins, clock frequency, and so on.

Select and configure camera sensor based on development kit:

##### MIPI-CSI Development Kit

```  
Component config  --->
    Espressif Camera Sensors Configurations  --->
        [*] SC2336  ---->
            Default format select for MIPI (RAW8 1280x720 30fps, MIPI 2lane 24M input)  --->
                (X) RAW8 1280x720 30fps, MIPI 2lane 24M input
```

##### DVP Development Kit

```
Component config  --->
    Espressif Camera Sensors Configurations  --->
        [*] OV2640  --->
            Default format select (RGB565 640x480 6fps, DVP 8bit 20M input)  --->
                (X) RGB565 640x480 6fps, DVP 8bit 20M input
```
#### Configure the format of stored image data

##### JPEG

```
Example Configuration  --->
	Example Video Configuration  --->
		Image Storage Format  --->
			(X) MJPEG
```

##### H.264

```
Example Configuration  --->
	Example Video Configuration  --->
		Image Storage Format  --->
			(X) H264
```
##### Non-Encode

```
Example Configuration  --->
	Example Video Configuration  --->
		Image Storage Format  --->
			(X) Non-Encode
```
#### Configure USB MSC

```
Example Configuration  --->
	Example TinyUSB MSC Configuration
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

#### SPI Flash

<details><summary>Example log output:</summary>

```
I (1544) main_task: Calling app_main()
I (1544) sc2336: Detected Camera sensor PID=0xcb3a
I (1624) example_main: Initializing storage...
I (1624) example_main: Initializing wear levelling
I (1624) example_main: Mount storage...
I (1624) example_main: Storage mounted to application: Yes
I (1624) example_main: 
ls command output:
System Volume Information
I (1634) example_main: USB MSC initialization
I (1634) tusb_desc: 
┌─────────────────────────────────┐
│  USB Device Descriptor Summary  │
├───────────────────┬─────────────┤
│bDeviceClass       │ 239         │
├───────────────────┼─────────────┤
│bDeviceSubClass    │ 2           │
├───────────────────┼─────────────┤
│bDeviceProtocol    │ 1           │
├───────────────────┼─────────────┤
│bMaxPacketSize0    │ 64          │
├───────────────────┼─────────────┤
│idVendor           │ 0x303a      │
├───────────────────┼─────────────┤
│idProduct          │ 0x4002      │
├───────────────────┼─────────────┤
│bcdDevice          │ 0x100       │
├───────────────────┼─────────────┤
│iManufacturer      │ 0x1         │
├───────────────────┼─────────────┤
│iProduct           │ 0x2         │
├───────────────────┼─────────────┤
│iSerialNumber      │ 0x3         │
├───────────────────┼─────────────┤
│bNumConfigurations │ 0x1         │
└───────────────────┴─────────────┘
I (1804) TinyUSB: TinyUSB Driver installed
I (1804) example_main: USB MSC initialization DONE, storage capacity 2016KB
I (1904) example_main: file name:/data/0_415141.jpg
I (3774) example_main: File written
I (3774) main_task: Returned from app_main()
I (40774) example_main: Storage mounted to application: No

```
</details>

#### SD Card

<details><summary>Example log output:</summary>

```
I (1551) main_task: Calling app_main()
I (1551) sc2336: Detected Camera sensor PID=0xcb3a
I (1631) example_main: Initializing storage...
I (1631) example_main: Initializing SDCard
I (1631) gpio: GPIO[43]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1631) gpio: GPIO[44]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1641) gpio: GPIO[39]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
Name: SC16G
Type: SDHC
Speed: 20.00 MHz (limit: 20.00 MHz)
Size: 15193MB
CSD: ver=2, sector_size=512, capacity=31116288 read_bl_len=9
SSR: bus_width=1
I (1811) example_main: Mount storage...
I (1821) example_main: Storage mounted to application: Yes
I (1821) example_main: 
ls command output:
0_476473.JPG
System Volume Information
I (1831) example_main: USB MSC initialization
I (1841) tusb_desc: 
┌─────────────────────────────────┐
│  USB Device Descriptor Summary  │
├───────────────────┬─────────────┤
│bDeviceClass       │ 239         │
├───────────────────┼─────────────┤
│bDeviceSubClass    │ 2           │
├───────────────────┼─────────────┤
│bDeviceProtocol    │ 1           │
├───────────────────┼─────────────┤
│bMaxPacketSize0    │ 64          │
├───────────────────┼─────────────┤
│idVendor           │ 0x303a      │
├───────────────────┼─────────────┤
│idProduct          │ 0x4002      │
├───────────────────┼─────────────┤
│bcdDevice          │ 0x100       │
├───────────────────┼─────────────┤
│iManufacturer      │ 0x1         │
├───────────────────┼─────────────┤
│iProduct           │ 0x2         │
├───────────────────┼─────────────┤
│iSerialNumber      │ 0x3         │
├───────────────────┼─────────────┤
│bNumConfigurations │ 0x1         │
└───────────────────┴─────────────┘
I (2011) TinyUSB: TinyUSB Driver installed
I (2011) example_main: USB MSC initialization DONE, storage capacity 15558144KB

I (2111) example_main: file name:/data/0_611683.jpg
I (2201) example_main: File written
I (2201) main_task: Returned from app_main()
```
</details>

Connect the USB port of the PC to the USB-OTG peripheral of the development board, and then you can access the acquired image data on the PC.
