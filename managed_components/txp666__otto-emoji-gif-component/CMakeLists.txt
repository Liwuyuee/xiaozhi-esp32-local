# Otto机器人GIF表情组件
# 
# 这个组件包含了Otto机器人的6个GIF表情资源：
# - staticstate (静态状态/中性表情)
# - sad (悲伤表情)
# - happy (开心表情)
# - scare (惊吓/惊讶表情)
# - buxue (不学/困惑表情)
# - anger (愤怒表情)

# 收集所有GIF源文件
file(GLOB GIF_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# 检查是否找到GIF源文件
list(LENGTH GIF_SOURCES GIF_COUNT)
if(GIF_COUNT EQUAL 0)
    message(WARNING "未找到GIF源文件，请确保src目录中包含.c文件")
endif()

# 注册组件
idf_component_register(
    SRCS ${GIF_SOURCES}
    INCLUDE_DIRS "include"
    REQUIRES "lvgl"
)

# 添加编译定义
target_compile_definitions(${COMPONENT_LIB}
    PRIVATE OTTO_EMOJI_GIF_VERSION="1.0.2"
)

# 输出调试信息
message(STATUS "Otto Emoji GIF Component:")
message(STATUS "  Found ${GIF_COUNT} GIF source files")
message(STATUS "  Include directory: ${CMAKE_CURRENT_SOURCE_DIR}/include") 