# Example Video Common Component

This component provides board-level initialization for esp_video, including MIPI-CSI sensor I2C port, DVP sensor I2C port, DVP interface configuration and SPI interface configuration. It is primarily designed for esp_video examples to simplify board-level configuration and initialization processes.

## Supported Boards and GPIO Pins

| Hardware | ESP32-P4-Function-EV-Board V1.4 | ESP32-P4-Function-EV-Board V1.5 | ESP32-P4-EYE | ESP32-S3-EYE |
|:-:|:-:|:-:|:-:|:-:|
| MIPI-CSI I2C SCL Pin        |  8 |  8 | 13 | NA |
| MIPI-CSI I2C SDA Pin        |  7 |  7 | 14 | NA |
| MIPI-CSI I2C Reset Pin      | NA | NA | 26 | NA |
| MIPI-CSI I2C Power-down Pin | NA | NA | 12 | NA |
| MIPI-CSI I2C XCLK           | NA | NA | 11 | NA |
|   |   |   |   |
| DVP I2C SCL Pin             | NA |  8 | NA |  5 |
| DVP I2C SDA Pin             | NA |  7 | NA |  4 |
| DVP I2C Reset Pin           | NA | 36 | NA | NA |
| DVP I2C Power-down Pin      | NA | 38 | NA | NA |
| DVP XCLK Pin                | NA | 20 | NA | 15 |
| DVP PCLK Pin                | NA |  4 | NA | 13 |
| DVP V-SYNC Pin              | NA | 37 | NA |  6 |
| DVP DE Pin                  | NA | 22 | NA |  7 |
| DVP D0 Pin                  | NA |  2 | NA | 11 |
| DVP D1 Pin                  | NA | 32 | NA |  9 |
| DVP D2 Pin                  | NA | 33 | NA |  8 |
| DVP D3 Pin                  | NA | 23 | NA | 10 |
| DVP D4 Pin                  | NA |  3 | NA | 12 |
| DVP D5 Pin                  | NA |  6 | NA | 18 |
| DVP D6 Pin                  | NA |  5 | NA | 17 |
| DVP D7 Pin                  | NA | 21 | NA | 16 |
|   |   |   |   |
| SPI I2C SCL Pin             | NA |  8 | NA |  5 |
| SPI I2C SDA Pin             | NA |  7 | NA |  4 |
| SPI I2C Reset Pin           | NA | NA | NA | NA |
| SPI I2C Power-down Pin      | NA | NA | NA | NA |
| SPI XCLK Pin                | NA | 20 | NA | 15 |
| SPI CS Pin                  | NA | 37 | NA |  6 |
| SPI SCLK Pin                | NA |  4 | NA | 13 |
| SPI Data0 I/O Pin           | NA | 21 | NA | 16 |

**Note:** The ESP32-P4-Function-EV v1.4 board and ESP32-P4-EYE do not support DVP interface camera sensors by default. If you need to connect a DVP interface camera sensor to these boards, please select "Customized Development Board" in the menu and configure the GPIO pins and clock according to your specific hardware setup.

### Customized Development Board Default Configuration

When using "ESP32-XX-DevKitC" development boards, you can try the default GPIO pin configuration for "Customized Development Board" as shown in the following table:

