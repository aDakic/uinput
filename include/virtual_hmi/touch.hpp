#pragma once

#include "virtual_hmi/system/virtual_device.hpp"

class touch final
{
    touch(std::uint16_t width, std::uint16_t height, std::uint16_t twidth, std::uint16_t theight);

    bool press(const std::int32_t x, const std::int32_t y, const std::int32_t slot = 0) noexcept;
    bool release(const std::int32_t x, const std::int32_t y, const std::int32_t slot = 0) noexcept;
    bool move(const std::int32_t x, const std::int32_t y, const std::int32_t slot = 0) noexcept;

private:
constexpr std::int32_t convert_x(const int32_t x) const noexcept;
constexpr std::int32_t convert_y(const int32_t y) const noexcept;
    static constexpr const char *touch_tag = "touch";
    virtual_device m_vdev;
};