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