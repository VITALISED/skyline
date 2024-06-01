#include <engine/renderer/EgPipeline.h>

void cEgPipeline::Construct()
{
    this->mpShader = new cEgShader();
}

void cEgPipeline::LoadBackgroundPipelines()
{
    VkPipelineLayoutCreateInfo lPipelineLayoutCreateInfo = {};
    lPipelineLayoutCreateInfo.sType                      = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    lPipelineLayoutCreateInfo.pNext                      = TK_NULL;
}

bool cEgPipeline::Load(VkDevice lDevice, const char *lpacShaderFilename)
{
    this->mpShader->LoadShaderModule(lDevice, lpacShaderFilename);

    this->LoadBackgroundPipelines();

    return true;
}