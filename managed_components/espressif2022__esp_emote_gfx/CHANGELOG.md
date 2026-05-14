# Changelog

All notable changes to the ESP Emote GFX component will be documented in this file.

## [1.2.0] - 2025-09-0
- use eaf as a lib

## [1.1.2] - 2025-09-29

### Upgrade dependencies
- Update `espressif/esp_new_jpeg` to 0.6.x by @Kevincoooool. [#8](https://github.com/espressif2022/esp_emote_gfx/pull/8)

## [1.1.1] - 2025-09-23

### Fixed
- Resolve image block decoding failure in specific cases. [#6](https://github.com/espressif2022/esp_emote_gfx/issues/6)

## [1.0.0] - 2025-08-01

### Added
- Initial release of ESP Emote GFX framework
- Core graphics rendering engine
- Object system for images and labels
- Basic drawing functions and color utilities
- Software blending capabilities
- Timer system for animations
- Support for ESP-IDF 5.0+
- FreeType font rendering integration
- JPEG image decoding support

### Features
- Lightweight graphics framework optimized for embedded systems
- Memory-efficient design for resource-constrained environments
