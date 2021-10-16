#pragma once

#include "uinput/common/crtp.hpp"
#include "uinput_defines.hpp"

namespace ui
{
    template<typename uinput_base, std::uint16_t... btncodes>
    struct mouse_feature : utils::crtp_with_params<uinput_base, mouse_feature>
    {
        mouse_feature()
        {
            auto error = this->get().set_events(ev_type::sync, ev_type::key, ev_type::rel);
            if(!error)
                throw std::runtime_error{ "Failed to enable REL, KEY and SYNC events" };
            
            error = this->get().set_rel_codes(rel_code::x, rel_code::y, rel_code::wheel);
            if (!error)
                throw std::runtime_error{ "Failed to enable X, Y and WHEEL codes." }; 

            error = this->get().set_key_codes(btncodes...);
            if (!error)
                throw std::runtime_error{ "Failed to enable Button codes." }; 
        }

        bool mouse_click_left() noexcept { return this->get().emit(gen_click_event(btn_code::left)); }
        bool mouse_click_right() noexcept { return this->get().emit(gen_click_event(btn_code::right)); }
        bool mouse_click_middle() noexcept { return this->get().emit(gen_click_event(btn_code::middle)); }

        bool mouse_move(const std::int32_t x, const std::int32_t y) noexcept
        {
            return this->get().emit(gen_move_event(x, y));
        }

        bool mouse_scroll_up() noexcept
        {
            return this->get().emit(gen_scroll_event(scroll_ev_value::up));
        }

        bool mouse_scroll_down() noexcept
        {
            return this->get().emit(gen_scroll_event(scroll_ev_value::up));
        }
    private:

        constexpr event_buffer_t<4> gen_click_event(const std::uint16_t btn) const noexcept
        {
            return { { { 0, 0, ev_type::key, btn, key_value::press }, { 0, 0, ev_type::sync, sync_code::report, 0 },
                       { 0, 0, ev_type::key, btn, key_value::release }, { 0, 0, ev_type::sync, sync_code::report, 0 } } };
        }

        constexpr event_buffer_t<3> gen_move_event(const std::int32_t x, const std::int32_t y) const noexcept
        {
            return { { { 0, 0, ev_type::rel, rel_code::x, x },
                    { 0, 0, ev_type::rel, rel_code::y, y },
                    { 0, 0, ev_type::sync, sync_code::report, 0 } } };
        }

        constexpr event_buffer_t<2> gen_scroll_event(const std::int32_t up_or_down) const noexcept
        {
            return { { { 0, 0, ev_type::rel, rel_code::wheel, up_or_down }, { 0, 0, ev_type::sync, sync_code::report, 0 } } };
        }
    };

    template <std::uint16_t... btncodes>
    struct mouse_with_buttons
    {
        template <typename T>
        using type = mouse_feature<T, btncodes...>;
    };
}