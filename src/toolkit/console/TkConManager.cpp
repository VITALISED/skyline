#include <toolkit/console/TkConManager.h>

cTkVector<cTkConObject *> *gConVarList;

cTkConManager::cTkConManager()
{
    gConVarList = new cTkVector<cTkConObject *>();
}

cTkConManager::~cTkConManager()
{
    for (cTkConObject *lConObj : *gConVarList) { delete lConObj; }
}