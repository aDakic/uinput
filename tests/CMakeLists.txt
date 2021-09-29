set(test_sources
    test_file_descriptor.cpp
    test_virtual_device.cpp
    test_keyboard.cpp)

add_executable(test ${test_sources})

target_compile_features(
   test
   PUBLIC
   cxx_std_17
)

find_package(GTest REQUIRED)

target_link_libraries(
  test
  PUBLIC
  GTest::GTest
  GTest::Main
  virtual_hmi::virtual_hmi
)
