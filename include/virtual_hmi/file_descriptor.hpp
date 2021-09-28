#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <string_view>
#include <stdexcept>
#include <array>
#include <optional>
#include <iostream>

#include "types.hpp"
#include "logger.h"

class file_descriptor final
{
public:

    template <typename... Flags>
    file_descriptor(const std::string_view& name, Flags... flags);

    file_descriptor(const file_descriptor&) = delete;
    file_descriptor& operator=(const file_descriptor&) = delete;

    file_descriptor(file_descriptor&& fd) noexcept;
    file_descriptor& operator=(file_descriptor&& fd) noexcept;

    ~file_descriptor() noexcept;

    explicit operator bool() const noexcept;

    template <typename T, std::size_t N>
    [[nodiscard]] bool write(std::array<T, N> buffer) noexcept;

    template <typename T, std::size_t N>
    [[nodiscard]] std::optional<std::array<T, N>> read() const noexcept;

    template <typename... Args>
    [[nodiscard]] bool ioctl(std::uint64_t request, Args&&... args) noexcept;

private:
    static constexpr const char *m_file_descriptor_tag = "file_descriptor";
    int32_t m_fd {-1};
};

// Template methods implementation

template <typename... Flags>
file_descriptor::file_descriptor(const std::string_view& name, Flags... flags)
{
    static_assert(std::conjunction_v<std::is_integral<Flags>...>);

    log_info(m_file_descriptor_tag, "{}\n", __FUNCTION__);

    m_fd = open(name.data(), (flags | ...));
    if (-1 == m_fd)
    {
        throw std::runtime_error{"Failed to open file descriptor"};
    }
}

template <typename T, std::size_t N>
bool file_descriptor::write(std::array<T, N> buffer) noexcept
{
    log_info(m_file_descriptor_tag, "{}\n", __FUNCTION__);

    if ( 0 >= ::write(m_fd, std::addressof(buffer), N * sizeof(T)))
    {
        log_error(m_file_descriptor_tag, "Failed to write buffer with size: {}\n", N);
        return false;
    }
    else
    {
        log_info(m_file_descriptor_tag, "write ended successfully\n");
        return true;
    }
}

template <typename T, std::size_t N>
std::optional<std::array<T, N>> file_descriptor::read() const noexcept
{
    std::array<T, N> buffer;

    if ( 0 >= ::read(m_fd, std::addressof(buffer), N * sizeof(T)))
    {
        log_error(m_file_descriptor_tag, "Failed to read buffer with size: {}\n", N);
        return std::nullopt;
    }
    else
    {
        log_info(m_file_descriptor_tag, "read ended successfully\n");
        return { buffer };
    }
}

template <typename... Args>
bool file_descriptor::ioctl(std::uint64_t request, Args&&... args) noexcept
{
    if (-1 == ::ioctl(m_fd, request, std::forward<Args>(args)...))
    {
        log_error(m_file_descriptor_tag, "ioctl failed for request: {}\n", request);
        return false;
    }
    else
    {
        log_info(m_file_descriptor_tag, "ioctl ended successfully\n");
        return true;
    }
}