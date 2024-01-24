#include <game/application/GcApplication.h>

cGcApplication *gApplication = NULL;

void cGcApplication::Construct()
{
    AllocConsole();
    this->mbQuit  = false;
    this->mpClock = new cTkClock();
}

void cGcApplication::Update() {}