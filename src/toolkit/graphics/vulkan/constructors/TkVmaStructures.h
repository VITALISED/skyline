#pragma once

#include <toolkit/graphics/vulkan/constructors/TkVulkanConstructors.h>
#include <toolkit/graphics/vulkan/vk_mem_alloc.h>

template <>
class cTkVkConstructor<VmaAllocatorCreateInfo>
{
  public:
    static inline VmaAllocatorCreateInfo Initialise(
        VkPhysicalDevice lChosenGPU, VkDevice lDevice, VkInstance lInstance, VmaAllocatorCreateFlags lxFlags)
    {
        VmaAllocatorCreateInfo lAllocatorInfo = {};
        lAllocatorInfo.physicalDevice         = lChosenGPU;
        lAllocatorInfo.device                 = lDevice;
        lAllocatorInfo.instance               = lInstance;
        lAllocatorInfo.flags                  = lxFlags;
        return lAllocatorInfo;
    }
};

template <>
class cTkVkConstructor<VmaAllocationCreateInfo>
{
  public:
    static inline VmaAllocationCreateInfo Initialise(VmaMemoryUsage lxUsage, VkMemoryPropertyFlags lxRequiredFlags)
    {
        VmaAllocationCreateInfo lAllocationInfo = {};
        lAllocationInfo.usage                   = lxUsage;
        lAllocationInfo.requiredFlags           = lxRequiredFlags;
        return lAllocationInfo;
    }
};
