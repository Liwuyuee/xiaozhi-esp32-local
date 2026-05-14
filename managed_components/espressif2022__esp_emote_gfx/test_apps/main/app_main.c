/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "unity.h"
#include "unity_test_utils.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
// #include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_check.h"
#include "driver/gpio.h"
#if CONFIG_IDF_TARGET_ESP32S3 && ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
#include "esp_lcd_panel_rgb.h"
#endif
#include "gfx.h"
#include "mmap_generate_test_assets.h"

static const char *TAG = "player";
#define TEST_MEMORY_LEAK_THRESHOLD (500)

extern const gfx_image_dsc_t icon1;
extern const gfx_image_dsc_t icon5;

extern const lv_font_t font_puhui_16_4;

static size_t before_free_8bit;
static size_t before_free_32bit;

static gfx_handle_t emote_handle = NULL;
static esp_lcd_panel_io_handle_t io_handle = NULL;
static esp_lcd_panel_handle_t panel_handle = NULL;

static gfx_obj_t *label_tips = NULL;

void setUp(void)
{
    before_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    before_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
}

void tearDown(void)
{
    size_t after_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t after_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    unity_utils_check_leak(before_free_8bit, after_free_8bit, "8BIT", TEST_MEMORY_LEAK_THRESHOLD);
    unity_utils_check_leak(before_free_32bit, after_free_32bit, "32BIT", TEST_MEMORY_LEAK_THRESHOLD);
}

static bool flush_io_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    gfx_handle_t emote_handle = (gfx_handle_t)user_ctx;
    if (emote_handle) {
        gfx_emote_flush_ready(emote_handle, true);
    }
    return true;
}

static void flush_callback(gfx_handle_t emote_handle, int x1, int y1, int x2, int y2, const void *data)
{
    esp_lcd_panel_handle_t panel = (esp_lcd_panel_handle_t)gfx_emote_get_user_data(emote_handle);
    esp_lcd_panel_draw_bitmap(panel, x1, y1, x2, y2, data);
    gfx_emote_flush_ready(emote_handle, true);
}

void clock_tm_callback(void *user_data)
{
    gfx_obj_t *label_obj = (gfx_obj_t *)user_data;
    if (label_obj) {
        gfx_label_set_text_fmt(label_obj, "%d*%d: %d", BSP_LCD_H_RES, BSP_LCD_V_RES, gfx_timer_get_actual_fps(emote_handle));
    }
    ESP_LOGI("FPS", "%d*%d: %" PRIu32 "", BSP_LCD_H_RES, BSP_LCD_V_RES, gfx_timer_get_actual_fps(emote_handle));
}

static void test_timer_function(void)
{
    ESP_LOGI(TAG, "=== Testing Timer Function ===");

    gfx_emote_lock(emote_handle);
    gfx_timer_handle_t timer = gfx_timer_create(emote_handle, clock_tm_callback, 1000, label_tips);
    TEST_ASSERT_NOT_NULL(timer);
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_timer_set_period(timer, 500);
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_timer_set_repeat_count(timer, 5);
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_timer_pause(timer);
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_timer_resume(timer);
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_timer_reset(timer);
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_timer_delete(emote_handle, timer);
    gfx_emote_unlock(emote_handle);
}

