#include "uinput/system/file_desc.hpp"

#include <utility>

namespace fd
{
    file_desc::file_desc(const file_desc& other) { *this = other; }

    file_desc& file_desc::operator=(const file_desc& other)
    {
        if (this != &other)
        {
            int dup_fd = dup(other.m_fd);
            if (-1 == dup_fd)
            {
                throw std::runtime_error{ "Failed to crate file descriptor duplicate.\n" };
            }

            ::close(m_fd);
            m_fd = dup_fd;
        }

        return *this;
    }

    file_desc::file_desc(file_desc&& other) noexcept { *this = std::move(other); }

    file_desc& file_desc::operator=(file_desc&& other) noexcept
    {
        if (this != &other)
        {
            m_fd = std::exchange(other.m_fd, -1);
        }

        return *this;
    }

    file_desc::~file_desc() noexcept
    {
        if (-1 != m_fd)
        {
            if (-1 == ::close(m_fd))
            {
                log_w("The file descriptor is not closed properly.");
            }
        }
    }

    file_desc::operator bool() const noexcept { return -1 != m_fd; }

    const native_handle_t& file_desc::native_handle() const noexcept { return m_fd; }
}  // namespace fd