| Hardware | ESP32-P4 | ESP32-S3 | ESP32-C3 | ESP32-C6 | ESP32-C61 | ESP32-C5 |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| MIPI-CSI CAM I2C SCL Pin        |  8 | NA | NA | NA | NA | NA |
| MIPI-CSI CAM I2C SDA Pin        |  7 | NA | NA | NA | NA | NA |
| MIPI-CSI CAM I2C Reset Pin      | NA | NA | NA | NA | NA | NA |
| MIPI-CSI CAM I2C Power-down Pin | NA | NA | NA | NA | NA | NA |
| MIPI-CSI CAM I2C XCLK           | NA | NA | NA | NA | NA | NA |
|   |   |   |   |
| DVP CAM I2C SCL Pin             |  8 |  5 | NA | NA | NA | NA |
| DVP CAM I2C SDA Pin             |  7 |  4 | NA | NA | NA | NA |
| DVP CAM I2C Reset Pin           | NA | NA | NA | NA | NA | NA |
| DVP CAM I2C Power-down Pin      | NA | NA | NA | NA | NA | NA |
| DVP CAM XCLK Pin                | 20 | 15 | NA | NA | NA | NA |
| DVP CAM PCLK Pin                |  4 | 13 | NA | NA | NA | NA |
| DVP CAM V-SYNC Pin              | 37 |  6 | NA | NA | NA | NA |
| DVP CAM DE Pin                  | 22 |  7 | NA | NA | NA | NA |
| DVP CAM D0 Pin                  |  2 | 11 | NA | NA | NA | NA |
| DVP CAM D1 Pin                  | 32 |  9 | NA | NA | NA | NA |
| DVP CAM D2 Pin                  | 33 |  8 | NA | NA | NA | NA |
| DVP CAM D3 Pin                  | 23 | 10 | NA | NA | NA | NA |
| DVP CAM D4 Pin                  |  3 | 12 | NA | NA | NA | NA |
| DVP CAM D5 Pin                  |  6 | 18 | NA | NA | NA | NA |
| DVP CAM D6 Pin                  |  5 | 17 | NA | NA | NA | NA |
| DVP CAM D7 Pin                  | 21 | 16 | NA | NA | NA | NA |
|   |   |   |   |
| SPI CAM0 I2C SCL Pin             |  8 |  5 |  5 |  5 |  5 |  5 |
| SPI CAM0 I2C SDA Pin             |  7 |  4 |  4 |  4 |  4 |  4 |
| SPI CAM0 I2C Reset Pin           | NA | NA | NA | NA | NA | NA |
| SPI CAM0 I2C Power-down Pin      | NA | NA | NA | NA | NA | NA |
| SPI CAM0 XCLK Pin                | 20 | 15 |  8 |  0 |  0 |  0 |
| SPI CAM0 CS Pin                  | 37 |  6 | 10 |  1 |  8 | 10 |
| SPI CAM0 SCLK Pin                |  4 | 13 |  6 |  6 |  6 |  6 |
| SPI CAM0 Data0 I/O Pin           | 21 | 16 |  7 |  7 |  7 |  7 |
|   |   |   |   |
| SPI CAM1 I2C SCL Pin             |  5 |  1 | NA | NA | NA | NA |
| SPI CAM1 I2C SDA Pin             |  6 |  2 | NA | NA | NA | NA |
| SPI CAM1 I2C Reset Pin           | NA | NA | NA | NA | NA | NA |
| SPI CAM1 I2C Power-down Pin      | NA | NA | NA | NA | NA | NA |
| SPI CAM1 XCLK Pin                | 23 | 39 | NA | NA | NA | NA |
| SPI CAM1 CS Pin                  | 38 | 42 | NA | NA | NA | NA |
| SPI CAM1 SCLK Pin                | 22 | 41 | NA | NA | NA | NA |
| SPI CAM1 Data0 I/O Pin           |  3 | 40 | NA | NA | NA | NA |

**Note 1**: Only SoCs that have more than one SPI port, except for SPI flash and SPI RAM ports, can use the SPI CAM0 and SPI CAM1 simultaneously.

**Note 2**: If the SPI CAM0 and SPI CAM1 use the same camera sensor and it only owns one I2C slave address, the SPI CAM0 and SPI CAM1 should use different I2C ports to communicate with their target camera sensor.

## Usage Instructions

### MIPI-CSI Development Kit

To configure your development board with MIPI-CSI interface, follow these steps:

