#pragma once

#include <toolkit/graphics/vulkan/constructors/TkVulkanConstructors.h>

template <>
class cTkVkConstructor<VkImageCreateInfo>
{
  public:
    static inline VkImageCreateInfo Initialise(VkFormat lFormat, VkImageUsageFlags lxUsageFlags, VkExtent3D lExtent)
    {
        VkImageCreateInfo lInfo = {};
        lInfo.sType             = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        lInfo.pNext             = NULL;

        lInfo.imageType = VK_IMAGE_TYPE_2D;

        lInfo.format = lFormat;
        lInfo.extent = lExtent;

        lInfo.mipLevels   = 1;
        lInfo.arrayLayers = 1;

        lInfo.samples = VK_SAMPLE_COUNT_1_BIT;

        lInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        lInfo.usage  = lxUsageFlags;

        return lInfo;
    }
};

template <>
class cTkVkConstructor<VkImageViewCreateInfo>
{
  public:
    static inline VkImageViewCreateInfo Initialise(VkFormat lFormat, VkImage lImage, VkImageAspectFlags lxAspectFlags)
    {
        VkImageViewCreateInfo lInfo = {};
        lInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        lInfo.pNext                 = nullptr;

        lInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
        lInfo.image                           = lImage;
        lInfo.format                          = lFormat;
        lInfo.subresourceRange.baseMipLevel   = 0;
        lInfo.subresourceRange.levelCount     = 1;
        lInfo.subresourceRange.baseArrayLayer = 0;
        lInfo.subresourceRange.layerCount     = 1;
        lInfo.subresourceRange.aspectMask     = lxAspectFlags;

        return lInfo;
    }
};