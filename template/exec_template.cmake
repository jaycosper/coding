# define minumum CMake version to use
cmake_minimum_required(VERSION 3.5)

# use directory name as module name
get_filename_component(projectname ${CMAKE_CURRENT_LIST_DIR} NAME)

# define the CMake project
project(${projectname})

# build options
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/gcc)
set(CMAKE_BUILD_TYPE Debug) # set the debug build type ("-g")

set(compile_defines
    "-DMY_DEFINE=1"
)
set(compile_options
    -Werror
    -Wall
)
#add_definitions(${compile_defines})
#add_compile_options(${compile_options})

# define library source files
set(sourcefiles
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)

# add source files to library
add_executable(${projectname}
    ${sourcefiles}
)

target_compile_definitions(${projectname} PRIVATE "${compile_defines}")
target_compile_options(${projectname} PRIVATE "${compile_options}")

# link to dependent libraries (if required)
#target_link_libraries(${projectname}
#    assert
#)

# include and publically expose everything in inc directory
target_include_directories(${projectname}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>
)
