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

cTkFileHandle cTkFileSystem::Open(const cTkString &lsFilename, eTkFileMode leFileMode)
{
    cTkFile *lFile = new cTkFile(lsFilename, leFileMode);

    TkSizeType liNewLookup    = this->maFileCache.Size() + 1;
    cTkFileHandle lFileHandle = cTkFileHandle(liNewLookup, leFileMode, false, false, false);

    this->maFileCache.Insert(lFileHandle, lFile);
    this->maFileHandleCache.Insert(lsFilename, lFileHandle);

    TK_INFO("New FH created: {} for file: {}", lFileHandle.muiIndex, lsFilename);

    return lFileHandle;
}

void cTkFileSystem::Close(cTkFileHandle lFileHandle)
{
    cTkFile *lFile = this->Get(lFileHandle);
    if (lFile)
    {
        this->maFileCache.Remove(lFileHandle);

        TkOptional<cTkString> lMapLookup = this->maFileHandleCache.Find(lFileHandle);
        bool lbFound                     = lMapLookup.HasValue();

        TK_ASSERT(lbFound, "File handle not found in cache: {}", lFileHandle.muiHandle);

        if (lbFound) this->maFileHandleCache.Remove(lMapLookup.Value());

        delete lFile;
        lFileHandle.Invalidate();
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