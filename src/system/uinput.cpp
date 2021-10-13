#include "hmi/system/uinput.hpp"

namespace ui
{
    uinput::uinput() : fd::file_desc(uinput_path, fd::flag::write_only, fd::flag::non_block) { }

    void uinput::set_info(std::string_view name, const std::uint16_t vendor_id, const std::uint16_t product_id,
                          const std::uint16_t version) noexcept
    {
        m_uinput_setup.id.bustype = setup::virtual_bus;
        m_uinput_setup.id.vendor  = vendor_id;
        m_uinput_setup.id.product = product_id;
        m_uinput_setup.id.version = version;
        std::strncpy(m_uinput_setup.name, name.data(), setup::max_name_size);
    }

    uinput::~uinput() noexcept
    {
        if (!fd::file_desc::ioctl(bit::dev_destroy))
        {
            log_w("{}: The virtual device is not destroyed properly.", __FUNCTION__);
        }
    }

    bool uinput::create_device() noexcept
    {
        fd::buffer_t<uinput_user_dev, 1> buffer{ m_uinput_setup };
        return fd::file_desc::write(buffer) && fd::file_desc::ioctl(bit::dev_create);
    }
}  // namespace ui