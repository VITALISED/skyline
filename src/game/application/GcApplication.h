#pragma once

#include <toolkit/core/TkCore.h>

class cGcApplication : public cTkSingleton<cGcApplication>
{
  public:
    void Construct();
    void Destruct();
    void Update();

    bool mbQuit;
    cTkClock *mpClock;
};