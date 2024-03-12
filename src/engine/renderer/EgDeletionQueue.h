#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>

class cEgDeletionQueue
{
  public:
    void PushFunction(std::function<void()> lFunction) { mDeletors.push_back(lFunction); }
    void Flush()
    {
        for (auto it = mDeletors.rbegin(); it != mDeletors.rend(); ++it) (*it)();
    }

  private:
    std::deque<std::function<void()>> mDeletors;
};