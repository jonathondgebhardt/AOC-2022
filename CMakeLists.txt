cmake_minimum_required(VERSION 3.0)

# TODO: Don't hardcode year
project(AOC_2022 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
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
    src/Utilities.ipp
    ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.ipp
)

set(AOC_SOURCE
    src/Utilities.cpp
)

add_library(AOC STATIC
    ${AOC_SOURCE_H}
    ${AOC_SOURCE}
)

set(BUILD_SOLUTIONS ON CACHE BOOL "Enable building solutions")
if(BUILD_SOLUTIONS)
    add_subdirectory(solutions)
endif()


set(BUILD_STARTNEWDAY ON CACHE BOOL "Enable building StartNewDay")
if(BUILD_STARTNEWDAY)
    # TODO: Use vcpkg now that we have two dependencies?
    find_package(CURL REQUIRED)
    add_executable(StartNewDay src/StartNewDay.cpp src/HttpsRequest.cpp src/HttpsRequest.h)
    target_include_directories(StartNewDay PRIVATE ${CURL_INCLUDE_DIRS})
    target_link_libraries(StartNewDay ${CURL_LIBRARIES} AOC)
endif()

# https://crascit.com/2015/07/25/cmake-gtest/
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(
    COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(
    COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory(
    "${CMAKE_BINARY_DIR}/googletest-src"
    "${CMAKE_BINARY_DIR}/googletest-build"
)

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories(
        "${gtest_SOURCE_DIR}/include"
        "${gmock_SOURCE_DIR}/include"
    )
endif ()