static void test_animation_function(mmap_assets_handle_t assets_handle)
{
    ESP_LOGI(TAG, "=== Testing Animation Function ===");

    // Define test cases for different bit depths and animation files
    struct {
        int asset_id;
        const char *name;
        int mirror_offset;
    } test_cases[] = {
        {MMAP_TEST_ASSETS_MI_1_EYE_4BIT_AAF,    "MI_1_EYE 4-bit animation",     10},
        {MMAP_TEST_ASSETS_MI_1_EYE_8BIT_EAF,    "MI_1_EYE 8-bit animation",     10},
        {MMAP_TEST_ASSETS_MI_1_EYE_24BIT_AAF,   "MI_1_EYE 24-bit animation",    10},
        {MMAP_TEST_ASSETS_MI_2_EYE_4BIT_AAF,    "MI_2_EYE 4-bit animation",     100},
        {MMAP_TEST_ASSETS_MI_2_EYE_8BIT_AAF,    "MI_2_EYE 8-bit animation",     100},
        {MMAP_TEST_ASSETS_MI_2_EYE_24BIT_AAF,   "MI_2_EYE 24-bit animation",    100}
    };

    gfx_emote_lock(emote_handle);
    gfx_emote_set_bg_color(emote_handle, GFX_COLOR_HEX(0xFF0000));
    gfx_emote_unlock(emote_handle);

    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        ESP_LOGI(TAG, "--- Testing %s ---", test_cases[i].name);

        gfx_emote_lock(emote_handle);

        gfx_obj_t *anim_obj = gfx_anim_create(emote_handle);
        TEST_ASSERT_NOT_NULL(anim_obj);

        const void *anim_data = mmap_assets_get_mem(assets_handle, test_cases[i].asset_id);
        size_t anim_size = mmap_assets_get_size(assets_handle, test_cases[i].asset_id);
        esp_err_t ret = gfx_anim_set_src(anim_obj, anim_data, anim_size);
        TEST_ASSERT_EQUAL(ESP_OK, ret);

        if (strstr(test_cases[i].name, "MI_1_EYE")) {
            gfx_obj_set_pos(anim_obj, 20, 10);
        } else {
            gfx_obj_align(anim_obj, GFX_ALIGN_CENTER, 0, 0);
        }
        gfx_anim_set_mirror(anim_obj, false, 0);
        gfx_obj_set_size(anim_obj, 200, 150);
        gfx_anim_set_segment(anim_obj, 0, 90, 50, true);

        ret = gfx_anim_start(anim_obj);
        TEST_ASSERT_EQUAL(ESP_OK, ret);

        gfx_emote_unlock(emote_handle);

        vTaskDelay(pdMS_TO_TICKS(3000));

        gfx_emote_lock(emote_handle);
        gfx_anim_set_mirror(anim_obj, true, test_cases[i].mirror_offset);
        gfx_emote_unlock(emote_handle);

        vTaskDelay(pdMS_TO_TICKS(3000));

        gfx_emote_lock(emote_handle);
        gfx_anim_stop(anim_obj);
        gfx_emote_unlock(emote_handle);

        vTaskDelay(pdMS_TO_TICKS(2000));

        gfx_emote_lock(emote_handle);
        gfx_obj_delete(anim_obj);
        gfx_emote_unlock(emote_handle);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_LOGI(TAG, "=== Animation Function Testing Completed ===");
}

static void test_label_map_function(mmap_assets_handle_t assets_handle)
{
    ESP_LOGI(TAG, "=== Testing Label Map Function ===");

    gfx_emote_lock(emote_handle);

    gfx_obj_t *label_obj = gfx_label_create(emote_handle);
    TEST_ASSERT_NOT_NULL(label_obj);
    ESP_LOGI(TAG, "Label object created successfully");

    gfx_obj_set_size(label_obj, 150, 100);
    gfx_label_set_font(label_obj, (gfx_font_t)&font_puhui_16_4);

    gfx_label_set_text(label_obj, "AAA乐鑫BBB乐鑫CCC乐鑫CCC乐鑫BBB乐鑫AAA");
    gfx_label_set_color(label_obj, GFX_COLOR_HEX(0x0000FF));
    gfx_label_set_long_mode(label_obj, GFX_LABEL_LONG_SCROLL);
    gfx_label_set_bg_color(label_obj, GFX_COLOR_HEX(0xFF0000));
    gfx_label_set_bg_enable(label_obj, true);
    gfx_obj_align(label_obj, GFX_ALIGN_TOP_MID, 0, 100);

    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_label_set_color(label_obj, GFX_COLOR_HEX(0x00FF00));
    gfx_emote_unlock(emote_handle);

    ESP_LOGI(TAG, "re-render label end");
    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_obj_delete(label_obj);
    gfx_emote_unlock(emote_handle);

}

