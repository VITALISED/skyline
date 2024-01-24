#pragma once

#include <toolkit/core/TkCore.h>

class cTkClock
{
  public:
    inline cTkClock() { this->Construct(); }

    void Construct();
    void Update();

    inline void SyncAccumulatorUpdate()
    {
        this->mfAccumulator -= cTkClock::kfFixedTimeStep;
        this->mfTime += cTkClock::kfFixedTimeStep;
    }

    inline long double Now()
    {
        TkSTD::Chrono::time_point lTime                          = TkSTD::Chrono::high_resolution_clock::now();
        TkSTD::Chrono::high_resolution_clock::duration lDuration = lTime.time_since_epoch();
        return TkSTD::Chrono::duration<long double>(lDuration).count();
    }

    inline bool IsAccumulatorGreaterThanDT() { return this->mfAccumulator >= kfFixedTimeStep; }

    static const long double kfFixedTimeStep;

    long double mfCurrentTime;
    long double mfAccumulator;
    long double mfTime;
};