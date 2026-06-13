cmake_minimum_required(VERSION 3.16)
project(esc)

# Set C language standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Automatically collect all .c files from core/src and platform/host (and platform/common/src)
file(GLOB CORE_SOURCES core/src/*.c)
file(GLOB HAL_HOST_SOURCES hal/host/src/*.c)
file(GLOB HAL_COMMON_SOURCES hal/common/src/*.c)
file(GLOB UTILS_SOURCES utils/src/*.c)

# Add PC-side entry points
set(SOURCES
    ${CORE_SOURCES}
    ${HAL_HOST_SOURCES}
    ${HAL_COMMON_SOURCES}
    ${UTILS_SOURCES}
)

add_executable(esc ${SOURCES})

# Include dirs for headers
target_include_directories(esc PRIVATE
    core/inc
    hal/host/inc
    hal/common/inc
    utils/inc
)
