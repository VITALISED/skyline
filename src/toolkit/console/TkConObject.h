#pragma once

#include <toolkit/core/TkCore.h>

#include <string>

enum eTkConFlags
{
    ETkConFlags_None,
};

class cTkConObject
{
  public:
    cTkConObject()          = default;
    virtual ~cTkConObject() = default;

    virtual cTkString &GetName() { return this->msName; }
    virtual cTkString &PrintInfo() { cTkAssert::Info("ConVar: "_sz + msName + "Description: "_sz + msDescription); };

  private:
    cTkString msName;
    cTkString msDescription;
    eTkConFlags mxFlags;
};