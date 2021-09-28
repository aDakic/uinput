#pragma once

#include "file_descriptor.hpp"

struct virtual_event
{
    std::int64_t sec;
    std::int64_t usec;
    std::uint16_t type;
    std::uint16_t code;
    std::int32_t value;
};

class virtual_device
{
public:
    virtual_device(const std::string_view& name, std::uint16_t vendor_id, std::uint16_t product_id, std::uint16_t version);
    virtual_device(const virtual_device&) = delete;
    virtual_device(virtual_device&&) = default;
    virtual_device& operator=(const virtual_device&) = delete;
    virtual_device& operator=(virtual_device&&) = default;
    ~virtual_device() noexcept;

    template <typename... Events>
    bool set_events(Events... events) noexcept
    {
        log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

        return set_bits(ui_bits::set_events, events...);
    }

    template <typename... KeyCodes>
    bool set_key_codes(KeyCodes... key_codes) noexcept
    {
        log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

        return set_bits(ui_bits::set_keys, key_codes...);
    }

    template <typename... RelCodes>
    bool set_rel_codes(RelCodes... rel_codes) noexcept
    {
        log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

        return set_bits(ui_bits::set_rels, rel_codes...);
    }

    template <typename... AbsCodes>
    bool set_abs_codes(AbsCodes... abs_codes) noexcept
    {
        log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

        return set_bits(ui_bits::set_abss, abs_codes...);
    }

    bool create_device() noexcept;

    template <std::size_t N>
    bool emit(std::array<virtual_event, N> events) noexcept
    {
        return m_fd.write(events);
    }

private:
    template <typename... Bits>
    bool set_bits(int flag, Bits... bits)
    {
        auto bits_ioctl  = [&](auto bit) { return m_fd.ioctl(flag, bit); };

        return (bits_ioctl(bits) && ...);
    }

    static constexpr const char * m_uinput_path = "/dev/uinput";
    static constexpr const char * m_virtual_device_tag = "virtual_device";
    file_descriptor m_fd;
    uinput_setup m_uinput_setup {};
};