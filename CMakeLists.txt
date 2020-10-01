cmake_minimum_required(VERSION 3.13)
project(pljit)

if (NOT UNIX)
    message(FATAL_ERROR "Unsupported OS")
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(EnableAddressSanitizer)
include(EnableUndefinedSanitizer)
include(clang-tidy)
include(BundledGTest)

add_custom_target(lint)

add_subdirectory(pljit)
add_subdirectory(test)
