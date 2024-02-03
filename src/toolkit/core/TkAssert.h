#pragma once

#include <spdlog/spdlog.h>
#include <toolkit/core/TkMacros.h>
#include <toolkit/core/TkSTD.h>

#define TK_LOG_BASE(message)               \
    TkSTD::String("[" __FILE__ "#")        \
        .append(TkSTD::ToString(__LINE__)) \
        .append("]\n")                     \
        .append("(" __FUNCTION__ ") ")     \
        .append(TkSTD::String(message))
#define TK_LOG_ASSERT(condition, ...)                    \
    TkSTD::String("[" __FILE__ "#")                      \
        .append(TkSTD::ToString(__LINE__))               \
        .append("]\n")                                   \
        .append("(" __FUNCTION__ ") Assert Failed: ")    \
        .append(TkSTD::String(__VA_ARGS__).append("\n")) \
        .append("(" #condition ")")

#ifdef D_DEBUG
#define TK_TRACE(message) cTkAssert::Trace(TK_LOG_BASE(message))
#define TK_DEBUG(message) cTkAssert::Debug(TK_LOG_BASE(message))
#define TK_INFO(message)  cTkAssert::Info(TK_LOG_BASE(message))
#define TK_WARN(message)  cTkAssert::Warn(TK_LOG_BASE(message))
#define TK_ERROR(message) cTkAssert::Error(TK_LOG_BASE(message))
#define TK_ASSERT(condition, ...)                                \
    if (!(condition))                                            \
    {                                                            \
        cTkAssert::Error(TK_LOG_ASSERT(condition, __VA_ARGS__)); \
        if (!IsDebuggerPresent()) exit(1);                       \
    }
#else // !D_DEBUG
#define TK_TRACE(message)
#define TK_DEBUG(message)
#define TK_INFO(message)
#define TK_WARN(message)
#define TK_ERROR(message) cTkAssert::Error(TK_LOG_BASE(message))
#define TK_ASSERT(condition, ...)
#endif // D_DEBUG

class cTkAssert
{
  public:
    static void Message(spdlog::level::level_enum leLevel, TkSTD::String &lsMessage);

    static void Trace(TkSTD::String &lsMessage) { cTkAssert::Message(spdlog::level::trace, lsMessage); }

    static void Debug(TkSTD::String &lsMessage) { cTkAssert::Message(spdlog::level::debug, lsMessage); }

    static void Info(TkSTD::String &lsMessage) { cTkAssert::Message(spdlog::level::info, lsMessage); }

    static void Warn(TkSTD::String &lsMessage) { cTkAssert::Message(spdlog::level::warn, lsMessage); }

    static void Error(TkSTD::String &lsMessage)
    {
        cTkAssert::Message(spdlog::level::err, lsMessage);
        if (IsDebuggerPresent()) __debugbreak();
    }
};