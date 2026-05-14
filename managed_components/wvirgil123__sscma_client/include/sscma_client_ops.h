#pragma once

#include "esp_err.h"
#include "esp_io_expander.h"
#include "sscma_client_types.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configuration of SCCMA client
 */
typedef struct
{
    int reset_gpio_num;                   /*!< GPIO number of reset pin */
    int tx_buffer_size;                   /*!< Size of TX buffer */
    int rx_buffer_size;                   /*!< Size of RX buffer */
    int process_task_priority;            /* SSCMA process task priority */
    int process_task_stack;               /* SSCMA process task stack size */
    int process_task_affinity;            /* SSCMA process task pinned to core (-1 is no
                                             affinity) */
    int monitor_task_priority;            /* SSCMA monitor task priority */
    int monitor_task_stack;               /* SSCMA monitor task stack size */
    int monitor_task_affinity;            /* SSCMA monitor task pinned to core (-1 is no
                                             affinity) */
    int event_queue_size;                 /* Event queue size */
    void *user_ctx;                       /* User context */
    esp_io_expander_handle_t io_expander; /*!< IO expander handle */
    struct
    {
        unsigned int reset_active_high : 1;  /*!< Setting this if the panel reset is
                                                high level active */
        unsigned int reset_use_expander : 1; /*!< Reset line use IO expander */
    } flags;                                 /*!< SSCMA client config flags */
} sscma_client_config_t;

#define SSCMA_CLIENT_CONFIG_DEFAULT()                                                                                                                                                                  \
    {                                                                                                                                                                                                  \
        .reset_gpio_num = -1, .tx_buffer_size = 4096, .rx_buffer_size = 65536, .process_task_priority = 5, .process_task_stack = 4096, .process_task_affinity = -1, .monitor_task_priority = 4,        \
        .monitor_task_stack = 10240, .monitor_task_affinity = -1, .event_queue_size = 2, .user_ctx = NULL,                                                                                             \
        .flags = {                                                                                                                                                                                     \
            .reset_active_high = false,                                                                                                                                                                \
        },                                                                                                                                                                                             \
    }

/**
 * @brief Create new SCCMA client
 *
 * @param[in] io IO handle
 * @param[in] config SCCMA client config
 * @param[out] ret_client SCCMA client handle
 * @return
 *          - ESP_OK on success
 *          - ESP_ERR_INVALID_ARG if parameter is invalid
 *          - ESP_ERR_NO_MEM if out of memory
 */
esp_err_t sscma_client_new(const sscma_client_io_handle_t io, const sscma_client_config_t *config, sscma_client_handle_t *ret_client);

/**
 * @brief Destroy SCCMA client
 *
 * @param[in] client SCCMA client handle
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_del(sscma_client_handle_t client);

/**
 * @brief Initialize SCCMA client
 *
 * @param[in] client SCCMA client handle
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_init(sscma_client_handle_t client);

/**
 * @brief Reset SCCMA client
 *
 * @param[in] client SCCMA client handle
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_reset(sscma_client_handle_t client);
/**
 * @brief Read data from SCCMA client
 *
 * @param[in] client SCCMA client handle
 * @param[out] data Data to be read
 * @param[in] size Size of data
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NOT_SUPPORTED if read is not supported by transport
 *          - ESP_OK                on success
 */
esp_err_t sscma_client_read(sscma_client_handle_t client, void *data, size_t size);

/**
 * @brief Write data to SCCMA client
 *
 * @param[in] client SCCMA client handle
 * @param[in] data Data to be written
 * @param[in] size Size of data
 * @return
 *          - ESP_ERR_INVALID_ARG   if parameter is invalid
 *          - ESP_ERR_NOT_SUPPORTED if read is not supported by transport
 *          - ESP_OK                on success
 */
esp_err_t sscma_client_write(sscma_client_handle_t client, const void *data, size_t size);

/**
 * @brief Get available data
 *
 * @param[in] client SCCMA client handle
 * @param[out] ret_avail Available data
 *
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_available(sscma_client_handle_t client, size_t *ret_avail);

/**
 * @brief Register callback
 *
 * @param[in] client SCCMA client handle
 * @param[in] callback SCCMA client callback
 * @param[in] user_ctx User context
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_register_callback(sscma_client_handle_t client, const sscma_client_callback_t *callback, void *user_ctx);

/**
 * @brief Clear reply
 *
 * @param[in] reply Reply
 * @return void
 */
void sscma_client_reply_clear(sscma_client_reply_t *reply);

/**
 * @brief Send request to SCCMA client
 *
 * @param[in] client SCCMA client handle
 *
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_request(sscma_client_handle_t client, const char *cmd, sscma_client_reply_t *reply, bool wait, TickType_t timeout);

/**
 * @brief Get SCCMA client info
 *
 * @param[in] client SCCMA client handle
 * @param[in] info Copyer to sscma_client_info_t
 * @param[in] cached true if info is cached
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_get_info(sscma_client_handle_t client, sscma_client_info_t **info, bool cached);

/**
 * @brief Send request to SCCMA clien
 *
 * @param[in] client SCCMA client handle
 * @param[in] model Copyer to sscma_client_model_t
 * @param[in] cached true if model is cached
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_get_model(sscma_client_handle_t client, sscma_client_model_t **model, bool cached);

/**
 * @brief Set model
 *
 * @param[in] client SCCMA client handle
 * @param[in] model Copyer to sscma_client_model_t
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_set_model(sscma_client_handle_t client, int model);

/**
 * @brief Set sensor
 *
 * @param[in] client SCCMA client handle
 * @param[in] id sensor id
 * @param[in] opt_id sensor config
 * @param[in] bool true if enable
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_set_sensor(sscma_client_handle_t client, int id, int opt_id, bool enable);

/**
 * @brief Get sensor
 *
 * @param[in] client SCCMA client handle
 * @param[in] sensor Copyer to sscma_client_sensor_t
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_get_sensor(sscma_client_handle_t client, sscma_client_sensor_t *sensor);

/**
 * @brief SSCMA client sample
 * @param[in] client SCCMA client handle
 * @param[in] times Number of times
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_sample(sscma_client_handle_t client, int times);

/**
 * @brief SSCMA client invoke
 * @param[in] client SCCMA client handle
 * @param[in] times Number of times
 * @param[in] fliter true if fliter
 * @param[in] show true if show
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_invoke(sscma_client_handle_t client, int times, bool fliter, bool show);

/**
 * @brief SSCMA client break
 * @param[in] client SCCMA client handle
 * @return
 *          - ESP_OK on success
 */

