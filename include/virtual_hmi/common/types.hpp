#pragma once

#include <fcntl.h>
#include <linux/uinput.h>

namespace flags {
    inline constexpr std::int32_t read_only = O_RDONLY;
    inline constexpr std::int32_t read_write = O_RDWR;
    inline constexpr std::int32_t write_only = O_WRONLY;
    inline constexpr std::int32_t non_block = O_NONBLOCK;
    inline constexpr std::int32_t no_delay = O_NDELAY;
};

namespace ui_bits {
    inline constexpr std::uint64_t dev_create = UI_DEV_CREATE;
    inline constexpr std::uint64_t dev_destroy = UI_DEV_DESTROY;
    inline constexpr std::uint64_t dev_setup = UI_DEV_SETUP;
    inline constexpr std::uint64_t set_events = UI_SET_EVBIT;
    inline constexpr std::uint64_t set_keys = UI_SET_KEYBIT;
    inline constexpr std::uint64_t set_rels = UI_SET_RELBIT;
    inline constexpr std::uint64_t set_abss = UI_SET_ABSBIT;
}

namespace event_codes {
    inline constexpr std::uint16_t sync = EV_SYN;
    inline constexpr std::uint16_t key = EV_KEY;
    inline constexpr std::uint16_t rel = EV_REL;
    inline constexpr std::uint16_t abs = EV_ABS;
}

namespace ui_setup {
    inline constexpr std::uint16_t virtual_bus = BUS_VIRTUAL;
    inline constexpr std::uint16_t max_name_size = UINPUT_MAX_NAME_SIZE;
}

namespace sync_codes {
    inline constexpr std::uint16_t report =  SYN_REPORT;
    inline constexpr std::uint16_t config = SYN_CONFIG;
    inline constexpr std::uint16_t mt_report =  SYN_MT_REPORT;
}

namespace key_codes {
    inline constexpr std::uint16_t esc = KEY_ESC;
    inline constexpr std::uint16_t k1 = KEY_1;
    inline constexpr std::uint16_t k2 = KEY_2;			
    inline constexpr std::uint16_t k3 = KEY_3;			
    inline constexpr std::uint16_t k4 = KEY_4;		
    inline constexpr std::uint16_t k5 = KEY_5;		
    inline constexpr std::uint16_t k6 = KEY_6;		
    inline constexpr std::uint16_t k7 = KEY_7;	
    inline constexpr std::uint16_t k8 = KEY_8;	
    inline constexpr std::uint16_t k9 = KEY_9;		
    inline constexpr std::uint16_t k0 = KEY_0;	
    inline constexpr std::uint16_t minus = KEY_MINUS;		
    inline constexpr std::uint16_t equal = KEY_EQUAL;	
    inline constexpr std::uint16_t bspace = KEY_BACKSPACE	;	
    inline constexpr std::uint16_t tab = KEY_TAB;			
    inline constexpr std::uint16_t q = KEY_Q;	
    inline constexpr std::uint16_t w = KEY_W;		
    inline constexpr std::uint16_t e = KEY_E;	
    inline constexpr std::uint16_t r = KEY_R;		
    inline constexpr std::uint16_t t = KEY_T;		
    inline constexpr std::uint16_t y = KEY_Y;		
    inline constexpr std::uint16_t u = KEY_U;		
    inline constexpr std::uint16_t i = KEY_I;	
    inline constexpr std::uint16_t o = KEY_O;	
    inline constexpr std::uint16_t p = KEY_P;	
    inline constexpr std::uint16_t lbrace = KEY_LEFTBRACE;		
    inline constexpr std::uint16_t rbrace = KEY_RIGHTBRACE;	
    inline constexpr std::uint16_t enter = KEY_ENTER;	
    inline constexpr std::uint16_t lctrl = KEY_LEFTCTRL;	
    inline constexpr std::uint16_t a = KEY_A;		
    inline constexpr std::uint16_t s = KEY_S;	
    inline constexpr std::uint16_t d = KEY_D;		
    inline constexpr std::uint16_t f = KEY_F;	
    inline constexpr std::uint16_t g = KEY_G;	
    inline constexpr std::uint16_t h = KEY_H;	
    inline constexpr std::uint16_t j = KEY_J;		
    inline constexpr std::uint16_t k = KEY_K;	
    inline constexpr std::uint16_t l = KEY_L;	
    inline constexpr std::uint16_t semicol = KEY_SEMICOLON;
    inline constexpr std::uint16_t apostr = KEY_APOSTROPHE;
    inline constexpr std::uint16_t grave = KEY_GRAVE;
    inline constexpr std::uint16_t lshift = KEY_LEFTSHIFT;
    inline constexpr std::uint16_t backslash = KEY_BACKSLASH;
    inline constexpr std::uint16_t z = KEY_Z;
    inline constexpr std::uint16_t x = KEY_X;
    inline constexpr std::uint16_t c = KEY_C;
    inline constexpr std::uint16_t v = KEY_V;
    inline constexpr std::uint16_t b = KEY_B;
    inline constexpr std::uint16_t n = KEY_N;
    inline constexpr std::uint16_t m = KEY_M;
    inline constexpr std::uint16_t comma = KEY_COMMA;
    inline constexpr std::uint16_t dot = KEY_DOT;
    inline constexpr std::uint16_t slash = KEY_SLASH;
    inline constexpr std::uint16_t rslash = KEY_RIGHTSHIFT;
    inline constexpr std::uint16_t lalt = KEY_LEFTALT;
    inline constexpr std::uint16_t space = KEY_SPACE;
    inline constexpr std::uint16_t capslock = KEY_CAPSLOCK;
    inline constexpr std::uint16_t f1 = KEY_F1;
    inline constexpr std::uint16_t f2 = KEY_F2;
    inline constexpr std::uint16_t f3 = KEY_F3;
    inline constexpr std::uint16_t f4 = KEY_F4;
    inline constexpr std::uint16_t f5 = KEY_F5;
    inline constexpr std::uint16_t f6 = KEY_F6;
    inline constexpr std::uint16_t f7 = KEY_F7;
    inline constexpr std::uint16_t f8 = KEY_F8;
    inline constexpr std::uint16_t f9 = KEY_F9;
    inline constexpr std::uint16_t f10 = KEY_F10;
    inline constexpr std::uint16_t numlock = KEY_NUMLOCK;
    inline constexpr std::uint16_t scrollock = KEY_SCROLLLOCK;   
}

