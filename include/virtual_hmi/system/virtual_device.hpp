#pragma once

#include "file_descriptor.hpp"

struct virtual_event
{
    std::uint64_t sec;
    std::uint64_t usec;
    std::uint16_t type;
    std::uint16_t code;
    std::int32_t value;
};

template <std::size_t N>
using event_buffer_t = std::array<virtual_event, N>;

class virtual_device
{
public:
    virtual_device();
    virtual_device(const virtual_device&) = delete;
    virtual_device(virtual_device&&) = default;
    virtual_device& operator=(const virtual_device&) = delete;
    virtual_device& operator=(virtual_device&&) = default;
    ~virtual_device() noexcept;

    void set_info(const std::string_view& name, std::uint16_t vendor_id, 
                  std::uint16_t product_id, std::uint16_t version) noexcept;

    template <typename... Events>
    [[nodiscard]] bool set_events(const Events... events) noexcept;

    template <typename... KeyCodes>
    [[nodiscard]] bool set_key_codes(const KeyCodes... key_codes) noexcept;

    template <typename... RelCodes>
    [[nodiscard]] bool set_rel_codes(const RelCodes... rel_codes) noexcept;

    template <typename... AbsCodes>
    [[nodiscard]] bool set_abs_codes(const AbsCodes... abs_codes) noexcept;

    [[nodiscard]] bool create_device() noexcept;

    template <std::size_t N>
    [[nodiscard]] bool emit(const event_buffer_t<N> events) noexcept;

    template <std::uint16_t Code>
    void set_abs_info(const std::int32_t min, const std::int32_t max) noexcept;

private:
    template <typename... Bits>
    bool set_bits(const int flag, const Bits... bits) noexcept;

    static constexpr const char * m_uinput_path = "/dev/uinput";
    static constexpr const char * m_virtual_device_tag = "virtual_device";
    file_descriptor m_fd;
    uinput_user_dev m_uinput_setup {};
};

// Template methods implementation

template <typename... Events>
bool virtual_device::set_events(const Events... events) noexcept
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

    return set_bits(ui_bits::set_events, events...);
}

template <typename... KeyCodes>
bool virtual_device::set_key_codes(const KeyCodes... key_codes) noexcept
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

    return set_bits(ui_bits::set_keys, key_codes...);
}

template <typename... RelCodes>
bool virtual_device::set_rel_codes(const RelCodes... rel_codes) noexcept
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

    return set_bits(ui_bits::set_rels, rel_codes...);
}

template <typename... AbsCodes>
bool virtual_device::set_abs_codes(const AbsCodes... abs_codes) noexcept
{
    log_info(m_virtual_device_tag, "{}\n", __FUNCTION__);

    return set_bits(ui_bits::set_abss, abs_codes...);
}

template <std::size_t N>
bool virtual_device::emit(const event_buffer_t<N> events) noexcept
{
    return m_fd.write(events);
}

template <typename... Bits>
bool virtual_device::set_bits(const int flag, const Bits... bits) noexcept
{
    auto bits_ioctl  = [&](auto bit) { return m_fd.ioctl(flag, bit); };

    return (bits_ioctl(bits) && ...);
}

template <std::uint16_t Code>
void virtual_device::set_abs_info(const std::int32_t min, const std::int32_t max) noexcept
{
    m_uinput_setup.absmin[Code] = min;
    m_uinput_setup.absmax[Code] = max;
}