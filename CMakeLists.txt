# -------------------------------------------------------------------

cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)  # CMake version check


# -------------------------------------------------------------------

set(PROJECT_NAME                      # Define all project info
    FallingSand 
    LANGUAGES CXX
    VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project

set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# Flags of compiling
add_compile_options(
    -Wall -Wextra -Wpedantic -Werror -pedantic -g -Ofast 
)

add_subdirectory(src)

# -------------------------------------------------------------------