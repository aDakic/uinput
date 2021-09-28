cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(virtual_hmi
        VERSION 1.0.0
        LANGUAGES CXX)

set(sources
    src/file_descriptor.cpp
    src/virtual_device.cpp)

set(headers
    include/${PROJECT_NAME}/file_descriptor.hpp
    include/${PROJECT_NAME}/virtual_device.hpp)

add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

option(${PROJECT_NAME}_ENABLE_UNIT_TESTING "Enable unit tests for the projects (from the `test` subfolder)." ON)

if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
        add_subdirectory(tests)
endif()