```
Example Video Initialization Configuration  --->
    Select Target Development Board (ESP32-P4-Function-EV-Board V1.5)
        ( ) ESP32-P4-Function-EV-Board V1.4
        (X) ESP32-P4-Function-EV-Board V1.5
        ( ) ESP32-P4-EYE

        ......

        ( ) Customized Development Board
    Select and Set Camera Sensor Interface  --->
        [*] MIPI-CSI  --->
        [ ] DVP  ----
```

If your development board is not listed in the menu, select "Customized Development Board" and configure the GPIO pins according to your board specifications:

```
Example Video Initialization Configuration  --->
    Select Target Development Board (Customized Development Board)
        ( ) ESP32-P4-Function-EV-Board V1.4
        ( ) ESP32-P4-Function-EV-Board V1.5
        ( ) ESP32-P4-EYE

        ......

        (X) Customized Development Board
    Select and Set Camera Sensor Interface  --->
        [*] MIPI-CSI  --->
            (0) SCCB(I2C) Port Number
            (100000) SCCB(I2C) Frequency (100K-400K Hz)
            (8) SCCB(I2C) SCL Pin
            (7) SCCB(I2C) SDA Pin
            (-1) Reset Pin
            (-1) Power Down Pin
            (-1) XCLK Pin
        [ ] DVP  ----
```

### DVP Development Kit

To configure your development board with DVP interface, follow these steps:

```
Example Video Initialization Configuration  --->
    Select Target Development Board (ESP32-P4-Function-EV-Board V1.5)
        ( ) ESP32-P4-Function-EV-Board V1.4
        (X) ESP32-P4-Function-EV-Board V1.5
        ( ) ESP32-P4-EYE

        ......

        ( ) Customized Development Board
    Select and Set Camera Sensor Interface  --->
        [ ] MIPI-CSI  ---
        [*] DVP  ---->
```

If your development board is not listed in the menu, select "Customized Development Board" and configure the GPIO pins according to your board specifications:

```
Example Video Initialization Configuration  --->
    Select Target Development Board (Customized Development Board)
        ( ) ESP32-P4-Function-EV-Board V1.4
        ( ) ESP32-P4-Function-EV-Board V1.5
        ( ) ESP32-P4-EYE

        ......

        (X) Customized Development Board
    Select and Set Camera Sensor Interface  --->
        [ ] MIPI-CSI  ---
        [*] DVP  ---->
            (0) SCCB(I2C) Port Number
            (100000) SCCB(I2C) Frequency (100K-400K Hz)
            (20000000) XCLK Frequency (Hz)
            (8) SCCB(I2C) SCL Pin
            (7) SCCB(I2C) SDA Pin
            (-1) Reset Pin
            (-1) Power Down Pin
            (20) XCLK Pin
            (4) PCLK Pin
            (37) VSYNC Pin
            (22) DE Pin
            (2) Data0 Pin
            (32) Data1 Pin
            (33) Data2 Pin
            (23) Data3 Pin
            (3) Data4 Pin
            (6) Data5 Pin
            (5) Data6 Pin
            (21) Data7 Pin
```

### SPI Development Kit

To enable SPI video device support, first enable the following configuration:

```
Component config  --->
    Espressif Video Configuration  --->
        [*] Enable SPI based Video Device  ----
```

Then configure your development board with SPI interface:

```
Example Video Initialization Configuration  --->
    Select Target Development Board (ESP32-P4-Function-EV-Board V1.5)
        ( ) ESP32-P4-Function-EV-Board V1.4
        (X) ESP32-P4-Function-EV-Board V1.5
        ( ) ESP32-P4-EYE

        ......

        ( ) Customized Development Board
    Select and Set Camera Sensor Interface  --->
        [ ] MIPI-CSI  ---
        [ ] DVP  ----
        [*] SPI  ---->
```

If your development board is not listed in the menu, select "Customized Development Board" and configure the GPIO pins according to your board specifications:

