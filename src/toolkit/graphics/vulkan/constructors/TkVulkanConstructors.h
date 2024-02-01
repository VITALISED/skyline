#pragma once

#include <vulkan/vulkan.h>

template <typename T>
class cTkVkConstructor
{
  public:
    template <typename... Args>
    static inline T Initialise(Args... lArgs);
};

template <>
class cTkVkConstructor<VkExtent2D>
{
  public:
    static inline VkExtent2D Initialise(uint32_t luiWidth, uint32_t luiHeight)
    {
        VkExtent2D lExtent = {};
        lExtent.width      = luiWidth;
        lExtent.height     = luiHeight;

        return lExtent;
    }
};