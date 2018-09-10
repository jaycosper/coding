# define minumum CMake version to use
cmake_minimum_required(VERSION 3.5)

# use directory name as module name
get_filename_component(modulename ${CMAKE_CURRENT_LIST_DIR} NAME)

# define the CMake project
project(${modulename})

# set the debug build type ("-g")
set(CMAKE_BUILD_TYPE Debug)

# define library source files
set(sourcefiles
    ${CMAKE_CURRENT_LIST_DIR}/template.c
)

# add source files to library
add_library(${modulename}
    ${sourcefiles}
)

# link to dependent libraries (if required)
#target_link_libraries(${modulename}
#    assert
#)

# include and publically expose everything in inc directory
target_include_directories(${modulename}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>
)

# add in the test CMake file
add_subdirectory(test)
