#include "virtual_hmi/touch.hpp"

touch::touch(std::uint16_t width, std::uint16_t height, std::uint16_t twidth, std::uint16_t theight)
{
    constexpr const char* name = "Virtual HMI Touch";
    constexpr std::uint16_t vendor = 0xACAD;
    constexpr std::uint16_t product = 0x0003;
    constexpr std::uint16_t version = 0x0001;

    m_vdev.set_info(name, vendor, product, version);

    if (!m_vdev.set_events(event_codes::sync, event_codes::key, event_codes::abs))
        throw std::runtime_error{"Failed to set supproted events."};

    if (!m_vdev.set_key_codes(btn_codes::touch))
        throw std::runtime_error{"Failed to set supproted key codes."};

    if (!m_vdev.set_abs_codes(abs_codes::mt_x, abs_codes::mt_y, abs_codes::mt_track_id, abs_codes::mt_slot))
        throw std::runtime_error{"Failed to set supproted abs codes."};

    m_vdev.set_abs_info<abs_codes::mt_x>(0, 4096);
    m_vdev.set_abs_info<abs_codes::mt_y>(0, 4096);
    m_vdev.set_abs_info<abs_codes::mt_track_id>(0, std::numeric_limits<std::uint16_t>::max());
    m_vdev.set_abs_info<abs_codes::mt_slot>(0, 10);

    if (!m_vdev.create_device())
        throw std::runtime_error{"Failed to create virtual device."};
}

bool touch::press(const std::int32_t x, const std::int32_t y, const std::int32_t slot) noexcept
{
    return false;
}

bool touch::release(const std::int32_t x, const std::int32_t y, const std::int32_t slot) noexcept
{
    return false;
}

bool touch::move(const std::int32_t x, const std::int32_t y, const std::int32_t slot) noexcept
{
    return false;
}

constexpr std::int32_t touch::convert_x(const int32_t x) const noexcept
{
    return 0;//(x * (twidth + 1)) / width;
}

constexpr std::int32_t touch::convert_y(const int32_t y) const noexcept
{
    return 0;//(y * (theight + 1)) / height;
}