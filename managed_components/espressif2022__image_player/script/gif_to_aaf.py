import numpy as np
import struct
import os
import sys
from PIL import Image
import math
from sklearn.cluster import KMeans
import time
from multiprocessing import Pool, cpu_count
import heapq
from collections import defaultdict, Counter, namedtuple
import argparse
from dataclasses import dataclass
import re

# Define Huffman tree node
class Node:
    def __init__(self, freq, char, left, right):
        self.freq = freq
        self.char = char
        self.left = left
        self.right = right
    
    def __lt__(self, other):  # For heapq comparison
        return self.freq < other.freq

@dataclass
class PackModelsConfig:
    target_path: str
    image_file: str
    assets_path: str

def compute_checksum(data):
    """Compute a simple checksum of the data."""
    return sum(data) & 0xFFFFFFFF

def get_frame_info(filename):
    """Extract frame name and number from filename."""
    match = re.search(r'(.+)_(\d+)\.sbmp$', filename)
    if match:
        return match.group(1), int(match.group(2))
    return None, 0

def sort_key(filename):
    """Sort files by frame name and number."""
    name, number = get_frame_info(filename)
    return (name, number) if name else ('', 0)

def pack_assets(config: PackModelsConfig):
    """
    Pack models based on the provided configuration.
    """
    target_path = config.target_path
    out_file = config.image_file
    assets_path = config.assets_path

    merged_data = bytearray()
    frame_info_list = []  # List of (frame_number, offset, size, is_repeated, original_frame)
    frame_map = {}  # Store frame offsets and sizes by frame number

    # First pass: process all frames and collect information
    file_list = sorted(os.listdir(target_path), key=sort_key)
    for filename in file_list:
        if not filename.lower().endswith('.sbmp'):
            continue

        file_path = os.path.join(target_path, filename)
        try:
            file_size = os.path.getsize(file_path)
            frame_name, frame_number = get_frame_info(filename)
            if not frame_name:
                print(f"Invalid filename format: {filename}")
                continue
            
            # Read file content to check for _R prefix
            with open(file_path, 'rb') as bin_file:
                bin_data = bin_file.read()
                if not bin_data:
                    print(f"Empty file '{filename}'")
                    continue
                
                # Check if this is a repeated frame
                if bin_data.startswith(b'_R'):
                    # Extract the original frame name from content
                    try:
                        # Format: _R + filename_length(1 byte) + original_filename
                        filename_length = bin_data[2]  # Get filename length (1 byte)
                        original_frame = bin_data[3:3+filename_length].decode('utf-8')
                        original_frame_name, original_frame_num = get_frame_info(original_frame)
                        
                        # print(f"Repeated {frame_name}_{frame_number} referencing {original_frame_name}_{original_frame_num}")
                        frame_info_list.append((frame_number, 0, file_size, True, original_frame_num))
                    except (ValueError, IndexError) as e:
                        print(f"Invalid repeated frame format in {filename}: {str(e)}")
                    continue

                # Process original frame
                # print(f"Original {frame_name}_{frame_number} with size {file_size} bytes")
                # Add 0x5A5A prefix to merged_data
                merged_data.extend(b'\x5A' * 2)
                merged_data.extend(bin_data)
                # Update frame info with correct offset and size (including prefix)
                #                   frame_number,     offset,                           size,          is_repeated, original_frame_num
                frame_info_list.append((frame_number, len(merged_data) - file_size - 2, file_size + 2, False, None))
                frame_map[frame_number] = (len(merged_data) - file_size - 2, file_size + 2)

        except IOError as e:
            print(f"Could not read file '{filename}': {str(e)}")
            continue
        except Exception as e:
            print(f"Unexpected error processing file '{filename}': {str(e)}")
            continue

    # Second pass: update repeated frame offsets and recalculate
    file_info_list = []
    new_merged_data = bytearray()
    new_offset = 0

    # First add all original frames to new_merged_data
    for frame_number, offset, size, is_repeated, original_frame in frame_info_list:
        if not is_repeated:
            frame_data = merged_data[offset:offset+size]
            new_merged_data.extend(frame_data)
            # Align to 4 bytes
            # padding = (4 - (len(new_merged_data) % 4)) % 4
            # if padding > 0:
            #     new_merged_data.extend(b'\x00' * padding)
            # Update frame map with new offset
            frame_map[frame_number] = (new_offset, size)
            file_info_list.append((new_offset, size))
            new_offset = len(new_merged_data)
        else:
            if original_frame in frame_map:
                orig_offset, orig_size = frame_map[original_frame]
                file_info_list.append((orig_offset, orig_size))

    total_files = len(file_info_list)
    if total_files == 0:
        print("No .sbmp files found to process")
        return

    mmap_table = bytearray()
    for i, (offset, file_size) in enumerate(file_info_list):
        mmap_table.extend(file_size.to_bytes(4, byteorder='little'))
        mmap_table.extend(offset.to_bytes(4, byteorder='little'))
        # print(f"[{i + 1}] frame_data: 0x{offset:08x} ({file_size})")

    # Align mmap_table to 4 bytes
    padding = (4 - (len(mmap_table) % 4)) % 4
    if padding > 0:
        mmap_table.extend(b'\x00' * padding)

    combined_data = mmap_table + new_merged_data
    combined_checksum = compute_checksum(combined_data)
    combined_data_length = len(combined_data).to_bytes(4, byteorder='little')
    header_data = total_files.to_bytes(4, byteorder='little') + combined_checksum.to_bytes(4, byteorder='little')
    final_data = header_data + combined_data_length + combined_data

    try:
        with open(out_file, 'wb') as output_bin:
            output_bin.write(final_data)
        print(f"\nSuccessfully packed {total_files} .sbmp files into {out_file}")
        print(f"Total size: {len(final_data)} bytes")
        print(f"Header size: {len(header_data)} bytes")
        print(f"Table size: {len(mmap_table)} bytes")
        print(f"Data size: {len(new_merged_data)} bytes")
    except IOError as e:
        print(f"Failed to write output file: {str(e)}")
    except Exception as e:
        print(f"Unexpected error writing output file: {str(e)}")