```
Example Video Initialization Configuration  --->
    Select Target Development Board (Customized Development Board)
        ( ) ESP32-P4-Function-EV-Board V1.4
        ( ) ESP32-P4-Function-EV-Board V1.5
        ( ) ESP32-P4-EYE

        ......

        (X) Customized Development Board
    Select and Set Camera Sensor Interface  --->
        [ ] MIPI-CSI  ---
        [ ] DVP  ----
        [*] SPI  ---->
            ()  SCCB(I2C) Port Number
            (100000) SCCB(I2C) Frequency (100K-400K Hz)
            (2) SPI Port Number
                Select XCLK Source (ESP Clock Router)  --->
            (24000000) XCLK Frequency (Hz)
            (8) SCCB(I2C) SCL Pin
            (7) SCCB(I2C) SDA Pin
            (-1) Reset Pin
            (-1) Power Down Pin
            (20) XCLK Output Pin
            (37) Chip Select Pin
            (4) Clock Pin
            (21) Data0 I/O Pin
```

### Dual SPI Camera Sensors

***ESP32-P4*** and ***ESP32-S3*** have more than two SPI ports (where one port is used for SPI flash and SPIRAM), allowing these two SoCs to connect to dual SPI camera sensors. To enable dual SPI camera sensors, first enable the following configuration:

```
Component config  --->
    Espressif Video Configuration  --->
        [*] Enable SPI based Video Device  --->
            [*] Enable The Second SPI Video Device
```

Then select the "Customized Development Board" configuration, as there is currently no dedicated dual SPI camera sensor development board available:

```
Example Video Initialization Configuration  --->
    Select Target Development Board (Customized Development Board)  --->
        ......
        (X) Customized Development Board
```

Configure the GPIO pins according to your board specifications:

```
Example Video Initialization Configuration  --->
    Select and Set Camera Sensor Interface  --->
        [*] SPI Camera Sensor 0  --->
            (0) SCCB(I2C) Port Number
            (100000) SCCB(I2C) Frequency (100K-400K Hz)
            (2) SPI Port Number
                Select XCLK Source (ESP Clock Router)  --->
            (24000000) XCLK Frequency (Hz)
            (8) SCCB(I2C) SCL Pin (NEW)
            (7) SCCB(I2C) SDA Pin (NEW)
            (-1) Reset Pin (NEW)
            (-1) Power Down Pin (NEW)
            (20) XCLK Output Pin (NEW)
            (37) Chip Select Pin (NEW)
            (4) Clock Pin (NEW)
            (21) Data0 I/O Pin (NEW)
       [*] SPI Camera Sensor 1  --->
            (1) SCCB(I2C) Port Number
            (100000) SCCB(I2C) Frequency (100K-400K Hz)
            (1) SPI Port Number
                Select XCLK Source (LEDC Timer)  --->
            (20000000) XCLK Frequency (Hz)
            (1) XCLK LEDC Timer Number
            (1) XCLK LEDC Timer Channel
            (5) SCCB(I2C) SCL Pin (NEW)
            (6) SCCB(I2C) SDA Pin (NEW)
            (-1) Reset Pin (NEW)
            (-1) Power Down Pin (NEW)
            (23) XCLK Output Pin (NEW)
            (38) Chip Select Pin (NEW)
            (22) Clock Pin (NEW)
            (3) Data0 I/O Pin (NEW)
```

### Use Pre-initialized SCCB(I2C) Bus

For some development boards, the MIPI-CSI, DVP, SPI camera sensors or motors share the same SCCB(I2C) port and GPIO pins, such as ESP32-P4-Function-EV-Board V1.5. You can select and set the following options:

```
Example Video Initialization Configuration  --->
    [*] Use Pre-initialized SCCB(I2C) Bus for All Camera Sensors And Motors  --->
        (0) SCCB(I2C) Port Number
        (8) SCCB(I2C) SCL Pin
        (7) SCCB(I2C) SDA Pin
```