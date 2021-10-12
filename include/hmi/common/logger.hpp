#pragma once

#include <fmt/color.h>
#include <fmt/core.h>

namespace logger
{
    constexpr const char* g_info    = "[info]";
    constexpr const char* g_warning = "[warning]";
    constexpr const char* g_error   = "[error]";

    template<typename Message, typename... Args>
    inline void log(fmt::color color, const char* level, Message&& msg, Args&&... args)
    {
        auto log = fmt::format("{}: {}\n", level, std::forward<Message>(msg));
        fmt::print(fg(color), log, std::forward<Args>(args)...);
    }
};  // namespace logger

template<typename Message, typename... Args>
inline void log_i(Message msg, Args&&... args)
{
    if constexpr (LOGGING)
    {
        logger::log(fmt::color::medium_sea_green, logger::g_info, std::forward<Message>(msg),
                    std::forward<Args>(args)...);
    }
}

template<typename Message, typename... Args>
inline void log_w(Message msg, Args&&... args)
{
    if constexpr (LOGGING)
    {
        logger::log(fmt::color::orange, logger::g_warning, std::forward<Message>(msg),
                    std::forward<Args>(args)...);
    }
}

template<typename Message, typename... Args>
inline void log_e(Message msg, Args&&... args)
{
    if constexpr (LOGGING)
    {
        logger::log(fmt::color::red, logger::g_error, std::forward<Message>(msg),
                    std::forward<Args>(args)...);
    }
}

template<typename T>
inline const void* format_ptr(const T* p)
{
    return fmt::ptr(p);
}