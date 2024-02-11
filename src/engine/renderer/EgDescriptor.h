#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>

class cEgDescriptorAllocator
{
  public:
    class PoolSizeRatio
    {
      public:
        VkDescriptorType meType;
        float mfRatio;
    };

    void Construct(VkDevice lDevice, uint32_t luiMaxSets, const TkSTD::Span<PoolSizeRatio> &lPoolSizeRatios);
    void Clear(VkDevice lDevice);
    void Destruct(VkDevice lDevice);
    VkDescriptorSet Allocate(VkDevice lDevice, VkDescriptorSetLayout lLayout);

    VkDescriptorPool mPool;
};

class cEgDescriptorLayoutBuilder
{
  public:
    void AddBinding(uint32_t luiBinding, VkDescriptorType leType);
    void Clear();
    VkDescriptorSetLayout Build(VkDevice lDevice, VkShaderStageFlags lxShaderStages);

    TkSTD::Vector<VkDescriptorSetLayoutBinding> mvBindings;
};