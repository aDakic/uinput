cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(uinput
        VERSION 1.0.0
        LANGUAGES CXX)

include(cmake/StandardSettings.cmake)
include(cmake/Tools.cmake)
include(cmake/CPM.cmake)

set (CMAKE_CXX_STANDARD 17)

set(headers
    include/${PROJECT_NAME}/common/logger.hpp
    include/${PROJECT_NAME}/system/file_desc_defines.hpp
    include/${PROJECT_NAME}/system/file_desc.hpp
    include/${PROJECT_NAME}/feature/uinput_key_feature.hpp
    include/${PROJECT_NAME}/feature/uinput_mouse_feature.hpp
    include/${PROJECT_NAME}/feature/uinput_mtouch_feature.hpp
    include/${PROJECT_NAME}/uinput_driver.hpp
    include/${PROJECT_NAME}/uinput_defines.hpp
    include/${PROJECT_NAME}/uinput.hpp)

set(sources
    src/system/file_desc.cpp
    src/uinput_driver.cpp)

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

if(${PROJECT_NAME}_ENABLE_EXAMPLES)
        add_subdirectory(examples)
endif()
