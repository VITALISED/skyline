#pragma once

#include <toolkit/console/TkConObject.h>

extern cTkVector<cTkConObject *> *g_ConVarList;

template <TkFundamental T>
class cTkConVar : public cTkConObject
{
  public:
    cTkConVar()          = delete;
    virtual ~cTkConVar() = default;

    explicit cTkConVar(cTkString lsName, cTkString lsDescription, eTkConFlags lxFlags)
        : cTkConObject(lsName, lsDescription, lxFlags), mValue()
    {
        g_ConVarList->push_back(this);
    }

    virtual cTkString &PrintInfo() final { cTkAssert::Info("ConVar "_sz + this->GetName()); }
    virtual eTkConObjectType GetType() final { return eTkConObjectType::ETkConObjectType_ConVar; }
    virtual const char *GetInnerTypeID() final { return typeid(T); }

    T &GetValue() { return this->mValue; }
    void SetValue(T lValue) { this->mValue = lValue; }
    void SetValue(T &lValue) { this->mValue = lValue; }

  private:
    T mValue;
};