def process_merge(input_dir):
    """Process all .sbmp files in the directory and group them by name."""
    # Group files by their base name
    file_groups = defaultdict(list)
    
    for filename in os.listdir(input_dir):
        if filename.lower().endswith('.sbmp'):
            name, _ = get_frame_info(filename)
            if name:
                file_groups[name].append(filename)
    
    # Process each group
    for name, files in file_groups.items():
        if not files:
            continue
            
        # Create output filename based on the group name
        output_file = os.path.join(input_dir, f"{name}.aaf")
        
        # Create a temporary directory for this group
        temp_dir = os.path.join(input_dir, f"temp_{name}")
        os.makedirs(temp_dir, exist_ok=True)
        
        # Copy files to temporary directory
        for file in files:
            src = os.path.join(input_dir, file)
            dst = os.path.join(temp_dir, file)
            os.link(src, dst)  # Use hard link to save space
        
        # Process the group
        config = PackModelsConfig(
            target_path=temp_dir,
            image_file=output_file,
            assets_path=temp_dir
        )
        
        pack_assets(config)
        
        # Clean up temporary directory
        for file in files:
            os.remove(os.path.join(temp_dir, file))
        os.rmdir(temp_dir)


def floyd_steinberg_dithering(img, bit_depth=4):
    """Apply Floyd-Steinberg dithering and quantize to specified bit depth."""
    pixels = np.array(img, dtype=np.int32)
    height, width = pixels.shape
    
    # Calculate quantization levels based on bit depth
    num_levels = 2 ** bit_depth
    step = 256 // (num_levels - 1)
    
    for y in range(height - 1):
        for x in range(1, width - 1):
            old_pixel = pixels[y, x]
            new_pixel = round(old_pixel / step) * step
            pixels[y, x] = new_pixel
            error = old_pixel - new_pixel
            pixels[y, x + 1] += error * 7 / 16
            pixels[y + 1, x - 1] += error * 3 / 16
            pixels[y + 1, x] += error * 5 / 16
            pixels[y + 1, x + 1] += error * 1 / 16

    np.clip(pixels, 0, 255, out=pixels)
    return pixels.astype(np.uint8)


def generate_palette(bit_depth=4):
    """Generate a grayscale palette based on bit depth."""
    num_colors = 2 ** bit_depth
    palette = []
    for i in range(num_colors):
        level = int(i * 255 / (num_colors - 1))
        palette.append((level, level, level, 0))  # (B, G, R, 0)
    return palette


def process_row(args):
    """Process a single row of pixels."""
    y, pixels, width, bit_depth, palette, row_padded = args
    row = []
    processed = [False] * width  # Track processed pixels
    
    if bit_depth == 4:
        for x in range(0, width, 2):
            if processed[x]:  # Skip if already processed
                continue
                
            p1 = pixels[y, x] // 17  # 0-15
            if x + 1 < width:
                p2 = pixels[y, x + 1]
                # Check if next pixel is the same
                if p2 == p1:
                    processed[x + 1] = True  # Mark as processed
            else:
                p2 = 0
            byte = (p1 << 4) | p2
            row.append(byte)
    else:  # 8-bit
        for x in range(width):
            if processed[x]:  # Skip if already processed
                continue
                
            color = pixels[y, x]
            index = find_closest_color(color, palette)
            row.append(index)
            
            # Check subsequent pixels for duplicates
            for next_x in range(x + 1, width):
                if pixels[y, next_x] == color:
                    processed[next_x] = True  # Mark as processed
                    row.append(index)
    
    while len(row) < row_padded:
        row.append(0)  # padding
    return row


