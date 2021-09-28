#pragma once

#include "file_descriptor.hpp"

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
        auto set_event = [&](auto ev) { return m_fd.ioctl(ui_bits::set_events, ev); };

        return (set_event(events) && ...);
    }

    template <typename... KeyCodes>
    bool set_key_codes(KeyCodes... keycodes) noexcept
    {
        auto set_key_codes = [&](auto key) { return m_fd.ioctl(event_bits::key_codes, key); };

        return (set_key_codes(keycodes) && ...);
    }

    bool create_device() noexcept;
private:

    static constexpr const char * m_uinput_path = "/dev/uinput";
    file_descriptor m_fd;
    uinput_user_dev m_uinput_setup;
};