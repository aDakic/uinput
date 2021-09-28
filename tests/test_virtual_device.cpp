#include <gtest/gtest.h>

#include "virtual_hmi/virtual_device.hpp"

TEST(virtual_device, constructor)
{
    virtual_device dev("virtual_device", 0x1234, 0x5678, 1);
    //dev.set_events(EV_KEY, EV_SYN);
    //dev.set_key_codes(KEY_SPACE);
    dev.create_device();

    while(1)
    {
        sleep(1);
    }
}