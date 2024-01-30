#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>

class cTkVulkan
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

    static inline VkAttachmentReference2 Initialise(uint32_t luiAttachment, VkImageLayout leLayout)
    {

        VkAttachmentReference2 lColorAttachmentRef = {};
        lColorAttachmentRef.sType                  = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
        lColorAttachmentRef.attachment             = luiAttachment;
        lColorAttachmentRef.layout                 = leLayout;

        return lColorAttachmentRef;
    }

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

    static inline VkCommandPoolCreateInfo Initialise(uint32_t luiFamilyIndex)
    {
        VkCommandPoolCreateInfo lCommandPoolCreateInfo = {};
        lCommandPoolCreateInfo.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        lCommandPoolCreateInfo.pNext                   = NULL;
        lCommandPoolCreateInfo.flags                   = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        lCommandPoolCreateInfo.queueFamilyIndex        = luiFamilyIndex;

        return lCommandPoolCreateInfo;
    }

    static inline VkCommandBufferAllocateInfo Initialise(VkCommandPool lCommandPool)
    {
        VkCommandBufferAllocateInfo lCmdAllocInfo = {};
        lCmdAllocInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        lCmdAllocInfo.pNext                       = NULL;
        lCmdAllocInfo.commandPool                 = lCommandPool;
        lCmdAllocInfo.commandBufferCount          = 1;
        lCmdAllocInfo.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

        return lCmdAllocInfo;
    }

    static inline VkExtent2D Initialise(uint32_t luiWidth, uint32_t luiHeight)
    {
        VkExtent2D lExtent = {};
        lExtent.width      = luiWidth;
        lExtent.height     = luiHeight;

        return lExtent;
    }
};