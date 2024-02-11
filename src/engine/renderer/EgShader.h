#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>

class cEgShader
{
  public:
    void Construct(VkDevice lDevice, const char *lpacFilename);
    void Destruct(VkDevice lDevice);

    static cTkFixedString<256, char> &GetPrelude();
    static void SetPrelude(const char *lpacPrelude);
    static cTkFixedString<256, char> msPrelude;

    VkShaderModule mModule;
};