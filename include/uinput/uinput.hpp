#include "uinput_base.hpp"
#include "uinput_key_feature.hpp"
#include "uinput_mouse_feature.hpp"

namespace ui
{
    template<typename... Features>
    struct uinput
      : uinput_base
      , Features::template type<uinput<Features...>>...
    {
        uinput(std::string_view name,
               const std::uint16_t vendor_id,
               const std::uint16_t product_id,
               const std::uint16_t version)
        {
            uinput_base::set_info(name, vendor_id, product_id, version);
            if (!uinput_base::create_device())
                throw std::runtime_error{ "Failed to create uinput device." };
        }
    };
}
