cmake_minimum_required(VERSION 3.20)
project(cpu LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(cmx-bootstrap)

file(GLOB_RECURSE CPU_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_library(cpu STATIC ${CPU_SOURCE_FILES})
cmx_set_freestanding(cpu PRIVATE)
target_include_directories(cpu PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

cmx_add_tests(cpu-test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test")
target_link_libraries(cpu-test PRIVATE cpu)
add_dependencies(cpu-test cpu)
