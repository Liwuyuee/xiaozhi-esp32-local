#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <string.h>
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "anim_player.h"
#include "anim_vfs.h"
#include "anim_dec.h"

static const char *TAG = "anim_player";

#define NEED_DELETE     BIT0
#define DELETE_DONE     BIT1
#define WAIT_FLUSH_DONE BIT2
#define WAIT_STOP       BIT3
#define WAIT_STOP_DONE  BIT4

#define FPS_TO_MS(fps) (1000 / (fps))  // Convert FPS to milliseconds

typedef struct {
    player_action_t action;
} anim_player_event_t;

typedef struct {
    EventGroupHandle_t event_group;
    QueueHandle_t event_queue;
} anim_player_events_t;

typedef struct {
    uint32_t start;
    uint32_t end;
    anim_vfs_handle_t file_desc;
} anim_player_info_t;

// Animation player context
typedef struct {
    anim_player_info_t info;
    int run_start;
    int run_end;
    bool repeat;
    int fps;
    anim_flush_cb_t flush_cb;
    anim_update_cb_t update_cb;
    void *user_data;
    anim_player_events_t events;
    TaskHandle_t handle_task;
    struct {
        unsigned char swap: 1;
    } flags;
} anim_player_context_t;

typedef struct {
    player_action_t action;
    int run_start;
    int run_end;
    bool repeat;
    int fps;
    int64_t last_frame_time;
} anim_player_run_ctx_t;

static esp_err_t anim_player_parse(const uint8_t *data, size_t data_len, image_header_t *header, anim_player_context_t *ctx)
{
    // Allocate memory for split offsets
    uint16_t *offsets = (uint16_t *)malloc(header->splits * sizeof(uint16_t));
    if (offsets == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for offsets");
        return ESP_FAIL;
    }

    anim_dec_calculate_offsets(header, offsets);

    // Allocate frame buffer
    void *frame_buffer = malloc(header->width * header->split_height * sizeof(uint16_t));
    if (frame_buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for frame buffer");
        free(offsets);
        return ESP_FAIL;
    }

    // Allocate decode buffer
    uint8_t *decode_buffer = NULL;
    if (header->bit_depth == 4) {
        decode_buffer = (uint8_t *)malloc(header->width * (header->split_height + (header->split_height % 2)) / 2);
    } else if (header->bit_depth == 8) {
        decode_buffer = (uint8_t *)malloc(header->width * header->split_height);
    }
    if (decode_buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for decode buffer");
        free(offsets);
        free(frame_buffer);
        return ESP_FAIL;
    }

    uint16_t *pixels = (uint16_t *)frame_buffer;

    uint16_t color_depth = 0;

    if (header->bit_depth == 4) {
        color_depth = 16;
    } else if (header->bit_depth == 8) {
        color_depth = 256;
    }

    uint32_t *color_cache = (uint32_t *)malloc(color_depth * sizeof(uint32_t));
    if (color_cache == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for color_cache");
        free(frame_buffer);
        free(decode_buffer);
        free(offsets);
        return ESP_FAIL;
    }

    for (int i = 0; i < color_depth; i++) {
        color_cache[i] = 0xFFFFFFFF;
    }

    // Process each split
    for (int split = 0; split < header->splits; split++) {
        const uint8_t *compressed_data = data + offsets[split];
        int compressed_len = header->split_lengths[split];

        esp_err_t decode_result = ESP_FAIL;
        int valid_height;

        if (split == header->splits - 1) {
            valid_height = header->height - split * header->split_height;
        } else {
            valid_height = header->split_height;
        }
        ESP_LOGD(TAG, "split:%d(%d), height:%d(%d), compressed_len:%d", split, header->splits, header->split_height, valid_height, compressed_len);

        // Check encoding type from first byte
        if (compressed_data[0] == ENCODING_TYPE_RLE) {
            decode_result = anim_dec_rte_decode(compressed_data + 1, compressed_len - 1,
                                                decode_buffer, header->width * header->split_height);
        } else if (compressed_data[0] == ENCODING_TYPE_HUFFMAN) {
            uint8_t *huffman_buffer = malloc(header->width * header->split_height);
            if (huffman_buffer == NULL) {
                ESP_LOGE(TAG, "Failed to allocate memory for Huffman buffer");
                continue;
            }

            size_t huffman_decoded_len = 0;
            anim_dec_huffman_decode(compressed_data, compressed_len, huffman_buffer, &huffman_decoded_len);
            decode_result = ESP_OK;
            if (decode_result == ESP_OK) {
                decode_result = anim_dec_rte_decode(huffman_buffer, huffman_decoded_len,
                                                    decode_buffer, header->width * header->split_height);
            }
            free(huffman_buffer);
        } else {
            ESP_LOGE(TAG, "Unknown encoding type: %02X", compressed_data[0]);
            continue;
        }

        if (decode_result != ESP_OK) {
            ESP_LOGE(TAG, "Failed to decode split %d", split);
            continue;
        }

        // Convert to RGB565 based on bit depth
        if (header->bit_depth == 4) {
            // 4-bit mode: each byte contains two pixels
            for (int y = 0; y < valid_height; y++) {
                for (int x = 0; x < header->width; x += 2) {
                    uint8_t packed_gray = decode_buffer[y * (header->width / 2) + (x / 2)];
                    uint8_t index1 = (packed_gray & 0xF0) >> 4;
                    uint8_t index2 = (packed_gray & 0x0F);

                    if (color_cache[index1] == 0xFFFFFFFF) {
                        uint16_t color = anim_dec_parse_palette(header, index1, ctx->flags.swap);
                        color_cache[index1] = color;
                    }
                    pixels[y * header->width + x] = (uint16_t)color_cache[index1];

                    if (x + 1 < header->width) {
                        if (color_cache[index2] == 0xFFFFFFFF) {
                            uint16_t color = anim_dec_parse_palette(header, index2, ctx->flags.swap);
                            color_cache[index2] = color;
                        }
                        pixels[y * header->width + x + 1] = (uint16_t)color_cache[index2];
                    }
                }
            }
            
        } else if (header->bit_depth == 8) {
            // 8-bit mode: each byte is one pixel
            for (int y = 0; y < valid_height; y++) {
                // First process all indices in the line to ensure color_cache is populated
                for (int x = 0; x < header->width; x++) {
                    uint8_t index = decode_buffer[y * header->width + x];
                    if (color_cache[index] == 0xFFFFFFFF) {
                        uint16_t color = anim_dec_parse_palette(header, index, ctx->flags.swap);
                        color_cache[index] = color;
                    }
                    // Copy the color value directly
                    pixels[y * header->width + x] = (uint16_t)color_cache[index];
                }
            }
        } else {
            ESP_LOGE(TAG, "Unsupported bit depth: %d", header->bit_depth);
            continue;
        }

        // Flush decoded data
        xEventGroupClearBits(ctx->events.event_group, WAIT_FLUSH_DONE);
        if (ctx->flush_cb) {
            ctx->flush_cb(ctx, 0, split * header->split_height, header->width, split * header->split_height + valid_height, pixels);
        }
        xEventGroupWaitBits(ctx->events.event_group, WAIT_FLUSH_DONE, pdTRUE, pdFALSE, pdMS_TO_TICKS(20));
    }

    // Cleanup
    free(color_cache);
    free(offsets);
    free(frame_buffer);
    free(decode_buffer);
    anim_dec_free_header(header);

    return ESP_OK;
}

