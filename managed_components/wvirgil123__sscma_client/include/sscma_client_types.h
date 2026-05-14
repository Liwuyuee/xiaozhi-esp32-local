#pragma once

#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "cJSON.h"

#include "esp_assert.h"

#include "sscma_client_io_interface.h"
#include "sscma_client_flasher_interface.h"

#include "esp_io_expander.h"

#define SSCMA_CLIENT_MODEL_MAX_CLASSES   80
#define SSCMA_CLIENT_MODEL_KEYPOINTS_MAX 80

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sscma_client_t *sscma_client_handle_t;                 /*!< Type of SCCMA client handle */
typedef struct sscma_client_io_t *sscma_client_io_handle_t;           /*!< Type of SSCMA client IO handle */
typedef struct sscma_client_flasher_t *sscma_client_flasher_handle_t; /*!< Type of SCCMA client flasher handle */

/**
 * @brief Reply message
 */
typedef struct
{
    cJSON *payload;
    char *data;
    size_t len;
} sscma_client_reply_t;

/**
 * @brief Request message
 */
typedef struct
{
    char cmd[32];
    QueueHandle_t reply;
    ListItem_t item;
} sscma_client_request_t;

/**
 *
 */
typedef struct
{
    char *id;     /* !< ID */
    char *name;   /* !< Name */
    char *hw_ver; /* !< Hardware version */
    char *sw_ver; /* !< Software version */
    char *fw_ver; /* !< Firmware version */
} sscma_client_info_t;

typedef struct
{
    int id;                                        /* !< ID */
    char *uuid;                                    /* !< UUID */
    char *name;                                    /*!< Name */
    char *ver;                                     /*!< Version */
    char *url;                                     /*!< URL */
    char *checksum;                                /*!< Checksum */
    char *classes[SSCMA_CLIENT_MODEL_MAX_CLASSES]; /*!< Classes */
} sscma_client_model_t;

typedef struct
{
    int id;
    int type;
    int state;
    int opt_id;
    char *opt_detail;
} sscma_client_sensor_t;

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint8_t score;
    uint8_t target;
} sscma_client_box_t;

typedef struct
{
    uint8_t target;
    uint8_t score;
} sscma_client_class_t;

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint8_t score;
    uint8_t target;
} sscma_client_point_t;

typedef struct
{
    sscma_client_box_t box;
    uint8_t points_num;
    sscma_client_point_t points[SSCMA_CLIENT_MODEL_KEYPOINTS_MAX];
} sscma_client_keypoint_t;

/**
 * @brief Callback function of SCCMA client
 * @param[in] client SCCMA client handle
 * @param[in] reply Reply message
 * @param[in] user_ctx User context
 * @return None
 */
typedef void (*sscma_client_reply_cb_t)(sscma_client_handle_t client, const sscma_client_reply_t *reply, void *user_ctx);

/**
 * @brief Type of SCCMA client callback
 */
typedef struct
{
    sscma_client_reply_cb_t on_connect;
    sscma_client_reply_cb_t on_disconnect; // TODO
    sscma_client_reply_cb_t on_response;
    sscma_client_reply_cb_t on_event;
    sscma_client_reply_cb_t on_log;
} sscma_client_callback_t;

struct sscma_client_t
{
    sscma_client_io_handle_t io;           /* !< IO handle */
    sscma_client_flasher_handle_t flasher; /* !< flasher */
    int reset_gpio_num;                    /* !< GPIO number of reset pin */
    bool reset_level;                      /* !< Level of reset pin */
    bool inited;                           /* !< Whether inited */
    sscma_client_info_t info;              /* !< Info */
    sscma_client_model_t model;            /* !< Model */
    sscma_client_reply_cb_t on_connect;    /* !< Callback function */
    sscma_client_reply_cb_t on_disconnect; /* !< Callback function */
    sscma_client_reply_cb_t on_response;   /* !< Callback function */
    sscma_client_reply_cb_t on_event;      /* !< Callback function */
    sscma_client_reply_cb_t on_log;        /* !< Callback function */
    void *user_ctx;                        /* !< User context */
    esp_io_expander_handle_t io_expander;  /* !< IO expander handle */
    struct
    {
        TaskHandle_t handle;
#ifdef CONFIG_SSCMA_PROCESS_TASK_STACK_ALLOC_EXTERNAL
        StaticTask_t *task;
        StackType_t *stack;
#endif
    } monitor_task;
    struct
    {
        TaskHandle_t handle;
#ifdef CONFIG_SSCMA_MONITOR_TASK_STACK_ALLOC_EXTERNAL
        StaticTask_t *task;
        StackType_t *stack;
#endif
    } process_task;
    struct
    {
        char *data;            /* !< Data buffer */
        size_t len;            /* !< Data length */
        size_t pos;            /* !< Data position */
    } rx_buffer, tx_buffer;    /* !< RX and TX buffer */
    QueueHandle_t reply_queue; /* !< Queue for reply message */
    List_t *request_list;      /* !< Request list */
};

#ifdef __cplusplus
}
#endif
