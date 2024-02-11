#include <engine/renderer/EgRenderer.h>

#define VMA_IMPLEMENTATION
#include <toolkit/graphics/vulkan/vk_mem_alloc.h>

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
    TK_ASSERT(
        glfwCreateWindowSurface(this->mVkInstance, gSystem.mpGLFWWindow, nullptr, &this->mSurfaceKHR) == VK_SUCCESS,
        "Couldn't make window surface!");

    const std::vector<const char *> lDeviceExts = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME};

    vkb::PhysicalDeviceSelector lDeviceSelector(lInstance);
    vkb::PhysicalDevice lPhysicalDevice = lDeviceSelector.set_minimum_version(1, 3)
                                              .add_required_extensions(lDeviceExts)
                                              .set_surface(this->mSurfaceKHR)
                                              .set_required_features_13({.synchronization2 = VK_TRUE})
                                              .set_required_features_12({.bufferDeviceAddress = VK_TRUE})
                                              .select()
                                              .value();

    vkb::DeviceBuilder lDeviceBuilder(lPhysicalDevice);

    vkb::Device lDevice = lDeviceBuilder.build().value();

    this->mPhysicalDevice = lPhysicalDevice.physical_device;
    this->mDevice         = lDevice.device;

    this->mGraphicsQueue         = lDevice.get_queue(vkb::QueueType::graphics).value();
    this->muiGraphicsQueueFamily = lDevice.get_queue_index(vkb::QueueType::graphics).value();
    this->mRenderPass            = VkRenderPass();
    this->mSwapchainExtent       = cTkVkConstructor<VkExtent2D>::Initialise(gSystem.muiWidth, gSystem.muiHeight);

    VmaAllocatorCreateInfo lAllocatorInfo = cTkVkConstructor<VmaAllocatorCreateInfo>::Initialise(
        this->mPhysicalDevice, this->mDevice, this->mVkInstance, VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT);
    vmaCreateAllocator(&lAllocatorInfo, &this->mAllocator);

    this->mPrimaryDeletionQueue.PushFunction([&]() { vmaDestroyAllocator(this->mAllocator); });

    this->ConstructSwapChain();
    this->ConstructRenderpass();
    this->ConstructFramebuffers();
    this->ConstructSyncStructures();
    this->ConstructCommandBuffers();
    this->ConstructDescriptors();
}

void cEgRenderer::ConstructDescriptors()
{
    this->mpDescriptorAllocator = new cEgDescriptorAllocator();

    TkSTD::Vector<cEgDescriptorAllocator::PoolSizeRatio> lPoolSizeRatios = {{VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1.0f}};
    this->mpDescriptorAllocator->Construct(this->mDevice, 10, lPoolSizeRatios);

    cEgDescriptorLayoutBuilder lLayoutBuilder;
    lLayoutBuilder.AddBinding(0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);
    this->mDrawImageDescriptorLayout = lLayoutBuilder.Build(this->mDevice, VK_SHADER_STAGE_COMPUTE_BIT);

    this->mDrawImageDescriptors =
        this->mpDescriptorAllocator->Allocate(this->mDevice, this->mDrawImageDescriptorLayout);
    VkDescriptorImageInfo lImageInfo = {};
    lImageInfo.imageLayout           = VK_IMAGE_LAYOUT_GENERAL;
    lImageInfo.imageView             = this->mDrawImage.mImageView;

    VkWriteDescriptorSet lImageWrite = {};
    lImageWrite.sType                = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    lImageWrite.pNext                = NULL;
    lImageWrite.dstBinding           = 0;
    lImageWrite.dstSet               = this->mDrawImageDescriptors;
    lImageWrite.descriptorCount      = 1;
    lImageWrite.descriptorType       = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    lImageWrite.pImageInfo           = &lImageInfo;
    vkUpdateDescriptorSets(this->mDevice, 1, &lImageWrite, 0, NULL);
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

    this->mSwapChain                       = lSwapChain.swapchain;
    std::vector<VkImage> lImageVec         = lSwapChain.get_images().value();
    this->mvSwapChainImages                = TkSTD::Vector<VkImage>(lImageVec.begin(), lImageVec.end());
    std::vector<VkImageView> lImageViewVec = lSwapChain.get_image_views().value();
    this->mvSwapChainImageViews            = TkSTD::Vector<VkImageView>(lImageViewVec.begin(), lImageViewVec.end());
    this->mSwapChainImageFormat            = lSwapChain.image_format;

    VkExtent3D lDrawImageExtent   = {.width = gSystem.muiWidth, .height = gSystem.muiHeight, .depth = 1};
    this->mDrawImage.mImageFormat = VK_FORMAT_R16G16B16A16_SFLOAT;
    this->mDrawImage.mImageExtent = lDrawImageExtent;

    VkImageUsageFlags lDrawImageUsageFlags = {};
    lDrawImageUsageFlags |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    lDrawImageUsageFlags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    lDrawImageUsageFlags |= VK_IMAGE_USAGE_STORAGE_BIT;
    lDrawImageUsageFlags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    VkImageCreateInfo lImageCreateInfo = cTkVkConstructor<VkImageCreateInfo>::Initialise(
        this->mDrawImage.mImageFormat, lDrawImageUsageFlags, this->mDrawImage.mImageExtent);

    VmaAllocationCreateInfo lImageAllocCreateInfo = cTkVkConstructor<VmaAllocationCreateInfo>::Initialise(
        VMA_MEMORY_USAGE_GPU_ONLY, VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT));

    _VK_GUARD(vmaCreateImage(
        this->mAllocator, &lImageCreateInfo, &lImageAllocCreateInfo, &this->mDrawImage.mImage,
        &this->mDrawImage.mAllocation, NULL));

    VkImageViewCreateInfo lImageViewInfo = cTkVkConstructor<VkImageViewCreateInfo>::Initialise(
        this->mDrawImage.mImageFormat, this->mDrawImage.mImage, VK_IMAGE_ASPECT_COLOR_BIT);

    _VK_GUARD(vkCreateImageView(this->mDevice, &lImageViewInfo, NULL, &this->mDrawImage.mImageView));

    this->mPrimaryDeletionQueue.PushFunction([&]() {
        vkDestroyImageView(this->mDevice, this->mDrawImage.mImageView, NULL);
        vmaDestroyImage(this->mAllocator, this->mDrawImage.mImage, this->mDrawImage.mAllocation);
    });
}

