cmake_minimum_required(VERSION 3.5)

set(testname test_${modulename})

project(${testname})

set(CMAKE_BUILD_TYPE Debug)

add_executable (${testname}
    ${CMAKE_CURRENT_LIST_DIR}/linkedlist_tests.c
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

target_link_libraries (${testname}
    ${modulename}
    cutest
)

add_test(${testname} ${testname})

set_tests_properties(${testname}
    PROPERTIES
    PASS_REGULAR_EXPRESSION "OK")
set_tests_properties(${testname}
    PROPERTIES
    FAIL_REGULAR_EXPRESSION "(Exception|FAILURES)")
set_tests_properties(${testname}
    PROPERTIES
    TIMEOUT 120)
