#include "virtual_hmi/system/virtual_device.hpp"

#include <cstring>

virtual_device::virtual_device() : m_fd(m_uinput_path, flags::write_only, flags::non_block)
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);
}

void virtual_device::set_info(const std::string_view& name, std::uint16_t vendor_id, std::uint16_t product_id,
                              std::uint16_t version) noexcept
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

    m_uinput_setup.id.bustype = ui_setup::virtual_bus;
    m_uinput_setup.id.vendor  = vendor_id;
    m_uinput_setup.id.product = product_id;
    m_uinput_setup.id.version = version;
    std::strncpy(m_uinput_setup.name, name.data(), ui_setup::max_name_size);
}

virtual_device::~virtual_device() noexcept
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

    if (!m_fd.ioctl(ui_bits::dev_destroy))
    {
        log_warning(m_virtual_device_tag, "The virtual device is not destroyed properly.\n");
    }
}

bool virtual_device::create_device() noexcept
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

    return m_fd.ioctl(ui_bits::dev_setup, std::addressof(m_uinput_setup)) && m_fd.ioctl(ui_bits::dev_create);
}