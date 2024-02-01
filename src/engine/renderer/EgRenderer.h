#pragma once

#include <toolkit/engine/TkEngineSettings.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>
#include <toolkit/system/TkSystem.h>

class cEgRenderer
{
  public:
    inline cEgRenderer(cTkEngineSettings &lSettings) { this->Construct(lSettings); }

    void Construct(cTkEngineSettings &lSettings);
    void ConstructSwapChain();
    void ConstructRenderpass();
    void ConstructFramebuffers();
    void ConstructCommandBuffers();
    void ConstructSyncStructures();

    void Destruct();

    void Render();
    // cEgFrameData &GetCurrentFrame() { return mFrames[muiFrameNum % cEgFrameData::kiFrameOverlap]; }

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
    VkExtent2D mSwapchainExtent;

    VkSemaphore mPresentSemaphore, mRenderSemaphore;
    VkFence mRenderFence;

    TkSTD::Vector<VkFramebuffer> mvFramebuffers;
    TkSTD::Vector<VkImage> mvSwapChainImages;
    TkSTD::Vector<VkImageView> mvSwapChainImageViews;

    uint32_t muiFrameNum = NULL;
};