// #include <gtest/gtest.h>
// #include "uinput/system/file_desc.hpp"

// class file_descriptor_test : public ::testing::Test {
// protected:
//    void SetUp() override 
//    {
//       std::system("touch read_only.txt");
//       std::system("echo read_only >> read_only.txt");
//       std::system("chmod +r-w read_only.txt");

//       std::system("touch read_write.txt; chmod +rw read_write.txt");
//       std::system("echo read_write >> read_write.txt");

//       std::system("touch write_only.txt; chmod -r+w write_only.txt");
//    }

//    void TearDown() override 
//    {
//       std::system("rm -f read_only.txt read_write.txt write_only.txt");
//    }

// public:
//    static constexpr const char* ro_file_name = "read_only.txt";
//    static constexpr const char* rw_file_name = "read_write.txt";
//    static constexpr const char* wo_file_name = "write_only.txt";
// };

// TEST_F(file_descriptor_test, constructor)
// {

//   EXPECT_THROW(fd::file_desc("aaa", fd::flag::read_only), std::runtime_error);
   
//   EXPECT_NO_THROW(fd::file_desc(file_descriptor_test::ro_file_name, fd::flag::read_only));
//   EXPECT_NO_THROW(fd::file_desc(file_descriptor_test::rw_file_name, fd::flag::read_write));
//   EXPECT_NO_THROW(fd::file_desc(file_descriptor_test::wo_file_name, fd::flag::write_only));

//   EXPECT_THROW(fd::file_desc(file_descriptor_test::ro_file_name, fd::flag::read_write), std::runtime_error);
//   EXPECT_THROW(fd::file_desc(file_descriptor_test::wo_file_name, fd::flag::read_write), std::runtime_error);
// }

// TEST_F(file_descriptor_test, move_operation)
// {
//    // move from temporary
//    auto new_fd = fd::file_desc(file_descriptor_test::ro_file_name, fd::flag::read_write);
//    // bool() implicit conversion operator
//    EXPECT_TRUE(new_fd);

//    // move from optional
//    std::optional<fd::file_desc> opt_fd;
//    opt_fd.emplace(file_descriptor_test::ro_file_name, fd::flag::read_only);

//    EXPECT_NO_THROW(auto new_fd = std::move(opt_fd).value());

//    // move
//    bool is_new_fd_valid = false;
//    auto new_fd_2 = std::move(new_fd);

//    if (new_fd_2)
//       is_new_fd_valid = true;

//    EXPECT_TRUE(is_new_fd_valid);
// }

// TEST_F(file_descriptor_test, write)
// {
//    {
//       fd::file_desc fd(file_descriptor_test::ro_file_name, fd::flag::read_only);
//       EXPECT_TRUE(fd);

//       std::array<char, 4> buf {"aaa"};

//       EXPECT_FALSE(fd.write(buf));
//    }

//    {
//       fd::file_desc fd(file_descriptor_test::wo_file_name, fd::flag::write_only);

//       std::array<char, 4> buf {"aaa"};
//       EXPECT_TRUE(fd.write(buf));
//    }
// }

// TEST_F(file_descriptor_test, read)
// {
//    {
//       fd::file_desc fd(file_descriptor_test::ro_file_name, fd::flag::read_only);
//       EXPECT_TRUE(fd);

//       auto op_buf = fd.read<char, 4>();
//       EXPECT_TRUE(op_buf != std::nullopt);

//       constexpr std::array<char, 4> expected_result {'r', 'e', 'a', 'd'};
//       EXPECT_EQ(op_buf.value(), expected_result);
//    }

//    {
//       fd::file_desc fd(file_descriptor_test::wo_file_name, fd::flag::write_only);

//       auto op_buf = fd.read<char, 4>();
//       EXPECT_TRUE(op_buf == std::nullopt);
//    }
// }