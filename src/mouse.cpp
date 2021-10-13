#include "hmi/mouse.hpp"

#include "hmi/system/ev_generator.hpp"

namespace hmi
{
    mouse::mouse()
    {
        constexpr const char* name      = "Virtual HMI Mouse";
        constexpr std::uint16_t vendor  = 0xACAD;
        constexpr std::uint16_t product = 0x0002;
        constexpr std::uint16_t version = 0x0001;

        set_info(name, vendor, product, version);

        if (!set_events(ui::ev_type::sync, ui::ev_type::key, ui::ev_type::rel))
            throw std::runtime_error{ "Failed to set supproted events." };

        if (!set_key_codes(ui::btn_code::left, ui::btn_code::middle, ui::btn_code::right))
            throw std::runtime_error{ "Failed to set supproted key codes." };

        if (!set_rel_codes(ui::rel_code::x, ui::rel_code::y, ui::rel_code::wheel))
            throw std::runtime_error{ "Failed to set supproted rel codes." };

        if (!create_device())
            throw std::runtime_error{ "Failed to create virtual device." };
    }

    bool mouse::click_left() noexcept { return emit(ui::event_gen::click_event(ui::btn_code::left)); }

    bool mouse::click_right() noexcept { return emit(ui::event_gen::click_event(ui::btn_code::right)); }

    bool mouse::click_middle() noexcept { return emit(ui::event_gen::click_event(ui::btn_code::middle)); }

    bool mouse::move(std::int32_t x, std::int32_t y) noexcept { return emit(ui::event_gen::move_event(x, y)); }

    bool mouse::scroll_up() noexcept { return emit(ui::event_gen::scroll_event(ui::scroll_ev_value::up)); }

    bool mouse::scroll_down() noexcept { return emit(ui::event_gen::scroll_event(ui::scroll_ev_value::down)); }
}  // namespace hmi