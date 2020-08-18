file(GLOB_RECURSE file_sources "*.cpp" "*.h" "*.hpp")

set(target_name tweeny)

add_library(${target_name} SHARED ${file_sources})

target_include_directories(${target_name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")
