set(test_sources
    system/test_file_desc.cpp
    system/test_uinput.cpp)

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
  hmi::hmi
)
