# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# (Not part of the boilerplate)
# This example uses extra components for the following -
# 1. Check sd card pins info
list(APPEND EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/storage/sd_card/sdmmc/components/sd_card)

project(sd_card)
