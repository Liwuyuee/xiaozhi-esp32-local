/**
 * @file otto_emoji_gif.h
 * @brief Otto机器人GIF表情资源组件
 *
 * 这个头文件声明了Otto机器人的6个GIF表情资源，用于在LVGL显示屏上显示动态表情。
 *
 * @version 1.0.2
 * @date 2024
 *
 * 支持的表情：
 * - staticstate: 静态状态/中性表情
 * - sad: 悲伤表情
 * - happy: 开心表情
 * - scare: 惊吓/惊讶表情
 * - buxue: 不学/困惑表情
 * - anger: 愤怒表情
 */

#pragma once

#include <libs/gif/lv_gif.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Otto机器人表情GIF声明
 *
 * 这些GIF资源可以直接用于LVGL的lv_gif组件
 *
 * 使用示例：
 * ```c
 * lv_obj_t* gif = lv_gif_create(parent);
 * lv_gif_set_src(gif, &happy);  // 设置开心表情
 * ```
 */

// 静态状态/中性表情 - 默认表情，表示平静状态
LV_IMAGE_DECLARE(staticstate);

// 悲伤表情 - 表示难过、沮丧等负面情绪
LV_IMAGE_DECLARE(sad);

// 开心表情 - 表示高兴、愉快等正面情绪
LV_IMAGE_DECLARE(happy);

// 惊吓/惊讶表情 - 表示震惊、意外等情绪
LV_IMAGE_DECLARE(scare);

// 不学/困惑表情 - 表示疑惑、不理解等状态
LV_IMAGE_DECLARE(buxue);

// 愤怒表情 - 表示生气、愤怒等强烈情绪
LV_IMAGE_DECLARE(anger);

/**
 * @brief 获取组件版本
 * @return 版本字符串
 */
const char* otto_emoji_gif_get_version(void);

/**
 * @brief 获取支持的表情数量
 * @return 表情数量
 */
int otto_emoji_gif_get_count(void);

/**
 * @brief 根据名称获取表情资源
 * @param name 表情名称
 * @return 表情资源指针，如果未找到则返回NULL
 */
const lv_image_dsc_t* otto_emoji_gif_get_by_name(const char* name);

#ifdef __cplusplus
}
#endif