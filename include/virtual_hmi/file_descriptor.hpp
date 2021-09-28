#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <string_view>
#include <stdexcept>
#include <array>
#include <optional>
#include <iostream>

#include "types.hpp"

class file_descriptor final
{
public:

    template <typename... Flags>
    file_descriptor(const std::string_view& name, Flags... flags)
    {
        static_assert(std::conjunction_v<std::is_integral<Flags>...>);

        m_fd = open(name.data(), (flags | ...));
        if (-1 == m_fd)
        {
            throw std::runtime_error{"Failed to open file descriptor"};
        }
    }

    file_descriptor(const file_descriptor&) = delete;
    file_descriptor& operator=(const file_descriptor&) = delete;

    file_descriptor(file_descriptor&& fd) noexcept;
    file_descriptor& operator=(file_descriptor&& fd) noexcept;

    ~file_descriptor() noexcept;

    explicit operator bool() const noexcept;

    template <typename T, size_t N>
    [[nodiscard]] bool write(std::array<T, N> buffer) noexcept
    {
        if ( 0 >= ::write(m_fd, std::addressof(buffer), N * sizeof(T)))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template <typename T, size_t N>
    [[nodiscard]] std::optional<std::array<T, N>> read() const noexcept
    {
        std::array<T, N> buffer;

        if ( 0 >= ::read(m_fd, std::addressof(buffer), N * sizeof(T)))
        {
            return std::nullopt;
        }
        else
        {
            return { buffer };
        }
    }

    template <typename... Args>
    [[nodiscard]] bool ioctl(unsigned long request, Args&&... args) noexcept
    {
        if (-1 == ::ioctl(m_fd, request, std::forward<Args>(args)...))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

private:
    int m_fd {-1};
};