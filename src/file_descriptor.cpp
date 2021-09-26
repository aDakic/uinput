#include "virtual_hmi/file_descriptor.hpp"
#include <utility>

file_descriptor::file_descriptor(file_descriptor&& fd) noexcept
{
    *this = std::move(fd);
}

file_descriptor& file_descriptor::operator=(file_descriptor&& fd) noexcept
{
    if (this != &fd)
    {
        m_fd = std::exchange(fd.m_fd, -1);
    }

    return *this;
}

file_descriptor::~file_descriptor() noexcept
{
    if (*this)
    {
        ::close(m_fd);
    }

}

file_descriptor::operator bool() const noexcept
{
    return -1 != m_fd;
}