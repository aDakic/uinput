#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <string_view>
#include <stdexcept>
#include <array>
#include <optional>
#include <iostream>

#include "hmi/common/logger.hpp"
#include "file_desc_defines.hpp"

namespace fd
{

class file_desc
{
public:

    template <typename... Flags>
    file_desc(std::string_view name, Flags... flags);

    file_desc(const file_desc&);
    file_desc& operator=(const file_desc&);

    file_desc(file_desc&& fd) noexcept;
    file_desc& operator=(file_desc&& fd) noexcept;

    virtual ~file_desc() noexcept;

    explicit operator bool() const noexcept;

    template <typename T, std::size_t N>
    [[nodiscard]] bool write(const buffer_t<T, N>& buffer) noexcept;

    template <typename T, std::size_t N>
    [[nodiscard]] opt_buffer_t<T, N> read() const noexcept;

    template <typename... Args>
    [[nodiscard]] bool ioctl(const std::uint64_t request, Args&&... args) noexcept;

private:
    native_handle_t m_fd {-1};
};

// Template methods implementation

template <typename... Flags>
file_desc::file_desc(std::string_view name, Flags... flags)
{
    static_assert(std::conjunction_v<std::is_integral<Flags>...>);

    m_fd = open(name.data(), (flags | ...));
    if (-1 == m_fd)
    {
        log_e("{}: Failed to open file descriptor.", __FUNCTION__);
        throw std::runtime_error{"Failed to open file descriptor"};
    }

    log_i("{}: File descriptor is successfully opened.", __FUNCTION__);
}

template <typename T, std::size_t N>
bool file_desc::write(const buffer_t<T, N>& buffer) noexcept
{
    if ( 0 >= ::write(m_fd, std::addressof(buffer), N * sizeof(T)))
    {
        log_e("{}: Failed to write buffer with size: {}.", __FUNCTION__, N);
        return false;
    }
    else
    {
        log_i("{}: Buffer is successfully written.", __FUNCTION__);
        return true;
    }
}

template <typename T, std::size_t N>
opt_buffer_t<T, N> file_desc::read() const noexcept
{
    buffer_t<T, N> buffer;

    if ( 0 >= ::read(m_fd, std::addressof(buffer), N * sizeof(T)))
    {
        log_e("{}: Failed to read buffer with size: {}", __FUNCTION__, N);
        return std::nullopt;
    }
    else
    {
        log_i("{}: Buffer is successfully read.", __FUNCTION__);
        return { buffer };
    }
}

template <typename... Args>
bool file_desc::ioctl(const std::uint64_t request, Args&&... args) noexcept
{
    if (-1 == ::ioctl(m_fd, request, std::forward<Args>(args)...))
    {
        log_e("{}: ioctl failed for request: {}", __FUNCTION__, request);
        return false;
    }
    else
    {
        log_i("{}: ioctl ended successfully", __FUNCTION__);
        return true;
    }
}
}