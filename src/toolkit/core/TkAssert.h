#pragma once

#include <spdlog/spdlog.h>
#include <toolkit/core/TkMacros.h>
#include <toolkit/core/TkSTD.h>

#define TK_LOG_BASE(message) TkSTD::String("[" __FILE__ ":").append(TkSTD::ToString(__LINE__)).append("] " message)

#ifdef D_DEBUG
#define TK_TRACE(message) cTkAssert::Trace(TK_LOG_BASE(message))
#define TK_DEBUG(message) cTkAssert::Debug(TK_LOG_BASE(message))
#define TK_INFO(message)  cTkAssert::Info(TK_LOG_BASE(message))
#define TK_WARN(message)  cTkAssert::Warn(TK_LOG_BASE(message))
#define TK_ERROR(message) cTkAssert::Error(TK_LOG_BASE(message))
#else // !D_DEBUG
#define TK_TRACE(message)
#define TK_DEBUG(message)
#define TK_INFO(message)
#define TK_WARN(message)
#define TK_ERROR(message) cTkAssert::Error(TK_LOG_BASE(message))
#endif // D_DEBUG

enum eLogLevel
{
    eLogLevel_Trace,
    eLogLevel_Debug,
    ELogLevel_Info,
    eLogLevel_Warn,
    eLogLevel_Error
};

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