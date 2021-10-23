#pragma once

#include "system/file_desc.hpp"
#include "uinput_defines.hpp"

namespace ui
{
    class uinput_driver
    {
    public:
        uinput_driver();
        uinput_driver(const uinput_driver&) = default;
        uinput_driver(uinput_driver&&)      = default;
        uinput_driver& operator=(const uinput_driver&) noexcept = default;
        uinput_driver& operator=(uinput_driver&&) noexcept = default;
        ~uinput_driver() noexcept;

        void set_info(std::string_view name, const std::uint16_t vendor_id, const std::uint16_t product_id,
                      const std::uint16_t version) noexcept;

        template<typename... Events>
        [[nodiscard]] bool set_events(const Events... events) noexcept;

        template<typename... KeyCodes>
        [[nodiscard]] bool set_key_codes(const KeyCodes... key_codes) noexcept;

        template<typename... RelCodes>
        [[nodiscard]] bool set_rel_codes(const RelCodes... rel_codes) noexcept;

        template<typename... AbsCodes>
        [[nodiscard]] bool set_abs_codes(const AbsCodes... abs_codes) noexcept;

        [[nodiscard]] bool create_device() noexcept;

        template<std::size_t N>
        [[nodiscard]] bool emit(const event_buffer_t<N>& events) noexcept;
        template<std::uint16_t Code>
        void set_abs_info(const std::int32_t min, const std::int32_t max) noexcept;

    private:
        static constexpr const char* uinput_path = "/dev/uinput";
        setup_t m_setup{};
        fd::file_desc m_fd;

        template<typename... Bits>
        bool set_bits(const int flag, const Bits... bits) noexcept;
    };

    template<typename... Events>
    bool uinput_driver::set_events(const Events... events) noexcept
    {
        return set_bits(bit::set_events, events...);
    }

    template<typename... KeyCodes>
    bool uinput_driver::set_key_codes(const KeyCodes... key_codes) noexcept
    {
        return set_bits(bit::set_keys, key_codes...);
    }

    template<typename... RelCodes>
    bool uinput_driver::set_rel_codes(const RelCodes... rel_codes) noexcept
    {
        return set_bits(bit::set_rels, rel_codes...);
    }

    template<typename... AbsCodes>
    bool uinput_driver::set_abs_codes(const AbsCodes... abs_codes) noexcept
    {
        return set_bits(bit::set_abss, abs_codes...);
    }

    template<std::size_t N>
    bool uinput_driver::emit(const event_buffer_t<N>& events) noexcept
    {
        return m_fd.write(events);
    }

    template<std::uint16_t Code>
    void uinput_driver::set_abs_info(const std::int32_t min, const std::int32_t max) noexcept
    {
        m_setup.absmin[Code] = min;
        m_setup.absmax[Code] = max;
    }

    template<typename... Bits>
    bool uinput_driver::set_bits(const int flag, const Bits... bits) noexcept
    {
        auto bits_ioctl = [&](auto bit) { return m_fd.ioctl(flag, bit); };
        return (bits_ioctl(bits) && ...);
    }
}  // namespace ui