void cEgRenderer::ConstructRenderpass()
{
    VkAttachmentDescription2 lColorAttachment =
        cTkVkConstructor<VkAttachmentDescription2>::Initialise(this->mSwapChainImageFormat);

    VkAttachmentReference2 lColorAttachmentRef =
        cTkVkConstructor<VkAttachmentReference2>::Initialise(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

    VkSubpassDescription2 lSubpass = cTkVkConstructor<VkSubpassDescription2>::Initialise(&lColorAttachmentRef, 1);

    VkSubpassDependency2 lSubpassDependency = cTkVkConstructor<VkSubpassDependency2>::Initialise();

    VkRenderPassCreateInfo2 lRenderPassCreateInfo = cTkVkConstructor<VkRenderPassCreateInfo2>::Initialise(
        1, &lColorAttachment, 1, &lSubpass, 1, &lSubpassDependency);

    _VK_GUARD(vkCreateRenderPass2(this->mDevice, &lRenderPassCreateInfo, NULL, &this->mRenderPass));
}

void cEgRenderer::ConstructFramebuffers()
{
    VkFramebufferCreateInfo lFramebufferCreateInfo =
        cTkVkConstructor<VkFramebufferCreateInfo>::Initialise(this->mRenderPass, this->mSwapchainExtent);

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
    VkCommandPoolCreateInfo lCommandPoolCreateInfo = cTkVkConstructor<VkCommandPoolCreateInfo>::Initialise(
        this->muiGraphicsQueueFamily, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    _VK_GUARD(vkCreateCommandPool(this->mDevice, &lCommandPoolCreateInfo, nullptr, &this->mCommandPool));
    VkCommandBufferAllocateInfo lCmdAllocInfo = cTkVkConstructor<VkCommandBufferAllocateInfo>::Initialise(
        this->mCommandPool, 1, VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    _VK_GUARD(vkAllocateCommandBuffers(this->mDevice, &lCmdAllocInfo, &this->mCommandBuffer));
}

void cEgRenderer::ConstructSyncStructures()
{
    VkFenceCreateInfo lFenceCreateInfo = cTkVkConstructor<VkFenceCreateInfo>::Initialise(VK_FENCE_CREATE_SIGNALED_BIT);
    VkSemaphoreCreateInfo lSemaphoreCreateInfo = cTkVkConstructor<VkSemaphoreCreateInfo>::Initialise(0);

    _VK_GUARD(vkCreateFence(this->mDevice, &lFenceCreateInfo, NULL, &this->mRenderFence));
    _VK_GUARD(vkCreateSemaphore(this->mDevice, &lSemaphoreCreateInfo, NULL, &this->mPresentSemaphore));
    _VK_GUARD(vkCreateSemaphore(this->mDevice, &lSemaphoreCreateInfo, NULL, &this->mRenderSemaphore));
}

void cEgRenderer::Render()
{
    _VK_GUARD(vkWaitForFences(this->mDevice, 1, &this->mRenderFence, VK_TRUE, UINT64_MAX));
    _VK_GUARD(vkResetFences(this->mDevice, 1, &this->mRenderFence));

    VkCommandBuffer lCmdBuffer = this->mCommandBuffer;
    _VK_GUARD(vkResetCommandBuffer(lCmdBuffer, 0));

    uint32_t luiImageIndex;
    _VK_GUARD(vkAcquireNextImageKHR(
        this->mDevice, this->mSwapChain, UINT64_MAX, this->mPresentSemaphore, VK_NULL_HANDLE, &luiImageIndex));

    VkCommandBufferBeginInfo lCmdBufferBeginInfo =
        cTkVkConstructor<VkCommandBufferBeginInfo>::Initialise(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

    _VK_GUARD(vkBeginCommandBuffer(lCmdBuffer, &lCmdBufferBeginInfo));

    VkClearValue lClearValue;
    float lfFlash     = std::abs(std::sin(this->muiFrameNum / 120.0f));
    lClearValue.color = {{0.0f, 0.0f, lfFlash, 1.0f}};

    VkRenderPassBeginInfo lRenderPassBeginInfo = cTkVkConstructor<VkRenderPassBeginInfo>::Initialise(
        this->mRenderPass, this->mvFramebuffers[luiImageIndex], {0, 0}, this->mSwapchainExtent, 1, &lClearValue);

    VkImageSubresourceRange lClearRange = cTkVkConstructor<VkImageSubresourceRange>::Initialise();

    vkCmdBeginRenderPass(lCmdBuffer, &lRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    // commands

    vkCmdEndRenderPass(lCmdBuffer);

    _VK_GUARD(vkEndCommandBuffer(lCmdBuffer));

    VkCommandBufferSubmitInfo lSubmitInfo = cTkVkConstructor<VkCommandBufferSubmitInfo>::Initialise(lCmdBuffer);
    VkSemaphoreSubmitInfo lWaitInfo   = cTkVkConstructor<VkSemaphoreSubmitInfo>::Initialise(this->mPresentSemaphore, 0);
    VkSemaphoreSubmitInfo lSignalInfo = cTkVkConstructor<VkSemaphoreSubmitInfo>::Initialise(this->mRenderSemaphore, 0);
    VkSubmitInfo2 lSubmitInfo2 =
        cTkVkConstructor<VkSubmitInfo2>::Initialise(&lWaitInfo, 1, &lSignalInfo, 1, &lSubmitInfo, 1, 0);

    _VK_GUARD(vkQueueSubmit2(this->mGraphicsQueue, 1, &lSubmitInfo2, this->mRenderFence));

    VkPresentInfoKHR lPresentInfo = cTkVkConstructor<VkPresentInfoKHR>::Initialise(
        &this->mSwapChain, 1, &this->mRenderSemaphore, 1, &luiImageIndex);

    _VK_GUARD(vkQueuePresentKHR(this->mGraphicsQueue, &lPresentInfo));

    this->muiFrameNum++;
}

void cEgRenderer::Destruct()
{
    vkDeviceWaitIdle(this->mDevice);
    this->mPrimaryDeletionQueue.Flush();
    vkDestroyCommandPool(this->mDevice, this->mCommandPool, NULL);

    vkDestroyFence(this->mDevice, this->mRenderFence, NULL);
    vkDestroySemaphore(this->mDevice, this->mPresentSemaphore, NULL);
    vkDestroySemaphore(this->mDevice, this->mRenderSemaphore, NULL);

    delete this->mpDescriptorAllocator;

    vkDestroySwapchainKHR(this->mDevice, this->mSwapChain, NULL);
    vkDestroyRenderPass(this->mDevice, this->mRenderPass, NULL);
    for (int i = 0; i < this->mvFramebuffers.size(); i++)
    {
        vkDestroyFramebuffer(this->mDevice, this->mvFramebuffers[i], NULL);
        vkDestroyImageView(this->mDevice, this->mvSwapChainImageViews[i], NULL);
    }

    vkDestroySurfaceKHR(this->mVkInstance, this->mSurfaceKHR, nullptr);
    vkb::destroy_debug_utils_messenger(this->mVkInstance, this->mDebugMessenger);
    vkDestroyDevice(this->mDevice, nullptr);

    vkDestroyInstance(this->mVkInstance, nullptr);
}