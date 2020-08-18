cmake_minimum_required(VERSION 3.4.3)

project(tweeny)
include(CTest)

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

add_subdirectory(tweeny)

if(BUILD_TWEENY_TESTS)
    add_subdirectory(tests)
endif()