esp_err_t sscma_client_break(sscma_client_handle_t client);

/**
 * @brief Set iou threshold
 * @param[in] client SCCMA client handle
 * @param[in] threshold iou threshold
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_set_iou_threshold(sscma_client_handle_t client, int threshold);

/**
 * @brief Get iou threshold
 * @param[in] client SCCMA client handle
 * @param[out] threshold iou threshold
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_get_iou_threshold(sscma_client_handle_t client, int *threshold);

/**
 * @brief Set confidence threshold
 * @param[in] client SCCMA client handle
 * @param[in] threshold confidence threshold
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_set_confidence_threshold(sscma_client_handle_t client, int threshold);

/**
 * @brief Get confidence threshold
 * @param[in] client SCCMA client handle
 * @param[out] threshold confidence threshold
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_get_confidence_threshold(sscma_client_handle_t client, int *threshold);

/**
 * @brief Set model info
 * @param[in] client SCCMA client handle
 * @param[in] model_info model info
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_set_model_info(sscma_client_handle_t client, const char *model_info);

/**
 * Fetch boxes and classes from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] boxes sscma client boxes
 * @param[out] num_boxes number of boxes
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_fetch_boxes_from_reply(const sscma_client_reply_t *reply, sscma_client_box_t **boxes, int *num_boxes);

/**
 * Prase boxes from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] boxes sscma client boxes
 * @param[in] max_boxes max number of boxes
 * @param[out] num_boxes number of boxes
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_copy_boxes_from_reply(const sscma_client_reply_t *reply, sscma_client_box_t *boxes, int max_boxes, int *num_boxes);

/**
 * Fetch classes from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] classes sscma client classes
 * @param[out] num_classes number of classes
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_fetch_classes_from_reply(const sscma_client_reply_t *reply, sscma_client_class_t **classes, int *num_classes);

/**
 * Prase classes from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] classes sscma client classes
 * @param[in] max_classes max number of classes
 * @param[out] num_classes number of classes
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_copy_classes_from_reply(const sscma_client_reply_t *reply, sscma_client_class_t *classes, int max_classes, int *num_classes);

/**
 * Fetch points from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] points sscma client points
 * @param[out] num_points number of points
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_fetch_points_from_reply(const sscma_client_reply_t *reply, sscma_client_point_t **points, int *num_points);

/**
 * Prase points from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] points sscma client points
 * @param[in] max_points max number of points
 * @param[out] num_points number of points
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_copy_points_from_reply(const sscma_client_reply_t *reply, sscma_client_point_t *points, int max_points, int *num_points);

/**
 * Fetch keypoints from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] keypoints sscma client keypoints
 * @param[out] num_keypoints number of keypoints
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_fetch_keypoints_from_reply(const sscma_client_reply_t *reply, sscma_client_keypoint_t **keypoints, int *num_keypoints);

/**
 * Prase keypoints from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] keypoints sscma client keypoints
 * @param[in] max_keypoints max number of keypoints
 * @param[out] num_keypoints number of keypoints
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_copy_keypoints_from_reply(const sscma_client_reply_t *reply, sscma_client_keypoint_t *keypoints, int max_keypoints, int *num_keypoints);

/**
 * Fetch image from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] image sscma client image
 * @param[out] image_size size of image
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_fetch_image_from_reply(const sscma_client_reply_t *reply, char **image, int *image_size);

/**
 * Prase image from sscma client reply
 * @param[in] reply sscma client reply
 * @param[out] image sscma client image
 * @param[in] max_image_size max size of image
 * @param[out] image_size size of image
 * @return
 *    - ESP_OK
 */
esp_err_t sscma_utils_copy_image_from_reply(const sscma_client_reply_t *reply, char *image, int max_image_size, int *image_size);

/**
 * Start ota
 * @param[in] client SCCMA client handle
 * @param[in] flasher flasher handle
 * @param[in] offset offset in file
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_ota_start(sscma_client_handle_t client, const sscma_client_flasher_handle_t flasher, size_t offset);

/**
 * Write data to ota
 * @param[in] client SCCMA client handle
 * @param[in] data data to write
 * @param[in] len length of data
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_ota_write(sscma_client_handle_t client, const void *data, size_t len);

/**
 * Finish ota
 * @param[in] client SCCMA client handle
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_ota_finish(sscma_client_handle_t client);

/**
 * Abort ota
 * @param[in] client SCCMA client handle
 * @return
 *          - ESP_OK on success
 */
esp_err_t sscma_client_ota_abort(sscma_client_handle_t client);

#ifdef __cplusplus
}
#endif