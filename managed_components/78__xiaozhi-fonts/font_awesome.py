import os
import sys
import argparse

# map to font awesome icons
icon_mapping = {
    # emojis
    "neutral": 0xf5a4,  # 0xf5a4 [blank]  0xf11a 😐
    "happy": 0xf118,    # 😊
    "laughing": 0xf59b, # 😆
    "funny": 0xf588,    # 😂
    "sad": 0xe384,      # 😔
    "angry": 0xf556,    # 😡
    "crying": 0xf5b3,   # 😭
    "loving": 0xf584,   # 😍
    "embarrassed": 0xf579, # 😳
    "surprised": 0xe36b,   # 😲
    "shocked": 0xe375,     # 😱
    "thinking": 0xe39b,    # 🤔
    "winking": 0xf4da,     # 😉
    "cool": 0xe398,        # 😎
    "relaxed": 0xe392,     # 😌
    "delicious": 0xe372,   # 😋
    "kissy": 0xf598,       # 😗
    "confident": 0xe409,   # 😏
    "sleepy": 0xe38d,      # 😴
    "silly": 0xe3a4,       # 😜
    "confused": 0xe36d,    # 😕

    # battery icons
    "battery_full": 0xf240,
    "battery_three_quarters": 0xf241,
    "battery_half": 0xf242, 
    "battery_quarter": 0xf243,
    "battery_empty": 0xf244,
    "battery_slash": 0xf377,
    "battery_bolt": 0xf376,

    # wifi icons
    "wifi": 0xf1eb,
    "wifi_fair": 0xf6ab,
    "wifi_weak": 0xf6aa,
    "wifi_slash": 0xf6ac,

    # signal icons
    "signal": 0xf012,
    "signal_strong": 0xf68f,
    "signal_good": 0xf68e,
    "signal_fair": 0xf68d,
    "signal_weak": 0xf68c,
    "signal_off": 0xf695,

    # volume icons
    "volume_high": 0xf028,
    "volume": 0xf6a8,
    "volume_low": 0xf027,
    "volume_xmark": 0xf6a9,

    # media controls
    "music": 0xf001,
    "check": 0xf00c,
    "xmark": 0xf00d,
    "power_off": 0xf011,
    "gear": 0xf013,
    "trash": 0xf1f8,
    "house": 0xf015,
    "image": 0xf03e,
    "pen_to_square": 0xf044,
    "backward_step": 0xf048,
    "forward_step": 0xf051,
    "play": 0xf04b,
    "pause": 0xf04c,
    "stop": 0xf04d,

    # arrows
    "arrow_left": 0xf060,
    "arrow_right": 0xf061,
    "arrow_up": 0xf062,
    "arrow_down": 0xf063,

    # misc icons
    "triangle_exclamation": 0xf071,
    "bell": 0xf0f3,
    "location_dot": 0xf3c5,
    "globe": 0xf0ac,
    "location_arrow": 0xf124,
    "sd_card": 0xf7c2,
    "bluetooth": 0xf293,
    "comment": 0xf075,
    "microchip_ai": 0xe1ec,
    "user": 0xf007,
    "user_robot": 0xe04b,
    "download": 0xf019,

    # Added 20250827
    "lock": 0xf023,
    "unlock": 0xf09c,
    "key": 0xf084,
    "link": 0xf0c1,
    "circle_info": 0xf05a,
    "circle_question": 0xf059,
    "circle_check": 0xf058,
    "circle_xmark": 0xf057,
    "clock": 0xf017,
    "alarm_clock": 0xf34e,
    "spinner": 0xf110,
    "temperature_half": 0xf2c9,
    "headphones": 0xf025,
    "microphone": 0xf130,
    "microphone_slash": 0xf131,
    # "comment_dot": 0xe6dc,
    "comment_question": 0xe14b,
    "camera": 0xf030,
    "calendar": 0xf133,
    "envelope": 0xf0e0,
    "brightness": 0xe0c9,
    "phone": 0xf095,
    "compass": 0xf14e,
    "calculator": 0xf1ec,
    "glasses": 0xf530,
    "magnifying_glass": 0xf002,
    "heart": 0xf004,
    "star": 0xf005,
    "gamepad": 0xf11b,
    "watch": 0xf2e1,

    # arrows more
    "arrows_repeat": 0xf364,
    "arrows_rotate": 0xf021,
    "angle_left": 0xf104,
    "angle_right": 0xf105,
    "angle_up": 0xf106,
    "angle_down": 0xf107,
    "angles_left": 0xf100,
    "angles_right": 0xf101,
    "angles_up": 0xf102,
    "angles_down": 0xf103,
    "cloud_arrow_down": 0xf0ed, # 下云
    "cloud_arrow_up": 0xf0ee, # 上云
    "cloud_slash": 0xe137,

    # Weather
    "sun": 0xf185, # 晴
    "moon": 0xf186, # 月亮
    "cloud": 0xf0c2, # 云
    "clouds": 0xf744, # 阴
    "cloud_sun": 0xf746, # 晴间多云
    "cloud_sun_rain": 0xf743, # 阵雨
    "cloud_moon": 0xf6c3, # 多云有月
    "cloud_bolt": 0xf76c, # 雷电
    "cloud_hail": 0xf73a, # 冰雹
    "cloud_sleet": 0xf741, # 雨夹雪
    "cloud_drizzle": 0xf738, # 小雨
    "cloud_moon": 0xf6c3, # 多云有月
    "cloud_fog": 0xf74e, # 雾
    "cloud_rain": 0xf73d, # 中雨
    "cloud_showers": 0xf73f, # 大雨
    "cloud_showers_heavy": 0xf740, # 暴雨
    "snowflake": 0xf2dc, # 雪花
    "snowflakes": 0xf7cf, # 大雪
    "smog": 0xf75f, # 雾霾
    "wind": 0xf72e, # 风
    "hurricane": 0xf751, # 飓风
    "tornado": 0xf76f, # 龙卷风
}

