#include <toolkit/console/TkConManager.h>

cTkVector<cTkConObject *> *g_ConVarList;

cTkConManager::cTkConManager()
{
    g_ConVarList = new cTkVector<cTkConObject *>();
}

cTkConManager::~cTkConManager()
{
    for (cTkConObject *lConObj : *g_ConVarList) { delete lConObj; }
}