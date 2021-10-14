#include "hmi/system/uinput.hpp"

namespace ui
{
    uinput::uinput() : fd::file_desc(uinput_path, fd::flag::write_only, fd::flag::non_block) { }

    void uinput::set_info(std::string_view name, const std::uint16_t vendor_id, const std::uint16_t product_id,
                          const std::uint16_t version) noexcept
    {
        m_setup.id.bustype = setup::virtual_bus;
        m_setup.id.vendor  = vendor_id;
        m_setup.id.product = product_id;
        m_setup.id.version = version;
        std::strncpy(m_setup.name, name.data(), setup::max_name_size);
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
        return fd::file_desc::write(m_setup) && fd::file_desc::ioctl(bit::dev_create);
    }
}  // namespace ui