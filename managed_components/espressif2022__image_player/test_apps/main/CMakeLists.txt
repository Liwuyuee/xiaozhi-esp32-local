
idf_component_register(
    SRC_DIRS "."
    INCLUDE_DIRS "."
)

spiffs_create_partition_assets(
    assets_4bit
    "../test_4bit"
    FLASH_IN_PROJECT
    MMAP_FILE_SUPPORT_FORMAT ".aaf"
)

spiffs_create_partition_assets(
    assets_8bit
    "../test_8bit"
    FLASH_IN_PROJECT
    MMAP_FILE_SUPPORT_FORMAT ".aaf"
)