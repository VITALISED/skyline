#include <toolkit/core/TkAssert.h>

void cTkAssert::Message(spdlog::level::level_enum leLevel, TkSTD::String &lsMessage)
{
    spdlog::log(leLevel, lsMessage);
}