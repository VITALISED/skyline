#pragma once

#include <toolkit/graphics/vulkan/constructors/TkVulkanConstructors.h>

template <>
class cTkVkConstructor<VkFenceCreateInfo>
{
  public:
    static inline VkFenceCreateInfo Initialise(VkFenceCreateFlagBits lxFlags)
    {
        VkFenceCreateInfo lCreateInfo = {};
        lCreateInfo.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        lCreateInfo.pNext             = NULL;
        lCreateInfo.flags             = lxFlags;
        return lCreateInfo;
    }
};

template <>
class cTkVkConstructor<VkSemaphoreCreateInfo>
{
  public:
    static inline VkSemaphoreCreateInfo Initialise(VkSemaphoreCreateFlags lxFlags)
    {
        VkSemaphoreCreateInfo lSemaphoreCreateInfo = {};
        lSemaphoreCreateInfo.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        lSemaphoreCreateInfo.pNext                 = NULL;
        lSemaphoreCreateInfo.flags                 = lxFlags;

        return lSemaphoreCreateInfo;
    }
};

template <>
class cTkVkConstructor<VkSemaphoreSubmitInfo>
{
  public:
    static inline VkSemaphoreSubmitInfo Initialise(VkSemaphore lSemaphore, VkPipelineStageFlags2 lxStageMask)
    {
        VkSemaphoreSubmitInfo lSemaphoreSubmitInfo = {};
        lSemaphoreSubmitInfo.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
        lSemaphoreSubmitInfo.pNext                 = NULL;
        lSemaphoreSubmitInfo.semaphore             = lSemaphore;
        lSemaphoreSubmitInfo.stageMask             = lxStageMask;
        lSemaphoreSubmitInfo.deviceIndex           = 0;
        lSemaphoreSubmitInfo.value                 = 1;
        return lSemaphoreSubmitInfo;
    }
};