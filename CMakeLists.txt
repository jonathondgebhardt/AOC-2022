cmake_minimum_required(VERSION 3.0)

project(AOC_2022 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})

include_directories(src)

get_filename_component(INPUT_FILE_PATH "inputs" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOLUTIONS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/solutions")
configure_file(src/InputDirectoryConfig.ipp.in ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp)
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(AOC_SOURCE_H
    src/ACSolver.ipp
    src/Export.hpp
    src/Utilities.ipp
    ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp
)

set(AOC_SOURCE
    src/Utilities.cpp
)

add_library(AOC SHARED
    ${AOC_SOURCE_H}
    ${AOC_SOURCE}
)

set(BUILD_SOLUTIONS ON CACHE BOOL "Enable building solutions")
if(BUILD_SOLUTIONS)
    add_subdirectory(solutions)
endif()


set(BUILD_STARTNEWDAY ON CACHE BOOL "Enable building StartNewDay")
if(BUILD_STARTNEWDAY)
    add_executable(StartNewDay ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp src/StartNewDay.cpp)
endif()