static void test_label_freetype_function(mmap_assets_handle_t assets_handle)
{
    ESP_LOGI(TAG, "=== Testing Label Function ===");

    gfx_emote_lock(emote_handle);

    gfx_obj_t *label_obj = gfx_label_create(emote_handle);
    TEST_ASSERT_NOT_NULL(label_obj);
    ESP_LOGI(TAG, "Label object created successfully");

#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
    gfx_label_cfg_t font_cfg = {
        .name = "DejaVuSans.ttf",
        .mem = mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_DEJAVUSANS_TTF),
        .mem_size = (size_t)mmap_assets_get_size(assets_handle, MMAP_TEST_ASSETS_DEJAVUSANS_TTF),
        .font_size = 20,
    };

    gfx_font_t font_DejaVuSans;
    esp_err_t ret = gfx_label_new_font(&font_cfg, &font_DejaVuSans);
    TEST_ASSERT_EQUAL(ESP_OK, ret);
    gfx_label_set_font(label_obj, font_DejaVuSans);
#endif

    gfx_label_set_bg_enable(label_obj, true);
    gfx_label_set_bg_color(label_obj, GFX_COLOR_HEX(0xFF0000));
    gfx_label_set_long_mode(label_obj, GFX_LABEL_LONG_WRAP);
    gfx_label_set_text(label_obj, "Hello World");
    gfx_label_set_color(label_obj, GFX_COLOR_HEX(0x00FF00));
    gfx_obj_set_pos(label_obj, 100, 200);
    gfx_obj_align(label_obj, GFX_ALIGN_TOP_MID, 0, 100);
    gfx_obj_set_size(label_obj, 200, 100);

    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(1000 * 3));

    gfx_emote_lock(emote_handle);
    gfx_label_set_text_fmt(label_obj, "Count: %d, Float: %.2f", 42, 3.14);
    gfx_label_set_long_mode(label_obj, GFX_LABEL_LONG_SCROLL);
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(2000));

    gfx_emote_lock(emote_handle);
    gfx_label_set_color(label_obj, GFX_COLOR_HEX(0x0000FF));
    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(2000));

    gfx_emote_lock(emote_handle);
    gfx_obj_delete(label_obj);
#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
    gfx_label_delete_font(font_DejaVuSans);
#endif
    gfx_emote_unlock(emote_handle);
}

