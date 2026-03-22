cmake_minimum_required(VERSION 3.14)
project(math_lib VERSION 0.1.0 LANGUAGES CXX)

add_library(math_lib INTERFACE)

target_include_directories(math_lib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(math_lib INTERFACE cxx_std_17)