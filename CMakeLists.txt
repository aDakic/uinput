cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(virtual_hmi
        VERSION 1.0.0
        LANGUAGES CXX)

include(cmake/StandardSettings.cmake)
include(cmake/Tools.cmake)
include(cmake/CPM.cmake)

set(sources
    src/system/file_descriptor.cpp
    src/system/virtual_device.cpp
    src/keyboard.cpp
    src/mouse.cpp
    src/touch.cpp)

set(headers
    include/${PROJECT_NAME}/common/logger.hpp
    include/${PROJECT_NAME}/common/types.hpp
    include/${PROJECT_NAME}/system/file_descriptor.hpp
    include/${PROJECT_NAME}/system/virtual_device.hpp
    include/${PROJECT_NAME}/keyboard.hpp
    include/${PROJECT_NAME}/mouse.hpp
    include/${PROJECT_NAME}/touch.hpp)

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

if(${PROJECT_NAME}_ENABLE_TRACE_LOGGING)
    set(FMT_INSTALL ON)
    set(CMAKE_POSITION_INDEPENDENT_CODE true)
    CPMAddPackage("gh:fmtlib/fmt#7.1.3")
    target_link_libraries(${PROJECT_NAME} fmt)
endif()

if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
        add_subdirectory(tests)
endif()