def save_bmp(filename, pixels, bit_depth=4):
    """Save a numpy array as a BMP file with specified bit depth."""
    if bit_depth == 8:
        # For 8-bit color images, use RGB channels
        height, width, _ = pixels.shape
    else:
        # For 4-bit grayscale images
        height, width = pixels.shape

    bits_per_pixel = bit_depth
    bytes_per_pixel = bits_per_pixel // 8
    row_size = (width * bits_per_pixel + 7) // 8
    row_padded = (row_size + 3) & ~3  # 4-byte align each row

    # BMP Header (14 bytes)
    bfType = b'BM'
    bfSize = 14 + 40 + (2 ** bits_per_pixel) * 4 + row_padded * height
    bfReserved1 = 0
    bfReserved2 = 0
    bfOffBits = 14 + 40 + (2 ** bits_per_pixel) * 4

    bmp_header = struct.pack('<2sIHHI', bfType, bfSize, bfReserved1, bfReserved2, bfOffBits)

    # DIB Header (BITMAPINFOHEADER, 40 bytes)
    biSize = 40
    biWidth = width
    biHeight = height
    biPlanes = 1
    biBitCount = bits_per_pixel
    biCompression = 0
    biSizeImage = row_padded * height
    biXPelsPerMeter = 3780
    biYPelsPerMeter = 3780
    biClrUsed = 2 ** bits_per_pixel
    biClrImportant = 2 ** bits_per_pixel

    dib_header = struct.pack('<IIIHHIIIIII',
                             biSize, biWidth, biHeight, biPlanes, biBitCount,
                             biCompression, biSizeImage,
                             biXPelsPerMeter, biYPelsPerMeter,
                             biClrUsed, biClrImportant)

    # Generate appropriate palette based on bit depth
    if bit_depth == 8:
        # For 8-bit color images, generate a color palette
        palette = generate_color_palette(pixels)
    else:
        # For 4-bit grayscale images, use grayscale palette
        palette = generate_palette(bit_depth)

    palette_data = b''.join(struct.pack('<BBBB', *color) for color in palette)

    # Pixel Data
    # Start timing
    start_time = time.time()
    
    # Prepare parallel processing arguments
    process_args = [(y, pixels, width, bit_depth, palette, row_padded) 
                   for y in range(height - 1, -1, -1)]
    
    # Use process pool for parallel processing
    with Pool(processes=cpu_count()) as pool:
        rows = pool.map(process_row, process_args)
    
    # Merge processing results
    pixel_data = bytearray()
    for row in rows:
        pixel_data.extend(row)

    # End timing and print
    end_time = time.time()
    execution_time = end_time - start_time
    # print(f"Processing completed: Image size {width}x{height}, Total time: {execution_time:.3f} seconds")

    with open(filename, 'wb') as f:
        f.write(bmp_header)
        f.write(dib_header)
        f.write(palette_data)
        f.write(pixel_data)
    print(f"{os.path.basename(filename)}")


def generate_color_palette(pixels):
    """Generate a 256-color palette from the image using median cut algorithm."""
    # Reshape pixels to 2D array of RGB values
    pixels_2d = pixels.reshape(-1, 3)
    
    # Count unique colors
    unique_colors = np.unique(pixels_2d, axis=0)
    num_colors = min(len(unique_colors), 256)
    
    if num_colors < 256:
        # If we have fewer than 256 unique colors, use them directly
        colors = unique_colors
    else:
        # Use k-means clustering to find representative colors
        kmeans = KMeans(n_clusters=num_colors, random_state=0, n_init=10).fit(pixels_2d)
        colors = kmeans.cluster_centers_.astype(np.uint8)
    
    # Convert to palette format (B, G, R, A)
    palette = []
    for color in colors:
        palette.append((color[2], color[1], color[0], 255))  # BGR format
    
    # Pad palette to 256 colors if necessary
    while len(palette) < 256:
        palette.append((0, 0, 0, 255))
    
    return palette


def find_closest_color(color, palette):
    """Find the index of the closest color in the palette."""
    min_dist = float('inf')
    closest_index = 0
    
    for i, palette_color in enumerate(palette):
        # Calculate Euclidean distance in RGB space using uint8 arithmetic
        r_diff = int(color[0]) - int(palette_color[2])
        g_diff = int(color[1]) - int(palette_color[1])
        b_diff = int(color[2]) - int(palette_color[0])
        dist = r_diff * r_diff + g_diff * g_diff + b_diff * b_diff
        
        if dist < min_dist:
            min_dist = dist
            closest_index = i
    
    return closest_index


