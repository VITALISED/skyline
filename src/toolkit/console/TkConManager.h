#pragma once

#include <toolkit/console/TkConCommand.h>
#include <toolkit/console/TkConVar.h>

class cTkConManager : public cTkSingleton<cTkConManager>
{
  public:
    cTkConManager();
    ~cTkConManager();

    template <typename T>
    cTkConVar<T> *FindCVar(cTkString lsName)
    {
        for (cTkConObject *lpObj : *g_ConVarList)
        {
            if (lpObj->GetType() == eTkConObjectType::ETkConObjectType_ConVar && lpObj->GetName() == lsName)
            {
                TK_ASSERT(lpObj->GetInnerTypeID() == typeid(T));
                return dynamic_cast<cTkConVar<T> *>(lpObj);
            }
        }

        return TK_NULL;
    }

    template <typename T>
    void AddCVar(cTkConVar<T> *lpObj)
    {
        TK_ASSERT(lpObj != TK_NULL && lpObj->GetType() == eTkConObjectType::ETkConObjectType_ConVar);

        g_ConVarList->insert(lpObj);
    }
};