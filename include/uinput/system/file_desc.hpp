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
#include "uinput/common/enum_cast.hpp"
#include "uinput/common/logger.hpp"

namespace fd
{
    template<flag... Flags>
    class file_desc
    {
    public:
        file_desc(const std::string_view path)
        {
            m_fd = ::open(path.data(), (utils::to_underlying(Flags) | ...));
            if (-1 == m_fd)
            {
                log_e("{}: Failed to open file descriptor for {}.", __FUNCTION__, path.data());
                throw std::runtime_error{ "Failed to open file descriptor" };
            }

            log_i("{}: File descriptor is successfully opened.", __FUNCTION__);
        }

        file_desc(const file_desc& other) { *this = other; }
        file_desc& operator=(const file_desc& other)
        {
            if (this != &other)
            {
                int dup_fd = ::dup(other.m_fd);
                if (-1 == dup_fd)
                {
                    throw std::runtime_error{ "Failed to crate file descriptor duplicate.\n" };
                }

                ::close(m_fd);
                m_fd = dup_fd;
            }

            return *this;
        }

        file_desc(file_desc&& other) noexcept { *this = std::move(other); }
        file_desc& operator=(file_desc&& other) noexcept
        {
            if (this != &other)
            {
                m_fd = std::exchange(other.m_fd, -1);
            }

            return *this;
        }

        ~file_desc() noexcept
        {
            if (-1 != m_fd)
            {
                if (-1 == ::close(m_fd))
                {
                    log_w("The file descriptor is not closed properly.");
                }
            }
        }

        explicit operator bool() const noexcept { return -1 != m_fd; }

        const native_handle_t& native_handle() const noexcept { return m_fd; }

        template<typename T, std::size_t N>
        [[nodiscard]] bool write(const buffer_t<T, N>& buffer) noexcept
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
        [[nodiscard]] bool write(T& value) noexcept
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
        [[nodiscard]] opt_buffer_t<T, N> read() const noexcept
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
        [[nodiscard]] opt_t<T> read() const noexcept
        {
            T value;
            if (0 >= ::read(m_fd, std::addressof(value), sizeof(T)))
            {
                log_e("{}: Failed to read value", __FUNCTION__);
                return opt_null;
            }
            else
            {
                log_i("{}: Value is successfully read.", __FUNCTION__);
                return { value };
            }
        }

        template<typename... Args>
        [[nodiscard]] bool ioctl(const std::uint64_t request, Args&&... args) noexcept
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

    private:
        native_handle_t m_fd{ -1 };
    };
}  // namespace fd