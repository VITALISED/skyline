#pragma once

#include <toolkit/core/TkCore.h>

class cGcApplication : public cTkSingleton<cGcApplication>
{
  public:
    void Construct();
    void Destruct();
    void Update(float lfTimestep);

    bool mbQuit;
    cTkClock *mpClock;
};