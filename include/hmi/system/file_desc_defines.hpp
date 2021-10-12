#pragma once

#include <fcntl.h>

namespace fd {

    using native_handle_t = std::int32_t;
    
    template <typename T, std::size_t N>
    using buffer_t = std::array<T, N>;

    template <typename T, std::size_t N>
    using opt_buffer_t = std::optional<buffer_t<T, N>>;

namespace flag {
    inline constexpr std::int32_t read_only = O_RDONLY;
    inline constexpr std::int32_t read_write = O_RDWR;
    inline constexpr std::int32_t write_only = O_WRONLY;
    inline constexpr std::int32_t non_block = O_NONBLOCK;
    inline constexpr std::int32_t no_delay = O_NDELAY;
}
}