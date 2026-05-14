set(srcs "src/esp_video_buffer.c"
         "src/esp_video_init.c"
         "src/esp_video_ioctl.c"
         "src/esp_video_mman.c"
         "src/esp_video_vfs.c"
         "src/esp_video.c"
         "src/esp_video_cam.c")

set(include_dirs "include")
set(priv_include_dirs "private_include")
set(priv_requires "vfs")
set(requires "esp_driver_cam" "esp_cam_sensor")

if(CONFIG_IDF_TARGET_ESP32P4)
    if(CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT)
        list(APPEND srcs "src/data_reprocessing/esp32p4/esp_video_swap_short.c")
        list(APPEND srcs "src/data_reprocessing/esp32p4/esp_video_swap_short.S")
    endif()

    if(CONFIG_ESP_VIDEO_ENABLE_SWAP_BYTE)
        list(APPEND srcs "src/data_reprocessing/esp32p4/esp_video_swap_byte.c")
        list(APPEND srcs "src/data_reprocessing/esp32p4/esp_video_swap_byte.S")
    endif()
endif()

if(CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE)
    list(APPEND srcs "src/device/esp_video_csi_device.c")
endif()

if(CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE)
    list(APPEND srcs "src/device/esp_video_dvp_device.c")
endif()

if(CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE)
    list(APPEND srcs "src/device/esp_video_spi_device.c")
endif()

if(CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE)
    list(APPEND srcs "src/device/esp_video_usb_uvc_device.c")
endif()

if(CONFIG_ESP_VIDEO_ENABLE_H264_VIDEO_DEVICE)
    list(APPEND srcs "src/device/esp_video_h264_device.c")
endif()

if(CONFIG_ESP_VIDEO_ENABLE_JPEG_VIDEO_DEVICE)
    list(APPEND srcs "src/device/esp_video_jpeg_device.c")
endif()

if(CONFIG_ESP_VIDEO_ENABLE_ISP)
    list(APPEND srcs "src/device/esp_video_isp_device.c")

    if(CONFIG_ESP_VIDEO_ENABLE_ISP_PIPELINE_CONTROLLER)
        list(APPEND srcs "src/esp_video_isp_pipeline.c")
    endif()
endif()

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${include_dirs}
                       PRIV_INCLUDE_DIRS ${priv_include_dirs}
                       PRIV_REQUIRES ${priv_requires}
                       REQUIRES ${requires})

include(package_manager)
cu_pkg_define_version(${CMAKE_CURRENT_LIST_DIR})

if(CONFIG_ESP_VIDEO_ENABLE_ISP_PIPELINE_CONTROLLER)
    idf_component_optional_requires(PRIVATE "esp_ipa")
endif()

 if(CONFIG_IDF_TARGET_ESP32P4)
    if(CONFIG_ESP_VIDEO_ENABLE_ISP)
        # Supply the header files to applications
        idf_component_optional_requires(PUBLIC "esp_driver_isp")
    endif()

    if(CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE)
        # Supply the header files to applications
        idf_component_optional_requires(PUBLIC "esp_driver_jpeg")
    endif()

    if(CONFIG_ESP_VIDEO_ENABLE_H264_VIDEO_DEVICE)
        idf_component_optional_requires(PRIVATE "esp_h264")
    endif()

    if(CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT_PERF_LOG)
        idf_component_optional_requires(PRIVATE "esp_timer")
    endif()

    if(CONFIG_ESP_VIDEO_ENABLE_BITSCRAMBLER)
        idf_component_optional_requires(PRIVATE "esp_driver_bitscrambler")

        if(CONFIG_ESP_VIDEO_ENABLE_SWAP_SHORT)
            target_bitscrambler_add_src("src/data_reprocessing/esp32p4/esp_video_swap_short.bsasm")
        endif()

        if(CONFIG_ESP_VIDEO_ENABLE_SWAP_BYTE)
            target_bitscrambler_add_src("src/data_reprocessing/esp32p4/esp_video_swap_byte.bsasm")
        endif()
    endif()
endif()
