#pragma once

#include "uinput/uinput_defines.hpp"

namespace ui
{
    namespace details
    {
        template<typename Driver, std::int32_t ScreenWidth, std::int32_t ScreenHeight, std::int32_t TouchWidth,
                 std::int32_t TouchHeight, std::int32_t MaxSlots>
        struct multi_touch_feature
        {
            multi_touch_feature()
            {
                auto error = get().set_events(ev_type::sync, ev_type::key, ev_type::abs);
                if (!error)
                    throw std::runtime_error{ "Failed to enable ABS, KEY and SYNC events." };

                error = get().set_key_codes(ui::btn_code::touch);
                if (!error)
                    throw std::runtime_error{ "Failed to enable BTN_TOUCH code." };

                error = get().set_abs_codes(ui::abs_code::mt_x, ui::abs_code::mt_y, ui::abs_code::mt_track_id,
                                            ui::abs_code::mt_slot);
                if (!error)
                    throw std::runtime_error{ "Failed to set ABS codes." };

                get().template set_abs_info<ui::abs_code::mt_x>(0, TouchWidth);
                get().template set_abs_info<ui::abs_code::mt_y>(0, TouchHeight);
                get().template set_abs_info<ui::abs_code::mt_track_id>(0, std::numeric_limits<std::int32_t>::max());
                get().template set_abs_info<ui::abs_code::mt_slot>(0, MaxSlots);
            }

            bool touch_press(const std::int32_t x, const std::int32_t y, const std::int32_t track_id,
                             const std::int32_t slot) noexcept
            {
                return get().emit(gen_press_event(get_x(x), get_y(y), track_id, slot));
            }

            bool touch_release(const std::int32_t x, const std::int32_t y, const std::int32_t slot) noexcept
            {
                return get().emit(gen_release_event(get_x(x), get_y(y), slot));
            }

            bool touch_move(const std::int32_t x, const std::int32_t y, const std::int32_t track_id,
                            const std::int32_t slot) noexcept
            {
                return get().emit(gen_move_event(get_x(x), get_y(y), track_id, slot));
            }

        private:
            constexpr decltype(auto) get() noexcept { return static_cast<Driver&>(*this); }

            constexpr std::int32_t get_x(const std::int32_t x) const noexcept
            {
                return (x * (TouchWidth + 1)) / ScreenWidth;
            }

            constexpr std::int32_t get_y(const std::int32_t y) const noexcept
            {
                return (y * (TouchHeight + 1)) / ScreenHeight;
            }

            constexpr event_buffer_t<6> gen_press_event(const std::int32_t x, const std::int32_t y,
                                                        const std::int32_t track_id, const std::int32_t slot) noexcept
            {
                return { { { 0, 0, ev_type::abs, abs_code::mt_slot, slot },
                           { 0, 0, ev_type::abs, abs_code::mt_track_id, track_id },
                           { 0, 0, ev_type::abs, abs_code::mt_x, x },
                           { 0, 0, ev_type::abs, abs_code::mt_y, y },
                           { 0, 0, ev_type::key, btn_code::touch, key_value::press },
                           { 0, 0, ev_type::sync, sync_code::report, 0 } } };
            }

            constexpr event_buffer_t<4> gen_release_event(const std::int32_t x, const std::int32_t y,
                                                          const std::int32_t slot) noexcept
            {
                return { { { 0, 0, ev_type::abs, abs_code::mt_slot, slot },
                           { 0, 0, ev_type::abs, abs_code::mt_track_id, -1 },
                           { 0, 0, ev_type::key, btn_code::touch, key_value::release },
                           { 0, 0, ev_type::sync, sync_code::report, 0 } } };
            }

            constexpr event_buffer_t<5> gen_move_event(const std::int32_t x, const std::int32_t y,
                                                       const std::int32_t track_id, const std::int32_t slot) noexcept
            {
                return { { { 0, 0, ev_type::abs, abs_code::mt_slot, slot },
                           { 0, 0, ev_type::abs, abs_code::mt_track_id, track_id },
                           { 0, 0, ev_type::abs, abs_code::mt_x, x },
                           { 0, 0, ev_type::abs, abs_code::mt_y, y },
                           { 0, 0, ev_type::sync, sync_code::report, 0 } } };
            }
        };
    }  // namespace details

    template<std::int32_t ScreenWidth, std::int32_t ScreenHeight, std::int32_t TouchWidth = 4096,
             std::int32_t TouchHeight = 4096, std::int32_t MaxSlots = 10>
    struct multi_touch_for_display
    {
        template<typename T>
        using type = details::multi_touch_feature<T, ScreenWidth, ScreenHeight, TouchWidth, TouchHeight, MaxSlots>;
    };
}  // namespace ui