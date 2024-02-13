#pragma once

#include <toolkit/core/TkID.h>
#include <toolkit/core/TkSTD.h>

#include <unordered_map>

template <typename T>
class cTkIDMap
{
  public:
    void Add(cTkID liID, T lpObject) { mpaMap[liID] = lpObject; }
    T Get(cTkID liID) { return mpaMap[liID]; }
    void Remove(cTkID liID) { mpaMap.erase(liID); }

  private:
    TkSTD::UnorderedMap<cTkID, T, cTkID::Hash> mpaMap;
};