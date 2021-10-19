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

    enum class flag : std::int32_t
    {
        read_only  = O_RDONLY,
        read_write = O_RDWR,
        write_only = O_WRONLY,
        non_block  = O_NONBLOCK,
        no_delay   = O_NDELAY
    };
}  // namespace fd