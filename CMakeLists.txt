cmake_minimum_required(VERSION 3.14)
project(EEDatabase CXX)

set(CMAKE_CXX_STANDARD 14)

# Library
set(SRC_FILES src/EEDatabase.cpp)
add_library(EEDatabase ${SRC_FILES})
target_include_directories(EEDatabase PUBLIC ${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/include)
target_compile_options(EEDatabase PUBLIC -Wall -O3 -g)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)
