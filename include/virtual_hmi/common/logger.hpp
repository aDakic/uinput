#pragma once

#include <fmt/color.h>
#include <fmt/core.h>

namespace logger
{
    constexpr const char* g_info    = "[info]";
    constexpr const char* g_warning = "[warning]";
    constexpr const char* g_error   = "[error]";

    template<typename Tag, typename Message, typename... Args>
    inline void log(fmt::color color, const char* level, Tag&& tag, Message&& msg, Args&&... args)
    {
        auto log = fmt::format("{} [{}]: {}", level, std::forward<Tag>(tag), std::forward<Message>(msg));
        fmt::print(fg(color), log, std::forward<Args>(args)...);
    }
};  // namespace logger

template<typename Tag, typename Message, typename... Args>
inline void log_info(Tag tag, Message msg, Args&&... args)
{
    if constexpr (LOGGING)
    {
        logger::log(fmt::color::medium_sea_green, logger::g_info, std::forward<Tag>(tag), std::forward<Message>(msg),
                    std::forward<Args>(args)...);
    }
    else
    {
        // NO LOGGING
    }
}

template<typename Tag, typename Message, typename... Args>
inline void log_warning(Tag tag, Message msg, Args&&... args)
{
    if constexpr (LOGGING)
    {
        logger::log(fmt::color::orange, logger::g_warning, std::forward<Tag>(tag), std::forward<Message>(msg),
                    std::forward<Args>(args)...);
    }
    else
    {
        // NO LOGGING
    }
}

template<typename Tag, typename Message, typename... Args>
inline void log_error(Tag tag, Message msg, Args&&... args)
{
    if constexpr (LOGGING)
    {
        logger::log(fmt::color::red, logger::g_error, std::forward<Tag>(tag), std::forward<Message>(msg),
                    std::forward<Args>(args)...);
    }
    else
    {
        // NO LOGGING
    }
}

template<typename T>
inline const void* format_ptr(const T* p)
{
    return fmt::ptr(p);
}