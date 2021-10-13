#pragma once

#include "hmi/system/uinput.hpp"

namespace hmi
{

struct touch_config
{
    std::int32_t screen_width;
    std::int32_t screen_height;
    std::int32_t touch_width;
    std::int32_t touch_height;
    std::int32_t max_slots;
};

class touch final : ui::uinput
{
public:
    touch(touch_config config);
    bool press(const std::int32_t x, const std::int32_t y, const std::int32_t track_id, const std::int32_t slot = 0) noexcept;
    bool release(const std::int32_t x, const std::int32_t y, const std::int32_t slot = 0) noexcept;
    bool move(const std::int32_t x, const std::int32_t y, const std::int32_t track_id, const std::int32_t slot = 0) noexcept;

private:
    std::int32_t get_x(std::int32_t x) const noexcept;
    std::int32_t get_y(std::int32_t y) const noexcept;

    touch_config m_config;
};

}