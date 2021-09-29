#pragma once

#include "virtual_hmi/system/virtual_device.hpp"

class keyboard final
{
public:
    template <std::uint16_t vendor = def::vendor_id, std::uint16_t product = def::product_id,
              std::uint16_t version = def::verson, typename... KeyCodes>
    keyboard(const std::string_view& name, KeyCodes... key_codes);

    bool press(std::uint16_t key) noexcept;
    bool release(std::uint16_t key) noexcept;

private:
    template <std::uint8_t value>
    constexpr event_buffer_t<2> generate_event(std::uint16_t key) const noexcept;

    static constexpr const char *keyboard_tag = "keyboard";
    virtual_device m_vdev;
};

template <std::uint16_t vendor, std::uint16_t product,
          std::uint16_t version, typename... KeyCodes>
keyboard::keyboard(const std::string_view& name, KeyCodes... key_codes)
{
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