#include <gtest/gtest.h>

#include "virtual_hmi/virtual_device.hpp"

TEST(virtual_device, constructor)
{
    virtual_device dev("virtual_device", 0x1234, 0x5678, 1);

    if(!dev.set_events(event_codes::sync, event_codes::key, event_codes::rel, event_codes::abs))
        EXPECT_TRUE(false);

    if(!dev.set_key_codes(key_codes::space))
        EXPECT_TRUE(false);

    if(!dev.set_rel_codes(rel_codes::x))
        EXPECT_TRUE(false);

    if(!dev.set_abs_codes(abs_codes::x))
        EXPECT_TRUE(false);

    if(!dev.create_device())
        EXPECT_TRUE(false);
    sleep(4);
    constexpr std::array<virtual_event, 2> press  {{
            {0, 0, event_codes::key, key_codes::space, 1},
            {0, 0, event_codes::sync, sync_codes::report, 0} 
    }};

    if(!dev.emit(press))
        EXPECT_TRUE(false);

    constexpr std::array<virtual_event, 2> release {{
            {0, 0, event_codes::key, key_codes::space, 0},
            {0, 0, event_codes::sync, sync_codes::report, 0}
    }};

    if(!dev.emit(release))
        EXPECT_TRUE(false);
}