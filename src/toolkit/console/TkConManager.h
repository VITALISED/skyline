#pragma once

#include <toolkit/console/TkConCommand.h>
#include <toolkit/console/TkConVar.h>
#include <toolkit/containers/TkVector.h>

class cTkConManager : public cTkSingleton<cTkConManager>
{
  public:
    cTkConManager();
    ~cTkConManager();

    template <typename T>
    cTkConVar<T> *FindCVar(cTkString lsName)
    {
        for (cTkConObject *lpObj : this->mvCvarList)
        {
            if (lpObj->GetType() == ETkConObjectType_ConVar && lpObj->GetName() == lsName)
            {
                return dynamic_cast<cTkConVar<T> *>(lpObj);
            }
        }

        return TK_NULL;
    }

  private:
    template <typename T>
    void AddCVar(cTkConVar<T> *lpObj)
    {
        TK_ASSERT(lpObj != TK_NULL && lpObj->GetObjectType() == ETkConObjectType_ConVar);

        this->mvCvarList.PushBack(lpObj);
    }

    cTkVector<cTkConObject *> mvCvarList;

    template <TkFundamental T>
    friend class cTkConVar;
};