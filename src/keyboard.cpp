#include "hmi/keyboard.hpp"
#include "hmi/system/ev_generator.hpp"

namespace hmi
{

bool keyboard::press(std::uint16_t key) noexcept
{
   return emit(ev_generator::key_event<ui::key_value::press>(key));
}

bool keyboard::release(std::uint16_t key) noexcept
{
   return emit(ev_generator::key_event<ui::key_value::release>(key));
}
}