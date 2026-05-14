#ifndef LOCAL_ASR_H
#define LOCAL_ASR_H

#include <esp_mn_iface.h>
#include <esp_mn_models.h>
#include <model_path.h>

#include <atomic>
#include <functional>
#include <string>
#include <vector>

class LocalAsr {
public:
    LocalAsr();
    ~LocalAsr();

    bool Initialize(srmodel_list_t* models_list);
    void Feed(const std::vector<int16_t>& data);
    void Start();
    void Stop();
    void Reset();
    bool IsRunning() const { return running_; }
    size_t GetFeedSize();

    void OnCommandDetected(std::function<void(int cmd_id, const std::string& command, const std::string& display)> callback);
    void OnTimeout(std::function<void()> callback);

    void SetDuration(int ms) { duration_ = ms; }
    void SetThreshold(float threshold) { threshold_ = threshold; }
    int GetDurationMs() const { return duration_; }

    // Human-readable name for display
    const std::string& GetLastCommand() const { return last_command_; }
    const std::string& GetLastDisplay() const { return last_display_; }

public:
    // Expose command definitions for use by Application
    struct CommandDef {
        int id;
        const char* phrase;
        const char* display;
    };
    static const CommandDef kCommands[];
    static const int kCommandCount;

private:
    esp_mn_iface_t* multinet_ = nullptr;
    model_iface_data_t* multinet_model_data_ = nullptr;
    srmodel_list_t* models_ = nullptr;
    char* mn_name_ = nullptr;

    std::string language_ = "cn";
    int duration_ = 4000;   // Max 4 seconds listening window
    float threshold_ = 0.3f;
    std::atomic<bool> running_{false};
    bool initialized_ = false;

    int64_t start_time_us_ = 0;
    bool timeout_fired_ = false;

    std::string last_command_;
    std::string last_display_;

    std::function<void(int, const std::string&, const std::string&)> command_detected_callback_;
    std::function<void()> timeout_callback_;
};

#endif // LOCAL_ASR_H
