option(${PROJECT_NAME}_ENABLE_EXAMPLES "Enable uinput examples (from the `examples` subfolder)." ON)

option(${PROJECT_NAME}_ENABLE_CLANG_TIDY "Enable static analysis with Clang-Tidy." ON)
option(${PROJECT_NAME}_ENABLE_CLANG_FORMAT "Enable formating with Clang-Format." ON)

option(${PROJECT_NAME}_ENABLE_TRACE_LOGGING "Enable trace logging" ON)
if(${PROJECT_NAME}_ENABLE_TRACE_LOGGING)
    add_compile_definitions(LOGGING)
endif()