cmake_minimum_required(VERSION 3.5)

set(modulename cutest)

project(${modulename})

set(CMAKE_BUILD_TYPE Debug)

set(sourcefiles
    ${CMAKE_CURRENT_LIST_DIR}/cutest.c
)

add_library(${modulename}
    ${sourcefiles}
)

target_include_directories(${modulename}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>
)
