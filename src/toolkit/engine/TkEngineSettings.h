#pragma once

#include <toolkit/core/TkCore.h>

class cTkEngineSettings
{
  public:
    inline cTkEngineSettings(
        cTkString &lsApplicationName, uint32_t luiApplicationVersion, cTkString &lsEngineName,
        uint32_t luiEngineVersion)
        : msApplicationName(lsApplicationName), muiApplicationVersion(luiApplicationVersion),
          msEngineName(lsEngineName), muiEngineVersion(luiEngineVersion)
    {}

    cTkString &msApplicationName;
    cTkString &msEngineName;
    uint32_t muiEngineVersion;
    uint32_t muiApplicationVersion;
};