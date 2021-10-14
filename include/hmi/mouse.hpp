#include "hmi/system/uinput.hpp"

namespace hmi
{
    class mouse final
    {
    public:
        mouse();

        bool click_left() noexcept;
        bool click_right() noexcept;
        bool click_middle() noexcept;

        bool move(std::int32_t x, std::int32_t y) noexcept;

        bool scroll_up() noexcept;
        bool scroll_down() noexcept;

    private:
        ui::uinput m_driver;
    };

}  // namespace hmi