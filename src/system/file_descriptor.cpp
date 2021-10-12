#include "hmi/system/file_descriptor.hpp"

#include <utility>

namespace fd
{

file_descriptor::file_descriptor(const file_descriptor& other)
{
    log_info(m_file_descriptor_tag, "Copy constructor\n");
    *this = other;
}

file_descriptor& file_descriptor::operator=(const file_descriptor& other)
{
    log_info(m_file_descriptor_tag, "Copy {}\n", __FUNCTION__);

    if (this != &other)
    {
        int dup_fd = dup(other.m_fd);
        if (-1 == dup_fd)
        {
            throw std::runtime_error{"Failed to crate file descriptor duplicate.\n"};
        }

        ::close(m_fd);
        m_fd = dup_fd;
    }

    return *this;
}

file_descriptor::file_descriptor(file_descriptor&& other) noexcept
{
    log_info(m_file_descriptor_tag, "Move constructor\n");
    *this = std::move(other);
}

file_descriptor& file_descriptor::operator=(file_descriptor&& other) noexcept
{
    log_info(m_file_descriptor_tag, "Move {}\n", __FUNCTION__);

    if (this != &other)
    {
        m_fd = std::exchange(other.m_fd, -1);
    }

    return *this;
}

file_descriptor::~file_descriptor() noexcept
{
    log_info(m_file_descriptor_tag, "{}\n", __FUNCTION__);

    if (-1 != m_fd)
    {
        if (-1 == ::close(m_fd))
        {
            log_warning(m_file_descriptor_tag, "The file descriptor is not closed properly.\n");
        }
    }
}

file_descriptor::operator bool() const noexcept { return -1 != m_fd; }
}