#include <toolkit/console/TkConManager.h>

cTkConManager::cTkConManager()
{
    this->mvCvarList = cTkVector<cTkConObject *>();
}

cTkConManager::~cTkConManager()
{
    for (cTkConObject *lConObj : this->mvCvarList) { delete lConObj; }
}