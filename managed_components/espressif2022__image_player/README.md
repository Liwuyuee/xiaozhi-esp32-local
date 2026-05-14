# Image Player

## Introduction
`image_player` is a lightweight and efficient image rendering component designed for embedded systems. It enables seamless integration of various image formats into your projects. This module ensures high performance and flexibility for modern embedded applications that require efficient image playback and rendering.

[![Component Registry](https://components.espressif.com/components/espressif2022/image_player/badge.svg)](https://components.espressif.com/components/espressif2022/image_player)


## Dependencies

1. **ESP-IDF**  
   Ensure your project includes ESP-IDF 5.0 or higher. Refer to the [ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/) for setup instructions.

## Scripts

### GIF to AAF Converter (`gif_to_aaf.py`)
This script converts GIF animations into AAF format.

#### Usage
```bash
python gif_to_aaf.py <input_folder> <output_folder> --split <split_height> --depth <bit_depth> [--enable-huffman]
```

#### Parameters
- `input_folder`: Directory containing GIF files to process
- `output_folder`: Directory where processed files will be saved
- `--split`: Height of each split block (must be a positive integer)
- `--depth`: Bit depth (4 for 4-bit grayscale, 8 for 8-bit color)
- `--enable-huffman`: Optional flag to enable Huffman compression (default: disabled)

#### Example
```bash
# Using only RLE compression
python gif_to_aaf.py ./gifs ./output --split 16 --depth 4

# Using both RLE and Huffman compression
python gif_to_aaf.py ./gifs ./output --split 16 --depth 4 --enable-huffman
```

#### Features
- Automatically detects and handles duplicate frames
- Optimizes storage by referencing repeated frames
- Generates a single asset file with all frames
- Supports both 4-bit and 8-bit color depth
- Includes compression for efficient storage
- Supports both RLE and Huffman compression methods
