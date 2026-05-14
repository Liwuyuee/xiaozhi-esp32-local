# Otto 机器人 GIF 表情组件

Otto Robot Emoji GIF Component for ESP-IDF

## 概述

这是一个 ESP-IDF 组件，包含了 Otto 机器人的 6 个 GIF 表情资源，专为 LVGL 显示系统设计。组件提供了完整的 GIF 动画资源，可以在支持 LVGL 的 ESP32 设备上显示动态表情。

## 支持的表情

| 表情名称      | 描述              | 用途                     |
| ------------- | ----------------- | ------------------------ |
| `staticstate` | 静态状态/中性表情 | 默认表情，表示平静状态   |
| `sad`         | 悲伤表情          | 表示难过、沮丧等负面情绪 |
| `happy`       | 开心表情          | 表示高兴、愉快等正面情绪 |
| `scare`       | 惊吓/惊讶表情     | 表示震惊、意外等情绪     |
| `buxue`       | 不学/困惑表情     | 表示疑惑、不理解等状态   |
| `anger`       | 愤怒表情          | 表示生气、愤怒等强烈情绪 |

## 系统要求

- ESP-IDF >= 5.4.0
- LVGL >= 9.0
- 支持的芯片：ESP32, ESP32-S3, ESP32-C3, ESP32-C6, ESP32-H2, ESP32-P4

## 安装方法

### 方法 1：使用 ESP-IDF 组件管理器（推荐）

在您的项目的 `idf_component.yml` 文件中添加：

```yaml
dependencies:
  otto_emoji_gif:
    version: "^1.0.2"
    # 或者使用本地路径
    # path: "../path/to/otto-emoji-gif-component"
```

### 方法 2：手动安装

1. 将此组件复制到您的项目的 `components/` 目录中
2. 或者将其添加为 Git 子模块

## 使用方法

### 基础用法

```c
#include "otto_emoji_gif.h"

void display_emotion(lv_obj_t* parent) {
    // 创建GIF对象
    lv_obj_t* gif = lv_gif_create(parent);

    // 设置表情
    lv_gif_set_src(gif, &happy);  // 显示开心表情

    // 设置位置和大小
    lv_obj_set_size(gif, 240, 240);
    lv_obj_center(gif);
}
```

### 动态切换表情

```c
#include "otto_emoji_gif.h"

void switch_emotion(lv_obj_t* gif, const char* emotion_name) {
    const lv_img_dsc_t* emotion = otto_emoji_gif_get_by_name(emotion_name);
    if (emotion != NULL) {
        lv_gif_set_src(gif, emotion);
    } else {
        // 使用默认表情
        lv_gif_set_src(gif, &staticstate);
    }
}

// 使用示例
void example_usage(lv_obj_t* gif) {
    switch_emotion(gif, "happy");    // 切换到开心表情
    switch_emotion(gif, "sad");      // 切换到悲伤表情
    switch_emotion(gif, "anger");    // 切换到愤怒表情
}
```

### 获取组件信息

```c
#include "otto_emoji_gif.h"

void print_component_info() {
    printf("Otto Emoji GIF组件版本: %s\n", otto_emoji_gif_get_version());
    printf("支持的表情数量: %d\n", otto_emoji_gif_get_count());
}
```

## 文件结构

```
otto-emoji-gif-component/
├── idf_component.yml          # 组件配置文件
├── CMakeLists.txt            # 构建配置
├── README.md                 # 说明文档
├── LICENSE                   # 许可证
├── include/
│   └── otto_emoji_gif.h      # 头文件
└── src/
    ├── otto_emoji_gif_utils.c # 辅助函数
    ├── staticstate.c         # 静态表情GIF数据
    ├── sad.c                 # 悲伤表情GIF数据
    ├── happy.c               # 开心表情GIF数据
    ├── scare.c               # 惊吓表情GIF数据
    ├── buxue.c               # 困惑表情GIF数据
    └── anger.c               # 愤怒表情GIF数据
```

## 技术细节

- 所有 GIF 资源都经过优化，适合在嵌入式设备上使用
- 使用 LVGL 的 GIF 库进行渲染
- 支持透明背景
- 文件大小经过优化，平衡了画质和存储空间

## 许可证

MIT License - 详见 [LICENSE](LICENSE) 文件

## 贡献

欢迎提交问题和拉取请求。在贡献代码之前，请阅读贡献指南。

## 更新日志

### v1.0.2 (2025)

- bug fix

### v1.0.1 (2025)

- 删除示例项目，简化组件结构
- 优化组件发布配置

### v1.0.0 (2025)

- 初始版本发布
- 包含 6 个基础表情 GIF
- 支持 ESP-IDF 5.4.0+和 LVGL 9.0+

## 联系方式

如有问题请提交 Issue 或联系维护者。
