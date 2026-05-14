#include "ec801e_mqtt.h"
#include <esp_log.h>

#define TAG "Ec801EMqtt"

Ec801EMqtt::Ec801EMqtt(std::shared_ptr<AtUart> at_uart, int mqtt_id) : at_uart_(at_uart), mqtt_id_(mqtt_id) {
    event_group_handle_ = xEventGroupCreate();

    urc_callback_it_ = at_uart_->RegisterUrcCallback([this](const std::string& command, const std::vector<AtArgumentValue>& arguments) {
        if (command == "QMTRECV" && arguments.size() >= 4) {
            if (arguments[0].int_value == mqtt_id_) {
                auto topic = arguments[2].string_value;
                if (on_message_callback_) {
                    on_message_callback_(topic, at_uart_->DecodeHex(arguments[3].string_value));
                }
            }
        } else if (command == "QMTSTAT" && arguments.size() == 2) {
            if (arguments[0].int_value == mqtt_id_) {
                auto error_code = arguments[1].int_value;
                if (error_code != 0) {
                    auto error_message = ErrorToString(error_code);
                    ESP_LOGE(TAG, "MQTT error occurred: %s", error_message.c_str());
                    if (on_error_callback_) {
                        on_error_callback_(error_message);
                    }
                    if (connected_) {
                        connected_ = false;
                        if (on_disconnected_callback_) {
                            on_disconnected_callback_();
                        }
                    }
                    xEventGroupSetBits(event_group_handle_, EC801E_MQTT_DISCONNECTED_EVENT);
                }
            }
        } else if (command == "QMTCONN" && arguments.size() == 3) {
            if (arguments[0].int_value == mqtt_id_) {
                error_code_ = arguments[2].int_value;
                if (error_code_ == 0) {
                    if (!connected_) {
                        connected_ = true;
                        if (on_connected_callback_) {
                            on_connected_callback_();
                        }
                    }
                    xEventGroupSetBits(event_group_handle_, EC801E_MQTT_CONNECTED_EVENT);
                } else {
                    if (connected_) {
                        connected_ = false;
                        if (on_disconnected_callback_) {
                            on_disconnected_callback_();
                        }
                    }
                    xEventGroupSetBits(event_group_handle_, EC801E_MQTT_DISCONNECTED_EVENT);
                }
            }
        } else if (command == "QMTOPEN" && arguments.size() == 2) {
            if (arguments[0].int_value == mqtt_id_) {
                error_code_ = arguments[1].int_value;
                if (error_code_ == 0) {
                    xEventGroupSetBits(event_group_handle_, EC801E_MQTT_OPEN_COMPLETE);
                } else {
                    xEventGroupSetBits(event_group_handle_, EC801E_MQTT_OPEN_FAILED);
                }
            }
        } else if (command == "QMTDISC" && arguments.size() == 2) {
            if (arguments[0].int_value == mqtt_id_) {
                if (arguments[1].int_value == 0) {
                    xEventGroupSetBits(event_group_handle_, EC801E_MQTT_DISCONNECTED_EVENT);
                } else {
                    ESP_LOGE(TAG, "Failed to disconnect from MQTT broker");
                }
            }
        }
    });
}

Ec801EMqtt::~Ec801EMqtt() {
    at_uart_->UnregisterUrcCallback(urc_callback_it_);
    vEventGroupDelete(event_group_handle_);
}