def convert_gif_to_bmp(gif_path, output_dir, bit_depth=4):
    """Convert GIF frames to BMPs with specified bit depth."""
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    base_name = os.path.splitext(os.path.basename(gif_path))[0]

    with Image.open(gif_path) as im:
        frame = 0
        try:
            while True:
                if bit_depth == 8:
                    # For 8-bit, convert to palette mode
                    frame_image = im.convert('P', palette=Image.ADAPTIVE, colors=256)
                    output_path = os.path.join(output_dir, f"{base_name}_{frame:04d}.bmp")
                    frame_image.save(output_path, 'BMP')
                else:
                    # For 4-bit, convert to grayscale and dither
                    gray_frame = im.convert('L')
                    dithered_pixels = floyd_steinberg_dithering(gray_frame, bit_depth)
                    output_path = os.path.join(output_dir, f"{base_name}_{frame:04d}.bmp")
                    save_bmp(output_path, dithered_pixels, bit_depth)
                
                frame += 1
                im.seek(frame)
        except EOFError:
            pass


def create_header(width, height, splits, split_height, lenbuf, ext, bit_depth=4):
    """Creates the header for the output file based on the format.
    
    Args:
        width: Image width
        height: Image height
        splits: Number of splits
        split_height: Height of each split
        lenbuf: List of split lengths
        ext: File extension
        bit_depth: Bit depth (4 or 8)
    """
    header = bytearray()

    if ext.lower() == '.bmp':
        header += bytearray('_S'.encode('UTF-8'))

    # 6 BYTES VERSION
    header += bytearray(('\x00V1.00\x00').encode('UTF-8'))
    
    # 1 BYTE BIT DEPTH
    header += bytearray([bit_depth])

    # WIDTH 2 BYTES
    header += width.to_bytes(2, byteorder='little')

    # HEIGHT 2 BYTES
    header += height.to_bytes(2, byteorder='little')

    # NUMBER OF ITEMS 2 BYTES
    header += splits.to_bytes(2, byteorder='little')

    # SPLIT HEIGHT 2 BYTES
    header += split_height.to_bytes(2, byteorder='little')

    for item_len in lenbuf:
        # LENGTH 2 BYTES
        header += item_len.to_bytes(2, byteorder='little')

    return header


def rte_compress(data):
    """Simple RTE (Run-Time Encoding) compression: [count, value]"""
    if not data:
        return bytearray()

    compressed = bytearray()
    prev = data[0]
    count = 1

    for b in data[1:]:
        if b == prev and count < 255:
            count += 1
        else:
            compressed.extend([count, prev])
            prev = b
            count = 1

    # Don't forget the last run
    compressed.extend([count, prev])
    return compressed


def generate_palette_from_image(im, bit_depth=4):
    """Extracts or generates a palette based on bit depth.
    
    Args:
        im: PIL Image object
        bit_depth: Bit depth for the palette (4 or 8)
    
    Returns:
        tuple: (palette_bytes, palette_list)
            - palette_bytes: Byte array containing the palette
            - palette_list: List of RGB tuples
    """
    num_colors = 2 ** bit_depth
    palette_bytes = bytearray()
    
    if bit_depth == 8:
        # For 8-bit color images
        if im.mode == 'RGB':
            # Convert to numpy array for color analysis
            pixels = np.array(im)
            # Count unique colors
            unique_colors = np.unique(pixels.reshape(-1, 3), axis=0)
            num_unique = min(len(unique_colors), 256)
            
            if num_unique < 256:
                # If we have fewer than 256 unique colors, use them directly
                colors = unique_colors
            else:
                # Use k-means clustering to find representative colors
                kmeans = KMeans(n_clusters=num_unique, random_state=0, n_init=10).fit(pixels.reshape(-1, 3))
                colors = kmeans.cluster_centers_.astype(np.uint8)
            
            # Convert colors to palette format (B, G, R, A)
            for color in colors:
                palette_bytes.extend([color[2], color[1], color[0], 255])  # BGR format
            
            # Pad palette to 256 colors if necessary
            while len(palette_bytes) < 256 * 4:
                palette_bytes.extend([0, 0, 0, 255])
        else:
            # If not RGB, convert to RGB first
            im = im.convert('RGB')
            return generate_palette_from_image(im, bit_depth)
    else:
        # For 4-bit grayscale images
        if im.mode == 'P':
            # If image already has a palette, use it
            palette = im.getpalette()
            if palette is not None:
                # Extract the first `num_colors` colors from the palette
                palette = palette[:num_colors * 3]  # Each color is represented by 3 bytes (R, G, B)
                for i in range(0, len(palette), 3):
                    r, g, b = palette[i:i + 3]
                    palette_bytes.extend([r, g, b, 255])  # Add an alpha channel value of 255
        else:
            # Generate a grayscale palette based on bit depth
            for i in range(num_colors):
                level = int(i * 255 / (num_colors - 1))
                palette_bytes.extend([level, level, level, 255])  # (B, G, R, A)
    
    # Create palette list for color matching
    palette_list = []
    for i in range(0, len(palette_bytes), 4):
        b, g, r, _ = palette_bytes[i:i + 4]
        palette_list.append((r, g, b))
    
    return palette_bytes, palette_list


