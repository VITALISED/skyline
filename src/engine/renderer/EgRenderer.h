#pragma once

#include <engine/renderer/EgDeletionQueue.h>
#include <engine/renderer/EgDescriptor.h>
#include <engine/renderer/EgPipeline.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>
#include <toolkit/system/TkSystem.h>

class cEgRenderer
{
  public:
    cEgRenderer() { this->Construct(); }

    void Construct();
    void ConstructSwapChain();
    void ConstructRenderpass();
    void ConstructFramebuffers();
    void ConstructCommandBuffers();
    void ConstructSyncStructures();
    void ConstructDescriptors();
    void ConstructPipelines();

    void Destruct();

    void Render();

    class AllocatedImage
    {
      public:
        VkImage mImage;
        VkImageView mImageView;
        VmaAllocation mAllocation;
        VkExtent3D mImageExtent;
        VkFormat mImageFormat;
    };

    VmaAllocator mAllocator;
    VkInstance mVkInstance;
    VkSurfaceKHR mSurfaceKHR;
    VkDebugUtilsMessengerEXT mDebugMessenger;
    VkPhysicalDevice mPhysicalDevice;
    VkDevice mDevice;
    VkCommandPool mCommandPool;
    VkQueue mGraphicsQueue;
    uint32_t muiGraphicsQueueFamily;
    VkCommandBuffer mCommandBuffer;
    VkRenderPass mRenderPass;

    VkSwapchainKHR mSwapChain;
    VkFormat mSwapChainImageFormat;
    AllocatedImage mDrawImage;
    VkExtent2D mSwapchainExtent;

    cEgDescriptorAllocator *mpDescriptorAllocator;
    VkDescriptorSet mDrawImageDescriptors;
    VkDescriptorSetLayout mDrawImageDescriptorLayout;

    VkSemaphore mPresentSemaphore, mRenderSemaphore;
    VkFence mRenderFence;

    std::vector<VkFramebuffer> mvFramebuffers;
    std::vector<VkImage> mvSwapChainImages;
    std::vector<VkImageView> mvSwapChainImageViews;

    cEgDeletionQueue mPrimaryDeletionQueue;

    cEgPipeline mPipeline;

    uint32_t muiFrameNum = NULL;
};