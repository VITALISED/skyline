#include <engine/renderer/EgPipeline.h>

void cEgPipeline::Construct()
{
    this->mpShader = new cEgShader();
}

bool cEgPipeline::Load(VkDevice lDevice, const char *lpacShaderFilename)
{
    this->mpShader->LoadShaderModule(lDevice, lpacShaderFilename);

    return true;
}