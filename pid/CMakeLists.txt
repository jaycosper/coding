cmake_minimum_required(VERSION 3.15)

# use directory name as module name
get_filename_component(modulename ${CMAKE_CURRENT_LIST_DIR} NAME)

project(${modulename})

set(CMAKE_BUILD_TYPE Debug)

set(sourcefiles
    ${CMAKE_CURRENT_LIST_DIR}/pid.c
)

add_library(${modulename}
    ${sourcefiles}
)

target_link_libraries(${modulename}
    assert
)

target_include_directories(${modulename}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>
)

add_subdirectory(test)