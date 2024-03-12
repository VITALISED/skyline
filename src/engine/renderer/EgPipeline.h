#pragma once

#include <engine/renderer/EgShader.h>

class cEgPipeline
{
  public:
    void Construct();
    bool Load(VkDevice lDevice, const char *lpacShaderFilename);

    VkPipeline mPipeline;
    cEgShader *mpShader;
    VkPipelineLayout mPipelineLayout;
};