static void test_image_function(mmap_assets_handle_t assets_handle)
{
    gfx_image_dsc_t img_dsc;

    ESP_LOGI(TAG, "=== Testing Image Function ===");

    gfx_emote_lock(emote_handle);

    ESP_LOGI(TAG, "--- Testing C_ARRAY format image ---");
    gfx_obj_t *img_obj_c_array = gfx_img_create(emote_handle);
    TEST_ASSERT_NOT_NULL(img_obj_c_array);

    gfx_img_set_src(img_obj_c_array, (void *)&icon1);
    gfx_obj_set_pos(img_obj_c_array, 100, 100);

    uint16_t width, height;
    gfx_obj_get_size(img_obj_c_array, &width, &height);

    gfx_emote_unlock(emote_handle);
    vTaskDelay(pdMS_TO_TICKS(2000));

    gfx_emote_lock(emote_handle);
    gfx_obj_delete(img_obj_c_array);

    ESP_LOGI(TAG, "--- Testing BIN format image ---");
    gfx_obj_t *img_obj_bin = gfx_img_create(emote_handle);
    TEST_ASSERT_NOT_NULL(img_obj_bin);

    img_dsc.data_size = mmap_assets_get_size(assets_handle, MMAP_TEST_ASSETS_ICON5_BIN);
    img_dsc.data = mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_ICON5_BIN);

    memcpy(&img_dsc.header, mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_ICON5_BIN), sizeof(gfx_image_header_t));
    img_dsc.data += sizeof(gfx_image_header_t);
    img_dsc.data_size -= sizeof(gfx_image_header_t);
    gfx_img_set_src(img_obj_bin, (void *)&img_dsc);

    gfx_obj_set_pos(img_obj_bin, 100, 180);
    gfx_obj_get_size(img_obj_bin, &width, &height);

    gfx_emote_unlock(emote_handle);
    vTaskDelay(pdMS_TO_TICKS(2000));

    gfx_emote_lock(emote_handle);
    gfx_obj_delete(img_obj_bin);

    ESP_LOGI(TAG, "--- Testing multiple images with different formats ---");
    gfx_obj_t *img_obj1 = gfx_img_create(emote_handle);
    gfx_obj_t *img_obj2 = gfx_img_create(emote_handle);
    TEST_ASSERT_NOT_NULL(img_obj1);
    TEST_ASSERT_NOT_NULL(img_obj2);

    gfx_img_set_src(img_obj1, (void *)&icon5); // C_ARRAY format

    img_dsc.data_size = mmap_assets_get_size(assets_handle, MMAP_TEST_ASSETS_ICON1_BIN);
    img_dsc.data = mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_ICON1_BIN);

    memcpy(&img_dsc.header, mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_ICON1_BIN), sizeof(gfx_image_header_t));
    img_dsc.data += sizeof(gfx_image_header_t);
    img_dsc.data_size -= sizeof(gfx_image_header_t);
    gfx_img_set_src(img_obj2, (void *)&img_dsc); // BIN format

    gfx_obj_set_pos(img_obj1, 150, 100);
    gfx_obj_set_pos(img_obj2, 150, 180);

    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gfx_emote_lock(emote_handle);
    gfx_obj_delete(img_obj1);
    gfx_obj_delete(img_obj2);
    gfx_emote_unlock(emote_handle);
}

static void test_multiple_objects_function(mmap_assets_handle_t assets_handle)
{
    ESP_LOGI(TAG, "=== Testing Multiple Objects Interaction ===");

    gfx_emote_lock(emote_handle);

    gfx_obj_t *anim_obj = gfx_anim_create(emote_handle);
    gfx_obj_t *img_obj = gfx_img_create(emote_handle);
    gfx_obj_t *label_obj = gfx_label_create(emote_handle);
    gfx_timer_handle_t timer = gfx_timer_create(emote_handle, clock_tm_callback, 2000, label_obj);

    TEST_ASSERT_NOT_NULL(anim_obj);
    TEST_ASSERT_NOT_NULL(label_obj);
    TEST_ASSERT_NOT_NULL(img_obj);
    TEST_ASSERT_NOT_NULL(timer);
    ESP_LOGI(TAG, "Multiple objects created successfully");

    const void *anim_data = mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_MI_2_EYE_8BIT_AAF);
    size_t anim_size = mmap_assets_get_size(assets_handle, MMAP_TEST_ASSETS_MI_2_EYE_8BIT_AAF);

    gfx_anim_set_src(anim_obj, anim_data, anim_size);
    gfx_obj_align(anim_obj, GFX_ALIGN_CENTER, 0, 0);
    gfx_anim_set_segment(anim_obj, 0, 30, 15, true);
    gfx_anim_start(anim_obj);

#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
    gfx_label_cfg_t font_cfg = {
        .name = "DejaVuSans.ttf",
        .mem = mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_DEJAVUSANS_TTF),
        .mem_size = (size_t)mmap_assets_get_size(assets_handle, MMAP_TEST_ASSETS_DEJAVUSANS_TTF),
        .font_size = 20,
    };

    gfx_font_t font_DejaVuSans;
    esp_err_t ret = gfx_label_new_font(&font_cfg, &font_DejaVuSans);
    TEST_ASSERT_EQUAL(ESP_OK, ret);
    gfx_label_set_font(label_obj, font_DejaVuSans);
