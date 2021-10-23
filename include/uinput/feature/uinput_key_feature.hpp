#pragma once

#include "uinput/uinput_defines.hpp"

namespace ui
{
    namespace details
    {
        template<typename Driver, std::uint16_t... KeyCodes>
        struct keyboard_feature
        {
            keyboard_feature()
            {
                auto error = get().set_events(ev_type::sync, ev_type::key);
                if (!error)
                    throw std::runtime_error{ "Failed to enable KEY and SYNC events." };

                error = get().set_key_codes(KeyCodes...);
                if (!error)
                    throw std::runtime_error{ "Failed to enable key codes." };
            }

            bool key_press(std::uint16_t keycode) noexcept { return get().emit(gen_key_event<key_value::press>(keycode)); }

            bool key_release(std::uint16_t keycode) noexcept
            {
                return get().emit(gen_key_event<key_value::release>(keycode));
            }

        private:
            constexpr decltype(auto) get() noexcept { return static_cast<Driver&>(*this); }

            template<std::uint8_t value>
            constexpr event_buffer_t<2> gen_key_event(std::uint16_t key) noexcept
            {
                return { { { 0, 0, ev_type::key, key, value }, { 0, 0, ev_type::sync, sync_code::report, 0 } } };
            }
        };
    }  // namespace details

    template<std::uint16_t... KeyCodes>
    struct keyboard_with_keys
    {
        template<typename Driver>
        using type = details::keyboard_feature<Driver, KeyCodes...>;
    };
}  // namespace ui