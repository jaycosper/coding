cmake_minimum_required(VERSION 3.5)

# use directory name as module name
get_filename_component(modulename ${CMAKE_CURRENT_LIST_DIR} NAME)

project(${modulename})

set(CMAKE_BUILD_TYPE Debug)

# Create a header-only library
add_library(${modulename} INTERFACE)

target_include_directories(${modulename}
    INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc
)
