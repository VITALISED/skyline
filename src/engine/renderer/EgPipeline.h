#pragma once

#include <engine/renderer/EgShader.h>
#include <toolkit/system/TkSystem.h>

class cEgPipeline
{
  public:
    void Construct();
    bool LoadShaderModule(const char *lpacFilename);

    VkPipeline mPipeline;
    cEgShader *mpShader;
    VkPipelineLayout mPipelineLayout;
};