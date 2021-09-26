#pragma once

#include <fcntl.h>

namespace flags {
    inline constexpr int read_only = O_RDONLY;
    inline constexpr int read_write = O_RDWR;
    inline constexpr int write_only = O_WRONLY;
    inline constexpr int non_block = O_NONBLOCK;
    inline constexpr int no_delay = O_NDELAY;
};
