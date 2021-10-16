#pragma once

namespace utils
{
    template<typename T, template<typename> class crtpType>
    struct crtp
    {
        T& get() { return static_cast<T&>(*this); }
        T const& get() const { return static_cast<T const&>(*this); }

    private:
        crtp() { }
        friend crtpType<T>;
    };

    template<typename T, template<typename, std::uint16_t...> class crtp_type>
    struct crtp_with_params
    {
        T& get() { return static_cast<T&>(*this); }
        const T& get() const { return static_cast<const T&>(*this); }
    };

}
