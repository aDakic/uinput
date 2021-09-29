#include "virtual_hmi/keyboard.hpp"

bool keyboard::press(std::uint16_t key) noexcept
{
    return m_vdev.emit(generate_event<key_ev_values::press>(key));
}

bool keyboard::release(std::uint16_t key) noexcept
{
    return m_vdev.emit(generate_event<key_ev_values::release>(key));
}
