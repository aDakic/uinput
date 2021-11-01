#include "uinput/uinput.hpp"

int main()
{
    using namespace ui;
    using mouse_t = uinput<mouse>;

    mouse_t small_mouse { "Small mouse", 0xACAD, 0xDEDA, 0x01};

    small_mouse.mouse_click_left();
    small_mouse.mouse_click_right();
    small_mouse.mouse_click_middle();

    small_mouse.mouse_move(50, 50);

    small_mouse.mouse_scroll_up();
    small_mouse.mouse_scroll_down();

    return 0;
}