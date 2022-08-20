cmake_minimum_required(VERSION 3.23)
project(c_handler)

set(CMAKE_CXX_STANDARD 11)

set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB CPP_FILE_PATH
        ${SRC_PATH}/*.cpp
        )

add_library(
        c_handler
        SHARED
        ${CPP_FILE_PATH})

target_include_directories(c_handler
        PUBLIC
        ${SRC_PATH}
        )

add_executable(c_handler_demo demo.cpp)

target_link_libraries(
        c_handler_demo
        c_handler
)
