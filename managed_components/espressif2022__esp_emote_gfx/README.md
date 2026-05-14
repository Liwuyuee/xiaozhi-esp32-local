# ESP Emote GFX

## Introduction
A lightweight graphics framework for ESP-IDF with support for images, labels, animations, and fonts.

[![Component Registry](https://components.espressif.com/components/espressif2022/esp_emote_gfx/badge.svg)](https://components.espressif.com/components/espressif2022/esp_emote_gfx)

## Features

- **Images**: Display images in RGB565A8 format
- **Animations**: GIF animations with [ESP32 tools](https://esp32-gif.espressif.com/)
- **Fonts**: LVGL fonts and FreeType TTF/OTF support
- **Timers**: Built-in timing system for smooth animations
- **Memory Optimized**: Designed for embedded systems

## Dependencies

1. **ESP-IDF**  
   Ensure your project includes ESP-IDF 5.0 or higher. Refer to the [ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/) for setup instructions.

2. **FreeType**  
   This component depends on the FreeType library for font rendering.

3. **ESP New JPEG**  
   JPEG decoding support through the ESP New JPEG component.

## Usage

### Basic Setup

```c
#include "gfx.h"

// Initialize the GFX framework
gfx_core_config_t gfx_cfg = {
    .flush_cb = flush_callback,
    .h_res = BSP_LCD_H_RES,
    .v_res = BSP_LCD_V_RES,
    .fps = 50,
    // other configuration...
};
gfx_handle_t emote_handle = gfx_emote_init(&gfx_cfg);
```

For detailed widget usage and operations, see the [Widget Operations Reference](#widget-operations-reference) section below.


## Examples and Test Applications

For comprehensive widget usage examples, refer to the test applications in `esp_emote_gfx/test_apps/`. These examples demonstrate real-world usage patterns and advanced features.

### Running Test Examples

```bash
cd esp_emote_gfx/test_apps
idf.py build flash monitor
```

The test application includes the following widget demonstrations:

#### Timer Operations
- Creating and configuring timers
- Pausing, resuming, and resetting timers
- Setting repeat counts and periods
- Timer callback implementations

#### Animation Widget Examples
- Loading different animation formats (4-bit, 8-bit, 24-bit)
- Setting animation segments and playback control
- Mirror effects and positioning
- Multiple animation objects management

#### Label Widget Examples
- LVGL font rendering with Chinese text support
- FreeType font loading and usage
- Text formatting with `gfx_label_set_text_fmt()`
- Long text handling (scroll, wrap modes)
- Background colors and text styling

#### Image Widget Examples
- Loading C array format images
- Loading binary format images with headers
- Multiple image objects with different formats
- Image positioning and sizing

#### Multi-Object Scenarios
- Combining animations, images, and labels
- Object layering and interaction
- Resource management for multiple widgets
- Performance considerations

## Widget Operations Reference

### Common Object Operations

All widgets inherit from the base object system and support these common operations:

```c
// Object creation (replace 'widget' with img, label, or anim)
gfx_obj_t *obj = gfx_widget_create(emote_handle);

// Position and size
gfx_obj_set_pos(obj, x, y);                    // Set absolute position
gfx_obj_set_size(obj, width, height);          // Set size
gfx_obj_get_size(obj, &width, &height);        // Get current size

// Alignment
gfx_obj_align(obj, GFX_ALIGN_CENTER, x_offset, y_offset);
gfx_obj_align(obj, GFX_ALIGN_TOP_MID, 0, 10);
gfx_obj_align(obj, GFX_ALIGN_BOTTOM_LEFT, 5, -5);

// Visibility and cleanup
gfx_obj_set_hidden(obj, true);                 // Hide object
gfx_obj_set_hidden(obj, false);                // Show object
gfx_obj_delete(obj);                           // Delete object
```

### Label Widget Operations

```c
// Font management
gfx_label_set_font(label_obj, (gfx_font_t)&font_puhui_16_4);  // LVGL font

// FreeType font creation
gfx_label_cfg_t font_cfg = {
    .name = "DejaVuSans.ttf",
    .mem = font_data,
    .mem_size = font_size,
    .font_size = 20,
};
gfx_font_t freetype_font;
gfx_label_new_font(&font_cfg, &freetype_font);
gfx_label_set_font(label_obj, freetype_font);

// Text operations
gfx_label_set_text(label_obj, "Hello World");
gfx_label_set_text_fmt(label_obj, "Count: %d, Value: %.2f", 42, 3.14);

// Styling
gfx_label_set_color(label_obj, GFX_COLOR_HEX(0xFF0000));      // Text color
gfx_label_set_bg_color(label_obj, GFX_COLOR_HEX(0x00FF00));   // Background color
gfx_label_set_bg_enable(label_obj, true);                     // Enable background

// Long text handling
gfx_label_set_long_mode(label_obj, GFX_LABEL_LONG_WRAP);      // Wrap text
gfx_label_set_long_mode(label_obj, GFX_LABEL_LONG_SCROLL);    // Scroll text

// Cleanup
gfx_label_delete_font(freetype_font);  // Delete FreeType font when done
```

### Image Widget Operations

The framework supports RGB565A8 format images, which provide 16-bit RGB color with 8-bit alpha transparency. This format is optimized for embedded systems with limited memory.

#### RGB565A8 Format Details

- **RGB565**: 16-bit color (5 bits red, 6 bits green, 5 bits blue)
- **Alpha8**: 8-bit alpha channel for transparency
- **Memory Layout**: RGB565 data followed by Alpha data
- **File Size**: Width × Height × 3 bytes per image

#### Converting PNG to RGB565A8

Use the provided conversion script to convert PNG images to RGB565A8 format:

```bash
# Convert single PNG file to C array format
python scripts/png_to_rgb565a8.py image.png

# Convert single PNG file to binary format
python scripts/png_to_rgb565a8.py image.png --bin

# Batch convert all PNG files in current directory to binary format
python scripts/png_to_rgb565a8.py ./ --bin

# Convert with byte swapping (for different endianness)
python scripts/png_to_rgb565a8.py ./ --bin --swap16

# Convert to specific output directory
python scripts/png_to_rgb565a8.py ./ --bin --output ./converted_images/
```

**Script Options:**
- `--bin`: Output binary format instead of C array format
- `--swap16`: Enable byte swapping for RGB565 data
- `--output`, `-o`: Specify output directory

#### Using RGB565A8 Images

```c
// Create an image object
gfx_obj_t *img_obj = gfx_img_create(emote_handle);

// Method 1: Using C array format (generated by script without --bin)
extern const gfx_image_dsc_t my_image;
gfx_img_set_src(img_obj, (void*)&my_image);

// Method 2: Using binary format (generated by script with --bin)
gfx_image_dsc_t img_dsc;
img_dsc.data_size = binary_data_size;
img_dsc.data = binary_data_ptr;
// Copy header from binary data
memcpy(&img_dsc.header, binary_data_ptr, sizeof(gfx_image_header_t));
img_dsc.data += sizeof(gfx_image_header_t);
img_dsc.data_size -= sizeof(gfx_image_header_t);
gfx_img_set_src(img_obj, (void*)&img_dsc);

// Set position and display
gfx_obj_set_pos(img_obj, 100, 100);

// The framework automatically handles:
// - Image format detection (C array vs binary)
// - Memory layout parsing
// - Size calculation from image header
```

### Animation Widget Operations

Create animations using the [ESP32 GIF animation tools](https://esp32-gif.espressif.com/) (converts GIF files to EAF animation format):

```c
// Create animation object
gfx_obj_t *anim_obj = gfx_anim_create(emote_handle);

// Load animation data
gfx_anim_set_src(anim_obj, anim_data, anim_size);
gfx_obj_set_size(anim_obj, 200, 150);

// Playback control
gfx_anim_set_segment(anim_obj, start_frame, end_frame, fps, loop);
gfx_anim_start(anim_obj);
gfx_anim_stop(anim_obj);

// Visual effects
gfx_anim_set_mirror(anim_obj, enable, offset);  // Manual mirror effect
gfx_anim_set_auto_mirror(anim_obj, enable);     // Auto mirror effect (automatic horizontal mirroring)
```

### Timer System Operations

```c
// Create timer callback
void timer_callback(void *user_data) {
    // Timer callback code
}

// Create and configure timer
gfx_timer_handle_t timer = gfx_timer_create(emote_handle, timer_callback, 1000, user_data);

// Control timer
gfx_timer_pause(timer);
gfx_timer_resume(timer);
gfx_timer_reset(timer);
gfx_timer_set_period(timer, new_period_ms);
gfx_timer_set_repeat_count(timer, count);

// Cleanup
gfx_timer_delete(emote_handle, timer);
```

### Thread Safety

All widget operations must be performed within the graphics lock:

```c
gfx_emote_lock(emote_handle);
// Perform widget operations here
gfx_obj_set_pos(obj, x, y);
gfx_label_set_text(label, "New text");
gfx_emote_unlock(emote_handle);
```

## API Reference

The main API is exposed through the `gfx.h` header file, which includes:

- `core/gfx_types.h` - Type definitions and constants
- `core/gfx_core.h` - Core graphics functions
- `core/gfx_timer.h` - Timer and timing utilities
- `core/gfx_obj.h` - Graphics object system
- `widget/gfx_img.h` - Image widget functionality
- `widget/gfx_label.h` - Label widget functionality
- `widget/gfx_anim.h` - Animation framework

## License

This project is licensed under the Apache License 2.0. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit issues and enhancement requests.
