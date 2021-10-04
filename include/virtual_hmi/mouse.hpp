#pragma once

#include "virtual_hmi/system/virtual_device.hpp"

class mouse final
{
public:
    mouse();

    bool click_left() noexcept;
    bool click_right() noexcept;
    bool click_middle() noexcept;

    bool move(std::int32_t x, std::int32_t y) noexcept;

    bool scroll_up() noexcept;
    bool scroll_down() noexcept;

private:
    constexpr event_buffer_t<4> generate_click(std::uint16_t btn) const noexcept;
    constexpr event_buffer_t<3> generate_move(std::int32_t x, std::int32_t y) const noexcept;
    constexpr event_buffer_t<2> generate_scroll(std::int32_t up_or_down) const noexcept;

    static constexpr const char *keyboard_tag = "mouse";
    virtual_device m_vdev;
};
