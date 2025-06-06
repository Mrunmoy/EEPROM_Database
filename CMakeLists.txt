cmake_minimum_required(VERSION 3.5)
project(EEDatabase C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output binaries to bin/ similar to the old Makefile
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(EEDatabase
    src/EEPROM_Mapping.c
    src/database.c
    src/factory_defaults.c
    src/test.c
)

target_include_directories(EEDatabase PRIVATE ${CMAKE_SOURCE_DIR}/inc)

target_compile_options(EEDatabase PRIVATE -Wall -O3 -g -Wno-pointer-to-int-cast)
