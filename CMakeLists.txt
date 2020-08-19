cmake_minimum_required(VERSION 3.4.3)

project(tweeny)
include(CTest)

option(BUILD_TWEENY_SHARED "Build as a shared library." ON)
option(BUILD_TWEENY_TESTS "Build the tests" ON)

if(BUILD_TWEENY_TESTS)
    if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
    endif()
    if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
    endif()
    if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
    endif()
endif()

if(BUILD_TWEENY_SHARED)
	set(BUILD_SHARED_LIBS ON)
endif()

add_subdirectory(tweeny)

if(BUILD_TWEENY_TESTS)
    add_subdirectory(tests)
endif()