bool Ec801EMqtt::Connect(const std::string broker_address, int broker_port, const std::string client_id, const std::string username, const std::string password) {
    EventBits_t bits;

    if (broker_port == 8883) {
        // Config SSL Context
        at_uart_->SendCommand("AT+QSSLCFG=\"sslversion\",2,4;+QSSLCFG=\"ciphersuite\",2,0xFFFF;+QSSLCFG=\"seclevel\",2,0");
        if (!at_uart_->SendCommand(std::string("AT+QMTCFG=\"ssl\",") + std::to_string(mqtt_id_) + ",1,2")) {
            ESP_LOGE(TAG, "Failed to set MQTT to use SSL");
            return false;
        }
    }

    // Set version
    if (!at_uart_->SendCommand(std::string("AT+QMTCFG=\"version\",") + std::to_string(mqtt_id_) + ",4")) {
        ESP_LOGE(TAG, "Failed to set MQTT version to 3.1.1");
        return false;
    }

    // Set clean session
    if (!at_uart_->SendCommand(std::string("AT+QMTCFG=\"session\",") + std::to_string(mqtt_id_) + ",1")) {
        ESP_LOGE(TAG, "Failed to set MQTT clean session");
        return false;
    }

    // Set keep alive
    if (!at_uart_->SendCommand(std::string("AT+QMTCFG=\"keepalive\",") + std::to_string(mqtt_id_) + "," + std::to_string(keep_alive_seconds_))) {
        ESP_LOGE(TAG, "Failed to set MQTT keep alive");
        return false;
    }

    // Set HEX encoding (ASCII for sending, HEX for receiving)
    if (!at_uart_->SendCommand("AT+QMTCFG=\"dataformat\"," + std::to_string(mqtt_id_) + ",0,1")) {
        ESP_LOGE(TAG, "Failed to set MQTT to use HEX encoding");
        return false;
    }

    xEventGroupClearBits(event_group_handle_, EC801E_MQTT_OPEN_COMPLETE | EC801E_MQTT_OPEN_FAILED);
    std::string command = "AT+QMTOPEN=" + std::to_string(mqtt_id_) + ",\"" + broker_address + "\"," + std::to_string(broker_port);
    if (!at_uart_->SendCommand(command)) {
        ESP_LOGE(TAG, "Failed to open MQTT connection");
        return false;
    }

    bits = xEventGroupWaitBits(event_group_handle_, EC801E_MQTT_OPEN_COMPLETE | EC801E_MQTT_OPEN_FAILED, pdTRUE, pdFALSE, pdMS_TO_TICKS(EC801E_MQTT_CONNECT_TIMEOUT_MS));
    if (bits & EC801E_MQTT_OPEN_FAILED) {
        const char* error_code_str[] = {
            "Connected",
            "Parameter error",
            "MQTT identifier occupied",
            "PDP activation failed",
            "Domain name resolution failed",
            "Server disconnected"
        };
        const char* message = error_code_ < 6 ? error_code_str[error_code_] : "Unknown error";
        ESP_LOGE(TAG, "Failed to open MQTT connection: %s", message);

        if (error_code_ == 2) { // MQTT 标识符被占用
            at_uart_->SendCommand(std::string("AT+QMTDISC=") + std::to_string(mqtt_id_));
            bits = xEventGroupWaitBits(event_group_handle_, EC801E_MQTT_DISCONNECTED_EVENT, pdTRUE, pdFALSE, pdMS_TO_TICKS(EC801E_MQTT_CONNECT_TIMEOUT_MS));
            if (!(bits & EC801E_MQTT_DISCONNECTED_EVENT)) {
                ESP_LOGE(TAG, "Failed to disconnect from previous connection");
                return false;
            }
            return Connect(broker_address, broker_port, client_id, username, password);
        }
        return false;
    } else if (!(bits & EC801E_MQTT_OPEN_COMPLETE)) {
        ESP_LOGE(TAG, "MQTT connection timeout");
        return false;
    }

    xEventGroupClearBits(event_group_handle_, EC801E_MQTT_CONNECTED_EVENT | EC801E_MQTT_DISCONNECTED_EVENT);
    command = "AT+QMTCONN=" + std::to_string(mqtt_id_) + ",\"" + client_id + "\",\"" + username + "\",\"" + password + "\"";
    if (!at_uart_->SendCommand(command)) {
        ESP_LOGE(TAG, "Failed to connect to MQTT broker");
        return false;
    }

    // 等待连接完成
    bits = xEventGroupWaitBits(event_group_handle_, EC801E_MQTT_CONNECTED_EVENT | EC801E_MQTT_DISCONNECTED_EVENT, pdTRUE, pdFALSE, pdMS_TO_TICKS(EC801E_MQTT_CONNECT_TIMEOUT_MS));
    if (bits & EC801E_MQTT_DISCONNECTED_EVENT) {
        const char* error_code_str[] = {
            "Accepted",
            "Rejected: Unacceptable protocol version",
            "Rejected: Identifier rejected",
            "Rejected: Server unavailable",
            "Rejected: Wrong username or password",
            "Rejected: Unauthorized"
        };
        const char* message = error_code_ < 6 ? error_code_str[error_code_] : "Unknown error";
        ESP_LOGE(TAG, "Failed to connect to MQTT broker: %s", message);
        return false;
    } else if (!(bits & EC801E_MQTT_CONNECTED_EVENT)) {
        ESP_LOGE(TAG, "MQTT connection timeout");
        return false;
    }
    return true;
}

bool Ec801EMqtt::IsConnected() {
    return connected_;
}

void Ec801EMqtt::Disconnect() {
    if (!connected_) {
        return;
    }
    at_uart_->SendCommand(std::string("AT+QMTDISC=") + std::to_string(mqtt_id_));
}

bool Ec801EMqtt::Publish(const std::string topic, const std::string payload, int qos) {
    if (!connected_) {
        return false;
    }
    // If payload size is larger than 64KB, a CME ERROR 601 will be returned.
    std::string command = "AT+QMTPUBEX=" + std::to_string(mqtt_id_) + ",0,0,0,\"" + topic + "\",";
    command += std::to_string(payload.size());
    if (!at_uart_->SendCommandWithData(command, 1000, true, payload.data(), payload.size())) {
        return false;
    }
    return true;
}

bool Ec801EMqtt::Subscribe(const std::string topic, int qos) {
    if (!connected_) {
        return false;
    }
    std::string command = "AT+QMTSUB=" + std::to_string(mqtt_id_) + ",0,\"" + topic + "\"," + std::to_string(qos);
    return at_uart_->SendCommand(command);
}

bool Ec801EMqtt::Unsubscribe(const std::string topic) {
    if (!connected_) {
        return false;
    }
    std::string command = "AT+QMTUNS=" + std::to_string(mqtt_id_) + ",0,\"" + topic + "\"";
    return at_uart_->SendCommand(command);
}

std::string Ec801EMqtt::ErrorToString(int error_code) {
    switch (error_code) {
        case 0:
            return "Connected";
        case 1:
            return "Server disconnected or reset";
        case 2:
            return "Ping timeout or failed";
        case 3:
            return "Connect timeout or failed";
        case 4:
            return "Receive CONNACK timeout or failed";
        case 5:
            return "Client sends DISCONNECT packet, but server actively disconnects MQTT connection";
        case 6:
            return "Client actively disconnects MQTT connection because sending data packets always fails";
        case 7:
            return "Link does not work or server is unavailable";
        case 8:
            return "Client actively disconnects MQTT connection";
        default:
            return "Unknown error";
    }
}
