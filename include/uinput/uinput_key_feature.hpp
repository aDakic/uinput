#pragma once

#include "uinput/common/crtp.hpp"
#include "uinput_defines.hpp"

namespace ui
{
    template<typename uinput_base, std::uint16_t... keycodes>
    struct keyboard_feature : utils::crtp_with_params<uinput_base, keyboard_feature>
    {
        keyboard_feature()
        {
            auto error = this->get().set_events(ev_type::sync, ev_type::key);
            if (!error)
                throw std::runtime_error{ "Failed to enable KEY and SYNC events." };

            error = this->get().set_key_codes(keycodes...);
            if (!error)
                throw std::runtime_error{ "Failed to enable key codes." };
        }

        bool key_press(std::uint16_t keycode) noexcept { return this->get().emit(gen_key_event<key_value::press>(keycode)); }

        bool key_release(std::uint16_t keycode) noexcept
        {
            return this->get().emit(gen_key_event<key_value::release>(keycode));
        }

    private:
        template<std::uint8_t value>
        constexpr event_buffer_t<2> gen_key_event(std::uint16_t key) noexcept
        {
            return { { { 0, 0, ev_type::key, key, value }, { 0, 0, ev_type::sync, sync_code::report, 0 } } };
        }
    };

    template<std::uint16_t... keycodes>
    struct keyboard_with_keys
    {
        template<typename T>
        using type = keyboard_feature<T, keycodes...>;
    };
}