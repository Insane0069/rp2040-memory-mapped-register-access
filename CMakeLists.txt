cmake_minimum_required(VERSION 3.13)

# Pull in the Pico SDK
include(pico_sdk_import.cmake)

# Project Name
project(rp2040-register-access C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# Create Executable
add_executable(rp2040-register-access
    src/main.c
)

# Include Header Files
target_include_directories(rp2040-register-access PRIVATE
    include
)

# Create UF2, BIN and HEX files
pico_add_extra_outputs(rp2040-register-access)