def parse_arguments():
    parser = argparse.ArgumentParser(description='Font Awesome converter utility')
    parser.add_argument('type', choices=['lvgl', 'dump', 'generate'], help='Output type: lvgl, dump, or generate header files')
    parser.add_argument('--font-size', type=int, default=14, help='Font size (default: 14)')
    parser.add_argument('--bpp', type=int, default=4, help='Bits per pixel (default: 4)')
    return parser.parse_args()

def get_font_file(font_size):
    if font_size == 30:
        return "./tmp/fa-light-300.otf"
    return "./tmp/fa-regular-400.otf"

def main():
    args = parse_arguments()
    
    if args.type == "generate":
        return 0 if generate_symbols_header_file() else 1
    
    symbols = list(icon_mapping.values())
    flags = "--no-compress --no-prefilter --force-fast-kern-format"
    font = get_font_file(args.font_size)

    symbols_str = ",".join(map(hex, symbols))
    
    if args.type == "lvgl":
        output = f"src/font_awesome_{args.font_size}_{args.bpp}.c"
        cmd = f"lv_font_conv {flags} --font {font} --format lvgl --lv-include lvgl.h --bpp {args.bpp} -o {output} --size {args.font_size} -r {symbols_str}"
    else:  # dump
        output = f"./build/font_awesome_dump"
        import shutil
        shutil.rmtree(output, ignore_errors=True)
        os.makedirs(output, exist_ok=True)
        cmd = f"lv_font_conv {flags} --font {font} --format dump --bpp {args.bpp} -o {output} --size {args.font_size} -r {symbols_str}"

    print("Total symbols:", len(symbols))
    print("Generating", output)

    ret = os.system(cmd)
    if ret != 0:
        print(f"命令执行失败，返回码：{ret}")
        return ret
    print("命令执行成功")
    return 0

def generate_symbols_header_file():
    """根据当前的icon_mapping重新生成font_awesome.h文件"""
    
    # 合并所有符号
    symbols = {}
    for k, v in icon_mapping.items():
        symbols[k] = v
    
    # 生成头文件内容
    header_content = """#ifndef FONT_AWESOME_H
#define FONT_AWESOME_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

// 符号结构体
typedef struct {
    const char* name;
    const char* utf8_string;
} font_awesome_symbol_t;

"""
    
    # 为每个符号生成UTF-8编码的宏定义
    for k, v in symbols.items():
        ch = chr(v)
        utf8 = ''.join(f'\\x{c:02x}' for c in ch.encode("utf-8"))
        header_content += f'#define FONT_AWESOME_{k.upper()} "{utf8}"\n'
    
    # 添加符号数据表声明
    header_content += """
// 符号数据表声明
extern const font_awesome_symbol_t font_awesome_symbols[];
extern const size_t font_awesome_symbol_count;

// 内联函数实现
static inline const char* font_awesome_get_utf8(const char* name) {
    if (!name) return NULL;
    
    for (size_t i = 0; i < font_awesome_symbol_count; i++) {
        if (strcmp(font_awesome_symbols[i].name, name) == 0) {
            return font_awesome_symbols[i].utf8_string;
        }
    }
    return NULL;
}

#endif
"""
    
    # 写入头文件
    header_file = "include/font_awesome.h"
    try:
        with open(header_file, 'w', encoding='utf-8') as f:
            f.write(header_content)
        print(f"成功生成 {header_file}")
    except Exception as e:
        print(f"生成头文件失败: {e}")
        return False
    
    # 生成实现文件
    impl_content = """#include "font_awesome.h"

// 符号数据表实现
const font_awesome_symbol_t font_awesome_symbols[] = {
"""
    
    # 为每个符号生成数据表条目
    for k, v in symbols.items():
        ch = chr(v)
        utf8 = ''.join(f'\\x{c:02x}' for c in ch.encode("utf-8"))
        impl_content += f'    {{"{k}", "{utf8}"}},\n'
    
    impl_content += """};

// 符号总数
const size_t font_awesome_symbol_count = sizeof(font_awesome_symbols) / sizeof(font_awesome_symbols[0]);
"""
    
    # 写入实现文件
    impl_file = "src/font_awesome.c"
    try:
        with open(impl_file, 'w', encoding='utf-8') as f:
            f.write(impl_content)
        print(f"成功生成 {impl_file}")
        print(f"总共生成了 {len(symbols)} 个符号")
        return True
    except Exception as e:
        print(f"生成实现文件失败: {e}")
        return False

if __name__ == "__main__":
    sys.exit(main())

