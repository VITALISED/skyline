#include <toolkit/system/TkSystem.h>
#include <toolkit/system/filesystem/TkFile.h>

cTkFile &cTkFileHandle::Get()
{
    cTkSystem &gSystem = cTkSystem::GetInstance();
    gSystem.mpFilesystem->maFiles[mID.muiLookup];
}

void cTkFile::Read(void *lpData, TkSizeType liSize, int liCount)
{
    if (this->mxFlags.mbPak)
    {
        TK_ERROR("Loading from a pak file is not supported yet.");
        return;
    }

    int liResult = fread(lpData, liSize, liCount, mpFile);
    TK_DEBUG(TkSTD::Format("Read {} bytes from file.", liResult));
}