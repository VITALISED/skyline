#pragma once

#include <toolkit/core/TkCore.h>

#include <string>

enum class eTkConFlags : u32
{
    ETkConFlags_None      = (1 << 0),
    ETkConFlags_Developer = (1 << 1),
    ETkConFlags_ReadOnly  = (1 << 2), // only for cvars
};

enum class eTkConObjectType : u8
{
    ETkConObjectType_None,
    ETkConObjectType_ConVar,
    ETkConObjectType_ConCommand,
};

class cTkConObject
{
  public:
    cTkConObject() = delete;
    explicit cTkConObject(cTkString lsName, cTkString lsDescription, eTkConFlags lxFlags)
        : msName(lsName), msDescription(lsDescription), mxFlags(lxFlags)
    {}
    virtual ~cTkConObject() = default;

    virtual cTkString &PrintInfo()       = 0;
    virtual eTkConObjectType GetType()   = 0;
    virtual const char *GetInnerTypeID() = 0;

    cTkString &GetName() { return this->msName; }
    cTkString &GetDescription() { return this->msDescription; }

    bool HasFlag(eTkConFlags lxFlag)
    {
        return (static_cast<u32>(mxFlags) & static_cast<u32>(lxFlag)) == static_cast<u32>(lxFlag);
    }

    cTkString msName;
    cTkString msDescription;
    eTkConFlags mxFlags;
};