import os
import shutil

# 定义要生成的字体配置
emoji_configs = [
    (32, 'RGB565A8'),  # 32x32
    (64, 'RGB565A8'),  # 64x64
]

def main():
    # 遍历所有字体配置
    for size, cf in emoji_configs:
        print(f"\n正在生成 {size}x{size} emoji，{cf}...")
        
        # 构建命令并执行
        cmd = f"python font_emoji.py --type lvgl --size {size} --cf {cf} --compress NONE"
        ret = os.system(cmd)
        
        if ret != 0:
            print(f"生成 {size}x{size} emoji失败")
        else:
            # 复制 build/emoji_*.c 到 src/emoji/*
            src_dir = "./build"
            dst_dir = "./src/emoji"
            if not os.path.exists(dst_dir):
                os.makedirs(dst_dir)
            else:
                # 清空目标目录中的所有文件
                for file in os.listdir(dst_dir):
                    file_path = os.path.join(dst_dir, file)
                    if os.path.isfile(file_path):
                        os.remove(file_path)
            
            for file in os.listdir(src_dir):
                if file.startswith("emoji_") and file.endswith(".c"):
                    shutil.copy(os.path.join(src_dir, file), os.path.join(dst_dir, file))
            print(f"生成 {size}x{size} emoji成功")

if __name__ == "__main__":
    main()
