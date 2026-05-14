#!/usr/bin/env python3
# SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
"""
PNG to RGB565A8 C file converter
Converts PNG images to RGB565A8 format with optional byte swapping
RGB565 and Alpha data are stored separately
Supports both C file and binary output formats
Can process single files or batch process all PNG files in a directory
"""

import argparse
import os
import sys
from PIL import Image
import re
import struct
import glob

def rgb888_to_rgb565(r, g, b):
    """Convert RGB888 to RGB565"""
    r = (r >> 3) & 0x1F
    g = (g >> 2) & 0x3F
    b = (b >> 3) & 0x1F
    return (r << 11) | (g << 5) | b

def rgb565_to_bytes(rgb565, swap16=False):
    """Convert RGB565 to bytes, optionally swapping byte order"""
    high_byte = (rgb565 >> 8) & 0xFF
    low_byte = rgb565 & 0xFF

    if swap16:
        return [low_byte, high_byte]
    else:
        return [high_byte, low_byte]

def format_array(data, indent=4, per_line=130):
    """Format data as C array with proper indentation and line breaks"""
    lines = []
    for i in range(0, len(data), per_line):
        line = ', '.join(f'0x{b:02x}' for b in data[i:i + per_line])
        lines.append(' ' * indent + line + ',')
    return '\n'.join(lines)

def generate_c_file(image_path, output_path, var_name, swap16=False):
    """Generate C file from PNG image"""

    # Open and convert image
    try:
        img = Image.open(image_path)
        if img.mode != 'RGBA':
            img = img.convert('RGBA')
    except Exception as e:
        print(f'Error opening image {image_path}: {e}')
        return False

    width, height = img.size
    pixels = list(img.getdata())

    # Convert to RGB565A8 format - separate RGB565 and Alpha data
    rgb565_data = []
    alpha_data = []

    for pixel in pixels:
        r, g, b, a = pixel

        # Convert RGB to RGB565
        rgb565 = rgb888_to_rgb565(r, g, b)

        # Add RGB565 bytes (2 bytes) to RGB565 array
        rgb565_bytes = rgb565_to_bytes(rgb565, swap16)
        rgb565_data.extend(rgb565_bytes)

        # Add Alpha byte (1 byte) to Alpha array
        alpha_data.append(a)

    # Combine RGB565 and Alpha data: RGB565 first, then Alpha
    rgb565a8_data = rgb565_data + alpha_data

    # Generate C file content
    c_content = f"""#include "gfx.h"

const uint8_t {var_name}_map[] = {{
{format_array(rgb565a8_data)}
}};

const gfx_image_dsc_t {var_name} = {{
    .header.cf = GFX_COLOR_FORMAT_RGB565A8,
    .header.magic = C_ARRAY_HEADER_MAGIC,
    .header.w = {width},
    .header.h = {height},
    .data_size = {len(rgb565a8_data)},
    .data = {var_name}_map,
}};
"""

    # Write to file
    try:
        with open(output_path, 'w') as f:
            f.write(c_content)
        print(f'Successfully generated {output_path}')
        print(f'Image size: {width}x{height}')
        print(f'Data size: {len(rgb565a8_data)} bytes')
        print(f'RGB565 data: {len(rgb565_data)} bytes ({width * height * 2} bytes)')
        print(f'Alpha data: {len(alpha_data)} bytes ({width * height} bytes)')
        print(f"Swap16: {'enabled' if swap16 else 'disabled'}")
        return True
    except Exception as e:
        print(f'Error writing file {output_path}: {e}')
        return False

