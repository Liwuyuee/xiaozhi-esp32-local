#!/usr/bin/env python3
"""
Generate TTF font with DeepSeek tokenizer characters.

This script loads one or more model tokenizers, extracts all unique characters
from the vocabulary (union of all models), and creates a merged font file containing only those characters.

Usage:
    python3 scripts/gen_ttf.py                    # Process all tokens and build font
    python3 scripts/gen_ttf.py --max-tokens 1000  # Process first 1000 tokens (for testing)
    python3 scripts/gen_ttf.py --font-style Medium # Use Medium font style
    python3 scripts/gen_ttf.py --model deepseek-ai/DeepSeek-R1-Distill-Qwen-1.5B
    python3 scripts/gen_ttf.py --model model1,model2,model3  # Load multiple models and take union

Requirements:
    - transformers
    - tqdm
    - fonttools

Output:
    - build/chars.txt: Unique characters sorted by token ID (union of all models)
    - ttf/noto-{font_style}.ttf: Merged font file with common characters (e.g., noto-Regular.ttf)
"""

from tqdm import tqdm
from transformers import AutoTokenizer
import os
import argparse
from fontTools.subset import Subsetter, Options, load_font, save_font
from fontTools.merge import Merger
from fontTools.ttLib.scaleUpem import scale_upem

def parse_arguments():
    """Parse command line arguments."""
    parser = argparse.ArgumentParser(description='Generate TTF font with DeepSeek tokenizer characters')
    parser.add_argument('--max-tokens', type=int, default=None,
                        help='Maximum number of tokens to process (for testing)')
    parser.add_argument('--model', type=str, default="deepseek-ai/DeepSeek-R1,Qwen/Qwen3-235B-A22B-Instruct-2507",
                        help='Model name(s) to use, comma-separated for multiple models')
    parser.add_argument('--font-style', type=str, default="Regular",
                        help='Font style to use (Regular, Medium, Bold, etc.)')
    args = parser.parse_args()
    
    # Split comma-separated model names and strip whitespace
    model_names = [name.strip() for name in args.model.split(',') if name.strip()]
    
    return model_names, args.max_tokens, args.font_style

def ensure_build_directory():
    """Create build directory if it doesn't exist."""
    build_dir = "build"
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)
        print(f"Created directory: {build_dir}")
    return build_dir

def process_single_model(model_name, model_idx, total_models, max_tokens, unique_chars):
    """Process a single model and extract characters."""
    print(f"\n[{model_idx + 1}/{total_models}] Loading tokenizer from {model_name}...")
    try:
        tokenizer = AutoTokenizer.from_pretrained(model_name)
        print(f"Tokenizer loaded successfully.")
    except Exception as e:
        print(f"Error loading tokenizer: {e}")
        return False

    vocab_size = len(tokenizer.get_vocab())
    tokens_to_process = max_tokens if max_tokens else vocab_size
    print(f"Processing {tokens_to_process} tokens out of {vocab_size}...")

    for token_id in tqdm(range(min(tokens_to_process, vocab_size)), desc=f"Model {model_idx + 1}"):
        try:
            token = tokenizer.decode(token_id)
            if token.startswith("<｜"):
                continue
            # For each character, record the minimum token ID (from all models)
            for char in token:
                if char not in unique_chars:
                    unique_chars[char] = token_id
                else:
                    # If character already exists, keep the minimum token ID
                    unique_chars[char] = min(unique_chars[char], token_id)
        except Exception as e:
            print(f"Warning: Error decoding token {token_id}: {e}")
            continue
    
    return True

def extract_chars_from_models(model_names, max_tokens):
    """Extract characters from multiple models and return union of all characters."""
    unique_chars = {}  # Store characters and their minimum token ID (from all models)
    
    # Process all models and collect character union
    for model_idx, model_name in enumerate(model_names):
        process_single_model(model_name, model_idx, len(model_names), max_tokens, unique_chars)
    
    print(f"\nTotal unique chars (union of all models): {len(unique_chars)}")
    return unique_chars

