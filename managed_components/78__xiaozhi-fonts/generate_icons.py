import os

# 定义要生成的字体配置
font_configs = [
    (14, 1),  # 14号字体，1 bpp
    (16, 4),  # 16号字体，4 bpp
    (20, 4),  # 20号字体，4 bpp
    (30, 1),  # 30号字体，1 bpp
    (30, 4),  # 30号字体，4 bpp
]

def main():
    # 遍历所有字体配置
    for size, bpp in font_configs:
        print(f"\n正在生成 {size}px 字体，{bpp} bpp...")
        
        # 构建并执行命令
        cmd = f"python3 font_awesome.py lvgl --font-size {size} --bpp {bpp}"
        ret = os.system(cmd)
        
        if ret != 0:
            print(f"生成 {size}px {bpp}bpp 字体失败，返回码：{ret}")
            return ret
        
        print(f"成功生成 font_awesome_{size}_{bpp}.c")
    
    # 生成 font_awesome.h
    cmd = f"python3 font_awesome.py generate"
    ret = os.system(cmd)
    if ret != 0:
        print(f"生成 font_awesome.h 失败，返回码：{ret}")
        return ret
    
    return 0

if __name__ == "__main__":
    main()
