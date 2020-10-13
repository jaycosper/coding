cmake_minimum_required(VERSION 3.5)

# use directory name as module name
get_filename_component(modulename ${CMAKE_CURRENT_LIST_DIR} NAME)

project(${modulename})

set(CMAKE_BUILD_TYPE Debug)

set(sourcefiles
    ${CMAKE_CURRENT_LIST_DIR}/stack.c
)

add_executable(${modulename}
    ${sourcefiles}
)

#target_link_libraries(${modulename}
#    tbd
#)

target_include_directories(${modulename}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>
)

#add_subdirectory(test)

target_compile_options(${modulename} PRIVATE 
    -Wno-unused-variable
    -Wno-uninitialized
    -O3
)
