'''
- Graphics Author: Copyright 2020 Twitter, Inc and other contributors
- Graphics Source: https://github.com/twitter/twemoji
- Graphics License: CC-BY 4.0 (https://creativecommons.org/licenses/by/4.0/)
'''

import requests
import os
import sys
import argparse
import cairosvg
from LVGLImage import LVGLImage, ColorFormat, CompressMethod, OutputFormat

# map to emoji
emoji_mapping = {
    "neutral": 0x1f636, # 😶
    "happy": 0x1f642,    # 🙂
    "laughing": 0x1f606, # 😆
    "funny": 0x1f602,    # 😂
    "sad": 0x1f614,      # 😔
    "angry": 0x1f620,    # 😠
    "crying": 0x1f62d,   # 😭
    "loving": 0x1f60d,   # 😍
    "embarrassed": 0x1f633, # 😳
    "surprised": 0x1f62f,   # 😯
    "shocked": 0x1f631,     # 😱
    "thinking": 0x1f914,    # 🤔
    "winking": 0x1f609,     # 😉
    "cool": 0x1f60e,        # 😎
    "relaxed": 0x1f60c,     # 😌
    "delicious": 0x1f924,   # 🤤
    "kissy": 0x1f618,       # 😘
    "confident": 0x1f60f,   # 😏
    "sleepy": 0x1f634,      # 😴
    "silly": 0x1f61c,       # 😜
    "confused": 0x1f644     # 🙄
}


# download emoji from https://raw.githubusercontent.com/twitter/twemoji/refs/heads/master/assets/svg/1f644.svg
# to folder ./build/svg
def get_emoji_png(name, emoji_utf8, size):
    if not os.path.exists("./build/svg"):
        os.makedirs("./build/svg")
    
    # 检查SVG文件是否存在
    svg_path = f"./build/svg/{name}.svg"
    if not os.path.exists(svg_path):
        url = f"https://raw.githubusercontent.com/twitter/twemoji/refs/heads/master/assets/svg/{emoji_utf8}.svg"
        response = requests.get(url)
        with open(svg_path, "wb") as f:
            f.write(response.content)
    
    if not os.path.exists(f"./png/twemoji_{size}"):
        os.makedirs(f"./png/twemoji_{size}")
    # 检查指定大小的PNG文件是否存在
    png_path = f"./png/twemoji_{size}/{name}.png"
    if not os.path.exists(png_path):
        # 使用cairosvg转换SVG到PNG
        cairosvg.svg2png(
            url=svg_path,
            write_to=png_path,
            output_width=size,
            output_height=size
        )
    
    return png_path

def parse_arguments():
    parser = argparse.ArgumentParser(description='Emoji font converter utility')
    parser.add_argument('--size', type=int, default=32, help='Emoji size in pixels (default: 32)')
    parser.add_argument('--type', choices=['png', 'lvgl'], default='png', help='Output type: png or lvgl')
    parser.add_argument('--cf', 
                       choices=['I1', 'I2', 'I4', 'I8', 'ARGB8888', 'RGB565A8'],
                       default='RGB565A8',
                       help='Color format for LVGL output (default: RGB565A8)')
    parser.add_argument('--compress',
                       choices=['NONE', 'RLE', 'LZ4'],
                       default='NONE',
                       help='Compression method for LVGL output (default: NONE)')
    return parser.parse_args()

def generate_lvgl_image(png_path, cf_str, compress_str):
    cf = ColorFormat[cf_str]
    compress = CompressMethod[compress_str]
    img = LVGLImage().from_png(png_path, cf=cf)
    
    # 生成 C 文件
    c_path = png_path.replace('.png', '.c')
    img.to_c_array(c_path, compress=compress)
    
    # 生成 bin 文件
    bin_path = png_path.replace('.png', '.bin')
    img.to_bin(bin_path, compress=compress)
    
    return c_path, bin_path

def main():
    args = parse_arguments()
    
    # 处理每个表情符号
    for name, code in emoji_mapping.items():
        # 将十六进制代码转换为字符串格式
        emoji_utf8 = format(code, 'x')
        
        # 获取或下载 PNG 文件
        png_path = get_emoji_png(name, emoji_utf8, args.size)
        
        if args.type == 'lvgl':
            # 生成 LVGL 图像文件
            c_path, bin_path = generate_lvgl_image(png_path, args.cf, args.compress)
            print(f"Generated LVGL files for {name}: {c_path}, {bin_path}")
        else:
            print(f"Generated PNG file for {name}: {png_path}")

if __name__ == "__main__":
    sys.exit(main())
