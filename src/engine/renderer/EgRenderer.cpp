#include <engine/renderer/EgRenderer.h>

void cEgRenderer::Construct(cTkEngineSettings &lSettings)
{
    cTkSystem &gSystem = cTkSystem::GetInstance();

    vkb::InstanceBuilder lInstanceBuilder;

    auto lBuilderRet = lInstanceBuilder.set_app_name(lSettings.msApplicationName.c_str())
                           .set_app_version(lSettings.muiApplicationVersion)
                           .set_engine_name(lSettings.msEngineName.c_str())
                           .set_engine_version(lSettings.muiEngineVersion)
#ifdef D_DEBUG
                           .request_validation_layers()
                           .use_default_debug_messenger()
#endif
                           .require_api_version(1, 3)
                           .build();
    vkb::Instance lInstance = lBuilderRet.value();

    this->mVkInstance     = lInstance.instance;
    this->mDebugMessenger = lInstance.debug_messenger;

    if (glfwCreateWindowSurface(this->mVkInstance, gSystem.mpGLFWWindow, nullptr, &this->mSurfaceKHR) != VK_SUCCESS)
    {
        TK_ERROR("Couldn't make window surface!\n"
                 "(glfwCreateWindowSurface(this->mVkInstance, gSystem.mpGLFWWindow, nullptr, &this->mSurfaceKHR) != "
                 "VK_SUCCESS)");
    }

    vkb::PhysicalDeviceSelector lDeviceSelector(lInstance);
    vkb::PhysicalDevice lPhysicalDevice =
        lDeviceSelector.set_minimum_version(1, 2).set_surface(this->mSurfaceKHR).select().value();
    vkb::DeviceBuilder lDeviceBuilder(lPhysicalDevice);
    vkb::Device lDevice = lDeviceBuilder.build().value();

    this->mPhysicalDevice = lPhysicalDevice.physical_device;
    this->mDevice         = lDevice.device;

    this->mGraphicsQueue         = lDevice.get_queue(vkb::QueueType::graphics).value();
    this->muiGraphicsQueueFamily = lDevice.get_queue_index(vkb::QueueType::graphics).value();
    this->mRenderPass            = VkRenderPass();
    this->mSwapchainExtent       = cTkVulkan::Initialise(gSystem.muiWidth, gSystem.muiHeight);

    this->ConstructSwapChain();
    this->ConstructRenderpass();
    this->ConstructFramebuffers();
    this->ConstructSemaphores();
    this->ConstructCommandBuffers();
}

void cEgRenderer::ConstructSwapChain()
{
    cTkSystem &gSystem = cTkSystem::GetInstance();

    vkb::SwapchainBuilder lSwapChainBuilder(this->mPhysicalDevice, this->mDevice, this->mSurfaceKHR);
    vkb::Swapchain lSwapChain = lSwapChainBuilder.use_default_format_selection()
                                    .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
                                    .set_desired_extent(gSystem.muiWidth, gSystem.muiHeight)
                                    .build()
                                    .value();

    // hacky fix to copy out the vectors since we aren't using std::allocator.
    // could be better but then we wouldnt be using vkb
    this->mSwapChain                       = lSwapChain.swapchain;
    std::vector<VkImage> lImageVec         = lSwapChain.get_images().value();
    this->mvSwapChainImages                = TkSTD::Vector<VkImage>(lImageVec.begin(), lImageVec.end());
    std::vector<VkImageView> lImageViewVec = lSwapChain.get_image_views().value();
    this->mvSwapChainImageViews            = TkSTD::Vector<VkImageView>(lImageViewVec.begin(), lImageViewVec.end());
    this->mSwapChainImageFormat            = lSwapChain.image_format;
}

