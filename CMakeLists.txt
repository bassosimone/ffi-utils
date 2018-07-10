cmake_minimum_required(VERSION 3.10.0)
project(ffi-utils LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding the following definition allows to debug the nettest.hpp header
add_definitions(-DMK_NETTEST_TRACE)

add_library(ffimock SHARED src/main/cpp/libffimock/ffi.cpp)
target_include_directories(ffimock PUBLIC include)

find_package(JNI REQUIRED)
add_library(measurementkit-jni SHARED
            src/main/cpp/libmeasurementkit-jni/bindings_wrap.cxx
            src/main/cpp/libmeasurementkit-jni/bindings_wrap.h)
target_include_directories(measurementkit-jni PUBLIC include
                           ${JNI_INCLUDE_DIRS})
target_link_libraries(measurementkit-jni ffimock)

add_executable(mock-ffi src/test/cpp/mock-ffi/main.cpp)
target_link_libraries(mock-ffi ffimock)
target_include_directories(mock-ffi PUBLIC include)

add_executable(mock src/test/cpp/mock/main.cpp)
target_link_libraries(mock ffimock)
target_include_directories(mock PUBLIC include)
