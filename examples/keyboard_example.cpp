#include "uinput/uinput.hpp"

int main()
{
    using namespace ui;
    using keyboard_t = uinput<keyboard_with_keys<key_code::f1, key_code::f2, key_code::f3>>;

    keyboard_t small_keyboard { "Small keyboard", 0xACAD, 0xBABA, 0x01};

    small_keyboard.key_press(key_code::f1);
    small_keyboard.key_release(key_code::f1);

    return 0;
}