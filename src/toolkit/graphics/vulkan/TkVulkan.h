#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>
#include <toolkit/graphics/vulkan/constructors/TkVkConstructorIncludes.inl>

#ifdef D_DEBUG
#define _VK_GUARD(x) \
    if (x != VK_SUCCESS) { TK_ERROR("Vulkan Error: " #x " failed"); }
#else
#define _VK_GUARD(x) x
#endif

class cTkVulkan
{
  public:
    static inline VkFramebufferCreateInfo Initialise(VkRenderPass lRenderPass, VkExtent2D lExtent)
    {
        VkFramebufferCreateInfo lFramebufferCreateInfo = {};
        lFramebufferCreateInfo.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        lFramebufferCreateInfo.pNext                   = NULL;
        lFramebufferCreateInfo.renderPass              = lRenderPass;
        lFramebufferCreateInfo.attachmentCount         = 1;
        lFramebufferCreateInfo.width                   = lExtent.width;
        lFramebufferCreateInfo.height                  = lExtent.height;
        lFramebufferCreateInfo.layers                  = 1;

        return lFramebufferCreateInfo;
    }
};