def generate_bin_file(image_path, output_path, swap16=False):
    """Generate binary file from PNG image with header compatible with gfx_image_header_t structure"""

    # Open and convert image
    try:
        img = Image.open(image_path)
        if img.mode != 'RGBA':
            img = img.convert('RGBA')
    except Exception as e:
        print(f'Error opening image {image_path}: {e}')
        return False

    width, height = img.size
    pixels = list(img.getdata())

    # Convert to RGB565A8 format - separate RGB565 and Alpha data
    rgb565_data = []
    alpha_data = []

    for pixel in pixels:
        r, g, b, a = pixel

        # Convert RGB to RGB565
        rgb565 = rgb888_to_rgb565(r, g, b)

        # Add RGB565 bytes (2 bytes) to RGB565 array
        rgb565_bytes = rgb565_to_bytes(rgb565, swap16)
        rgb565_data.extend(rgb565_bytes)

        # Add Alpha byte (1 byte) to Alpha array
        alpha_data.append(a)

    # Combine RGB565 and Alpha data: RGB565 first, then Alpha
    rgb565a8_data = rgb565_data + alpha_data

    # Calculate stride for RGB565A8 format (2 bytes for RGB565 + 1 byte for Alpha = 3 bytes per pixel)
    stride = width * 3

    # Create gfx_image_header_t structure (12 bytes total)
    magic = 0x19  # C_ARRAY_HEADER_MAGIC
    cf = 0x0A  # GFX_COLOR_FORMAT_RGB565A8
    flags = 0x0000  # No special flags
    reserved = 0x0000  # Reserved field

    # Pack gfx_image_header_t as bit fields in 3 uint32_t values
    # First uint32: magic(8) + cf(8) + flags(16)
    header_word1 = (magic & 0xFF) | ((cf & 0xFF) << 8) | ((flags & 0xFFFF) << 16)

    # Second uint32: w(16) + h(16)
    header_word2 = (width & 0xFFFF) | ((height & 0xFFFF) << 16)

    # Third uint32: stride(16) + reserved(16)
    header_word3 = (stride & 0xFFFF) | ((reserved & 0xFFFF) << 16)

    # Pack header structure - use little-endian for ESP32 compatibility
    # Layout: header_word1(4) + header_word2(4) + header_word3(4) = 12 bytes total
    header = struct.pack('<III', header_word1, header_word2, header_word3)

    # Write binary file: header (12 bytes) + image data
    try:
        with open(output_path, 'wb') as f:
            f.write(header)
            f.write(bytes(rgb565a8_data))
        print(f'Successfully generated {output_path}')
        print(f'Image size: {width}x{height}')
        print(f'Header size: {len(header)} bytes')
        print(f'Data size: {len(rgb565a8_data)} bytes')
        print(f'RGB565 data: {len(rgb565_data)} bytes ({width * height * 2} bytes)')
        print(f'Alpha data: {len(alpha_data)} bytes ({width * height} bytes)')
        print(f'Stride: {stride} bytes per row')
        print(f'Data offset: 12 bytes')
        print(f'Total file size: {len(header) + len(rgb565a8_data)} bytes')
        print(f"Swap16: {'enabled' if swap16 else 'disabled'}")
        print(f'Header layout: magic=0x{magic:02x}, cf=0x{cf:02x}, flags=0x{flags:04x}')
        return True
    except Exception as e:
        print(f'Error writing file {output_path}: {e}')
        return False

def process_single_file(input_file, output_dir, bin_format, swap16):
    """Process a single PNG file"""
    # Determine output path and variable name from input filename
    base_name = os.path.splitext(os.path.basename(input_file))[0]

    if bin_format:
        # Output binary file
        output_path = os.path.join(output_dir, f'{base_name}.bin')
        return generate_bin_file(input_file, output_path, swap16)
    else:
        # Output C file
        output_path = os.path.join(output_dir, f'{base_name}.c')
        # Convert to valid C identifier
        var_name = re.sub(r'[^a-zA-Z0-9_]', '_', base_name)
        if var_name[0].isdigit():
            var_name = 'img_' + var_name
        return generate_c_file(input_file, output_path, var_name, swap16)

def find_png_files(input_path):
    """Find all PNG files in the given path"""
    png_files = []

    if os.path.isfile(input_path):
        # Single file
        if input_path.lower().endswith('.png'):
            png_files.append(input_path)
        else:
            print("Warning: Input file doesn't have .png extension")
            png_files.append(input_path)
    elif os.path.isdir(input_path):
        # Directory - find all PNG files
        png_pattern = os.path.join(input_path, '*.png')
        png_files = glob.glob(png_pattern)

        # Also search in subdirectories
        png_pattern_recursive = os.path.join(input_path, '**', '*.png')
        png_files.extend(glob.glob(png_pattern_recursive, recursive=True))

        # Remove duplicates and sort
        png_files = sorted(list(set(png_files)))

    return png_files

def main():
    parser = argparse.ArgumentParser(description='Convert PNG to RGB565A8 format')
    parser.add_argument('input', help='Input PNG file path or directory path')
    parser.add_argument('--output', '-o', help='Output directory (default: current directory)')
    parser.add_argument('--bin', action='store_true', help='Output binary format instead of C file')
    parser.add_argument('--swap16', action='store_true', help='Enable byte swapping for RGB565')

    args = parser.parse_args()

    # Validate input path
    if not os.path.exists(args.input):
        print(f"Error: Input path '{args.input}' does not exist")
        return 1

    # Set output directory
    output_dir = args.output if args.output else '.'
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Find all PNG files
    png_files = find_png_files(args.input)

    if not png_files:
        print(f"No PNG files found in '{args.input}'")
        return 1

    print(f'Found {len(png_files)} PNG file(s) to process:')
    for png_file in png_files:
        print(f'  - {png_file}')
    print()

    # Process each PNG file
    success_count = 0
    for png_file in png_files:
        print(f'Processing: {png_file}')
        if process_single_file(png_file, output_dir, args.bin, args.swap16):
            success_count += 1
        print()  # Add blank line between files

    print(f'Processing complete: {success_count}/{len(png_files)} files processed successfully')

    if success_count == len(png_files):
        return 0
    else:
        return 1

if __name__ == '__main__':
    sys.exit(main())
