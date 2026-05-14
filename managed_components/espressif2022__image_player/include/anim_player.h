#pragma once

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LVGL port configuration structure
 *
 */
#define ANIM_PLAYER_INIT_CONFIG()                   \
    {                                              \
        .task_priority = 4,                        \
        .task_stack = 7168,                        \
        .task_affinity = -1,                       \
        .task_stack_caps = MALLOC_CAP_DEFAULT,     \
    }

typedef void *anim_player_handle_t;

typedef enum {
    PLAYER_ACTION_STOP = 0,
    PLAYER_ACTION_START,
} player_action_t;

typedef enum {
    PLAYER_EVENT_IDLE = 0,
    PLAYER_EVENT_ONE_FRAME_DONE,
    PLAYER_EVENT_ALL_FRAME_DONE,
} player_event_t;

typedef void (*anim_flush_cb_t)(anim_player_handle_t handle, int x1, int y1, int x2, int y2, const void *data);

typedef void (*anim_update_cb_t)(anim_player_handle_t handle, player_event_t event);

typedef struct {
    anim_flush_cb_t flush_cb;         ///< Callback function for flushing decoded data
    anim_update_cb_t update_cb;       ///< Callback function for updating player
    void *user_data;             ///< User data

    struct {
        unsigned char swap:1;
    } flags;
    struct {
        int task_priority;      ///< Task priority (1-20)
        int task_stack;         ///< Task stack size in bytes
        int task_affinity;      ///< CPU core ID (-1: no affinity, 0: core 0, 1: core 1)
        unsigned task_stack_caps; /*!< LVGL task stack memory capabilities (see esp_heap_caps.h) */
    } task;
} anim_player_config_t;

/**
 * @brief Initialize animation player
 *
 * @param config Player configuration
 * @return anim_player_handle_t Player handle, NULL on error
 */
anim_player_handle_t anim_player_init(const anim_player_config_t *config);

/**
 * @brief Deinitialize animation player
 *
 * @param handle Player handle
 */
void anim_player_deinit(anim_player_handle_t handle);

/**
 * @brief Update player event
 *
 * @param handle Player handle
 * @param event New event
 */
void anim_player_update(anim_player_handle_t handle, player_action_t event);

/**
 * @brief Check if flush is ready
 *
 * @param handle Player handle
 * @return bool True if the flush is ready, false otherwise
 */
bool anim_player_flush_ready(anim_player_handle_t handle);

/**
 * @brief Set the source data of the animation
 *
 * @param handle Player handle
 * @param src_data Source data
 * @param src_len Source data length
 * @return esp_err_t ESP_OK if successful, otherwise an error code
 */
esp_err_t anim_player_set_src_data(anim_player_handle_t handle, const void *src_data, size_t src_len);

/**
 * @brief Get the segment of the animation
 *
 * @param handle Player handle
 * @param start Start index
 * @param end End index
 */
void anim_player_get_segment(anim_player_handle_t handle, uint32_t *start, uint32_t *end);

/**
 * @brief Set the segment of the animation
 *
 * @param handle Player handle
 * @param start Start index
 * @param end End index
 * @param repeat Repeat setting
 */
void anim_player_set_segment(anim_player_handle_t handle, uint32_t start, uint32_t end, uint32_t fps, bool repeat);

/**
 * @brief Get the user data of the animation
 *
 * @param handle Player handle
 * @return void* User data
 */
void *anim_player_get_user_data(anim_player_handle_t handle);

#ifdef __cplusplus
}
#endif