static void anim_player_task(void *arg)
{
    image_header_t header;
    anim_player_context_t *ctx = (anim_player_context_t *)arg;
    anim_player_run_ctx_t run_ctx;

    anim_player_event_t player_event;

    run_ctx.action = PLAYER_ACTION_STOP;
    run_ctx.run_start = ctx->run_start;
    run_ctx.run_end = ctx->run_end;
    run_ctx.repeat = ctx->repeat;
    run_ctx.fps = ctx->fps;
    run_ctx.last_frame_time = esp_timer_get_time();

    while (1) {
        EventBits_t bits = xEventGroupWaitBits(ctx->events.event_group,
                                               NEED_DELETE | WAIT_STOP,
                                               pdTRUE, pdFALSE, pdMS_TO_TICKS(10));

        if (bits & NEED_DELETE) {
            ESP_LOGW(TAG, "Player deleted");
            xEventGroupSetBits(ctx->events.event_group, DELETE_DONE);
            vTaskDeleteWithCaps(NULL);
        }

        if (bits & WAIT_STOP) {
            xEventGroupSetBits(ctx->events.event_group, WAIT_STOP_DONE);
        }

        // Check for new events in queue
        if (xQueueReceive(ctx->events.event_queue, &player_event, 0) == pdTRUE) {
            run_ctx.action = player_event.action;
            run_ctx.run_start = ctx->run_start;
            run_ctx.run_end = ctx->run_end;
            run_ctx.repeat = ctx->repeat;
            run_ctx.fps = ctx->fps;
            ESP_LOGD(TAG, "Player updated [%s]: %d -> %d, repeat:%d, fps:%d",
                     run_ctx.action == PLAYER_ACTION_START ? "START" : "STOP",
                     run_ctx.run_start, run_ctx.run_end, run_ctx.repeat, run_ctx.fps);
        }

        if (run_ctx.action == PLAYER_ACTION_STOP) {
            continue;
        }

        // Process animation frames
        do {
            for (int i = run_ctx.run_start; (i <= run_ctx.run_end) && (run_ctx.action != PLAYER_ACTION_STOP); i++) {
                // Frame rate control
                int64_t elapsed = esp_timer_get_time() - run_ctx.last_frame_time;
                elapsed = elapsed / 1000;
                if (elapsed < FPS_TO_MS(run_ctx.fps)) {
                    vTaskDelay(pdMS_TO_TICKS(FPS_TO_MS(run_ctx.fps) - elapsed));
                    ESP_LOGD(TAG, "delay: %d ms", (int)(FPS_TO_MS(run_ctx.fps) - elapsed));
                }
                run_ctx.last_frame_time = esp_timer_get_time();

                // Check for new events or delete request
                bits = xEventGroupWaitBits(ctx->events.event_group,
                                           NEED_DELETE | WAIT_STOP,
                                           pdTRUE, pdFALSE, pdMS_TO_TICKS(0));
                if (bits & NEED_DELETE) {
                    ESP_LOGW(TAG, "Playing deleted");
                    xEventGroupSetBits(ctx->events.event_group, DELETE_DONE);
                    vTaskDelete(NULL);
                }
                if (bits & WAIT_STOP) {
                    xEventGroupSetBits(ctx->events.event_group, WAIT_STOP_DONE);
                }

                if (xQueueReceive(ctx->events.event_queue, &player_event, 0) == pdTRUE) {
                    run_ctx.action = player_event.action;
                    run_ctx.run_start = ctx->run_start;
                    run_ctx.run_end = ctx->run_end;
                    run_ctx.fps = ctx->fps;
                    if (run_ctx.action == PLAYER_ACTION_STOP) {
                        run_ctx.repeat = false;
                    } else {
                        run_ctx.repeat = ctx->repeat;
                    }

                    ESP_LOGD(TAG, "Playing updated [%s]: %d -> %d, repeat:%d, fps:%d",
                             run_ctx.action == PLAYER_ACTION_START ? "START" : "STOP",
                             run_ctx.run_start, run_ctx.run_end, run_ctx.repeat, run_ctx.fps);
                    break;
                }

                const void *frame_data = anim_vfs_get_frame_data(ctx->info.file_desc, i);
                size_t frame_size = anim_vfs_get_frame_size(ctx->info.file_desc, i);

                image_format_t format = anim_dec_parse_header(frame_data, frame_size, &header);

                if (format == IMAGE_FORMAT_INVALID) {
                    ESP_LOGE(TAG, "Invalid frame format");
                    continue;
                } else if (format == IMAGE_FORMAT_REDIRECT) {
                    ESP_LOGE(TAG, "Invalid redirect frame");
                    continue;
                } else if (format == IMAGE_FORMAT_SBMP) {
                    anim_player_parse(frame_data, frame_size, &header, ctx);
                    if (ctx->update_cb) {
                        ctx->update_cb(ctx, PLAYER_EVENT_ONE_FRAME_DONE);
                    }
                }
            }
            if (ctx->update_cb) {
                ctx->update_cb(ctx, PLAYER_EVENT_ALL_FRAME_DONE);
            }
        } while (run_ctx.repeat);

        run_ctx.action = PLAYER_ACTION_STOP;

        if (ctx->update_cb) {
            ctx->update_cb(ctx, PLAYER_EVENT_IDLE);
        }
    }
}

