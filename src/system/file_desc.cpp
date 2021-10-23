#include <stdexcept>

#include "uinput/system/file_desc.hpp"

namespace fd
{
    file_desc::file_desc(const std::string_view path, access_mode_t access_mode)
    {
        m_fd = ::open(path.data(), access_mode);
        if (-1 == m_fd)
        {
            utils::log_e("{}: Failed to open file descriptor for {}.", __FUNCTION__, path.data());
            throw std::runtime_error{ "Failed to open file descriptor" };
        }

        utils::log_i("{}: File descriptor is successfully opened.", __FUNCTION__);
    }

    file_desc::file_desc(const file_desc& other) { *this = other; }

    file_desc& file_desc::operator=(const file_desc& other)
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
                utils::log_w("The file descriptor is not closed properly.");
            }
        }
    }

    file_desc::operator bool() const noexcept { return -1 != m_fd; }

    const native_handle_t& file_desc::native_handle() const noexcept { return m_fd; }
}  // namespace fd