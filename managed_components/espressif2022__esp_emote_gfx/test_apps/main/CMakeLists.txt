
idf_component_register(
    SRC_DIRS "." "./assets"
    INCLUDE_DIRS "."
)

get_filename_component(ESP_EMOTE_GFX_COMPONENT_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

# set_property(SOURCE font_puhui_16_4.c APPEND PROPERTY
#     INCLUDE_DIRECTORIES "${ESP_EMOTE_GFX_COMPONENT_DIR}/include"
# )

spiffs_create_partition_assets(
    assets_8bit
    "../test_assets"
    FLASH_IN_PROJECT
    MMAP_FILE_SUPPORT_FORMAT ".aaf,.ttf,.bin,.eaf"
)
