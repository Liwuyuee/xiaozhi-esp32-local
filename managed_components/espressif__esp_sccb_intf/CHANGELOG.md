## 0.0.6

- Fix `transmit_reg_a8v16()` transmission length

## 0.0.5

- Added support for transmitting / receiving 16-bit value
- Changed `transmit_reg_a16v16()`, `transmit_reg_a8v16()`, `transmit_receive_reg_a8v16()`, `transmit_receive_reg_a16v16()` default return value to `ESP_OK`

## 0.0.4

- Added timeout option in Kconfig

## 0.0.3

- Fix SCCB I2C memory leak

## 0.0.2

- Fixed IDF Dependency version. It's actually v5.3.
- Added build-only test app.

## 0.0.1

- Initial version for esp_sccb_intf component
