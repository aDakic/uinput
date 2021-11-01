set(keyboard_example_src keyboard_example.cpp)
add_executable(keyboard_example ${keyboard_example_src})
target_compile_features(keyboard_example PUBLIC cxx_std_17)
target_link_libraries(keyboard_example PUBLIC uinput::uinput)

set(mouse_example_src mouse_example.cpp)
add_executable(mouse_example ${mouse_example_src})
target_compile_features(mouse_example PUBLIC cxx_std_17)
target_link_libraries(mouse_example PUBLIC uinput::uinput)

set(touch_example_src touch_example.cpp)
add_executable(touch_example ${touch_example_src})
target_compile_features(touch_example PUBLIC cxx_std_17)
target_link_libraries(touch_example PUBLIC uinput::uinput)