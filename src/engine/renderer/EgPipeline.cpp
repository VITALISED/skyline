#include <engine/renderer/EgPipeline.h>

bool cEgPipeline::LoadShaderModule(const char *lpacFilename)
{
    cTkFilesystem *gpFileSystem = cTkSystem::GetInstance().mpFilesystem;
    cTkFileHandle lFH           = gpFileSystem->Open(lpacFilename, "rb");

    // TK_ASSERT(lFH.IsValid(), "Invalid FH");

    TkSTD::Vector<uint32_t> lBuffer;
    uint32_t luiSize;
    uint32_t luiCount;

    // TkSTD::SizeType gpFileSystem->Read(lFileHandle, static_cast<void *>(lBuffer.data()), luiSize, luiCount);

    return true;
}