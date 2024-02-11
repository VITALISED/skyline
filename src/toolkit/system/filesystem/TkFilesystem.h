#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/system/filesystem/TkFile.h>

class cTkFilesystem
{
  public:
    void Construct();
    void Destruct();

    inline cTkFileHandle CreateHandle(uint32_t luiIncrement)
    {
        cTkFileHandle lHandle;
        lHandle.mID.mbCached     = true;
        lHandle.mID.mbCompressed = false;
        lHandle.mID.mbReadOnly   = false;
        lHandle.mID.muiLookup    = luiIncrement;
        return lHandle;
    }

    cTkFileHandle Open(const char *lpacFilename, const char *lpacMode);
    void Close(cTkFileHandle lFileHandle);
    void SetWorkingDirectory(const char *lpacDirectory);

    TkSTD::UnorderedMap<uint32_t, TkSTD::File *> maFiles;
    TkSTD::UnorderedMap<const char *, uint32_t> maCachedFilenames;
};