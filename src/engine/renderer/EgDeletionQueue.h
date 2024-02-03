#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>

class cEgDeletionQueue
{
  public:
    void PushFunction(TkSTD::Function<void()> lFunction) { mDeletors.push_back(lFunction); }
    void Flush()
    {
        for (auto it = mDeletors.rbegin(); it != mDeletors.rend(); ++it) (*it)();
    }

  private:
    TkSTD::Deque<TkSTD::Function<void()>> mDeletors;
};