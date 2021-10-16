#pragma once

#include "system/file_desc.hpp"
#include "uinput_defines.hpp"

namespace ui
{
    class uinput_base
    {
    public:
        uinput_base()
          : m_fd(uinput_path, fd::flag::write_only, fd::flag::non_block)
        {
        }
        uinput_base(const uinput_base&) = default;
        uinput_base(uinput_base&&)      = default;
        uinput_base& operator=(const uinput_base&) noexcept = default;
        uinput_base& operator=(uinput_base&&) noexcept = default;
        ~uinput_base() noexcept
        {
            if (!m_fd.ioctl(bit::dev_destroy))
            {
                log_w("{}: The virtual device is not destroyed properly.", __FUNCTION__);
            }
        }

        void set_info(std::string_view name,
                      const std::uint16_t vendor_id,
                      const std::uint16_t product_id,
                      const std::uint16_t version) noexcept
        {
            m_setup.id.bustype = setup::virtual_bus;
            m_setup.id.vendor  = vendor_id;
            m_setup.id.product = product_id;
            m_setup.id.version = version;
            std::strncpy(m_setup.name, name.data(), setup::max_name_size);
        }

        template<typename... Events>
        [[nodiscard]] bool set_events(const Events... events) noexcept
        {
            return set_bits(bit::set_events, events...);
        }

        template<typename... KeyCodes>
        [[nodiscard]] bool set_key_codes(const KeyCodes... key_codes) noexcept
        {
            return set_bits(bit::set_keys, key_codes...);
        }

        template<typename... RelCodes>
        [[nodiscard]] bool set_rel_codes(const RelCodes... rel_codes) noexcept
        {
            return set_bits(bit::set_rels, rel_codes...);
        }

        template<typename... AbsCodes>
        [[nodiscard]] bool set_abs_codes(const AbsCodes... abs_codes) noexcept
        {
            return set_bits(bit::set_abss, abs_codes...);
        }

        [[nodiscard]] bool create_device() noexcept { return m_fd.write(m_setup) && m_fd.ioctl(bit::dev_create); }

        template<std::size_t N>
        [[nodiscard]] bool emit(const event_buffer_t<N>& events) noexcept
        {
            return m_fd.write(events);
        }

        template<std::uint16_t Code>
        void set_abs_info(const std::int32_t min, const std::int32_t max) noexcept
        {
            m_setup.absmin[Code] = min;
            m_setup.absmax[Code] = max;
        }

    private:
        static constexpr const char* uinput_path = "/dev/uinput";
        setup_t m_setup{};
        fd::file_desc m_fd;

        template<typename... Bits>
        bool set_bits(const int flag, const Bits... bits) noexcept
        {
            auto bits_ioctl = [&](auto bit) { return m_fd.ioctl(flag, bit); };
            return (bits_ioctl(bits) && ...);
        }
    };
} // namespace ui