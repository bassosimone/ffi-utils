cmake_minimum_required(VERSION 3.10.0)
project(ffi-utils LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(ffimock SHARED src/main/cpp/libffimock/ffi.cpp)
target_include_directories(ffimock PUBLIC include)
