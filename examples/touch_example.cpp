#include <chrono>
#include <thread>

#include "uinput/uinput.hpp"

using namespace ui;
using namespace std::chrono_literals;

int main()
{
    using touch_t = uinput<multi_touch_for_display<1920, 1200>>;

    touch_t small_touch{ "Small touch", 0xACAD, 0xDEDA, 0x01 };

    constexpr std::int32_t slot = 1;
    std::int32_t track_id       = 0;

    std::this_thread::sleep_for(150ms);
    small_touch.touch_press(200, 300, track_id++, slot);
    small_touch.touch_move(400, 300, track_id++, slot);
    small_touch.touch_release(400, 300, slot);

    std::this_thread::sleep_for(150ms);
    small_touch.touch_press(400, 300, track_id++, slot);
    small_touch.touch_move(400, 500, track_id++, slot);
    small_touch.touch_release(400, 500, slot);

    std::this_thread::sleep_for(150ms);
    small_touch.touch_press(400, 500, track_id++, slot);
    small_touch.touch_move(200, 500, track_id++, slot);
    small_touch.touch_release(200, 500, slot);

    std::this_thread::sleep_for(150ms);
    small_touch.touch_press(200, 500, track_id++, slot);
    small_touch.touch_move(200, 300, track_id++, slot);
    small_touch.touch_release(200, 300, slot);

    return 0;
}