#endif

    gfx_obj_set_size(label_obj, 200, 50);
    gfx_label_set_text(label_obj, "Multi-Object Test");
    gfx_label_set_color(label_obj, GFX_COLOR_HEX(0xFF0000));
    gfx_obj_align(label_obj, GFX_ALIGN_BOTTOM_MID, 0, 0);

    gfx_image_dsc_t img_dsc;
    const void *img_data = mmap_assets_get_mem(assets_handle, MMAP_TEST_ASSETS_ICON1_BIN);
    img_dsc.data_size = mmap_assets_get_size(assets_handle, MMAP_TEST_ASSETS_ICON1_BIN);
    img_dsc.data = img_data;

    memcpy(&img_dsc.header, img_data, sizeof(gfx_image_header_t));
    img_dsc.data += sizeof(gfx_image_header_t);
    img_dsc.data_size -= sizeof(gfx_image_header_t);

    gfx_img_set_src(img_obj, (void *)&img_dsc); // Use BIN format image
    gfx_obj_align(img_obj, GFX_ALIGN_TOP_MID, 0, 0);

    gfx_emote_unlock(emote_handle);

    vTaskDelay(pdMS_TO_TICKS(1000 * 10));

    gfx_emote_lock(emote_handle);
    gfx_timer_delete(emote_handle, timer);
    gfx_obj_delete(anim_obj);
    gfx_obj_delete(label_obj);
    gfx_obj_delete(img_obj);
#ifdef CONFIG_GFX_FONT_FREETYPE_SUPPORT
    gfx_label_delete_font(font_DejaVuSans);
#endif
    gfx_emote_unlock(emote_handle);
}

static esp_err_t init_display_and_graphics(const char *partition_label, uint32_t max_files, uint32_t checksum, mmap_assets_handle_t *assets_handle)
{
    const mmap_assets_config_t asset_config = {
        .partition_label = partition_label,
        .max_files = max_files,
        .checksum = checksum,
        .flags = {.mmap_enable = true, .full_check = true}
    };

    esp_err_t ret = mmap_assets_new(&asset_config, assets_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize assets");
        return ret;
    }

    const bsp_display_config_t bsp_disp_cfg = {
        .max_transfer_sz = (BSP_LCD_H_RES * 100) * sizeof(uint16_t),
    };
    bsp_display_new(&bsp_disp_cfg, &panel_handle, &io_handle);
    esp_lcd_panel_disp_on_off(panel_handle, true);
    // bsp_display_brightness_init();
    bsp_display_backlight_on();

    gfx_core_config_t gfx_cfg = {
        .flush_cb = flush_callback,
        .update_cb = NULL,
        .user_data = panel_handle,
        .flags = {.swap = true, .double_buffer = true},
        .h_res = BSP_LCD_H_RES,
        .v_res = BSP_LCD_V_RES,
        .fps = 30,
        .buffers = {.buf1 = NULL, .buf2 = NULL, .buf_pixels = BSP_LCD_H_RES * 16},
        .task = GFX_EMOTE_INIT_CONFIG()
    };
    gfx_cfg.task.task_stack_caps = MALLOC_CAP_DEFAULT;
    gfx_cfg.task.task_affinity = 0;
    gfx_cfg.task.task_priority = 7;
    gfx_cfg.task.task_stack = 20 * 1024;

    const esp_lcd_panel_io_callbacks_t cbs = {
        .on_color_trans_done = flush_io_ready,
    };
    esp_lcd_panel_io_register_event_callbacks(io_handle, &cbs, emote_handle);

    emote_handle = gfx_emote_init(&gfx_cfg);
    if (emote_handle == NULL) {
        ESP_LOGE(TAG, "Failed to initialize graphics system");
        mmap_assets_del(*assets_handle);
        return ESP_FAIL;
    }

    return ESP_OK;
}

