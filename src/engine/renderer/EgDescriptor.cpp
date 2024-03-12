#include <engine/renderer/EgDescriptor.h>

void cEgDescriptorAllocator::Construct(
    VkDevice lDevice, uint32_t luiMaxSets, const std::span<PoolSizeRatio> &lPoolSizeRatios)
{
    std::vector<VkDescriptorPoolSize> lPoolSizes;
    for (PoolSizeRatio lRatio : lPoolSizeRatios)
    {
        lPoolSizes.push_back(VkDescriptorPoolSize{
            .type = lRatio.meType, .descriptorCount = static_cast<uint32_t>(lRatio.mfRatio * luiMaxSets)});
    }

    VkDescriptorPoolCreateInfo lPoolInfo = {.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
    lPoolInfo.flags                      = 0;
    lPoolInfo.maxSets                    = luiMaxSets;
    lPoolInfo.poolSizeCount              = static_cast<uint32_t>(lPoolSizes.size());
    lPoolInfo.pPoolSizes                 = lPoolSizes.data();

    vkCreateDescriptorPool(lDevice, &lPoolInfo, NULL, &this->mPool);
}

void cEgDescriptorAllocator::Clear(VkDevice lDevice)
{
    vkResetDescriptorPool(lDevice, this->mPool, 0);
}

void cEgDescriptorAllocator::Destruct(VkDevice lDevice)
{
    vkDestroyDescriptorPool(lDevice, this->mPool, NULL);
}

VkDescriptorSet cEgDescriptorAllocator::Allocate(VkDevice lDevice, VkDescriptorSetLayout lLayout)
{
    VkDescriptorSetAllocateInfo lAllocInfo = {.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
    lAllocInfo.pNext                       = NULL;
    lAllocInfo.descriptorPool              = this->mPool;
    lAllocInfo.descriptorSetCount          = 1;
    lAllocInfo.pSetLayouts                 = &lLayout;

    VkDescriptorSet lDescriptorSet;
    _VK_GUARD(vkAllocateDescriptorSets(lDevice, &lAllocInfo, &lDescriptorSet));

    return lDescriptorSet;
}

void cEgDescriptorLayoutBuilder::AddBinding(uint32_t luiBinding, VkDescriptorType leType)
{
    VkDescriptorSetLayoutBinding lNewBinding = {};
    lNewBinding.binding                      = luiBinding;
    lNewBinding.descriptorCount              = 1;
    lNewBinding.descriptorType               = leType;

    this->mvBindings.push_back(lNewBinding);
}

void cEgDescriptorLayoutBuilder::Clear()
{
    this->mvBindings.clear();
}

VkDescriptorSetLayout cEgDescriptorLayoutBuilder::Build(VkDevice lDevice, VkShaderStageFlags lxShaderStages)
{
    for (VkDescriptorSetLayoutBinding &lBinding : this->mvBindings) { lBinding.stageFlags |= lxShaderStages; }

    VkDescriptorSetLayoutCreateInfo lLayoutInfo = {.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
    lLayoutInfo.pNext                           = NULL;
    lLayoutInfo.pBindings                       = this->mvBindings.data();
    lLayoutInfo.bindingCount                    = static_cast<uint32_t>(this->mvBindings.size());
    lLayoutInfo.flags                           = 0;

    VkDescriptorSetLayout lDescriptorSetLayout;
    _VK_GUARD(vkCreateDescriptorSetLayout(lDevice, &lLayoutInfo, NULL, &lDescriptorSetLayout));

    return lDescriptorSetLayout;
}