def save_chars_to_file(unique_chars, build_dir):
    """Save unique characters to file, sorted by token ID."""
    sorted_chars = sorted(unique_chars.items(), key=lambda x: x[1])
    
    output_file = os.path.join(build_dir, "chars.txt")
    with open(output_file, "w", encoding="utf-8") as f:
        # Output sorted by token ID
        for char, token_id in sorted_chars:
            f.write(char + "\n")
    
    print(f"Wrote {len(unique_chars)} unique characters to {output_file} (sorted by token ID)")
    return sorted_chars

def main():
    model_names, max_tokens, font_style = parse_arguments()
    build_dir = ensure_build_directory()
    
    unique_chars = extract_chars_from_models(model_names, max_tokens)
    sorted_chars = save_chars_to_file(unique_chars, build_dir)
    
    # Build font with the extracted characters
    build_font(sorted_chars, font_style)

def build_font(sorted_chars, font_style):
    print("Building subsetter")

    basic_unicodes = set(range(0x20, 0x7f)) | set(range(0xA1, 0x100))
    common_unicodes = basic_unicodes.copy()

    for char, token_id in sorted_chars:
        common_unicodes.add(ord(char))

    print(f"common_unicodes: Added chars: {len(common_unicodes)}")

    build_ttf("noto", font_style, "common", common_unicodes)

def build_ttf(font_type, font_style, font_name, unicodes):
    # Font directory path
    font_base_path = os.path.join(os.path.dirname(__file__), "..")

    font_list = [
        f"{font_base_path}/fonts/Noto_Sans/static/NotoSans-{font_style}.ttf",
        f"{font_base_path}/fonts/Noto_Emoji/static/NotoEmoji-{font_style}.ttf",
        f"{font_base_path}/fonts/Noto_Sans_SC/static/NotoSansSC-{font_style}.ttf",
        f"{font_base_path}/fonts/Noto_Sans_TC/static/NotoSansTC-{font_style}.ttf",
        f"{font_base_path}/fonts/Noto_Sans_JP/static/NotoSansJP-{font_style}.ttf",
        f"{font_base_path}/fonts/Noto_Sans_KR/static/NotoSansKR-{font_style}.ttf",
        f"{font_base_path}/fonts/Noto_Sans_Thai/static/NotoSansThai-{font_style}.ttf",
        f"{font_base_path}/fonts/Noto_Sans_Arabic/static/NotoSansArabic-{font_style}.ttf"
    ]

    if not os.path.exists("build/subsets"):
        os.makedirs("build/subsets")

    if not os.path.exists("ttf"):
        os.makedirs("ttf")

    print(f"Subsetting {len(font_list)} fonts")

    subset_fonts = []
    subsetter = Subsetter(Options())
    subsetter.populate(unicodes=list(unicodes))

    # 遍历 font_list，提取每个字体中的字符
    for font_path in tqdm(font_list):
        if not os.path.exists(font_path):
            print(f"Font {font_path} not found")
            continue

        font = load_font(font_path, Options())
        font_file = font_path.split('/')[-1].split('.')[0]

        subsetter.subset(font)
        scale_upem(font, 1000)

        save_path = f"build/subsets/{font_file}.ttf"
        font.save(save_path)
        subset_fonts.append(save_path)

    # 合并所有字体，保存到 ttf/noto-{font_style}.ttf
    print(f"Merging {len(subset_fonts)} fonts")

    output_path = f"ttf/{font_type}-{font_style}.ttf"

    if subset_fonts:
        cmd = f"fonttools merge {' '.join(subset_fonts)} --output-file={output_path} --drop-tables=vhea,vmtx"
        result = os.system(cmd)

        if result == 0:
            print(f"Merged font saved to {output_path}")
        else:
            print(f"Error merging fonts to {output_path}")
    else:
        print("No subset fonts to merge")

if __name__ == "__main__":
    main()
