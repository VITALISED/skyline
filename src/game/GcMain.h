#pragma once

#include <engine/EgMain.h>
#include <game/application/GcApplication.h>

enum eProcessExit
{
    EProcessExit_Success = 0,
    EProcessExit_Failure = 1,
};

class cGcMain
{
  public:
    static void Construct();
    static void Destruct();
    static eProcessExit Main();
};
