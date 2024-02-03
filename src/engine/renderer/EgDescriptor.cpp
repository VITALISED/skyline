#include <engine/renderer/EgDescriptor.h>

void cEgDescriptorPool::Construct(VkDevice lDevice, uint32_t luiMaxSets, TkSTD::Span<PoolSizeRatio> lPoolRatios)
{
    TkSTD::Vector<VkDescriptorPoolSize> lPoolSizes;
    for (PoolSizeRatio lRatio : lPoolRatios)
    {
        lPoolSizes.push_back(
            VkDescriptorPoolSize{.type = lRatio.meType, .descriptorCount = uint32_t(lRatio.mfRatio * luiMaxSets)});
    }

    VkDescriptorPoolCreateInfo pool_info = {.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
    pool_info.flags                      = 0;
    pool_info.maxSets                    = luiMaxSets;
    pool_info.poolSizeCount              = static_cast<uint32_t>(lPoolSizes.size());
    pool_info.pPoolSizes                 = lPoolSizes.data();

    vkCreateDescriptorPool(lDevice, &pool_info, nullptr, &this->mPool);
}

void cEgDescriptorPool::ClearDescriptors(VkDevice lDevice)
{
    vkResetDescriptorPool(lDevice, this->mPool, 0);
}

void cEgDescriptorPool::Destruct(VkDevice lDevice)
{
    vkDestroyDescriptorPool(lDevice, this->mPool, NULL);
}