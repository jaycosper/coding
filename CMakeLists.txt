# define minumum CMake version to use
cmake_minimum_required(VERSION 3.5)

# use directory name as module name
get_filename_component(modulename ${CMAKE_CURRENT_LIST_DIR} NAME)

# define the CMake project
project(${modulename})

# include CTest framework
include(CTest)

# set the debug build type ("-g")
set(CMAKE_BUILD_TYPE Debug)

# add global compilation flags
add_compile_options(
    -Wall
    -Werror
)

# add each library's CMake file
add_subdirectory( template )
add_subdirectory( cutest )
add_subdirectory( fixedpoint )
add_subdirectory( averager )
add_subdirectory( assert )
add_subdirectory( ffpn )
add_subdirectory( linkedlist )
add_subdirectory( stack )
