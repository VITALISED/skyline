#pragma once

#include <toolkit/core/TkCore.h>

class cTkEngineSettings
{
  public:
    inline cTkEngineSettings(
        TkSTD::String &lsApplicationName, uint32_t luiApplicationVersion, TkSTD::String &lsEngineName,
        uint32_t luiEngineVersion)
        : msApplicationName(lsApplicationName), muiApplicationVersion(luiApplicationVersion),
          msEngineName(lsEngineName), muiEngineVersion(luiEngineVersion)
    {}

    TkSTD::String &msApplicationName;
    TkSTD::String &msEngineName;
    uint32_t muiEngineVersion;
    uint32_t muiApplicationVersion;
};