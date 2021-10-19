#include "feature/uinput_key_feature.hpp"
#include "feature/uinput_mouse_feature.hpp"
#include "feature/uinput_mtouch_feature.hpp"
#include "uinput_driver.hpp"

namespace ui
{
    template<typename... Features>
    struct uinput : uinput_driver, Features::template type<uinput<Features...>>...
    {
        uinput(std::string_view name, const std::uint16_t vendor_id, const std::uint16_t product_id,
               const std::uint16_t version)
        {
            set_info(name, vendor_id, product_id, version);
            if (!create_device())
                throw std::runtime_error{ "Failed to create uinput device." };
        }
    };
}  // namespace ui