namespace key_ev_values
{
    inline constexpr std::uint8_t release = 0;
    inline constexpr std::uint8_t press = 1;
    inline constexpr std::uint8_t hold = 2;
}

namespace rel_codes {
    inline constexpr std::uint16_t x = REL_X;
    inline constexpr std::uint16_t y = REL_Y;
    inline constexpr std::uint16_t z = REL_Z;
    inline constexpr std::uint16_t wheel = REL_WHEEL;
}

namespace btn_codes {
    inline constexpr std::uint16_t b0 = BTN_0;
    inline constexpr std::uint16_t b1 = BTN_1;
    inline constexpr std::uint16_t b2 = BTN_2;
    inline constexpr std::uint16_t b3 = BTN_3;
    inline constexpr std::uint16_t b4 = BTN_4;
    inline constexpr std::uint16_t b5 = BTN_5;
    inline constexpr std::uint16_t b6 = BTN_6;
    inline constexpr std::uint16_t b7 = BTN_7;
    inline constexpr std::uint16_t b8 = BTN_8;
    inline constexpr std::uint16_t b9 = BTN_9;
    inline constexpr std::uint16_t left = BTN_LEFT;
    inline constexpr std::uint16_t right = BTN_RIGHT;
    inline constexpr std::uint16_t middle = BTN_MIDDLE;
    inline constexpr std::uint16_t side = BTN_SIDE;
}

namespace abs_codes {
    inline constexpr std::uint16_t x = ABS_X;
    inline constexpr std::uint16_t y = ABS_Y;
    inline constexpr std::uint16_t z = ABS_Z;
    inline constexpr std::uint16_t mt_slot = ABS_MT_SLOT;
    inline constexpr std::uint16_t mt_x = ABS_MT_POSITION_X;
    inline constexpr std::uint16_t mt_y = ABS_MT_POSITION_Y;
    inline constexpr std::uint16_t mt_track_id = ABS_MT_TRACKING_ID;
}

namespace def
{
    inline constexpr std::uint16_t vendor_id = 0x1234;
    inline constexpr std::uint16_t product_id = 0x4567;
    inline constexpr std::uint16_t verson = 0x1;
}