# xiaozhi-esp32-local — 离线语音命令识别扩展

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.5-blue)](https://github.com/espressif/esp-idf)
[![Platform](https://img.shields.io/badge/Platform-ESP32--S3-orange)](https://www.espressif.com/)

**基于 [xiaozhi-esp32](https://github.com/78/xiaozhi-esp32)的增强版本，核心新增离线语音命令识别功能。**

当设备无法连接服务器时，自动降级为本地离线模式，通过 ESP-SR 多命令词识别在端侧执行语音指令，实现"有网用云端、无网不中断"的双模语音交互体验。

---

## 主要贡献 ✨

### 离在线双模语音交互（本项目核心）

| 功能 | 说明 |
|------|------|
| **离线命令识别** | 唤醒词触发后，自动检测网络状态。在线 → 云端交互；离线 → 本地命令识别 |
| **10 条中文语音指令** | 灯控、风扇、时间查询等智能家居场景指令 |
| **4 秒聆听窗口** | 唤醒后开启 4 秒本地识别，超时自动回到待机，误唤醒后可通过再次唤醒重置 |
| **本地执行与反馈** | 识别成功后在屏幕显示执行结果 + 播放提示音 |

### 技术实现

```
用户说"你好小智"
  → ESP-SR 端侧唤醒词检测
    → 尝试连接云端服务器
      → 成功：原线上流程（ASR → LLM → TTS）
      → 失败：自动降级离线模式
        → 开启 4 秒本地聆听
        → ESP-SR multinet 命令识别
          → 匹配指令：执行本地动作 + 显示 + 提示音
          → 超时未匹配：回到待机
```

### 架构文件

| 文件 | 职责 |
|------|------|
| `main/local_asr/include/local_asr.h` | LocalAsr 类封装 ESP-SR multinet |
| `main/local_asr/local_asr.cc` | 10 条命令定义、音频馈送、识别回调 |
| `main/audio/audio_service.h/cc` | 新增 `AS_EVENT_LOCAL_ASR_RUNNING` 事件 & 音频路由 |
| `main/application.h/cc` | `EnterOfflineMode / ExitOfflineMode / ExecuteOfflineCommand` |
| `main/device_state.h` | 新增 `kDeviceStateOfflineListening` 状态 |
| `main/Kconfig.projbuild` | 新增 `LOCAL_ASR_ENABLE` 等菜单配置项 |

### Kconfig 配置

通过 `idf.py menuconfig` → `Xiaozhi Assistant` → `Enable Offline Voice Command Recognition` 可开关：

```
LOCAL_ASR_ENABLE=y         # 总开关
LOCAL_ASR_DURATION_MS=4000  # 聆听窗口 (ms)
LOCAL_ASR_THRESHOLD=30     # 识别置信度 (%)
```

所有离线 ASR 代码使用 `#if CONFIG_LOCAL_ASR_ENABLE` 条件编译，关闭后无额外资源占用。

---

## 硬件要求

与原项目相同，推荐 **ESP32-S3 + PSRAM**（ESP-SR 需要 PSRAM 运行模型）。支持 70+ 开源硬件。

本项目基于 **ICECAT K2** 开发板开发验证。

---

## 快速开始

### 烧录固件

```bash
git clone https://github.com/Liwuyuee/xiaozhi-esp32-local.git
cd xiaozhi-esp32-local

idf.py set-target esp32s3
idf.py menuconfig
  → Xiaozhi Assistant → Board Type → ICECAT K2
  → Xiaozhi Assistant → Enable Offline Voice Command Recognition  (默认开启)
idf.py build
idf.py -p PORT flash monitor
```

### 测试离线模式

1. 设备正常运行后**断开网络**
2. 说出唤醒词（默认"你好小智"）
3. 设备检测到服务器不可达，自动进入"离线聆听"模式
4. 在 4 秒内说出指令，例如：

| 你说 | 设备响应 |
|------|---------|
| "da kai deng" | 屏幕显示"已打开灯"+ 提示音 |
| "guan bi deng" | 屏幕显示"已关闭灯"+ 提示音 |
| "xian zai shi jian" | 屏幕显示当前时间 |
| (超时未说话) | 屏幕显示"未识别到指令"+ 回到待机 |

> **注意**：离线指令使用**拼音短语**，由 ESP-SR multinet 模型负责识别。
> 首次使用时建议开启串口日志查看识别置信度，如不准确可调整 `local_asr.cc` 中的拼音。

---

## 开发说明

- 框架：**ESP-IDF 5.5** + **FreeRTOS**
- 语音前端：**ESP-SR**（唤醒词 + 命令词）
- 离线命令识别：**ESP-SR multinet**（`esp_mn_commands_*` API）
- 音频流：I2S → ES7210/ES8311 → Opus 编解码
- 通信：Wi-Fi / MQTT+UDP / WebSocket

### 构建要求

- 安装 [ESP-IDF v5.5](https://docs.espressif.com/projects/esp-idf/en/v5.5/esp32s3/get-started/)
- Linux 或 macOS 推荐，Windows 也可用

### 添加自定义离线指令

编辑 `main/local_asr/local_asr.cc` 中的 `kCommands` 数组：

```cpp
const LocalAsr::CommandDef LocalAsr::kCommands[] = {
    {1,  "da kai deng",       "打开灯"},
    {2,  "guan bi deng",      "关闭灯"},
    // 在这里添加新指令...
};
```

添加后重新编译烧录即可。

---

## 致谢

- [xiaozhi-esp32](https://github.com/78/xiaozhi-esp32) — 虾哥开源的 ESP32 AI 聊天机器人项目
- [ESP-SR](https://github.com/espressif/esp-sr) — 乐鑫语音识别框架
- [ESP-IDF](https://github.com/espressif/esp-idf) — 乐鑫物联网开发框架

---

## License

MIT License — 与上游项目一致。允许自由使用、修改和商用。