def find_palette_index(pixel_value, palette):
    """Finds the closest palette index for a pixel value."""
    # Calculate the squared difference for each color channel (R, G, B)
    def color_distance_squared(c1, c2):
        return sum((c1[i] - c2[i]) ** 2 for i in range(3))

    # Find the index of the closest color in the palette
    closest_index = min(range(len(palette)), key=lambda i: color_distance_squared(
        (pixel_value, pixel_value, pixel_value), palette[i]))

    # Debugging: Print the distance for each palette index
    # for i in range(len(palette)):
    #     diff = color_distance_squared((pixel_value, pixel_value, pixel_value), palette[i])
    #     print(f"Palette index {i}, diff: {diff}")

    return closest_index


def build_huffman_tree(data):
    """Build Huffman tree from data using frequency analysis.
    
    Args:
        data: Input data to build tree from
        
    Returns:
        Node: Root node of the Huffman tree
    """
    # Count frequency of each byte
    freq = Counter(data)
    
    # Create leaf nodes for each unique byte
    heap = [Node(f, c, None, None) for c, f in freq.items()]
    heapq.heapify(heap)
    
    # Build tree by merging nodes
    while len(heap) > 1:
        node1 = heapq.heappop(heap)
        node2 = heapq.heappop(heap)
        merged = Node(node1.freq + node2.freq, None, node1, node2)
        heapq.heappush(heap, merged)
    
    root = heap[0] if heap else None
    
    # Print the tree structure
    # print("\nHuffman Tree Structure:")
    # print_tree(root)
    # print()
    
    return root


def build_code_map(node, prefix="", code_map=None):
    """Generate Huffman code map by traversing the tree.
    
    Args:
        node: Current node in the tree
        prefix: Current code prefix
        code_map: Dictionary to store the codes
        
    Returns:
        dict: Mapping of bytes to their Huffman codes
    """
    if code_map is None:
        code_map = dict()
    if node is None:
        return code_map
    if node.char is not None:
        code_map[node.char] = prefix
    build_code_map(node.left, prefix + "0", code_map)
    build_code_map(node.right, prefix + "1", code_map)
    return code_map


