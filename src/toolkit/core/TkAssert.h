#pragma once

#include <spdlog/spdlog.h>
#include <toolkit/core/TkMacros.h>
#include <toolkit/core/TkString.h>

#define TK_LOG_BASE(message)            \
    cTkString("[" __FILE__ "#")         \
        .Append(TK_STRINGIFY(__LINE__)) \
        .Append("]\n")                  \
        .Append("(" __FUNCTION__ ") ")  \
        .Append(message)
#define TK_LOG_ASSERT(condition, ...)                       \
    cTkString("[" __FILE__ "#")                             \
        .Append(cTkString::ToString(__LINE__))              \
        .Append("]\n")                                      \
        .Append("(" __FUNCTION__ ") Assert Failed: ")       \
        .Append(cTkAssert::Parse(__VA_ARGS__).Append("\n")) \
        .Append("(" #condition ")")

#ifdef D_DEBUG
#define TK_TRACE(...) cTkAssert::Trace(TK_LOG_BASE(cTkAssert::Parse(__VA_ARGS__)))
#define TK_DEBUG(...) cTkAssert::Debug(TK_LOG_BASE(cTkAssert::Parse(__VA_ARGS__)))
#define TK_INFO(...)  cTkAssert::Info(TK_LOG_BASE(cTkAssert::Parse(__VA_ARGS__)))
#define TK_WARN(...)  cTkAssert::Warn(TK_LOG_BASE(cTkAssert::Parse(__VA_ARGS__)))
#define TK_ERROR(...) cTkAssert::Error(TK_LOG_BASE(cTkAssert::Parse(__VA_ARGS__)))
#define TK_ASSERT(condition, ...)                                \
    if (!(condition))                                            \
    {                                                            \
        cTkAssert::Error(TK_LOG_ASSERT(condition, __VA_ARGS__)); \
        if (!IsDebuggerPresent()) exit(1);                       \
    }
#else // !D_DEBUG
#define TK_TRACE(...)
#define TK_DEBUG(...)
#define TK_INFO(...)
#define TK_WARN(...)
#define TK_ERROR(...) cTkAssert::Error(TK_LOG_BASE(cTkString::Format(__VA_ARGS__)))
#define TK_ASSERT(condition, ...)
#endif // D_DEBUG

class cTkAssert
{
  public:
    static void Setup();

    template <typename... Args>
    static cTkString Parse(const char *lpacFirst, Args... lArgs)
    {
        cTkString lsFormatString = cTkString(lpacFirst);
        return cTkString::Format(lsFormatString, lArgs...);
    }

    static cTkString Parse(const char *lpacFirst) { return cTkString(lpacFirst); }

    static void Message(spdlog::level::level_enum leLevel, cTkString &lsMessage) { spdlog::log(leLevel, lsMessage); }

    static void Trace(cTkString &lsMessage) { cTkAssert::Message(spdlog::level::trace, lsMessage); }
    static void Debug(cTkString &lsMessage) { cTkAssert::Message(spdlog::level::debug, lsMessage); }
    static void Info(cTkString &lsMessage) { cTkAssert::Message(spdlog::level::info, lsMessage); }
    static void Warn(cTkString &lsMessage) { cTkAssert::Message(spdlog::level::warn, lsMessage); }
    static void Error(cTkString &lsMessage)
    {
        cTkAssert::Message(spdlog::level::err, lsMessage);
        if (IsDebuggerPresent()) __debugbreak();
    }
};