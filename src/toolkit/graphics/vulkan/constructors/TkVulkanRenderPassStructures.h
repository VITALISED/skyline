#pragma once

#include <toolkit/graphics/vulkan/constructors/TkVulkanConstructors.h>

template <>
class cTkVkConstructor<VkSubpassDescription2>
{
  public:
    static inline VkSubpassDescription2 Initialise(
        const VkAttachmentReference2 *lColorAttachmentRef, uint32_t lColorAttachmentCount)
    {
        VkSubpassDescription2 lSubpassDesc = {};
        lSubpassDesc.sType                 = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
        lSubpassDesc.pipelineBindPoint     = VK_PIPELINE_BIND_POINT_GRAPHICS;
        lSubpassDesc.colorAttachmentCount  = lColorAttachmentCount;
        lSubpassDesc.pColorAttachments     = lColorAttachmentRef;

        return lSubpassDesc;
    }
};

template <>
class cTkVkConstructor<VkSubpassDependency2>
{
  public:
    static inline VkSubpassDependency2 Initialise()
    {
        VkSubpassDependency2 lSubpassDependency = {};
        lSubpassDependency.sType                = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
        lSubpassDependency.srcSubpass           = VK_SUBPASS_EXTERNAL;
        lSubpassDependency.dstSubpass           = 0;
        lSubpassDependency.srcStageMask         = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        lSubpassDependency.srcAccessMask        = 0;
        lSubpassDependency.dstStageMask         = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        lSubpassDependency.dstAccessMask        = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        return lSubpassDependency;
    }
};

template <>
class cTkVkConstructor<VkRenderPassCreateInfo2>
{
  public:
    static inline VkRenderPassCreateInfo2 Initialise(
        uint32_t lAttachmentCount, VkAttachmentDescription2 *lColorAttachment, uint32_t lSubpassCount,
        VkSubpassDescription2 *lSubpass, uint32_t lDependencyCount, VkSubpassDependency2 *lSubpassDependency)
    {
        VkRenderPassCreateInfo2 lRenderPassCreateInfo = {};
        lRenderPassCreateInfo.sType                   = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
        lRenderPassCreateInfo.attachmentCount         = lAttachmentCount;
        lRenderPassCreateInfo.pAttachments            = lColorAttachment;
        lRenderPassCreateInfo.subpassCount            = lSubpassCount;
        lRenderPassCreateInfo.pSubpasses              = lSubpass;
        lRenderPassCreateInfo.dependencyCount         = lDependencyCount;
        lRenderPassCreateInfo.pDependencies           = lSubpassDependency;

        return lRenderPassCreateInfo;
    }
};

template <>
class cTkVkConstructor<VkAttachmentDescription2>
{
  public:
    static inline VkAttachmentDescription2 Initialise(VkFormat lImageFormat)
    {
        VkAttachmentDescription2 lAttachmentDescription2 = {};

        lAttachmentDescription2.sType          = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
        lAttachmentDescription2.format         = lImageFormat;
        lAttachmentDescription2.samples        = VK_SAMPLE_COUNT_1_BIT;
        lAttachmentDescription2.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
        lAttachmentDescription2.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
        lAttachmentDescription2.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        lAttachmentDescription2.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        lAttachmentDescription2.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
        lAttachmentDescription2.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        return lAttachmentDescription2;
    }
};

template <>
class cTkVkConstructor<VkAttachmentReference2>
{
  public:
    static inline VkAttachmentReference2 Initialise(uint32_t luiAttachment, VkImageLayout leLayout)
    {

        VkAttachmentReference2 lColorAttachmentRef = {};
        lColorAttachmentRef.sType                  = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
        lColorAttachmentRef.attachment             = luiAttachment;
        lColorAttachmentRef.layout                 = leLayout;

        return lColorAttachmentRef;
    }
};

