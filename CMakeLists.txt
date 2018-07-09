cmake_minimum_required(VERSION 3.10.0)
project(ffi-utils LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ffimock SHARED src/main/cpp/libffimock/ffi.cpp)
target_include_directories(ffimock PUBLIC include)

add_executable(mock-ffi src/main/cpp/mock-ffi/main.cpp)
target_link_libraries(mock-ffi ffimock)
target_include_directories(mock-ffi PUBLIC include)

add_executable(mock src/main/cpp/mock/main.cpp)
target_link_libraries(mock ffimock)
target_include_directories(mock PUBLIC include)