bool anim_player_flush_ready(anim_player_handle_t handle)
{
    anim_player_context_t *ctx = (anim_player_context_t *)handle;
    if (ctx == NULL) {
        return false;
    }

    if (xPortInIsrContext()) {
        BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
        bool result = xEventGroupSetBitsFromISR(ctx->events.event_group, WAIT_FLUSH_DONE, &pxHigherPriorityTaskWoken);
        if (pxHigherPriorityTaskWoken == pdTRUE) {
            portYIELD_FROM_ISR();
        }
        return result;
    } else {
        return xEventGroupSetBits(ctx->events.event_group, WAIT_FLUSH_DONE);
    }
}

void anim_player_update(anim_player_handle_t handle, player_action_t event)
{
    anim_player_context_t *ctx = (anim_player_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid player context");
        return;
    }

    anim_player_event_t player_event = {
        .action = event,
    };

    if (xQueueSend(ctx->events.event_queue, &player_event, pdMS_TO_TICKS(10)) != pdTRUE) {
        ESP_LOGE(TAG, "Failed to send event to queue");
    }
    ESP_LOGD(TAG, "update event: %s", event == PLAYER_ACTION_START ? "START" : "STOP");
}

esp_err_t anim_player_set_src_data(anim_player_handle_t handle, const void *src_data, size_t src_len)
{
    anim_player_context_t *ctx = (anim_player_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid player context");
        return ESP_FAIL;
    }

    anim_vfs_handle_t new_desc;
    anim_vfs_init(src_data, src_len, &new_desc);
    if (new_desc == NULL) {
        ESP_LOGE(TAG, "Failed to initialize asset parser");
        return ESP_FAIL;
    }

    anim_player_update(handle, PLAYER_ACTION_STOP);
    xEventGroupSetBits(ctx->events.event_group, WAIT_STOP);
    xEventGroupWaitBits(ctx->events.event_group, WAIT_STOP_DONE, pdTRUE, pdFALSE, portMAX_DELAY);

    //delete old file_desc
    if (ctx->info.file_desc) {
        anim_vfs_deinit(ctx->info.file_desc);
        ctx->info.file_desc = NULL;
    }

    ctx->info.file_desc = new_desc;
    ctx->info.start = 0;
    ctx->info.end = anim_vfs_get_total_frames(new_desc) - 1;

    //default segment
    ctx->run_start = ctx->info.start;
    ctx->run_end = ctx->info.end;
    ctx->repeat = true;
    ctx->fps = CONFIG_ANIM_PLAYER_DEFAULT_FPS;

    return ESP_OK;
}