static void cleanup_display_and_graphics(mmap_assets_handle_t assets_handle)
{
    if (emote_handle != NULL) {
        gfx_emote_deinit(emote_handle);
        emote_handle = NULL;
    }
    if (assets_handle != NULL) {
        mmap_assets_del(assets_handle);
    }

    if (panel_handle) {
        esp_lcd_panel_del(panel_handle);
    }
    if (io_handle) {
        esp_lcd_panel_io_del(io_handle);
    }
    // spi_bus_free(BSP_LCD_SPI_NUM);
    spi_bus_free(SPI3_HOST);

    vTaskDelay(pdMS_TO_TICKS(1000));
}

TEST_CASE("test timer function", "[timer]")
{
    mmap_assets_handle_t assets_handle = NULL;
    esp_err_t ret = init_display_and_graphics("assets_8bit", MMAP_TEST_ASSETS_FILES, MMAP_TEST_ASSETS_CHECKSUM, &assets_handle);
    TEST_ASSERT_EQUAL(ESP_OK, ret);

    test_timer_function();

    cleanup_display_and_graphics(assets_handle);
}

TEST_CASE("test animation function", "[animation]")
{
    mmap_assets_handle_t assets_handle = NULL;
    esp_err_t ret = init_display_and_graphics("assets_8bit", MMAP_TEST_ASSETS_FILES, MMAP_TEST_ASSETS_CHECKSUM, &assets_handle);
    TEST_ASSERT_EQUAL(ESP_OK, ret);

    test_animation_function(assets_handle);

    cleanup_display_and_graphics(assets_handle);
}

TEST_CASE("test label function", "[label][freetype]")
{
    mmap_assets_handle_t assets_handle = NULL;
    esp_err_t ret = init_display_and_graphics("assets_8bit", MMAP_TEST_ASSETS_FILES, MMAP_TEST_ASSETS_CHECKSUM, &assets_handle);
    TEST_ASSERT_EQUAL(ESP_OK, ret);

    test_label_freetype_function(assets_handle);

    cleanup_display_and_graphics(assets_handle);
}

TEST_CASE("test label function", "[label][map]")
{
    mmap_assets_handle_t assets_handle = NULL;
    esp_err_t ret = init_display_and_graphics("assets_8bit", MMAP_TEST_ASSETS_FILES, MMAP_TEST_ASSETS_CHECKSUM, &assets_handle);
    TEST_ASSERT_EQUAL(ESP_OK, ret);

    test_label_map_function(assets_handle);

    cleanup_display_and_graphics(assets_handle);
}

TEST_CASE("test image function", "[image]")
{
    mmap_assets_handle_t assets_handle = NULL;
    esp_err_t ret = init_display_and_graphics("assets_8bit", MMAP_TEST_ASSETS_FILES, MMAP_TEST_ASSETS_CHECKSUM, &assets_handle);
    TEST_ASSERT_EQUAL(ESP_OK, ret);

    test_image_function(assets_handle);

    ESP_LOGE(TAG, "cleanup_display_and_graphics");
    cleanup_display_and_graphics(assets_handle);
}

TEST_CASE("test multi objects function", "[multi]")
{
    mmap_assets_handle_t assets_handle = NULL;
    esp_err_t ret = init_display_and_graphics("assets_8bit", MMAP_TEST_ASSETS_FILES, MMAP_TEST_ASSETS_CHECKSUM, &assets_handle);
    TEST_ASSERT_EQUAL(ESP_OK, ret);

    test_multiple_objects_function(assets_handle);

    cleanup_display_and_graphics(assets_handle);
}

void app_main(void)
{
    printf("Animation player test\n");
    unity_run_menu();
}
