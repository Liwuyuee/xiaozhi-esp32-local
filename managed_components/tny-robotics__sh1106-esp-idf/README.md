# SH1106 ESP-IDF Driver

Source code for the SH1106 I2C OLED screen driver for ESP-IDF.

## Introduction

This driver is a simple implementation of the SH1106 OLED screen driver for the ESP-IDF framework.

It is used to communicate with the SH1106 OLED screen using the standard LCD interface of the ESP-IDF framework.

## Installation

To install the driver, you can clone the repository and place it in the `components` folder of your project.

```bash
git clone https://github.com/TNY-Robotics/sh1106-esp-idf.git components/sh1106
```

## Usage

The driver exposes a simple header file named `esp_lcd_panel_sh1106.h`, that you can include using :

```c
#include "esp_lcd_panel_sh1106.h"
```

You can now create an lcd panel with the SH1106 driver using the following code :

```c
esp_err_t err = esp_lcd_new_panel_sh1106(panel_io_handle, &panel_dev_config, &panel_handle);
```

For more information about LCDs with the ESP-IDF framework, visit the [official documentation](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/lcd/index.html).

## Examples

An example of how ESP-IDF lcd creation using the SH1106 driver can be found in the `main` folder.

## Screen buffer format

Here's some information about the screen buffer format used by the SH1106 driver, and the SH1106 to better understand how to use the driver and display pixels on the screen.

### Pixels and pages
The SH1106 buffer format works with lines and pages.

Each page is `8` pixels high and `128` pixels wide. The screen has `8` pages for a total of `64` pixels high.

If we represent the screen buffer as an array of bytes *(8 bits)*, the screen will read each byte as a `page pixel` *(a vertical strip of 8 pixels high)*, and at the end of the page, it will move to the next page *(8 pixels down)*.

Each bit in the byte represents a pixel state, where `0` is off and `1` is on.

### Schematic representation
The way the screen reads the buffer is as follows:

![SH1106 Schema](./doc/sh1106%20schema.png)

- Each **RED Arrrow** represents one byte of data, corresponding to a `page pixel` *(vertical line of 8 pixels)*.
- Each **GREEN Arrow** represents one 128 byte of data, corresponding to a `page` *(horizontal line of 128 `page pixels`)*.
- Each **BLUE Arrow** represents the page shift *(8 pixels down, back to left side)* after reading one `page` of data.

### Adressing pixels in the buffer

Turning on and off one pixel in the buffer is a little bit tricky, as we need to only change the state of one bit in the byte buffer.

Here's a simple example of how to turn on and off a pixel in the buffer:

```c
// Creating the screen buffer
uint8_t buffer[128 * 8]; // 128 page pixels * 8 pages, with 8 pixels per page pixel

// Optional : Clear the buffer
memset(buffer, 0, sizeof(buffer)); // All pixels will be turned off if we fill the buffer with 0


// ==> Only turning on a pixel at [0, 0] (the top-left corner)
// the page index is 0, the page pixel index is 0
// so we just need to set the first bit of the first byte of the buffer to 1
buffer[0] = 0b00000001;

// note : if you don't want to affect the other pixels in the byte, you can use the bitwise OR operator
buffer[0] |= 0b00000001; // setting at 0 the pixels we don't want to change, and at 1 the pixel we want to turn on

// note : now if you want to turn off the pixel, you can use the bitwise AND operator
buffer[0] &= 0b11111110; // setting at 1 the pixels we don't want to change, and at 0 the pixel we want to turn off

// note: writing the entire binary value is a little bit tricky, so you can use shift operators instead
buffer[0] |= 1 << 0; // 1 << 0 is equivalent to 0b00000001, we are shifting the 1 by 0 positions to the left

// note: writing the entire binary value is a little bit tricky, so you can use shift operators instead
buffer[0] &= ~(1 << 0); // ~(1 << 0) is equivalent to 0b11111110, we are shifting the 1 by 0 positions to the left and inverting the bits

// ==> Turning on a pixel at [0, 1] (the pixel right below the top-left corner)
// the page index is 0, the page pixel index is 0
// so we just need to set the second bit of the first byte of the buffer to 1
buffer[0] |= 1 << 1; // 1 << 1 is equivalent to 0b00000010, we are shifting the 1 by 1 position to the left

// ==> Turning on a pixel at [127, 0] (the top-right corner)
// the page index is 0, the page pixel index is 127
// so we just need to set the first bit of the 127th byte of the buffer to 1
buffer[127] |= 1 << 0;

// ==> Turning on a pixel at [127, 63] (the bottom-right corner)
// the page index is 7, the page pixel index is 127
// so we just need to set the last bit of the byte at position 7*128 + 127 of the buffer to 1
buffer[7*128 + 127] |= 1 << 7; // shifting by 7 positions to the left is equivalent to 0b10000000
```

### General formula

To turn on a pixel at position `(x, y)` in the buffer, you can use the following formula:

```c
uint8_t x = 0; // the x position of the pixel
uint8_t y = 0; // the y position of the pixel

// Getting the page index
uint8_t page_index = y / 8; // integer division, we get the page index of the pixel
uint8_t page_pixel_index = x; // the page pixel index is the x position of the pixel
uint8_t page_pixel_shift = y % 8; // remainder of the division, we get the bit shift of the pixel in the page pixel

// Turning on the pixel
buffer[page_index * 128 + page_pixel_index] |= 1 << page_pixel_shift;

// Turning off the pixel
buffer[page_index * 128 + page_pixel_index] &= ~(1 << page_pixel_shift);
```

## Licence

This driver is under the MIT Licence.

## Author

This driver was created by the [TNY Robotics](https://tny-robotics.com) team, for any questions or suggestions, please contact us at [contact@furwaz.com](mailto:contact@furwaz.com).