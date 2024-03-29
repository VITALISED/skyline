#pragma once

#include <engine/EgMain.h>
#include <game/application/GcApplication.h>

enum eProcessExit
{
    eProcessExit_Success = 0,
    eProcessExit_Failure = 1,
};

class cGcMain
{
  public:
    static void Construct();
    static void Destruct();
    static int Main();
};
