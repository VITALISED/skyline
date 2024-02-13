#include <toolkit/system/TkSystem.h>
#include <toolkit/system/filesystem/TkFileHandle.h>

cTkFileHandle FactoryFunc(eTkFileMode leFileMode)
{
    return cTkFileHandle();
}

cTkFileHandle::InnerType *cTkFileHandle::Get()
{
    cTkFile *lResult = cTkSystem::GetInstance().mpFilesystem->GetFile(*this);
    return lResult;
}