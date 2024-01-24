#pragma once

class cGcApplication;

extern cGcApplication *gApplication;

class cGcApplication
{
  public:
    inline cGcApplication() { Construct(); }
    void Construct();
    void Prepare();
    void Update();
    void Destruct();

    bool mbQuit;
    cTkClock *mpClock;
};