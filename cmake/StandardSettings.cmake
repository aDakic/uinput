option(${PROJECT_NAME}_ENABLE_UNIT_TESTING "Enable unit tests for the projects (from the `test` subfolder)." ON)

option(${PROJECT_NAME}_ENABLE_CLANG_TIDY "Enable static analysis with Clang-Tidy." OFF)
option(${PROJECT_NAME}_ENABLE_CLANG_FORMAT "Enable formating with Clang-Format." OFF)

option(${PROJECT_NAME}_ENABLE_TRACE_LOGGING "Enable trace logging" OFF)
if(${PROJECT_NAME}_ENABLE_TRACE_LOGGING)
    add_compile_definitions(LOGGING)
endif()