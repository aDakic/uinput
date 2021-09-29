#include "virtual_hmi/system/file_descriptor.hpp"

#include <utility>

file_descriptor::file_descriptor(file_descriptor&& fd) noexcept
{
    log_info(m_file_descriptor_tag, "{}\n", __FUNCTION__);
    *this = std::move(fd);
}

file_descriptor& file_descriptor::operator=(file_descriptor&& fd) noexcept
{
    log_info(m_file_descriptor_tag, "{}\n", __FUNCTION__);

    if (this != &fd)
    {
        m_fd = std::exchange(fd.m_fd, -1);
    }

    return *this;
}

file_descriptor::~file_descriptor() noexcept
{
    log_info(m_file_descriptor_tag, "{}\n", __FUNCTION__);

    if (*this)
    {
        if (-1 == ::close(m_fd))
        {
            log_warning(m_file_descriptor_tag, "The file descriptor is not closed properly.\n");
        }
    }
}

file_descriptor::operator bool() const noexcept { return -1 != m_fd; }