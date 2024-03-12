#pragma once

#include <toolkit/graphics/vulkan/constructors/TkVulkanConstructors.h>

template <>
class cTkVkConstructor<VkShaderModuleCreateInfo>
{
  public:
    static inline VkShaderModuleCreateInfo Initialise(const uint32_t *lpCode, size_t lSize)
    {
        VkShaderModuleCreateInfo lInfo = {};
        lInfo.sType                    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        lInfo.pNext                    = NULL;
        lInfo.pCode                    = lpCode;
        lInfo.codeSize                 = lSize;

        return lInfo;
    }
};