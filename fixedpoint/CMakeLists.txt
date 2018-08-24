cmake_minimum_required(VERSION 3.5)

# use directory name as module name
get_filename_component(modulename "${CMAKE_CURRENT_LIST_DIR}" NAME)

project(${modulename})

set(sourcefiles
    ${CMAKE_CURRENT_LIST_DIR}/fixedpoint.c
)

add_library(${modulename}
    ${sourcefiles}
)

target_include_directories(${modulename}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc
)

add_subdirectory(test)