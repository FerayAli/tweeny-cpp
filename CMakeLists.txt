cmake_minimum_required(VERSION 3.4.3)

project(tweeny)
include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/utility")

option(BUILD_TWEENY_SHARED "Build as a shared library." ON)
option(BUILD_TWEENY_WITH_CODE_STYLE_CHECKS "Build with code style checks." ON)

if(BUILD_TWEENY_SHARED)
	set(BUILD_SHARED_LIBS ON)
endif()

add_subdirectory(tweeny)
