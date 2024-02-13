#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/system/filesystem/TkFile.h>
#include <toolkit/system/filesystem/TkFileHandleMap.h>

class cTkFilesystem
{
  public:
    void Construct();
    void Destruct();

    cTkFileHandle Open(const char *lpacFilename, const char *lpacMode);
    void Close(cTkFile *lpFile);
    cTkFileHandle GetFHandle(cTkID lID);
    cTkFile *GetFile(cTkFileHandle lFileHandle) { return this->GetFile(lFileHandle.mID.muiLookup); }
    cTkFile *GetFile(const TkFileLookup &lacLookup);
    void SetWorkingDirectory(const char *lpacDirectory);

    cTkFileHandleMap maFiles;
    cTkIDMap<cTkFileHandle> maCachedFilenames;
};