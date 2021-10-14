#include "hmi/touch.hpp"

#include "hmi/system/ev_generator.hpp"

namespace hmi
{
    touch::touch(touch_config config) : m_config(config)
    {
        constexpr const char* name      = "Virtual HMI Touch";
        constexpr std::uint16_t vendor  = 0xACAD;
        constexpr std::uint16_t product = 0x0003;
        constexpr std::uint16_t version = 0x0001;

        m_driver.set_info(name, vendor, product, version);

        if (!m_driver.set_events(ui::ev_type::sync, ui::ev_type::key, ui::ev_type::abs))
            throw std::runtime_error{ "Failed to set supproted events." };

        if (!m_driver.set_key_codes(ui::btn_code::touch))
            throw std::runtime_error{ "Failed to set supproted key codes." };

        if (!m_driver.set_abs_codes(ui::abs_code::mt_x, ui::abs_code::mt_y, ui::abs_code::mt_track_id, ui::abs_code::mt_slot))
            throw std::runtime_error{ "Failed to set supproted abs codes." };

        m_driver.set_abs_info<ui::abs_code::mt_x>(0, m_config.touch_width);
        m_driver.set_abs_info<ui::abs_code::mt_y>(0, m_config.touch_height);
        m_driver.set_abs_info<ui::abs_code::mt_track_id>(0, std::numeric_limits<std::int32_t>::max());
        m_driver.set_abs_info<ui::abs_code::mt_slot>(0, m_config.max_slots);

        if (!m_driver.create_device())
            throw std::runtime_error{ "Failed to create virtual device." };
    }

    bool touch::press(const std::int32_t x, const std::int32_t y, const std::int32_t track_id,
                      const std::int32_t slot) noexcept
    {
        return m_driver.emit(ui::event_gen::touch_press_event(get_x(x), get_y(y), track_id, slot));
    }

    bool touch::release(const std::int32_t x, const std::int32_t y, const std::int32_t slot) noexcept
    {
        return m_driver.emit(ui::event_gen::touch_release_event(get_x(x), get_y(y), slot));
    }

    bool touch::move(const std::int32_t x, const std::int32_t y, const std::int32_t track_id,
                     const std::int32_t slot) noexcept
    {
        return m_driver.emit(ui::event_gen::touch_move_event(get_x(x), get_y(y), track_id, slot));
    }

    std::int32_t touch::get_x(std::int32_t x) const noexcept
    {
        return (x * (m_config.touch_width + 1)) / m_config.screen_width;
    }

    std::int32_t touch::get_y(std::int32_t y) const noexcept
    {
        return (y * (m_config.touch_height + 1)) / m_config.screen_height;
    }
}  // namespace hmi