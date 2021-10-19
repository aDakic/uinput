#pragma once

namespace utils
{
    template<typename T>
    inline constexpr auto enum_to_underlying(const T& t)
    {
        return static_cast<std::underlying_type_t<T>>(t);
    }
}  // namespace utils