#pragma once

#include "uinput/system/uinput_defines.hpp"

namespace ui
{
    struct event_gen
    {
        template<std::uint8_t value>
        static constexpr event_buffer_t<2> key_event(std::uint16_t key) noexcept;
        static constexpr event_buffer_t<3> move_event(std::int32_t x, std::int32_t y) noexcept;
        static constexpr event_buffer_t<4> click_event(std::uint16_t btn) noexcept;
        static constexpr event_buffer_t<2> scroll_event(std::int32_t up_or_down) noexcept;
        static constexpr event_buffer_t<6> touch_press_event(const std::int32_t x,
                                                             const std::int32_t y,
                                                             const std::int32_t track_id,
                                                             const std::int32_t slot) noexcept;
        static constexpr event_buffer_t<5> touch_move_event(const std::int32_t x,
                                                            const std::int32_t y,
                                                            const std::int32_t track_id,
                                                            const std::int32_t slot) noexcept;
        static constexpr event_buffer_t<4> touch_release_event(const std::int32_t x,
                                                               const std::int32_t y,
                                                               const std::int32_t slot) noexcept;

    private:
        template<std::size_t N, std::size_t M, std::size_t... I, std::size_t... J>
        static constexpr auto concat_buffer_impl(event_buffer_t<N> lhs,
                                                 event_buffer_t<M> rhs,
                                                 std::index_sequence<I...>,
                                                 std::index_sequence<J...>) noexcept -> event_buffer_t<N + M>
        {
            return event_buffer_t<N + M>{ { lhs[I]..., rhs[J]... } };
        }

        template<std::size_t N, std::size_t M>
        static constexpr auto concat_buffer(event_buffer_t<N> lhs, event_buffer_t<M> rhs) noexcept -> event_buffer_t<N + M>
        {
            return concat_buffer_impl<N, M>(lhs, rhs, std::make_index_sequence<N>{}, std::make_index_sequence<M>{});
        }
    };

    // Template methods implementation

    template<std::uint8_t value>
    constexpr event_buffer_t<2> event_gen::key_event(std::uint16_t key) noexcept
    {
        return { { { 0, 0, ev_type::key, key, value }, { 0, 0, ev_type::sync, sync_code::report, 0 } } };
    }

    constexpr event_buffer_t<4> event_gen::click_event(std::uint16_t btn) noexcept
    {
        return concat_buffer(key_event<ui::key_value::press>(btn), key_event<ui::key_value::release>(btn));
    }

    constexpr event_buffer_t<3> event_gen::move_event(std::int32_t x, std::int32_t y) noexcept
    {
        return { { { 0, 0, ev_type::rel, rel_code::x, x },
                   { 0, 0, ev_type::rel, rel_code::y, y },
                   { 0, 0, ev_type::sync, sync_code::report, 0 } } };
    }

    constexpr event_buffer_t<2> event_gen::scroll_event(std::int32_t up_or_down) noexcept
    {
        return { { { 0, 0, ev_type::rel, rel_code::wheel, up_or_down }, { 0, 0, ev_type::sync, sync_code::report, 0 } } };
    }

    constexpr event_buffer_t<6> event_gen::touch_press_event(const std::int32_t x,
                                                             const std::int32_t y,
                                                             const std::int32_t track_id,
                                                             const std::int32_t slot) noexcept
    {
        event_buffer_t<4> id{ { { 0, 0, ev_type::abs, abs_code::mt_slot, slot },
                                { 0, 0, ev_type::abs, abs_code::mt_track_id, track_id },
                                { 0, 0, ev_type::abs, abs_code::mt_x, x },
                                { 0, 0, ev_type::abs, abs_code::mt_y, y } } };

        return concat_buffer(id, key_event<ui::key_value::press>(ui::btn_code::touch));
    }

    constexpr event_buffer_t<4> event_gen::touch_release_event(const std::int32_t x,
                                                               const std::int32_t y,
                                                               const std::int32_t slot) noexcept
    {
        event_buffer_t<2> id{ {
          { 0, 0, ev_type::abs, abs_code::mt_slot, slot },
          { 0, 0, ev_type::abs, abs_code::mt_track_id, -1 },
        } };

        return concat_buffer(id, key_event<ui::key_value::release>(ui::btn_code::touch));
    }

    constexpr event_buffer_t<5> event_gen::touch_move_event(const std::int32_t x,
                                                            const std::int32_t y,
                                                            const std::int32_t track_id,
                                                            const std::int32_t slot) noexcept
    {
        return { { { 0, 0, ev_type::abs, abs_code::mt_slot, slot },
                   { 0, 0, ev_type::abs, abs_code::mt_track_id, track_id },
                   { 0, 0, ev_type::abs, abs_code::mt_x, x },
                   { 0, 0, ev_type::abs, abs_code::mt_y, y },
                   { 0, 0, ev_type::sync, sync_code::report, 0 } } };
    }
} // namespace ui