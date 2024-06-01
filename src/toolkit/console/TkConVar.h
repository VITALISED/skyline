#pragma once

#include <toolkit/console/TkConObject.h>

template <typename T>
class cTkConVar : public cTkConObject
{
  public:
    cTkConVar(cTkString lsName, cTkString lsDescription, eTkConFlags lxFlags);
    virtual ~cTkConVar() = default;

    virtual cTkString &GetName() final;
    virtual cTkString &PrintInfo() final;

    T &GetValue() { return this->mValue; }
    void SetValue(T lValue) { this->mValue = lValue; }
    void SetValue(T &lValue) { this->mValue = lValue; }

  private:
    T mValue;
};