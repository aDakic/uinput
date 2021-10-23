#pragma once

#include "uinput/uinput_defines.hpp"

namespace ui
{
    namespace details
    {
        template<typename Driver, std::uint16_t... BtnCodes>
        struct mouse_feature
        {
            mouse_feature()
            {
                auto error = get().set_events(ev_type::sync, ev_type::key, ev_type::rel);
                if (!error)
                    throw std::runtime_error{ "Failed to enable REL, KEY and SYNC events" };

                error = get().set_rel_codes(rel_code::x, rel_code::y, rel_code::wheel);
                if (!error)
                    throw std::runtime_error{ "Failed to enable X, Y and WHEEL codes." };

                error = get().set_key_codes(BtnCodes...);
                if (!error)
                    throw std::runtime_error{ "Failed to enable Button codes." };
            }

            bool mouse_click_left() noexcept { return get().emit(gen_click_event(btn_code::left)); }
            bool mouse_click_right() noexcept { return get().emit(gen_click_event(btn_code::right)); }
            bool mouse_click_middle() noexcept { return get().emit(gen_click_event(btn_code::middle)); }

            bool mouse_move(const std::int32_t x, const std::int32_t y) noexcept { return get().emit(gen_move_event(x, y)); }

            bool mouse_scroll_up() noexcept { return get().emit(gen_scroll_event(scroll_ev_value::up)); }

            bool mouse_scroll_down() noexcept { return get().emit(gen_scroll_event(scroll_ev_value::up)); }

        private:
            constexpr decltype(auto) get() noexcept { return static_cast<Driver&>(*this); }

            constexpr event_buffer_t<4> gen_click_event(const std::uint16_t btn) const noexcept
            {
                return { { { 0, 0, ev_type::key, btn, key_value::press },
                           { 0, 0, ev_type::sync, sync_code::report, 0 },
                           { 0, 0, ev_type::key, btn, key_value::release },
                           { 0, 0, ev_type::sync, sync_code::report, 0 } } };
            }

            constexpr event_buffer_t<3> gen_move_event(const std::int32_t x, const std::int32_t y) const noexcept
            {
                return { { { 0, 0, ev_type::rel, rel_code::x, x },
                           { 0, 0, ev_type::rel, rel_code::y, y },
                           { 0, 0, ev_type::sync, sync_code::report, 0 } } };
            }

            constexpr event_buffer_t<2> gen_scroll_event(const std::int32_t up_or_down) const noexcept
            {
                return { { { 0, 0, ev_type::rel, rel_code::wheel, up_or_down },
                           { 0, 0, ev_type::sync, sync_code::report, 0 } } };
            }
        };
    }  // namespace details

    template<std::uint16_t... BtnCodes>
    struct mouse_with_buttons
    {
        template<typename Driver>
        using type = details::mouse_feature<Driver, BtnCodes...>;
    };
}  // namespace ui