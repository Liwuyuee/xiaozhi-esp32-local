#include "local_asr.h"
#include "assets.h"

#include <esp_log.h>
#include <esp_mn_iface.h>
#include <esp_mn_models.h>
#include <esp_mn_speech_commands.h>
#include <model_path.h>

#include <cstring>

#define TAG "LocalAsr"

// ========== Offline Command Definitions ==========
// These are Chinese smart-home commands that will be recognized locally
// when the device is offline. The phrases must match the training data
// of the ESP-SR multinet model (typically "esp_mn_zh" or similar).
//
// Recommended phrases for ESP-SR Chinese command recognition:
const LocalAsr::CommandDef LocalAsr::kCommands[] = {
    {1,  "da kai deng",    "打开灯"},
    {2,  "guan bi deng",   "关闭灯"},
    {3,  "da kai feng shang", "打开风扇"},
    {4,  "guan bi feng shang","关闭风扇"},
    {5,  "zhan ting",      "暂停"},
    {6,  "ji xu",          "继续"},
    {7,  "da sheng dian",  "大点声"},
    {8,  "xiao sheng dian","小点声"},
    {9,  "xian zai shi jian", "现在时间"},
    {10, "guan bi",        "关闭"},
};

const int LocalAsr::kCommandCount = sizeof(kCommands) / sizeof(kCommands[0]);

// ========== Implementation ==========

LocalAsr::LocalAsr() {}

LocalAsr::~LocalAsr() {
    if (multinet_model_data_ != nullptr && multinet_ != nullptr) {
        multinet_->destroy(multinet_model_data_);
        multinet_model_data_ = nullptr;
    }
    if (models_ != nullptr) {
        // We always own models_ since Initialize(nullptr) loads from assets
        esp_srmodel_deinit(models_);
        models_ = nullptr;
    }
}

bool LocalAsr::Initialize(srmodel_list_t* models_list) {
    // Load models from the assets partition
    if (models_list != nullptr) {
        // Use externally provided models (e.g. from AudioService)
        models_ = models_list;
    } else {
        // Load srmodels.bin from the assets SPIFFS partition
        ESP_LOGI(TAG, "Loading SR models from assets partition");
        auto& assets = Assets::GetInstance();
        void* ptr = nullptr;
        size_t size = 0;
        if (assets.GetAssetData("srmodels.bin", ptr, size)) {
            models_ = srmodel_load(static_cast<uint8_t*>(ptr));
        }
        if (models_ == nullptr) {
            // Fallback: try loading from "model" partition (rare)
            models_ = esp_srmodel_init("model");
        }
    }

    if (models_ == nullptr || models_->num == -1) {
        ESP_LOGE(TAG, "No SR models available, offline ASR disabled");
        return false;
    }

    // Find the multinet model for command recognition
    mn_name_ = esp_srmodel_filter(models_, ESP_MN_PREFIX, language_.c_str());
    if (mn_name_ == nullptr) {
        ESP_LOGE(TAG, "No multinet (command recognition) model found for language '%s'", language_.c_str());
        ESP_LOGI(TAG, "Offline ASR requires ESP-SR multinet model (esp_mn_zh or similar)");
        return false;
    }

    ESP_LOGI(TAG, "Using multinet model: %s", mn_name_);

    multinet_ = esp_mn_handle_from_name(mn_name_);
    if (multinet_ == nullptr) {
        ESP_LOGE(TAG, "Failed to get multinet handle from name: %s", mn_name_);
        return false;
    }

    multinet_model_data_ = multinet_->create(mn_name_, duration_);
    if (multinet_model_data_ == nullptr) {
        ESP_LOGE(TAG, "Failed to create multinet model data");
        return false;
    }

    multinet_->set_det_threshold(multinet_model_data_, threshold_);

    // Note: Commands are registered in Start(), not here,
    // because esp_mn_commands_* uses a global list that conflicts
    // with the wake word detector's command list.

    initialized_ = true;
    return true;
}

