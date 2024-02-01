#pragma once

#include <toolkit/graphics/vulkan/constructors/TkVulkanConstructors.h>

template <>
class cTkVkConstructor<VkCommandBufferBeginInfo>
{
  public:
    static inline VkCommandBufferBeginInfo Initialise(VkCommandBufferUsageFlags lxFlags)
    {
        VkCommandBufferBeginInfo lCmdBufferBeginInfo = {};
        lCmdBufferBeginInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        lCmdBufferBeginInfo.pNext                    = NULL;
        lCmdBufferBeginInfo.flags                    = lxFlags;
        lCmdBufferBeginInfo.pInheritanceInfo         = NULL;
        return lCmdBufferBeginInfo;
    }
};

template <>
class cTkVkConstructor<VkCommandPoolCreateInfo>
{
  public:
    static inline VkCommandPoolCreateInfo Initialise(uint32_t luiFamilyIndex, VkCommandPoolCreateFlags lxFlags)
    {
        VkCommandPoolCreateInfo lCommandPoolCreateInfo = {};
        lCommandPoolCreateInfo.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        lCommandPoolCreateInfo.pNext                   = NULL;
        lCommandPoolCreateInfo.flags                   = lxFlags;
        lCommandPoolCreateInfo.queueFamilyIndex        = luiFamilyIndex;

        return lCommandPoolCreateInfo;
    }
};

template <>
class cTkVkConstructor<VkCommandBufferSubmitInfo>
{
  public:
    static inline VkCommandBufferSubmitInfo Initialise(VkCommandBuffer lCommandBuffer)
    {
        VkCommandBufferSubmitInfo lCommandBufferSubmitInfo = {};
        lCommandBufferSubmitInfo.sType                     = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
        lCommandBufferSubmitInfo.pNext                     = NULL;
        lCommandBufferSubmitInfo.commandBuffer             = lCommandBuffer;
        lCommandBufferSubmitInfo.deviceMask                = 0;
        return lCommandBufferSubmitInfo;
    }
};

template <>
class cTkVkConstructor<VkCommandBufferAllocateInfo>
{
  public:
    static inline VkCommandBufferAllocateInfo Initialise(
        VkCommandPool lCommandPool, uint32_t luiCommandBufferCount, VkCommandBufferLevel lxLevel)
    {
        VkCommandBufferAllocateInfo lCmdAllocInfo = {};
        lCmdAllocInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        lCmdAllocInfo.pNext                       = NULL;
        lCmdAllocInfo.commandPool                 = lCommandPool;
        lCmdAllocInfo.commandBufferCount          = luiCommandBufferCount;
        lCmdAllocInfo.level                       = lxLevel;
        // VK_COMMAND_BUFFER_LEVEL_PRIMARY
        return lCmdAllocInfo;
    }
};