#include <gtest/gtest.h>

#include "virtual_hmi/virtual_device.hpp"

TEST(virtual_device, constructor)
{
    virtual_device dev("virtual_device", 0x1234, 0x5678, 1);
    bool ret = dev.set_events(event_codes::sync, event_codes::key, event_codes::rel, event_codes::abs);
    ret = dev.set_key_codes(KEY_SPACE);
    ret = dev.set_rel_codes(REL_X);
    ret = dev.set_abs_codes(ABS_X);
    ret = dev.create_device();

    constexpr std::array<virtual_event, 2> press  {{
                {0, 0, event_codes::key, KEY_SPACE, 1},
                {0, 0, event_codes::sync, SYN_REPORT, 0} 
    }};

    ret = dev.emit(press);

    constexpr std::array<virtual_event, 2> release {{
            {0, 0, event_codes::key, KEY_SPACE, 0},
            {0, 0, event_codes::sync, SYN_REPORT, 0}
    }};

    ret = dev.emit(release);
}