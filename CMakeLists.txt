cmake_minimum_required(VERSION 3.5)

# use directory name as module name
get_filename_component(modulename ${CMAKE_CURRENT_LIST_DIR} NAME)

project(${modulename})

include(CTest)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(
    -Werror
)

add_subdirectory( fixedpoint )
add_subdirectory( averager )
add_subdirectory( assert )
add_subdirectory( ffpn )
