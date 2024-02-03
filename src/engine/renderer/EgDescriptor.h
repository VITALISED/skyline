#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>

class cEgDescriptorPool
{
  public:
    struct PoolSizeRatio;

    void Construct(VkDevice device, uint32_t maxSets, TkSTD::Span<PoolSizeRatio> poolRatios);
    void SetupBindings(uint32_t luiBinding, VkDescriptorType leType);
    void ClearDescriptors(VkDevice device);
    void Destruct(VkDevice device);

    struct PoolSizeRatio
    {
        VkDescriptorType meType;
        float mfRatio;
    };

    VkDescriptorPool mPool;

    VkDescriptorSet mDrawImageDescriptors;
    VkDescriptorSetLayout mDrawImageDescriptorLayout;
};