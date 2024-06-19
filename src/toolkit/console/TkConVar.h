#pragma once

#include <toolkit/console/TkConObject.h>

template <TkFundamental T>
class cTkConVar : public cTkConObject
{
  public:
    cTkConVar()          = delete;
    virtual ~cTkConVar() = default;

    explicit cTkConVar(cTkString lsName, cTkString lsDescription, T lDefaultValue, eTkConFlags lxFlags);

    virtual void PrintInfo() final { cTkAssert::Info("ConVar "_s += this->GetName()); }
    virtual eTkConObjectType GetObjectType() final { return ETkConObjectType_ConVar; }

    T &GetValue() { return this->mValue; }
    void SetValue(T lValue) { this->mValue = lValue; }
    void SetValue(T &lValue) { this->mValue = lValue; }

  private:
    T mValue;
};