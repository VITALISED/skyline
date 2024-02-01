#include <game/application/GcApplication.h>

void cGcApplication::Construct()
{
    this->mbQuit  = false;
    this->mpClock = new cTkClock();
}

void cGcApplication::Destruct()
{
    delete this->mpClock;
}

void cGcApplication::Update(float lfTimestep)
{
    // TK_INFO(TkSTD::Format("Update call {}", lfTimestep));
}