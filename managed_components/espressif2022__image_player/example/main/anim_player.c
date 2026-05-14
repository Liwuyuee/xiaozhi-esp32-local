#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "bsp/esp-bsp.h"

#include "lvgl.h"
#include "anim_player.h"
#include "mmap_generate_assets.h"

static const char *TAG = "player";

static anim_player_handle_t handle = NULL;

static void anim_flush_cb(anim_player_handle_t handle, int x1, int y1, int x2, int y2, const void *data)
{
    lv_obj_t *flush_canvas = (lv_obj_t *)anim_player_get_user_data(handle);

    lv_canvas_copy_buf(flush_canvas, (const void *)data, (lv_coord_t)x1, (lv_coord_t)y1, (lv_coord_t)(x2 - x1), (lv_coord_t)(y2 - y1));
    anim_player_flush_ready(handle);
}

static void anim_update_cb(anim_player_handle_t handle, player_event_t event)
{
    lv_obj_t *flush_canvas = (lv_obj_t *)anim_player_get_user_data(handle);
    static uint32_t start_time = 0;
    static int total_frames = 0;

    switch (event) {
    case PLAYER_EVENT_IDLE:
        ESP_LOGI(TAG, "Event: IDLE");
        break;
    case PLAYER_EVENT_ONE_FRAME_DONE:
        if (start_time == 0) {
            start_time = esp_timer_get_time();
        }
        total_frames++;
        bsp_display_lock(0);
        lv_obj_invalidate(flush_canvas);
        // lv_refr_now(NULL);
        bsp_display_unlock();
        break;
    case PLAYER_EVENT_ALL_FRAME_DONE:
        {
            uint32_t end_time = esp_timer_get_time();
            float duration_sec = (end_time - start_time) / 1000000.0f;
            float fps = total_frames / duration_sec;
            ESP_LOGI(TAG, "Event: ALL_FRAME_DONE - FPS: %.2f (Frames: %d, Duration: %.2fs)", 
                    fps, total_frames, duration_sec);
            // Reset counters for next playback
            start_time = 0;
            total_frames = 0;
        }
        break;
    default:
        ESP_LOGI(TAG, "Event: UNKNOWN");
        break;
    }
}

static void test_anim_player_common(const char *partition_label, uint32_t max_files, uint32_t checksum, uint32_t delay_ms)
{
    mmap_assets_handle_t assets_handle = NULL;
    const mmap_assets_config_t asset_config = {
        .partition_label = partition_label,
        .max_files = max_files,
        .checksum = checksum,
        .flags = {.mmap_enable = true, .full_check = true}
    };

    esp_err_t ret = mmap_assets_new(&asset_config, &assets_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize assets");
        return;
    }

    bsp_display_start();
    bsp_display_backlight_on();

    bsp_display_lock(0);

    lv_obj_t *canvas = lv_canvas_create(lv_scr_act());
    lv_obj_set_size(canvas, 240, 400);
    lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(canvas, LV_ALIGN_CENTER, 0, 0);
    uint8_t *canvas_draw_buf  = heap_caps_malloc(240 * 400 * sizeof(uint16_t), MALLOC_CAP_DEFAULT);
    lv_canvas_set_buffer(canvas, (void *)canvas_draw_buf, 240, 400, LV_IMG_CF_TRUE_COLOR);

    bsp_display_unlock();

    anim_player_config_t config = {
        .flush_cb = anim_flush_cb,
        .update_cb = anim_update_cb,
        .user_data = canvas,
        .flags = {.swap = true},
        .task = ANIM_PLAYER_INIT_CONFIG()
    };
    config.task.task_stack_caps = MALLOC_CAP_INTERNAL;
    config.task.task_affinity = 1;

    handle = anim_player_init(&config);

    uint32_t start, end;

    const void *src_data = mmap_assets_get_mem(assets_handle, MMAP_ASSETS_OUTPUT_AAF);
    size_t src_len = mmap_assets_get_size(assets_handle, MMAP_ASSETS_OUTPUT_AAF);

    ESP_LOGW(TAG, "set src, %s", mmap_assets_get_name(assets_handle, MMAP_ASSETS_OUTPUT_AAF));
    anim_player_set_src_data(handle, src_data, src_len);
    anim_player_get_segment(handle, &start, &end);
    anim_player_set_segment(handle, start, end, 40, true);
    ESP_LOGW(TAG, "start:%" PRIu32 ", end:%" PRIu32 "", start, end);

    anim_player_update(handle, PLAYER_ACTION_START);
    vTaskDelay(pdMS_TO_TICKS(1000 * 1000));
}

void app_main(void)
{
    printf("Animation player test\n");
    // unity_run_menu();
    test_anim_player_common("assets_8bit", MMAP_ASSETS_FILES, MMAP_ASSETS_CHECKSUM, 5);
}