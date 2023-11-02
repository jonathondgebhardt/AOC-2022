cmake_minimum_required(VERSION 3.0)

# Must be done before the first call to project()
# https://github.com/Microsoft/vcpkg#vcpkg-with-visual-studio-cmake-projects
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Save on initial build time by only building vcpkg packages in release.
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_LIST_DIR}/triplets")

# TODO: Don't hardcode year
project(AOC_2022 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

include_directories(src)

# Generate a file that allows source code to use paths in the project like "inputs".
get_filename_component(INPUT_FILE_PATH "inputs" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOLUTIONS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/solutions")
configure_file(src/InputDirectoryConfig.cpp.in ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.cpp)
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(AOC_SOURCE_H
    src/ACSolver.ipp
    src/Utilities.ipp
    src/InputDirectoryConfig.hpp
)

set(AOC_SOURCE
    src/Utilities.cpp
    ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.cpp
)

add_library(AOC STATIC
    ${AOC_SOURCE_H}
    ${AOC_SOURCE}
)

find_package(CURL CONFIG REQUIRED)
add_executable(StartNewDay src/StartNewDay.cpp src/HttpsRequest.cpp src/HttpsRequest.hpp)
target_link_libraries(StartNewDay PRIVATE CURL::libcurl AOC)

enable_testing()
find_package(GTest CONFIG REQUIRED)
add_subdirectory(solutions)
