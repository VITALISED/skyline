#pragma once

#include <toolkit/engine/TkEngineSettings.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>
#include <toolkit/system/TkSystem.h>

class cEgRenderer
{
  public:
    inline cEgRenderer(cTkEngineSettings &lSettings) { this->Construct(lSettings); }

    void Construct(cTkEngineSettings &lSettings);
    void Destruct();

    VkInstance mVkInstance;
    VkSurfaceKHR mSurfaceKHR;
    VkDebugUtilsMessengerEXT mDebugMessenger;
    VkPhysicalDevice mPhysicalDevice;
    VkDevice mDevice;
};