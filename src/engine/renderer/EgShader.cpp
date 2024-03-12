#include <engine/renderer/EgShader.h>

bool cEgShader::LoadShaderModule(VkDevice lDevice, const char *lpacFilename)
{
    // cTkFileSystem *gpFileSystem = cTkSystem::GetInstance().mpFilesystem;
    // cTkFileHandle lFH           = gpFileSystem->Open(lpacFilename, ETkFileMode_Read, true);

    // TK_ASSERT(lFH.IsValid(), "Invalid FH");
    // std::vector<uint32_t> lBuffer;
    // lFH->Read(reinterpret_cast<char *>(lBuffer.data()), lFH->Size(), 1);
    // lFH->Close();

    // VkShaderModuleCreateInfo lCreateInfo =
    //     cTkVkConstructor<VkShaderModuleCreateInfo>::Initialise(lBuffer.data(), lBuffer.size() * sizeof(uint32_t));

    // if (vkCreateShaderModule(lDevice, &lCreateInfo, NULL, &mModule) != VK_SUCCESS)
    // {
    //     TK_INFO("Failed to create shader module for file: {}", lpacFilename);
    //     return false;
    // }

    return true;
}