void LocalAsr::Start() {
    if (!initialized_) {
        ESP_LOGW(TAG, "LocalAsr not initialized, cannot start");
        return;
    }

    // Register offline commands in the global command list.
    // This is done at Start time (not Initialize) to avoid conflicting
    // with the wake word detector's command list.
    esp_mn_commands_clear();
    for (int i = 0; i < kCommandCount; i++) {
        esp_mn_commands_add(kCommands[i].id, kCommands[i].phrase);
        ESP_LOGI(TAG, "  Command[%d]: %s -> %s", kCommands[i].id, kCommands[i].phrase, kCommands[i].display);
    }
    esp_mn_commands_update();
    multinet_->set_det_threshold(multinet_model_data_, threshold_);
    multinet_->print_active_speech_commands(multinet_model_data_);

    running_ = true;
    timeout_fired_ = false;
    start_time_us_ = esp_timer_get_time();
    last_command_.clear();
    last_display_.clear();
    ESP_LOGI(TAG, "Local ASR started, listening for commands (duration: %dms, threshold: %.2f)",
             duration_, threshold_);
}

void LocalAsr::Stop() {
    running_ = false;
    ESP_LOGI(TAG, "Local ASR stopped");
}

void LocalAsr::Reset() {
    if (multinet_model_data_ != nullptr && multinet_ != nullptr) {
        multinet_->clean(multinet_model_data_);
    }
    timeout_fired_ = false;
    last_command_.clear();
    last_display_.clear();
}

void LocalAsr::Feed(const std::vector<int16_t>& data) {
    if (!running_ || multinet_model_data_ == nullptr || !initialized_) {
        return;
    }

    // Check if we've exceeded the listening duration
    int64_t elapsed_us = esp_timer_get_time() - start_time_us_;
    if (elapsed_us > duration_ * 1000) {
        if (!timeout_fired_) {
            timeout_fired_ = true;
            ESP_LOGI(TAG, "Local ASR timeout (%dms exceeded)", duration_);
            Stop();
            if (timeout_callback_) {
                timeout_callback_();
            }
        }
        return;
    }

    // Feed audio to multinet for command detection
    esp_mn_state_t mn_state = multinet_->detect(
        multinet_model_data_, const_cast<int16_t*>(data.data()));

    if (mn_state == ESP_MN_STATE_DETECTING) {
        return;
    } else if (mn_state == ESP_MN_STATE_DETECTED) {
        esp_mn_results_t* mn_result = multinet_->get_results(multinet_model_data_);
        for (int i = 0; i < mn_result->num && running_; i++) {
            int cmd_id = mn_result->command_id[i];
            if (cmd_id >= 1 && cmd_id <= kCommandCount) {
                const auto& cmd = kCommands[cmd_id - 1];
                last_command_ = cmd.phrase;
                last_display_ = cmd.display;
                ESP_LOGI(TAG, "Command detected: id=%d, phrase=%s, display=%s, prob=%.3f",
                         cmd_id, cmd.phrase, cmd.display, mn_result->prob[i]);

                running_ = false;
                if (command_detected_callback_) {
                    command_detected_callback_(cmd_id, cmd.phrase, cmd.display);
                }
            }
        }
        multinet_->clean(multinet_model_data_);
    } else if (mn_state == ESP_MN_STATE_TIMEOUT) {
        // Per-chunk timeout within the multinet, just clean and continue
        ESP_LOGW(TAG, "Multinet chunk timeout, cleaning state");
        multinet_->clean(multinet_model_data_);
    }
}

size_t LocalAsr::GetFeedSize() {
    if (multinet_model_data_ == nullptr) {
        return 0;
    }
    return multinet_->get_samp_chunksize(multinet_model_data_);
}

void LocalAsr::OnCommandDetected(
    std::function<void(int cmd_id, const std::string& command, const std::string& display)> callback) {
    command_detected_callback_ = callback;
}

void LocalAsr::OnTimeout(std::function<void()> callback) {
    timeout_callback_ = callback;
}