def huffman_compress(data):
    """Compress data using Huffman coding.
    
    Args:
        data: Input data to compress
        
    Returns:
        tuple: (compressed_data, dict_size, dict_bytes)
            - compressed_data: Compressed data as bytes
            - dict_size: Number of entries in the dictionary
            - dict_bytes: Dictionary data for decompression
    """
    if not data:
        return bytearray(), 0, None
    
    # Build Huffman tree and get encoding dictionary
    tree = build_huffman_tree(data)
    code_map = build_code_map(tree)
    
    # Print code map for debugging
    # print("\nHuffman Code Map:")
    # for char, code in sorted(code_map.items()):
    #     print(f"  '{chr(char)}' ({char:02x}) -> {code}")
    # print()
    
    # Encode data
    encoded = ''.join(code_map[byte] for byte in data)
    
    # Pad encoded string to multiple of 8
    padding = (8 - len(encoded) % 8) % 8
    encoded += '0' * padding
    
    # Convert to bytes
    result = bytearray()
    for i in range(0, len(encoded), 8):
        byte = encoded[i:i+8]
        result.append(int(byte, 2))
    
    # Convert dictionary to bytes
    dict_bytes = bytearray()
    dict_bytes.append(padding)  # Store padding bits at the start of dictionary
    for byte, code in code_map.items():
        dict_bytes.extend([byte, len(code)])  # Store byte value and code length
        # Convert code string to bytes
        code_bytes = int(code, 2).to_bytes((len(code) + 7) // 8, byteorder='big')
        dict_bytes.extend(code_bytes)
    
    # Print debug information
    # print(f"Original data: {' '.join(f'{b:02x}' for b in data[:30])}")
    # print(f"Encoded bits: {encoded[:100]}")
    # print(f"Compressed data: {' '.join(f'{b:02x}' for b in result[:30])}")
    # print(f"Dictionary bytes: {' '.join(f'{b:02x}' for b in dict_bytes[:30])}")
    # print(f"Encoded length: {len(encoded)} bits")
    # print(f"Padding: {padding} bits")
    
    return result, len(code_map), dict_bytes


def print_tree(node, prefix="", is_left=True):
    """Print the Huffman tree structure.
    
    Args:
        node: Current node to print
        prefix: Prefix for the current level
        is_left: Whether this node is a left child
    """
    if node is None:
        return
        
    # Print current node
    print(f"{prefix}{'└── ' if is_left else '┌── '}", end="")
    if node.char is not None:
        print(f"'{chr(node.char)}' ({node.char:02x})")
    else:
        print("•")
        
    # Print children
    if node.left is not None:
        print_tree(node.left, prefix + ("    " if is_left else "│   "), True)
    if node.right is not None:
        print_tree(node.right, prefix + ("    " if is_left else "│   "), False)


def huffman_decode(data, dict_bytes):
    """Decompress data using Huffman coding.
    
    Args:
        data: Compressed data
        dict_bytes: Dictionary data for decompression
        
    Returns:
        bytearray: Decompressed data
    """
    if not data or not dict_bytes:
        return bytearray()
    
    # Print debug information
    print(f"\nCompressed data: {' '.join(f'{b:02x}' for b in data[:30])}")
    print(f"Compressed data length: {len(data)} bytes")
    print(f"Dictionary data: {' '.join(f'{b:02x}' for b in dict_bytes[:30])}")
    print(f"Dictionary data length: {len(dict_bytes)} bytes")
    
    # Get padding bits from dictionary
    padding = dict_bytes[0]
    dict_bytes = dict_bytes[1:]  # Remove padding info from dictionary
    print(f"Padding bits: {padding}")
    
    # Rebuild Huffman tree from dictionary
    root = Node(0, None, None, None)
    current = root
    i = 0
    
    while i < len(dict_bytes):
        # Read byte value and code length
        byte_val = dict_bytes[i]
        code_len = dict_bytes[i + 1]
        i += 2
        
        # Read code bytes
        code_bytes = dict_bytes[i:i + (code_len + 7) // 8]
        i += (code_len + 7) // 8
        
        # Convert code bytes to binary string
        code = bin(int.from_bytes(code_bytes, byteorder='big'))[2:].zfill(code_len)
        
        # Build tree path for this code
        for bit in code:
            if bit == '0':
                if current.left is None:
                    current.left = Node(0, None, None, None)
                current = current.left
            else:
                if current.right is None:
                    current.right = Node(0, None, None, None)
                current = current.right
        
        # Set leaf node value
        current.char = byte_val
        current = root

    # print_tree(root)
    
    # Decode data using the tree
    decoded = bytearray()
    current = root
    
    # Convert data to binary string
    binary = ''.join(bin(b)[2:].zfill(8) for b in data)
    print(f"Binary data length: {len(binary)} bits")
    
    # Remove padding bits from the end
    if padding > 0:
        binary = binary[:-padding]
        print(f"Binary data length after removing padding: {len(binary)} bits")
    
    # Traverse tree using bits
    for bit in binary:
        if bit == '0':
            current = current.left
        else:
            current = current.right
            
        # If we reached a leaf node, add its value to decoded data
        if current.char is not None:
            decoded.append(current.char)
            current = root
    
    print(f"Decoded data length: {len(decoded)} bytes")
    return decoded


def process_block(args):
    """Process a single block of pixels."""
    top, bottom, width, height, pixels, bit_depth = args
    block_height = bottom - top
    block_data = bytearray()
    
    for y in range(block_height):
        row_start = (top + y) * width
        if bit_depth == 4:
            # Pack two pixels into one byte
            for x in range(0, width, 2):
                p1 = pixels[row_start + x] & 0x0F  # Ensure p1 is 0-15
                if x + 1 < width:
                    p2 = pixels[row_start + x + 1] & 0x0F  # Ensure p2 is 0-15
                else:
                    p2 = 0
                packed_byte = ((p1 & 0x0F) << 4) | (p2 & 0x0F)  # Ensure result is 0-255
                block_data.append(packed_byte)
        else:  # 8-bit
            # Use pixel value directly as index
            for x in range(width):
                block_data.append(pixels[row_start + x] & 0xFF)  # Ensure value is 0-255
    
    # RTE compress this block
    rte_compressed = rte_compress(block_data)

    # Use test string for Huffman compression
    # test_string = "123456789"
    # rte_compressed = bytearray(test_string.encode('ascii'))
    
    # Huffman compress this block
    huffman_compressed, dict_size, dict_bytes = huffman_compress(rte_compressed)
    
    # Print compression comparison
    rte_size = len(rte_compressed)
    huffman_size = len(huffman_compressed) + len(dict_bytes)  # Include dictionary size
    original_size = len(block_data)
    # print(f"huffman_compressed: {huffman_compressed}")
    
    # print(f"Block {top}-{bottom} | Original: {original_size}B | RTE: {rte_size}B | Huffman: {huffman_size}B | Dict: {dict_size} entries")

    # 解码数据
    # decoded_data = huffman_decode(huffman_compressed, dict_bytes)    
    # print(f"Decoded:{' '.join(f'{b:02x}' for b in decoded_data[:30])}")
    # print(f"Decoded string: {decoded_data.decode('ascii', errors='replace')}")
    
    # return rte_compressed, huffman_compressed, dict_bytes, dict_size  # Return compressed data and dictionary
    block_original_size = len(block_data)  # Original uncompressed size
    
    return rte_compressed, huffman_compressed, dict_bytes, dict_size, block_original_size


def split_bmp(im, block_size, input_dir=None, bit_depth=4, enable_huffman=False):
    """Splits grayscale image into raw bitmap blocks with RTE compression.
    
    Args:
        im: PIL Image object (BMP file)
        block_size: Height of each block
        input_dir: Input directory (optional)
        bit_depth: Bit depth for the image (4 or 8)
        enable_huffman: Whether to enable Huffman compression
    
    Returns:
        tuple: (width, height, splits, palette_bytes, split_data, lenbuf)
    """
    width, height = im.size
    splits = math.ceil(height / block_size) if block_size else 1

    # Read palette from file
    palette_size = 2 ** bit_depth * 4  # Each palette entry is 4 bytes (B,G,R,A)
    with open(im.filename, 'rb') as f:
        f.seek(54)  # Skip BMP header (14 + 40 bytes)
        palette_bytes = f.read(palette_size)
        
        # Print palette in R:XX G:XX B:XX A:XX format
        # for i in range(0, len(palette_bytes), 4):
        #     b, g, r, a = palette_bytes[i:i+4]
        #     print(f"R:{r:02X} G:{g:02X} B:{b:02X} A:{a:02X}")

    # Read pixel data
    pixels = list(im.getdata())
    row_size = (width * bit_depth + 7) // 8
    row_padded = (row_size + 3) & ~3  # 4-byte align each row

    # Calculate original data size
    original_size = row_padded * height

    # Prepare parallel processing arguments
    process_args = []
    for i in range(splits):
        top = i * block_size
        bottom = min((i + 1) * block_size, height)
        process_args.append((top, bottom, width, height, pixels, bit_depth))

    # Use process pool for parallel processing
    split_data = bytearray()
    total_rte_size = 0
    total_huffman_size = 0
    total_rte_original = 0
    total_huffman_original = 0
    total_saved_size = 0
    lenbuf = []
    with Pool(processes=cpu_count()) as pool:
        compressed_blocks = pool.map(process_block, process_args)
        
        # Collect processing results
        for rte_block, huffman_block, dict_bytes, dict_size, block_original_size in compressed_blocks:
            rte_size = len(rte_block)
            huffman_size = len(huffman_block) + len(dict_bytes)  # Include dictionary size
            
            # Choose compression method based on enable_huffman flag and size comparison
            if enable_huffman and huffman_size < rte_size:
                split_data.append(1)  # Huffman identifier
                split_data.extend(len(dict_bytes).to_bytes(2, byteorder='little'))  # Dictionary size (2 bytes)
                split_data.extend(dict_bytes)  # Dictionary data
                split_data.extend(huffman_block)  # Compressed data
                lenbuf.append(len(huffman_block) + len(dict_bytes) + 3)  # +3 for identifier and dict size
                total_huffman_size += huffman_size + 3
                total_huffman_original += block_original_size
                total_saved_size += rte_size - huffman_size
            else:
                split_data.append(0)  # RTE identifier
                split_data.extend(rte_block)
                lenbuf.append(len(rte_block) + 1)  # +1 for identifier
                total_rte_size += rte_size + 1
                total_rte_original += block_original_size

    # Calculate compression ratios
    final_size = len(split_data)
    rte_ratio = (1 - total_rte_size / total_rte_original) * 100 if total_rte_original > 0 else 0
    haffman_ratio = (1 - total_huffman_size / total_huffman_original) * 100 if total_huffman_original > 0 else 0
    final_ratio = (1 - final_size / original_size) * 100

    # Print statistics in one line with colored ratios
    color_rte = '\033[31m' if rte_ratio < 0 else '\033[32m'
    color_huffman = '\033[31m' if haffman_ratio < 0 else '\033[32m'
    ratio_color_total = '\033[31m' if final_ratio < 0 else '\033[32m'

    print(f"Frame {width:4d}x{height:4d} | Splits: {splits:3d}")
    print(f"RTE:     {total_rte_size:8d}B | Ratio: {color_rte}{rte_ratio:+.2f}%\033[0m | Original: {total_rte_original:8d}B")
    if enable_huffman:
        print(f"Huffman: {total_huffman_size:8d}B | Ratio: {color_huffman}{haffman_ratio:+.2f}%\033[0m | Original: {total_huffman_original:8d}B | Saved: {total_saved_size:8d}B")
    print(f"Total:   {final_size:8d}B | Ratio: {ratio_color_total}{final_ratio:+.2f}%\033[0m | Original: {original_size:8d}B")

    return width, height, splits, palette_bytes, split_data, lenbuf


def save_image(output_file_path, header, split_data, palette_bytes):
    """Save the final packaged image with header, palette, and split data."""
    with open(output_file_path, 'wb') as f:
        f.write(header)
        # print("Header saved.")

        # Write the palette
        f.write(palette_bytes)
        # print("Palette saved.")

        # Write the split data
        f.write(split_data)
        # print("Split data saved.")


def process_bmp(input_file, output_file, split_height, bit_depth=4, enable_huffman=False):
    """Main function to process the image and save it as the packaged file."""
    try:
        SPLIT_HEIGHT = int(split_height)
        if SPLIT_HEIGHT <= 0:
            raise ValueError('Height must be a positive integer')
    except ValueError as e:
        print('Error:', e)
        sys.exit(1)

    input_dir, input_filename = os.path.split(input_file)
    base_filename, ext = os.path.splitext(input_filename)
    OUTPUT_FILE_NAME = base_filename
    # print(f'Processing {input_filename}')
    # print(f'Input directory: {input_dir}')
    # print(f'Output file name: {OUTPUT_FILE_NAME}')
    # print(f'File extension: {ext}')

    try:
        im = Image.open(input_file)
    except Exception as e:
        print('Error:', e)
        sys.exit(0)

    # Split the image into blocks based on the specified split height
    width, height, splits, palette_bytes, split_data, lenbuf = split_bmp(im, SPLIT_HEIGHT, input_dir, bit_depth, enable_huffman)

    # Create header based on image properties
    header = create_header(width, height, splits, SPLIT_HEIGHT, lenbuf, ext, bit_depth)

    # Save the final packaged file
    output_file_path = os.path.join(output_file, OUTPUT_FILE_NAME + '.sbmp')
    save_image(output_file_path, header, split_data, palette_bytes)

    print('Completed', base_filename)


def process_split(input_dir, output_dir, split_height, bit_depth=4, enable_huffman=False):
    """Process all BMP images in the input directory."""
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Dictionary to store processed image hashes and their corresponding output filenames
    # Key: (prefix, hash), Value: filename
    processed_images = {}

    # Loop through all files in the input directory
    for filename in os.listdir(input_dir):
        if filename.lower().endswith(('.bmp')):
            input_file = os.path.join(input_dir, filename)

            # Get the prefix (everything before the last underscore)
            base_name = os.path.splitext(filename)[0]
            parts = base_name.split('_')
            if len(parts) >= 1:
                prefix = '_'.join(parts[:-1])  # Get everything before the last part
                
                # Compute a hash of the input file to check for duplicates
                with open(input_file, 'rb') as f:
                    file_hash = hash(f.read())

                # Create a key using both prefix and hash
                key = (prefix, file_hash)

                # Check if the image has already been processed with the same prefix
                if key in processed_images:
                    # Modify the output filename based on the extension
                    if filename.lower().endswith('.bmp'):
                        output_file_path = os.path.join(output_dir, filename[:-4] + '.sbmp')
                    else:
                        output_file_path = os.path.join(output_dir, 's' + filename)

                    # Write the already processed filename string to the current file
                    with open(output_file_path, 'wb') as f:
                        converted_filename = os.path.splitext(processed_images[key])[0] + '.sbmp'
                        f.write("_R".encode('UTF-8'))
                        filename_length = len(converted_filename)
                        f.write(bytearray([filename_length]))
                        f.write(converted_filename.encode('UTF-8'))
                    print(f"Duplicate file: {filename} matches {converted_filename}.")
                    continue

                # Process the image
                process_bmp(input_file, output_dir, split_height, bit_depth, enable_huffman)

                # Save the processed filename in the dictionary
                processed_images[key] = filename


def process_cleanup(directory):
    """Delete intermediate BMP and SBMP files after processing."""
    for filename in os.listdir(directory):
        if filename.lower().endswith(('.bmp', '.sbmp')):
            file_path = os.path.join(directory, filename)
            try:
                os.remove(file_path)
            except Exception as e:
                print(f"Error deleting {filename}: {e}")

def main():
    parser = argparse.ArgumentParser(description='Convert GIF to BMP and split images')
    parser.add_argument('input_folder', help='Input folder containing GIF files')
    parser.add_argument('output_folder', help='Output folder for processed files')
    parser.add_argument('--split', type=int, required=True, help='Split height for image processing')
    parser.add_argument('--depth', type=int, choices=[4, 8], required=True, help='Bit depth (4 for 4-bit grayscale, 8 for 8-bit grayscale)')
    parser.add_argument('--enable-huffman', action='store_true', help='Enable Huffman compression (default: disabled)')

    args = parser.parse_args()

    input_dir = args.input_folder
    output_dir = args.output_folder
    split_height = args.split
    bit_depth = args.depth
    enable_huffman = args.enable_huffman

    for root, dirs, files in os.walk(input_dir):
        for file in files:
            if file.endswith('.gif'):
                gif_path = os.path.join(root, file)
                convert_gif_to_bmp(gif_path, output_dir, bit_depth)

    process_split(output_dir, output_dir, split_height, bit_depth, enable_huffman)

    process_merge(output_dir)
    
    # Clean up intermediate files after all processing is complete
    process_cleanup(output_dir)

if __name__ == "__main__":
    main()