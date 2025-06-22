cmake_minimum_required(VERSION 3.20)
project(SharedPtr)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(SharedPtr main.cpp)

# Compiler-specific options for GCC in MSYS2
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(SharedPtr PRIVATE -Wall -Wextra -pedantic)
endif()

# Explicitly set compiler for MSYS2
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")
endif()
