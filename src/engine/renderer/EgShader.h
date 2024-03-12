#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/graphics/vulkan/TkVulkan.h>

class cEgShader
{
  public:
    void Construct(VkDevice lDevice, const char *lpacFilename);
    void Destruct(VkDevice lDevice);

    static cTkString &GetPrelude();
    static void SetPrelude(const char *lpacPrelude);
    static cTkString msPrelude;

    bool LoadShaderModule(VkDevice lDevice, const char *lpacFilename);

    VkShaderModule mModule;
};