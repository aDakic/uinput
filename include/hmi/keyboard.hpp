#pragma once

#include "hmi/system/uinput.hpp"

namespace hmi
{
    class keyboard final
    {
    public:
        template<typename... KeyCodes>
        keyboard(const KeyCodes... key_codes);

        bool press(std::uint16_t key) noexcept;
        bool release(std::uint16_t key) noexcept;

        ui::uinput m_driver;
    };

    // Template methods implementation

    template<typename... KeyCodes>
    keyboard::keyboard(const KeyCodes... key_codes)
    {
        constexpr const char* name      = "Virtual HMI Keyboard";
        constexpr std::uint16_t vendor  = 0xACAD;
        constexpr std::uint16_t product = 0x0001;
        constexpr std::uint16_t version = 0x0001;

        m_driver.set_info(name, vendor, product, version);

        if (!m_driver.set_events(ui::ev_type::sync, ui::ev_type::key))
            throw std::runtime_error{ "Failed to set supproted events." };

        if (!m_driver.set_key_codes(key_codes...))
            throw std::runtime_error{ "Failed to set supproted key codes." };

        if (!m_driver.create_device())
            throw std::runtime_error{ "Failed to create virtual device." };
    }
}  // namespace hmi