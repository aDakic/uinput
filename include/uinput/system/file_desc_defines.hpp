#pragma once

#include <fcntl.h>

namespace fd
{
    using native_handle_t = std::int32_t;

    template<typename T, std::size_t N>
    using buffer_t = std::array<T, N>;

    template<typename T>
    using opt_t = std::optional<T>;

    template<typename T, std::size_t N>
    using opt_buffer_t = std::optional<buffer_t<T, N>>;

    inline constexpr auto opt_null = std::nullopt;

    using access_mode_t                       = std::int32_t;
    inline constexpr access_mode_t read_only  = O_RDONLY;
    inline constexpr access_mode_t read_write = O_RDWR;
    inline constexpr access_mode_t write_only = O_WRONLY;
    inline constexpr access_mode_t non_block  = O_NONBLOCK;
    inline constexpr access_mode_t no_delay   = O_NDELAY;

}  // namespace fd