#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/system/filesystem/TkFile.h>
#include <toolkit/system/filesystem/TkFileHandle.h>

class cTkFileSystem
{
  public:
    using TkFileHandleMap = cTkUnorderedMap<cTkString, cTkFileHandle, cTkString::Hash>;
    using TkFileCacheMap  = cTkUnorderedMap<cTkFileHandle, cTkFile *, cTkHandleHash<cTkFileHandle>>;

    cTkFileSystem() { this->Construct(); };
    ~cTkFileSystem() { this->Destruct(); };

    void Construct();
    void Destruct();

    void SetWorkingDirectory(const char *lpacDirectory);

    cTkFileHandle Open(const cTkString &lsFilename, eTkFileMode leFileMode);
    void Close(cTkFileHandle lFileHandle);
    cTkFileHandle Lookup(const cTkString &lFileHandleID);
    cTkFile *Get(cTkFileHandle lFileHandle)
    {
        if (lFileHandle.IsValid()) return maFileCache[lFileHandle];

        return TK_NULL;
    }

    TkFileHandleMap maFileHandleCache;
    TkFileCacheMap maFileCache;
};