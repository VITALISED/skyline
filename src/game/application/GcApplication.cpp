#include <game/application/GcApplication.h>

void cGcApplication::Construct()
{

    this->mbQuit  = false;
    this->mpClock = new cTkClock();
}

void cGcApplication::Destruct()
{
    delete this->mpClock;
    delete this;
}

void cGcApplication::Update() {}