void cEgRenderer::ConstructRenderpass()
{
    VkAttachmentDescription2 lColorAttachment = cTkVulkan::Initialise(this->mSwapChainImageFormat);

    VkAttachmentReference2 lColorAttachmentRef = cTkVulkan::Initialise(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

    VkSubpassDescription2 lSubpass = cTkVulkan::Initialise(&lColorAttachmentRef, 1);

    VkSubpassDependency2 lSubpassDependency = cTkVulkan::Initialise();

    VkRenderPassCreateInfo2 lRenderPassCreateInfo =
        cTkVulkan::Initialise(1, &lColorAttachment, 1, &lSubpass, 1, &lSubpassDependency);

    _VK_GUARD(vkCreateRenderPass2(this->mDevice, &lRenderPassCreateInfo, NULL, &this->mRenderPass));
}

void cEgRenderer::ConstructFramebuffers()
{
    VkFramebufferCreateInfo lFramebufferCreateInfo = cTkVulkan::Initialise(this->mRenderPass, this->mSwapchainExtent);

    const uint32_t luiSwapChainImageCount = this->mvSwapChainImages.size();
    this->mvFramebuffers                  = TkSTD::Vector<VkFramebuffer>(luiSwapChainImageCount);

    for (int i = 0; i < luiSwapChainImageCount; i++)
    {
        lFramebufferCreateInfo.pAttachments = &this->mvSwapChainImageViews[i];
        _VK_GUARD(vkCreateFramebuffer(this->mDevice, &lFramebufferCreateInfo, NULL, &this->mvFramebuffers[i]));
    }
}

void cEgRenderer::ConstructCommandBuffers()
{
    VkCommandPoolCreateInfo lCommandPoolCreateInfo = cTkVulkan::Initialise(this->muiGraphicsQueueFamily);

    _VK_GUARD(vkCreateCommandPool(this->mDevice, &lCommandPoolCreateInfo, nullptr, &this->mCommandPool));

    VkCommandBufferAllocateInfo lCmdAllocInfo = cTkVulkan::Initialise(this->mCommandPool);

    _VK_GUARD(vkAllocateCommandBuffers(this->mDevice, &lCmdAllocInfo, &this->mCommandBuffer));
}

void cEgRenderer::ConstructSemaphores()
{
    VkFenceCreateInfo lFenceCreateInfo = {};
    lFenceCreateInfo.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    lFenceCreateInfo.pNext             = NULL;
    lFenceCreateInfo.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

    VkSemaphoreCreateInfo lSemaphoreCreateInfo = {};
    lSemaphoreCreateInfo.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    _VK_GUARD(vkCreateFence(this->mDevice, &lFenceCreateInfo, NULL, &this->mRenderFence));
    _VK_GUARD(vkCreateSemaphore(this->mDevice, &lSemaphoreCreateInfo, NULL, &this->mPresentSemaphore));
    _VK_GUARD(vkCreateSemaphore(this->mDevice, &lSemaphoreCreateInfo, NULL, &this->mRenderSemaphore));
}

void cEgRenderer::Render()
{
    _VK_GUARD(vkWaitForFences(this->mDevice, 1, &this->mRenderFence, VK_TRUE, UINT64_MAX));
    _VK_GUARD(vkResetFences(this->mDevice, 1, &this->mRenderFence));

    uint32_t luiImageIndex;
    _VK_GUARD(vkAcquireNextImageKHR(
        this->mDevice, this->mSwapChain, UINT64_MAX, this->mPresentSemaphore, VK_NULL_HANDLE, &luiImageIndex));

    VkCommandBuffer lCmdBuffer = this->mCommandBuffer;
    _VK_GUARD(vkResetCommandBuffer(lCmdBuffer, 0));

    VkCommandBufferBeginInfo lCmdBufferBeginInfo = {};
    lCmdBufferBeginInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    lCmdBufferBeginInfo.pNext                    = NULL;
    lCmdBufferBeginInfo.flags                    = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    _VK_GUARD(vkBeginCommandBuffer(lCmdBuffer, &lCmdBufferBeginInfo));

    VkClearValue lClearValue;
    float lfFlash     = std::abs(std::sin(this->muiFrameNum / 120.0f));
    lClearValue.color = {{0.0f, 0.0f, lfFlash, 1.0f}};

    VkRenderPassBeginInfo lRenderPassBeginInfo = {};
    lRenderPassBeginInfo.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    lRenderPassBeginInfo.pNext                 = NULL;
    lRenderPassBeginInfo.renderPass            = this->mRenderPass;
    lRenderPassBeginInfo.framebuffer           = this->mvFramebuffers[luiImageIndex];
    lRenderPassBeginInfo.renderArea.offset     = {0, 0};
    lRenderPassBeginInfo.renderArea.extent     = this->mSwapchainExtent;
    lRenderPassBeginInfo.clearValueCount       = 1;
    lRenderPassBeginInfo.pClearValues          = &lClearValue;

    VkImageSubresourceRange lClearRange = {};
    lClearRange.aspectMask              = VK_IMAGE_ASPECT_COLOR_BIT;
    lClearRange.baseMipLevel            = 0;
    lClearRange.levelCount              = VK_REMAINING_MIP_LEVELS;
    lClearRange.baseArrayLayer          = 0;
    lClearRange.layerCount              = VK_REMAINING_ARRAY_LAYERS;

    vkCmdBeginRenderPass(lCmdBuffer, &lRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    // commands?

    vkCmdEndRenderPass(lCmdBuffer);

    _VK_GUARD(vkEndCommandBuffer(lCmdBuffer));

    VkCommandBufferSubmitInfo lSubmitInfo = {};
    lSubmitInfo.sType                     = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
    lSubmitInfo.pNext                     = NULL;
    lSubmitInfo.commandBuffer             = lCmdBuffer;
    lSubmitInfo.deviceMask                = 0;

    VkSemaphoreSubmitInfo lWaitInfo = {};
    lWaitInfo.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    lWaitInfo.pNext                 = NULL;
    lWaitInfo.semaphore             = this->mPresentSemaphore;
    lWaitInfo.stageMask             = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR;
    lWaitInfo.deviceIndex           = 0;
    lWaitInfo.value                 = 1;

    VkSemaphoreSubmitInfo lSignalInfo = {};
    lSignalInfo.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    lSignalInfo.pNext                 = NULL;
    lSignalInfo.semaphore             = this->mPresentSemaphore;
    lSignalInfo.stageMask             = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;
    lSignalInfo.deviceIndex           = 0;
    lSignalInfo.value                 = 1;

    VkSubmitInfo2 lSubmitInfo2            = {};
    lSubmitInfo2.sType                    = VK_STRUCTURE_TYPE_SUBMIT_INFO_2_KHR;
    lSubmitInfo2.pNext                    = NULL;
    lSubmitInfo2.waitSemaphoreInfoCount   = 1;
    lSubmitInfo2.pWaitSemaphoreInfos      = &lWaitInfo;
    lSubmitInfo2.signalSemaphoreInfoCount = 1;
    lSubmitInfo2.pSignalSemaphoreInfos    = &lSignalInfo;
    lSubmitInfo2.commandBufferInfoCount   = 1;
    lSubmitInfo2.pCommandBufferInfos      = &lSubmitInfo;
    lSubmitInfo2.flags                    = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR;

    _VK_GUARD(vkQueueSubmit2(this->mGraphicsQueue, 1, &lSubmitInfo2, this->mRenderFence));

    VkPresentInfoKHR lPresentInfo   = {};
    lPresentInfo.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    lPresentInfo.pNext              = NULL;
    lPresentInfo.pSwapchains        = &this->mSwapChain;
    lPresentInfo.swapchainCount     = 1;
    lPresentInfo.pWaitSemaphores    = &this->mRenderSemaphore;
    lPresentInfo.waitSemaphoreCount = 1;
    lPresentInfo.pImageIndices      = &luiImageIndex;

    _VK_GUARD(vkQueuePresentKHR(this->mGraphicsQueue, &lPresentInfo));

    this->muiFrameNum++;
}

void cEgRenderer::Destruct()
{
    vkDeviceWaitIdle(this->mDevice);
    vkDestroyCommandPool(this->mDevice, this->mCommandPool, nullptr);

    this->DestructSwapChain();

    vkDestroySurfaceKHR(this->mVkInstance, this->mSurfaceKHR, nullptr);
    vkDestroyDevice(this->mDevice, nullptr);
    vkb::destroy_debug_utils_messenger(this->mVkInstance, this->mDebugMessenger);

    vkDestroyInstance(this->mVkInstance, nullptr);
}

void cEgRenderer::DestructSwapChain() {}