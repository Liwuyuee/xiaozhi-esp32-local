#pragma once

#define RESPONSE_PREFIX "\r{"
#define RESPONSE_SUFFIX "}\n"

#define RESPONSE_PREFIX_LEN (sizeof(RESPONSE_PREFIX) - 1)
#define RESPONSE_SUFFIX_LEN (sizeof(RESPONSE_SUFFIX) - 1)

#define CMD_TYPE_RESPONSE 0
#define CMD_TYPE_EVENT    1
#define CMD_TYPE_LOG      2

#define CMD_PREFIX "AT+"
#define CMD_QUERY  "?"
#define CMD_SET    "="
#define CMD_SUFFIX "\r\n"

#define CMD_PREFIX_LEN (sizeof(CMD_PREFIX) - 1)
#define CMD_SUFFIX_LEN (sizeof(CMD_SUFFIX) - 1)

#define CMD_WAIT_DELAY 2000 // ms

#define CMD_AT_ID         "ID"
#define CMD_AT_NAME       "NAME"
#define CMD_AT_VERSION    "VER"
#define CMD_AT_STATS      "STAT"
#define CMD_AT_BREAK      "BREAK"
#define CMD_AT_RESET      "RST"
#define CMD_AT_WIFI       "WIFI"
#define CMD_AT_MQTTSERVER "MQTTSERVER"
#define CMD_AT_MQTTPUBSUB "MQTTPUBSUB"
#define CMD_AT_INVOKE     "INVOKE"
#define CMD_AT_SAMPLE     "SAMPLE"
#define CMD_AT_INFO       "INFO"
#define CMD_AT_TSCORE     "TSCORE"
#define CMD_AT_TIOU       "TIOU"
#define CMD_AT_ALGOS      "ALGOS"
#define CMD_AT_MODELS     "MODELS"
#define CMD_AT_MODEL      "MODEL"
#define CMD_AT_SENSORS    "SENSORS"
#define CMD_AT_SENSOR     "SENSOR"
#define CMD_AT_ACTION     "ACTION"
#define CMD_AT_LED        "LED"
#define CMD_AT_OTA        "OTA"

#define EVENT_INVOKE     "INVOKE"
#define EVENT_SAMPLE     "SAMPLE"
#define EVENT_WIFI       "WIFI"
#define EVENT_MQTT       "MQTT"
#define EVENT_SUPERVISOR "SUPERVISOR"
#define EVENT_INIT       "INIT@STAT"

#define LOG_AT  "AT"
#define LOG_LOG "LOG"

typedef enum {
    CMD_OK = 0,
    CMD_AGAIN = 1,
    CMD_ELOG = 2,
    CMD_ETIMEDOUT = 3,
    CMD_EIO = 4,
    CMD_EINVAL = 5,
    CMD_ENOMEM = 6,
    CMD_EBUSY = 7,
    CMD_ENOTSUP = 8,
    CMD_EPERM = 9,
    CMD_EUNKNOWN = 10
} sscma_client_error_t;
