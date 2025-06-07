cmake_minimum_required(VERSION 3.5)
project(EEDatabase C)

# Gather all source files
file(GLOB SOURCES src/*.c)

# Create executable
add_executable(EEDatabase ${SOURCES})

# Include directories
target_include_directories(EEDatabase PRIVATE inc)

# Compiler flags
target_compile_options(EEDatabase PRIVATE -Wall -O3 -g -Wno-pointer-to-int-cast)

# Output directory
set_target_properties(EEDatabase PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)


