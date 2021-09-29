#include <gtest/gtest.h>

#include "virtual_hmi/system/virtual_device.hpp"

TEST(virtual_device, constructor)
{
    EXPECT_NO_THROW(virtual_device{});
}

constexpr inline std::uint16_t vendor_id = 0x1234;
constexpr inline std::uint16_t product_id = 0x5678;
constexpr inline std::uint16_t version = 0x1;

TEST(virtual_device, keyboard)
{
    virtual_device dev;

    dev.set_info("virtual_keyboard", vendor_id, product_id, version);

    EXPECT_TRUE(dev.set_events(event_codes::sync, event_codes::key));
    EXPECT_TRUE(dev.set_key_codes(key_codes::space));
    EXPECT_TRUE(dev.set_key_codes(key_codes::k1, key_codes::k2));
    EXPECT_TRUE(dev.create_device());

    // press space
    constexpr event_buffer_t<2> space_press {{
        {0, 0, event_codes::key, key_codes::space, key_ev_values::press},
        {0, 0, event_codes::sync, sync_codes::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(space_press));

    // release space
    constexpr event_buffer_t<2> space_release {{
            {0, 0, event_codes::key, key_codes::space, key_ev_values::release},
            {0, 0, event_codes::sync, sync_codes::report, 0}
    }};

    EXPECT_TRUE(dev.emit(space_release));

    // press key 1
    constexpr event_buffer_t<2> key_1_press {{
        {0, 0, event_codes::key, key_codes::k1, key_ev_values::press},
        {0, 0, event_codes::sync, sync_codes::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(key_1_press));

    // release key 1
    constexpr event_buffer_t<2> key_1_release {{
        {0, 0, event_codes::key, key_codes::k1, key_ev_values::release},
        {0, 0, event_codes::sync, sync_codes::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(key_1_release));
}

TEST(virtual_device, mouse)
{
    virtual_device dev;

    dev.set_info("virtual_mouse", vendor_id, product_id, version);

    EXPECT_TRUE(dev.set_events(event_codes::sync, event_codes::key, event_codes::rel));
    EXPECT_TRUE(dev.set_key_codes(btn_codes::left, btn_codes::right));
    EXPECT_TRUE(dev.set_rel_codes(rel_codes::x, rel_codes::y));
    EXPECT_TRUE(dev.create_device());

    sleep(10);
    // move mouse
    constexpr event_buffer_t<3> move_mouse {{
        {0, 0, event_codes::rel, rel_codes::x, 50},
        {0, 0, event_codes::rel, rel_codes::y, 50},
        {0, 0, event_codes::sync, sync_codes::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(move_mouse));

    // press right click
    constexpr event_buffer_t<4> right_click {{
        {0, 0, event_codes::key, btn_codes::right, key_ev_values::press},
        {0, 0, event_codes::sync, sync_codes::report, 0},
        {0, 0, event_codes::key, btn_codes::right, key_ev_values::release},
        {0, 0, event_codes::sync, sync_codes::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(right_click));
}