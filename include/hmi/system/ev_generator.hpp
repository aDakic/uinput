#pragma once

#include "hmi/system/uinput_defines.hpp"

namespace hmi
{

struct ev_generator
{
    template <std::uint8_t value>
    static constexpr ui::event_buffer_t<2> key_event(std::uint16_t key) noexcept;
};

// Template methods implementation

template <std::uint8_t value>
constexpr ui::event_buffer_t<2> ev_generator::key_event(std::uint16_t key) noexcept
{
    return {{
        {0, 0, ui::ev_code::key, key, value},
        {0, 0, ui::ev_code::sync, ui::sync_code::report, 0}
    }};
}

}