void anim_player_get_segment(anim_player_handle_t handle, uint32_t *start, uint32_t *end)
{
    anim_player_context_t *ctx = (anim_player_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid player context");
        return;
    }

    *start = ctx->info.start;
    *end = ctx->info.end;
}

void anim_player_set_segment(anim_player_handle_t handle, uint32_t start, uint32_t end, uint32_t fps, bool repeat)
{
    anim_player_context_t *ctx = (anim_player_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid player context");
        return;
    }

    if (end > ctx->info.end || (start > end)) {
        ESP_LOGE(TAG, "Invalid segment");
        return;
    }

    ctx->run_start = start;
    ctx->run_end = end;
    ctx->repeat = repeat;
    ctx->fps = fps;
    ESP_LOGD(TAG, "set segment: %" PRIu32 " -> %" PRIu32 ", repeat:%d, fps:%" PRIu32 "", start, end, repeat, fps);
}

void *anim_player_get_user_data(anim_player_handle_t handle)
{
    anim_player_context_t *ctx = (anim_player_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid player context");
        return NULL;
    }

    return ctx->user_data;
}

anim_player_handle_t anim_player_init(const anim_player_config_t *config)
{
    if (!config) {
        ESP_LOGE(TAG, "Invalid configuration");
        return NULL;
    }

    anim_player_context_t *player = malloc(sizeof(anim_player_context_t));
    if (!player) {
        ESP_LOGE(TAG, "Failed to allocate player context");
        return NULL;
    }

    player->info.file_desc = NULL;
    player->info.start = 0;
    player->info.end = 0;
    player->run_start = 0;
    player->run_end = 0;
    player->repeat = false;
    player->fps = CONFIG_ANIM_PLAYER_DEFAULT_FPS;
    player->flush_cb = config->flush_cb;
    player->update_cb = config->update_cb;
    player->user_data = config->user_data;
    player->flags.swap = config->flags.swap;
    player->events.event_group = xEventGroupCreate();
    player->events.event_queue = xQueueCreate(5, sizeof(anim_player_event_t));

    // Set default task configuration if not specified
    const uint32_t caps = config->task.task_stack_caps ? config->task.task_stack_caps : MALLOC_CAP_DEFAULT; // caps cannot be zero
    if (config->task.task_affinity < 0) {
        xTaskCreateWithCaps(anim_player_task, "Anim Player", config->task.task_stack, player, config->task.task_priority, &player->handle_task, caps);
    } else {
        xTaskCreatePinnedToCoreWithCaps(anim_player_task, "Anim Player", config->task.task_stack, player, config->task.task_priority, &player->handle_task, config->task.task_affinity, caps);
    }

    return (anim_player_handle_t)player;
}

void anim_player_deinit(anim_player_handle_t handle)
{
    anim_player_context_t *ctx = (anim_player_context_t *)handle;
    if (ctx == NULL) {
        ESP_LOGE(TAG, "Invalid player context");
        return;
    }

    // Send event to stop the task
    if (ctx->events.event_group) {
        xEventGroupSetBits(ctx->events.event_group, NEED_DELETE);
        xEventGroupWaitBits(ctx->events.event_group, DELETE_DONE, pdTRUE, pdFALSE, portMAX_DELAY);
    }

    // Delete event group
    if (ctx->events.event_group) {
        vEventGroupDelete(ctx->events.event_group);
        ctx->events.event_group = NULL;
    }

    // Delete event queue
    if (ctx->events.event_queue) {
        vQueueDelete(ctx->events.event_queue);
        ctx->events.event_queue = NULL;
    }

    if (ctx->info.file_desc) {
        anim_vfs_deinit(ctx->info.file_desc);
        ctx->info.file_desc = NULL;
    }

    // Free player context
    free(ctx);
}
