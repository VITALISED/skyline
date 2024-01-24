#pragma once

#include <spdlog/spdlog.h>
#include <toolkit/core/TkMacros.h>

#ifdef D_DEBUG
#define TK_TRACE(message)             cTkAssert::Trace(message)
#define TK_DEBUG(message)             cTkAssert::Debug(message)
#define TK_INFO(message)              cTkAssert::Info(message)
#define TK_WARN(message, expression)  cTkAssert::Warn(message)
#define TK_ERROR(message, expression) cTkAssert::Error(message)
#else // !D_DEBUG
#define TK_TRACE(message)
#define TK_DEBUG(message)
#define TK_INFO(message)
#define TK_WARN(message)
#define TK_ERROR(message) cTkAssert::Error(message)
#endif // D_DEBUG

class cTkAssert
{
  public:
    static void Construct();

    static void Trace(const char *lpacMessage) { spdlog::trace(lpacMessage); }
    static void Debug(const char *lpacMessage) { spdlog::debug(lpacMessage); }
    static void Info(const char *lpacMessage) { spdlog::info(lpacMessage); }
    static void Warn(const char *lpacMessage, const char *lpacExpression)
    {
        spdlog::info("{}\n({})", lpacMessage, lpacExpression);
    }
    static void Error(const char *lpacMessage, const char *lpacExpression)
    {
        spdlog::info("{}\n({})", lpacMessage, lpacExpression);
        if (IsDebuggerPresent()) __debugbreak();
    }
};