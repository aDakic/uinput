# uinput
The uinput library utilizes features of the uinput kernel module which makes it possible to emulate input devices from userspace. By writing to /dev/uinput device, a process can create a virtual input device with specific capabilities. Once this virtual device is created, the process can send events through it, that will be delivered to userspace and in-kernel consumers. More details: [uinput](https://www.kernel.org/doc/html/v4.12/input/uinput.html)


## Usage
The central component of the library is `uinput` class which accept features as template parameters. The following features are currently supported:
Name  | Description
------------- | -------------
keyboard_with_keys<`uint16_t... KeyCodes`>  | Provides keyboard_press and keyboard_relase for the keycodes defined as KeyCodes..., all supported keycodes are defined in [uinput_defines.hpp](https://github.com/aDakic/uinput/blob/main/include/uinput/uinput_defines.hpp#L48).
mouse | Provides mouse_click_left, mouse_click_right, mouse_click_middle, mouse_scroll_up, mouse_scroll_down and mouse_move(x,y) where x and y are relative coordinates. 
multi_touch_for_display<`int32_t ScreenWidth,int32_t ScreenHeight, int32_t TouchWidth, int32_t TouchHeight, int32_t MaxSlots`> | Provides touch_press, touch_release and touch_move for the touch screen defined by parameters: ScreenWidth - screen width in px, ScreenHeight - screen height in px, TouchWidth - touch width in mm, TouchHeight - height in mm and MaxSlots - max slots. For TouchWidth, TouchHeight and MaxSlots default values are provided. 


`uinput` uses `uinput_driver` to perform low-level communication with the kernel. The user could use uinput_driver to create a custom device: [uinput_driver](#driver)

## Examples
### Keyboard
In this example, the uinput is defined with keyboard features and support for F1, F2 and F3 keycodes.
"Small keyboard", 0xACAD, 0xDEDA and 0x01 are device name, vendor identifier, product identifier and version, respectively. 
```cpp
#include "uinput/uinput.hpp"

using namespace ui;
using keyboard_t = uinput<keyboard_with_keys<key_code::f1, key_code::f2, key_code::f3>>;

keyboard_t small_keyboard { "Small keyboard", 0xACAD, 0xBABA, 0x01};

small_keyboard.key_press(key_code::f1);
small_keyboard.key_release(key_code::f1);
```
### Mouse
In this example, the uinput is defined with mouse features. "Small mouse", 0xACAD, 0xBABA and 0x01 are device name, vendor identifier, product identifier and version, respectively.
```cpp
#include "uinput/uinput.hpp"

using namespace ui;
using mouse_t = uinput<mouse>;

mouse_t small_mouse { "Small mouse", 0xACAD, 0xDEDA, 0x01};

small_mouse.mouse_click_left();
small_mouse.mouse_click_right();
small_mouse.mouse_click_middle();

small_mouse.mouse_move(50, 50);

small_mouse.mouse_scroll_up();
small_mouse.mouse_scroll_down();
```
### Touch
In this example, the uinput is defined with touch features for 1920x1200 display resolution. "Small touch", 0xACAD, 0xCECA and 0x01 are device name, vendor identifier, product identifier and version, respectively.
```cpp
#include "uinput/uinput.hpp"
#include <chrono>
#include <thread>

using namespace ui;
using namespace std::chrono_literals;

using touch_t = uinput<multi_touch_for_display<1920, 1200>>;

touch_t small_touch { "Small touch", 0xACAD, 0xCECA, 0x01 };

constexpr std::int32_t slot = 1;
std::int32_t track_id = 0;

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
```
The movement of the touch from this example draws a square:
![Alt text](.demo/gif.gif)
### Hybrid device
Users can combine features to create a hybrid device.
```cpp
#include "uinput/uinput.hpp"

using namespace ui;
using hybrid_t = uinput<keyboard_with_keys<key_code::space>, mouse>;

hybrid_t dev { "Keyboard&mouse", 0xACAD, 0xBABA, 0x01};

dev.key_press(key_code::space);
dev.key_release(key_code::space);

dev.mouse_click_left();

```
## Driver
The uinput_driver can be used for defining a custom device. [mouse_movements](https://www.kernel.org/doc/html/v4.12/input/uinput.html#mouse-movements) C example:
```c
#include <linux/uinput.h>

/* emit function is identical to of the first example */

int main(void)
{
   struct uinput_setup usetup;
   int i = 50;

   int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

   /* enable mouse button left and relative events */
   ioctl(fd, UI_SET_EVBIT, EV_KEY);
   ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);

   ioctl(fd, UI_SET_EVBIT, EV_REL);
   ioctl(fd, UI_SET_RELBIT, REL_X);
   ioctl(fd, UI_SET_RELBIT, REL_Y);

   memset(&usetup, 0, sizeof(usetup));
   usetup.id.bustype = BUS_USB;
   usetup.id.vendor = 0x1234; /* sample vendor */
   usetup.id.product = 0x5678; /* sample product */
   strcpy(usetup.name, "Example device");

   ioctl(fd, UI_DEV_SETUP, &usetup);
   ioctl(fd, UI_DEV_CREATE);

   /*
    * On UI_DEV_CREATE the kernel will create the device node for this
    * device. We are inserting a pause here so that userspace has time
    * to detect, initialize the new device, and can start listening to
    * the event, otherwise it will not notice the event we are about
    * to send. This pause is only needed in our example code!
    */
   sleep(1);

   /* Move the mouse diagonally, 5 units per axis */
   while (i--) {
      emit(fd, EV_REL, REL_X, 5);
      emit(fd, EV_REL, REL_Y, 5);
      emit(fd, EV_SYN, SYN_REPORT, 0);
      usleep(15000);
   }

   /*
    * Give userspace some time to read the events before we destroy the
    * device with UI_DEV_DESTOY.
    */
   sleep(1);

   ioctl(fd, UI_DEV_DESTROY);
   close(fd);

   return 0;
}
```
Rewritten with uinput_driver will look like:
```cpp
#include <chrono>
#include <thread>

#include "uinput/uinput_defines.hpp"
#include "uinput/uinput_driver.hpp"

using namespace ui;
using namespace std::chrono_literals;

int main()
{
    uinput_driver driver;
    int i = 50;

    if (!driver.set_events(ev_type::sync, ev_type::key, ev_type::rel))
        return EXIT_FAILURE;

    if (!driver.set_key_codes(btn_code::left))
        return EXIT_FAILURE;

    if (!driver.set_rel_codes(rel_code::x, rel_code::y))
        return EXIT_FAILURE;

    driver.set_info("Example device", 0x1234, 0x5678, 0x1);
    if (!driver.create_device())
        return EXIT_FAILURE;

    constexpr event_buffer_t<3> event{ { { 0, 0, ev_type::rel, rel_code::x, 5 },
                                         { 0, 0, ev_type::rel, rel_code::y, 5 },
                                         { 0, 0, ev_type::sync, sync_code::report, 0 } } };

    std::this_thread::sleep_for(1s);

    while (i--)
    {
        if (!driver.emit(event))
            return EXIT_FAILURE;

        std::this_thread::sleep_for(15ms);
    }

    return EXIT_SUCCESS;
}
```
