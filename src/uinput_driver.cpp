#include "uinput/uinput_driver.hpp"

namespace ui
{
    uinput_driver::uinput_driver() : m_fd(uinput_path, fd::write_only | fd::non_block) { }

    uinput_driver::~uinput_driver() noexcept
    {
        if (!m_fd.ioctl(bit::dev_destroy))
        {
            utils::log_w("{}: The virtual device is not destroyed properly.", __FUNCTION__);
        }
    }

    void uinput_driver::set_info(std::string_view name, const std::uint16_t vendor_id, const std::uint16_t product_id,
                                 const std::uint16_t version) noexcept
    {
        m_setup.id.bustype = setup::virtual_bus;
        m_setup.id.vendor  = vendor_id;
        m_setup.id.product = product_id;
        m_setup.id.version = version;
        std::strncpy(m_setup.name, name.data(), setup::max_name_size);
    }

    bool uinput_driver::create_device() noexcept { return m_fd.write(m_setup) && m_fd.ioctl(bit::dev_create); }
}  // namespace ui