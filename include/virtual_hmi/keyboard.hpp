#pragma once

#include "virtual_hmi/system/virtual_device.hpp"

class keyboard final
{
public:
    template <typename... KeyCodes>
    keyboard(KeyCodes... key_codes);

    bool press(std::uint16_t key) noexcept;
    bool release(std::uint16_t key) noexcept;

private:
    template <std::uint8_t value>
    constexpr event_buffer_t<2> generate_event(std::uint16_t key) const noexcept;

    static constexpr const char *keyboard_tag = "keyboard";
    virtual_device m_vdev;
};

template <typename... KeyCodes>
keyboard::keyboard(KeyCodes... key_codes)
{
    constexpr const char* name = "Virtual HMI Keyboard";
    constexpr std::uint16_t vendor = 0xACAD;
    constexpr std::uint16_t product = 0x0001;
    constexpr std::uint16_t version = 0x0001;

    m_vdev.set_info(name, vendor, product, version);

    if (!m_vdev.set_events(event_codes::sync, event_codes::key))
        throw std::runtime_error{"Failed to set supproted events."};

    if (!m_vdev.set_key_codes(key_codes...))
        throw std::runtime_error{"Failed to set supproted key codes."};

    if (!m_vdev.create_device())
        throw std::runtime_error{"Failed to create virtual device."};
}

template <std::uint8_t value>
constexpr event_buffer_t<2> keyboard::generate_event(std::uint16_t key) const noexcept
{
    return {{
        {0, 0, event_codes::key, key, value},
        {0, 0, event_codes::sync, sync_codes::report, 0}
    }};
}