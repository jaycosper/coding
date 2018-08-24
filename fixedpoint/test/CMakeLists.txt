cmake_minimum_required(VERSION 3.5)

project(test_${modulename})

set(CMAKE_BUILD_TYPE Debug)

add_executable (test_${modulename} 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

target_link_libraries (test_${modulename} 
    LINK_PUBLIC ${modulename}
)