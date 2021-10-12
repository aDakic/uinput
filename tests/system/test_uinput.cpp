#include <gtest/gtest.h>

#include "hmi/system/uinput.hpp"

class test_uinput : ui::uinput
{
    public:
    void set_info(std::string_view name, const std::uint16_t vendor_id, 
                const std::uint16_t product_id, const std::uint16_t version) noexcept
    {
        ui::uinput::set_info(name, vendor_id, product_id, version);
    }

    template <typename... Events>
    bool set_events(const Events... events) noexcept { return ui::uinput::set_events(events...); }

    template <typename... KeyCodes>
    bool set_key_codes(const KeyCodes... key_codes) noexcept { return ui::uinput::set_key_codes(key_codes...); }

    template <typename... RelCodes>
    bool set_rel_codes(const RelCodes... rel_codes) noexcept { return ui::uinput::set_rel_codes(rel_codes...); }

    template <typename... AbsCodes>
    bool set_abs_codes(const AbsCodes... abs_codes) noexcept { return ui::uinput::set_abs_codes(abs_codes...); }

    template <std::size_t N>
    bool emit(const ui::event_buffer_t<N>& events) noexcept  { return ui::uinput::emit(events); }

    bool create_device() noexcept { return ui::uinput::create_device(); }
};

TEST(uinput, constructor)
{
    EXPECT_NO_THROW(test_uinput{});
}

constexpr inline std::uint16_t vendor_id = 0x1234;
constexpr inline std::uint16_t product_id = 0x5678;
constexpr inline std::uint16_t version = 0x1;

TEST(uinput, keyboard)
{
    test_uinput dev;

    dev.set_info("virtual_keyboard", vendor_id, product_id, version);

    EXPECT_TRUE(dev.set_events(ui::ev_code::sync, ui::ev_code::key));
    EXPECT_TRUE(dev.set_key_codes(ui::key_code::space));
    EXPECT_TRUE(dev.set_key_codes(ui::key_code::k1, ui::key_code::k2));
    EXPECT_TRUE(dev.create_device());

    // press space
    constexpr ui::event_buffer_t<2> space_press {{
        {0, 0, ui::ev_code::key, ui::key_code::space, ui::key_value::press},
        {0, 0, ui::ev_code::sync, ui::sync_code::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(space_press));

    // release space
    constexpr ui::event_buffer_t<2> space_release {{
            {0, 0, ui::ev_code::key, ui::key_code::space, ui::key_value::release},
            {0, 0, ui::ev_code::sync, ui::sync_code::report, 0}
    }};

    EXPECT_TRUE(dev.emit(space_release));

    // press key 1
    constexpr ui::event_buffer_t<2> key_1_press {{
        {0, 0, ui::ev_code::key, ui::key_code::k1, ui::key_value::press},
        {0, 0, ui::ev_code::sync, ui::sync_code::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(key_1_press));

    // release key 1
    constexpr ui::event_buffer_t<2> key_1_release {{
        {0, 0, ui::ev_code::key, ui::key_code::k1, ui::key_value::release},
        {0, 0, ui::ev_code::sync, ui::sync_code::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(key_1_release));
}

TEST(uinput, mouse)
{
    test_uinput dev;

    dev.set_info("virtual_mouse", vendor_id, product_id, version);

    EXPECT_TRUE(dev.set_events(ui::ev_code::sync, ui::ev_code::key, ui::ev_code::rel));
    EXPECT_TRUE(dev.set_key_codes(ui::btn_code::left, ui::btn_code::right));
    EXPECT_TRUE(dev.set_rel_codes(ui::rel_code::x, ui::rel_code::y));
    EXPECT_TRUE(dev.create_device());

    // move mouse
    constexpr ui::event_buffer_t<3> move_mouse {{
        {0, 0, ui::ev_code::rel, ui::rel_code::x, 50},
        {0, 0, ui::ev_code::rel, ui::rel_code::y, 50},
        {0, 0, ui::ev_code::sync, ui::sync_code::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(move_mouse));

    // press right click
    constexpr ui::event_buffer_t<4> right_click {{
        {0, 0, ui::ev_code::key, ui::btn_code::right, ui::key_value::press},
        {0, 0, ui::ev_code::sync, ui::sync_code::report, 0},
        {0, 0, ui::ev_code::key, ui::btn_code::right, ui::key_value::release},
        {0, 0, ui::ev_code::sync, ui::sync_code::report, 0}         
    }};

    EXPECT_TRUE(dev.emit(right_click));
}