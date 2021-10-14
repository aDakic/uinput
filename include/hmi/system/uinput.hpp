#pragma once

#include "file_desc.hpp"
#include "uinput_defines.hpp"

namespace ui
{
    class uinput : fd::file_desc
    {
    public:
        uinput();
        uinput(const uinput&) = default;
        uinput(uinput&&)      = default;
        uinput& operator=(const uinput&) noexcept = default;
        uinput& operator=(uinput&&) noexcept = default;
        ~uinput() noexcept;

        void set_info(std::string_view name, const std::uint16_t vendor_id, const std::uint16_t product_id,
                      const std::uint16_t version) noexcept;

        template<typename... Events>
        [[nodiscard]] bool set_events(const Events... events) noexcept;

        template<typename... KeyCodes>
        [[nodiscard]] bool set_key_codes(const KeyCodes... key_codes) noexcept;

        template<typename... RelCodes>
        [[nodiscard]] bool set_rel_codes(const RelCodes... rel_codes) noexcept;

        template<typename... AbsCodes>
        [[nodiscard]] bool set_abs_codes(const AbsCodes... abs_codes) noexcept;

        [[nodiscard]] bool create_device() noexcept;

        template<std::size_t N>
        [[nodiscard]] bool emit(const event_buffer_t<N>& events) noexcept;

        template<std::uint16_t Code>
        void set_abs_info(const std::int32_t min, const std::int32_t max) noexcept;

    private:
        static constexpr const char* uinput_path = "/dev/uinput";
        setup_t m_setup{};

        template<typename... Bits>
        bool set_bits(const int flag, const Bits... bits) noexcept;
    };

    // Template methods implementation

    template<typename... Events>
    bool uinput::set_events(const Events... events) noexcept
    {
        return set_bits(bit::set_events, events...);
    }

    template<typename... KeyCodes>
    bool uinput::set_key_codes(const KeyCodes... key_codes) noexcept
    {
        return set_bits(bit::set_keys, key_codes...);
    }

    template<typename... RelCodes>
    bool uinput::set_rel_codes(const RelCodes... rel_codes) noexcept
    {
        return set_bits(bit::set_rels, rel_codes...);
    }

    template<typename... AbsCodes>
    bool uinput::set_abs_codes(const AbsCodes... abs_codes) noexcept
    {
        return set_bits(bit::set_abss, abs_codes...);
    }

    template<std::size_t N>
    bool uinput::emit(const event_buffer_t<N>& events) noexcept
    {
        return fd::file_desc::write(events);
    }

    template<std::uint16_t Code>
    void uinput::set_abs_info(const std::int32_t min, const std::int32_t max) noexcept
    {
        m_setup.absmin[Code] = min;
        m_setup.absmax[Code] = max;
    }

    template<typename... Bits>
    bool uinput::set_bits(const int flag, const Bits... bits) noexcept
    {
        auto bits_ioctl = [&](auto bit) { return fd::file_desc::ioctl(flag, bit); };

        return (bits_ioctl(bits) && ...);
    }

}  // namespace ui