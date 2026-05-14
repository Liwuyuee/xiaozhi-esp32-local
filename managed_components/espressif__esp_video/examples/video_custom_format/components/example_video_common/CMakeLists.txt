set(srcs "example_init_video.c")
set(inc_dirs "include")

if(NOT CONFIG_IDF_TARGET_ESP32C61)
    list(APPEND srcs "example_encoder.c")
endif()

if(CONFIG_EXAMPLE_SELECT_ESP32P4_FUNCTION_EV_BOARD_V1_4)
    list(APPEND inc_dirs "include/boards/esp32-p4-function-ev-board-v1.4")
elseif(CONFIG_EXAMPLE_SELECT_ESP32P4_FUNCTION_EV_BOARD_V1_5)
    list(APPEND inc_dirs "include/boards/esp32-p4-function-ev-board-v1.5")
elseif(CONFIG_EXAMPLE_SELECT_ESP32P4_EYE)
    list(APPEND inc_dirs "include/boards/esp32-p4-eye")
elseif(CONFIG_EXAMPLE_SELECT_ESP32S3_EYE)
    list(APPEND inc_dirs "include/boards/esp32-s3-eye")
elseif(CONFIG_EXAMPLE_SELECT_CUSTOMIZED_DEV_BOARD)
    list(APPEND inc_dirs "include/boards/customized")
endif()

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${inc_dirs}"
                       REQUIRES "esp_video")

if(CONFIG_EXAMPLE_SELECT_JPEG_HW_DRIVER)
    idf_component_optional_requires(PRIVATE "esp_driver_jpeg")
endif()
