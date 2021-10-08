#pragma once

#include <fcntl.h>

namespace linux_os::flags {
    inline constexpr std::int32_t read_only = O_RDONLY;
    inline constexpr std::int32_t read_write = O_RDWR;
    inline constexpr std::int32_t write_only = O_WRONLY;
    inline constexpr std::int32_t non_block = O_NONBLOCK;
    inline constexpr std::int32_t no_delay = O_NDELAY;
};