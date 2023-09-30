cmake_minimum_required(VERSION 3.20)
project(cpu LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(cmx-bootstrap)
include(cmx-efi)
include(cmx-efitest)

file(GLOB_RECURSE CPU_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_library(cpu STATIC ${CPU_SOURCE_FILES})
cmx_set_freestanding(cpu PRIVATE)
target_include_directories(cpu PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
if ((CMX_COMPILER_GCC OR CMX_COMPILER_CLANG) AND CMX_CPU_X86 AND CMX_CPU_64_BIT)
    target_compile_options(cpu PRIVATE -march=x86-64) # Disable SSE/AVX
endif ()

efitest_add_tests(cpu-tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/test")
efitest_link_libraries(cpu-tests PRIVATE cpu)