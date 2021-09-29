#include <gtest/gtest.h>
#include "virtual_hmi/system/file_descriptor.hpp"
#include <iostream>

TEST(file_descriptor, constructor)
{
   // EXPECT_THROW(file_descriptor{"aaa", flags::READ_ONLY}, std::runtime_error{});
    file_descriptor fd("foo.txt", flags::read_write);
}