#include <toolkit/system/filesystem/TkFileSystem.h>

void cTkFileSystem::Construct()
{
    this->maFileCache       = cTkFileSystem::TkFileCacheMap();
    this->maFileHandleCache = cTkFileSystem::TkFileHandleMap();
}

void cTkFileSystem::Destruct()
{
    for (auto &lFile : this->maFileCache) { delete lFile.second; }
}

cTkFileHandle cTkFileSystem::Open(cTkString &lsFilename, eTkFileMode leFileMode)
{
    cTkFile *lFile = new cTkFile(lsFilename, leFileMode);

    TkSizeType liNewLookup    = this->maFileCache.Size() + 1;
    cTkFileHandle lFileHandle = cTkFileHandle(liNewLookup, leFileMode, false, false, false);

    this->maFileCache.Insert(lFileHandle, lFile);
    this->maFileHandleCache.Insert(lsFilename, lFileHandle);

    return lFileHandle;
}

void cTkFileSystem::Close(cTkFileHandle lFileHandle)
{
    auto lFile = this->Get(lFileHandle);
    if (lFile)
    {
        this->maFileCache.Remove(lFileHandle);

        cTkString lFileHandleID = this->maFileHandleCache.Find(lFileHandle);

        if (!lFileHandleID.Empty()) this->maFileHandleCache.Remove(lFileHandleID);
        delete lFile;
    }
}

void cTkFileSystem::SetWorkingDirectory(const char *lpacDirectory)
{
    TK_DEBUG("Setting working directory to: {}", lpacDirectory);

#ifdef D_MSVC
    _chdir(lpacDirectory);
#else
    chdir(lpacDirectory);
#endif
}