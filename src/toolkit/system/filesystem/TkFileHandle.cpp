#include <toolkit/system/TkSystem.h>
#include <toolkit/system/filesystem/TkFileHandle.h>

cTkFile *cTkFileHandle::Get()
{
    cTkFileSystem *lFS = cTkSystem::GetInstance().mpFilesystem;
    return lFS->Get(*this);
}