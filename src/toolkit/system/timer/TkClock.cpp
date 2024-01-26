#include <toolkit/system/timer/TkClock.h>

const long double cTkClock::kfFixedTimeStep = 1.0 / 60.0;

void cTkClock::Construct()
{
    this->mfCurrentTime = this->Now();
    this->mfAccumulator = 0.0;
}

void cTkClock::Update()
{
    long double lNewTime   = this->Now();
    long double lFrameTime = lNewTime - this->mfCurrentTime;

    this->mfCurrentTime = lNewTime;
    this->mfAccumulator += lFrameTime;
}