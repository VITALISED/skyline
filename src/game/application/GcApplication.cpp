#include <game/application/GcApplication.h>

void cGcApplication::Construct()
{
    AllocConsole();
    this->mbQuit  = false;
    this->mpClock = new cTkClock();
}

void cGcApplication::Destruct()
{
    delete this->mpClock;
    delete this;
    FreeConsole();
}

void cGcApplication::Update() {}