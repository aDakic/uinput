#pragma once

#include <fcntl.h>
#include <linux/uinput.h>

namespace flags {
    inline constexpr int read_only = O_RDONLY;
    inline constexpr int read_write = O_RDWR;
    inline constexpr int write_only = O_WRONLY;
    inline constexpr int non_block = O_NONBLOCK;
    inline constexpr int no_delay = O_NDELAY;
};

namespace ui_bits {
    inline constexpr int dev_create = UI_DEV_CREATE;
    inline constexpr int dev_destroy = UI_DEV_DESTROY;
    inline constexpr int dev_setup = UI_DEV_SETUP;
    inline constexpr int set_events = UI_SET_EVBIT;
}

namespace event_bits {
    inline constexpr int sync_codes = EV_SYN;
    inline constexpr int key_codes = EV_KEY;
    inline constexpr int rel_codes = EV_REL;
    inline constexpr int abs_codes = EV_ABS;
}

namespace ui_setup {
    inline constexpr int virtual_bus = BUS_VIRTUAL;
    inline constexpr int max_name_size = UINPUT_MAX_NAME_SIZE;
}