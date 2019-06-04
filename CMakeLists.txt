cmake_minimum_required(VERSION 3.6)
project(jpeg2rgb C)

set(CMAKE_C_STANDARD 99)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")
find_package(TurboJPEG REQUIRED)

include_directories(${TurboJPEG_INCLUDE_DIRS})

add_executable(jpeg2rgb src/main.c src/rgb_file.c src/jpeg_file.c)
target_link_libraries(jpeg2rgb ${TurboJPEG_LIBRARIES})