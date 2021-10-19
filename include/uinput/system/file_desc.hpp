#pragma once

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string_view>

#include "file_desc_defines.hpp"
#include "uinput/common/logger.hpp"

namespace fd
{
    class file_desc
    {
    public:
        template<typename... Flags>
        file_desc(std::string_view name, Flags... flags);

        file_desc(const file_desc&);
        file_desc& operator=(const file_desc&);

        file_desc(file_desc&& fd) noexcept;
        file_desc& operator=(file_desc&& fd) noexcept;

        ~file_desc() noexcept;

        explicit operator bool() const noexcept;

        const native_handle_t& native_handle() const noexcept;

        template<typename T, std::size_t N>
        [[nodiscard]] bool write(const buffer_t<T, N>& buffer) noexcept;

        template<typename T>
        [[nodiscard]] bool write(T& value) noexcept;

        template<typename T, std::size_t N>
        [[nodiscard]] opt_buffer_t<T, N> read() const noexcept;

        template<typename T>
        [[nodiscard]] opt_t<T> read() const noexcept;

        template<typename... Args>
        [[nodiscard]] bool ioctl(const std::uint64_t request, Args&&... args) noexcept;

    private:
        native_handle_t m_fd{ -1 };
    };

    // Template methods implementation

    template<typename... Flags>
    file_desc::file_desc(std::string_view name, Flags... flags)
    {
        static_assert(std::conjunction_v<std::is_integral<Flags>...>);

        m_fd = open(name.data(), (flags | ...));
        if (-1 == m_fd)
        {
            log_e("{}: Failed to open file descriptor for {}.", __FUNCTION__, name.data());
            throw std::runtime_error{ "Failed to open file descriptor" };
        }

        log_i("{}: File descriptor is successfully opened.", __FUNCTION__);
    }

    template<typename T, std::size_t N>
    bool file_desc::write(const buffer_t<T, N>& buffer) noexcept
    {
        if (0 >= ::write(m_fd, std::addressof(buffer), N * sizeof(T)))
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

    template<typename T>
    [[nodiscard]] bool file_desc::write(T& value) noexcept
    {
        if (0 >= ::write(m_fd, std::addressof(value), sizeof(T)))
        {
            log_e("{}: Failed to write value with size: {}.", __FUNCTION__, sizeof(T));
            return false;
        }
        else
        {
            log_i("{}: Value is successfully written.", __FUNCTION__);
            return true;
        }
    }

    template<typename T, std::size_t N>
    opt_buffer_t<T, N> file_desc::read() const noexcept
    {
        buffer_t<T, N> buffer;

        if (0 >= ::read(m_fd, std::addressof(buffer), N * sizeof(T)))
        {
            log_e("{}: Failed to read buffer with size: {}", __FUNCTION__, N);
            return opt_null;
        }
        else
        {
            log_i("{}: Buffer is successfully read.", __FUNCTION__);
            return { buffer };
        }
    }

    template<typename T>
    opt_t<T> file_desc::read() const noexcept
    {
        opt_t<T> value;

        if (0 >= ::read(m_fd, std::addressof(value), sizeof(T)))
        {
            log_e("{}: Failed to read value with size: {}", __FUNCTION__, sizeof(T));
            return opt_null;
        }
        else
        {
            log_i("{}: Value is successfully read.", __FUNCTION__);
            return { value };
        }
    }

    template<typename... Args>
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

}  // namespace fd