# Get all source files recursively from src directory
file(GLOB_RECURSE SRC_FILES "src/*.c")

idf_component_register(
    SRCS ${SRC_FILES}
    INCLUDE_DIRS
        "include"
    PRIV_INCLUDE_DIRS
        "include_priv"
        "src/lib/eaf"
    REQUIRES esp_timer
)