template <>
class cTkVkConstructor<VkRenderPassBeginInfo>
{
  public:
    static inline VkRenderPassBeginInfo Initialise(
        VkRenderPass lRenderPass, VkFramebuffer lFrameBuffer, VkOffset2D lOffset, VkExtent2D lExtent,
        uint32_t luiClearValueCount, const VkClearValue *lpClearValue)
    {
        VkRenderPassBeginInfo lRenderPassBeginInfo = {};
        lRenderPassBeginInfo.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        lRenderPassBeginInfo.pNext                 = NULL;
        lRenderPassBeginInfo.renderPass            = lRenderPass;
        lRenderPassBeginInfo.framebuffer           = lFrameBuffer;
        lRenderPassBeginInfo.renderArea.offset     = lOffset;
        lRenderPassBeginInfo.renderArea.extent     = lExtent;
        lRenderPassBeginInfo.clearValueCount       = luiClearValueCount;
        lRenderPassBeginInfo.pClearValues          = lpClearValue;

        return lRenderPassBeginInfo;
    }
};

template <>
class cTkVkConstructor<VkImageSubresourceRange>
{
  public:
    static inline VkImageSubresourceRange Initialise()
    {
        VkImageSubresourceRange lImageSubresourceRange = {};
        lImageSubresourceRange.aspectMask              = VK_IMAGE_ASPECT_COLOR_BIT;
        lImageSubresourceRange.baseMipLevel            = 0;
        lImageSubresourceRange.levelCount              = VK_REMAINING_MIP_LEVELS;
        lImageSubresourceRange.baseArrayLayer          = 0;
        lImageSubresourceRange.layerCount              = VK_REMAINING_ARRAY_LAYERS;

        return lImageSubresourceRange;
    }
};

template <>
class cTkVkConstructor<VkSubmitInfo2>
{
  public:
    static inline VkSubmitInfo2 Initialise(
        const VkSemaphoreSubmitInfo *lpWaitInfo, uint32_t luiWaitCount, const VkSemaphoreSubmitInfo *lpSignalInfo,
        uint32_t luiSignalCount, const VkCommandBufferSubmitInfo *lpCommandBufferInfo, uint32_t luiCommandBufferCount,
        VkSubmitFlags lxFlags)
    {
        VkSubmitInfo2 lSubmitInfo2            = {};
        lSubmitInfo2.sType                    = VK_STRUCTURE_TYPE_SUBMIT_INFO_2_KHR;
        lSubmitInfo2.pNext                    = NULL;
        lSubmitInfo2.waitSemaphoreInfoCount   = luiWaitCount;
        lSubmitInfo2.pWaitSemaphoreInfos      = lpWaitInfo;
        lSubmitInfo2.signalSemaphoreInfoCount = luiSignalCount;
        lSubmitInfo2.pSignalSemaphoreInfos    = lpSignalInfo;
        lSubmitInfo2.commandBufferInfoCount   = luiCommandBufferCount;
        lSubmitInfo2.pCommandBufferInfos      = lpCommandBufferInfo;
        lSubmitInfo2.flags                    = lxFlags;

        return lSubmitInfo2;
    }
};

template <>
class cTkVkConstructor<VkPresentInfoKHR>
{
  public:
    static inline VkPresentInfoKHR Initialise(
        const VkSwapchainKHR *lpSwapchain, uint32_t luiSwapchainCount, const VkSemaphore *lpWaitSemaphore,
        uint32_t luiWaitSemaphoreCount, uint32_t *lpuiImageIndex)
    {
        VkPresentInfoKHR lPresentInfo   = {};
        lPresentInfo.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        lPresentInfo.pNext              = NULL;
        lPresentInfo.pSwapchains        = lpSwapchain;
        lPresentInfo.swapchainCount     = luiSwapchainCount;
        lPresentInfo.pWaitSemaphores    = lpWaitSemaphore;
        lPresentInfo.waitSemaphoreCount = luiWaitSemaphoreCount;
        lPresentInfo.pImageIndices      = lpuiImageIndex;

        return lPresentInfo;
    }
};

template <>
class cTkVkConstructor<VkFramebufferCreateInfo>
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
