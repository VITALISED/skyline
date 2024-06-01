#pragma once

#include <engine/renderer/EgShader.h>

class cEgPipeline
{
  public:
    void Construct();
    bool Load(VkDevice lDevice, const char *lpacShaderFilename);
    void LoadBackgroundPipelines();

    VkPipeline mPipeline;
    VkPipelineLayout mPipelineLayout;

    cEgShader *mpShader;
};