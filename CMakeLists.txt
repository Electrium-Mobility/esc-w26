cmake_minimum_required(VERSION 3.16)
project(esc)

# Set C language standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Automatically collect all .c files from core/src and platform/host (and platform/common/src)
file(GLOB CORE_SOURCES core/src/*.c)
file(GLOB PLATFORM_SOURCES platform/host/*.c)
file(GLOB PLATFORM_SRC_SOURCES platform/common/src/*.c)

# Add PC-side entry points
set(SOURCES
    ${CORE_SOURCES}
    ${PLATFORM_SOURCES}
    ${PLATFORM_SRC_SOURCES}
)   

add_executable(esc ${SOURCES})

# Include dirs for headers
target_include_directories(esc PRIVATE
    core/inc
    platform/inc
)
