#pragma once

#include <game/application/GcApplication.h>

enum eProcessExit
{
    eProcessExit_Success = 0,
    eProcessExit_Failure = 1,
};

class cGcMain
{
  public:
    static int Main();
};
