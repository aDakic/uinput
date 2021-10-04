#include "virtual_hmi/mouse.hpp"

mouse::mouse()
{
    constexpr const char* name = "Virtual HMI Mouse";
    constexpr std::uint16_t vendor = 0xACAD;
    constexpr std::uint16_t product = 0x0002;
    constexpr std::uint16_t version = 0x0001;

    m_vdev.set_info(name, vendor, product, version);

    if (!m_vdev.set_events(event_codes::sync, event_codes::key, event_codes::rel))
        throw std::runtime_error{"Failed to set supproted events."};

    if (!m_vdev.set_key_codes(btn_codes::left, btn_codes::middle, btn_codes::right))
        throw std::runtime_error{"Failed to set supproted key codes."};

    if (!m_vdev.set_rel_codes(rel_codes::x, rel_codes::y, rel_codes::wheel))
        throw std::runtime_error{"Failed to set supproted rel codes."};

    if (!m_vdev.create_device())
        throw std::runtime_error{"Failed to create virtual device."};
}

bool mouse::click_left() noexcept
{
    return m_vdev.emit(generate_click(btn_codes::left));
}

bool mouse::click_right() noexcept
{
    return m_vdev.emit(generate_click(btn_codes::right));
}

bool mouse::click_middle() noexcept
{
    return m_vdev.emit(generate_click(btn_codes::middle));
}

bool mouse::move(std::int32_t x, std::int32_t y) noexcept
{
    return m_vdev.emit(generate_move(x, y));
}

bool mouse::scroll_up() noexcept
{
    return m_vdev.emit(generate_scroll(scroll_ev_values::up));
}

bool mouse::scroll_down() noexcept
{
    return m_vdev.emit(generate_scroll(scroll_ev_values::down));
}

constexpr event_buffer_t<4> mouse::generate_click(std::uint16_t btn) const noexcept
{
    return {{
        {0, 0, event_codes::key, btn, key_ev_values::press},
        {0, 0, event_codes::sync, sync_codes::report, 0},
        {0, 0, event_codes::key, btn, key_ev_values::release},
        {0, 0, event_codes::sync, sync_codes::report, 0}
    }};
}

constexpr event_buffer_t<3> mouse::generate_move(std::int32_t x, std::int32_t y) const noexcept
{
    return {{
        {0, 0, event_codes::rel, rel_codes::x, x},
        {0, 0, event_codes::rel, rel_codes::y, y},
        {0, 0, event_codes::sync, sync_codes::report, 0}
    }};
}

constexpr event_buffer_t<2> mouse::generate_scroll(std::int32_t up_or_down) const noexcept
{
    return {{
        {0, 0, event_codes::rel, rel_codes::wheel, up_or_down},
        {0, 0, event_codes::sync, sync_codes::report, 0}
    }};
}
