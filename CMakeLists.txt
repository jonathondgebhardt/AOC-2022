cmake_minimum_required(VERSION 3.0)

project(AOC_2022 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)

set(CMAKE_BUILD_TYPE 
    Release 
    CACHE 
    STRING 
    "Choose the build type: Debug Release"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})

include_directories(include solutions)

set(AOC_SOURCE
    src/Utilities.cpp
)

get_filename_component(INPUT_FILE_PATH "inputs" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOLUTIONS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/solutions")
configure_file(include/InputDirectoryConfig.ipp.in ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp)
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(AOC_SOURCE_H
    include/Export.hpp
    include/Utilities.ipp
    ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp
)

set(BUILD_SOLUTIONS ON CACHE BOOL "Enable building solutions")
if(BUILD_SOLUTIONS)
    # My goal is to accumulate solution Utility definitions and compile them into a single library.
    # Add subdirectories before building our AOC shared library so we can grab solution Utility files.
    add_subdirectory(solutions)
endif()

add_library(AOC SHARED 
    ${AOC_SOURCE_H}
    ${AOC_SOURCE}
)

set(BUILD_STARTNEWDAY ON CACHE BOOL "Enable building StartNewDay")
if(BUILD_STARTNEWDAY)
    add_executable(StartNewDay ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp src/StartNewDay.cpp)
endif()
