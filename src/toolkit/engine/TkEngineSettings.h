#pragma once

#include <toolkit/core/TkCore.h>

class cTkEngineSettings
{
  public:
    cTkEngineSettings(
        cTkString &lsApplicationName, u32 luiApplicationVersion, cTkString &lsEngineName, u32 luiEngineVersion)
        : msApplicationName(lsApplicationName), muiApplicationVersion(luiApplicationVersion),
          msEngineName(lsEngineName), muiEngineVersion(luiEngineVersion)
    {}

    cTkString &msApplicationName;
    cTkString &msEngineName;
    u32 muiEngineVersion;
    u32 muiApplicationVersion;
};