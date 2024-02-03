#pragma once

#include <toolkit/core/TkCore.h>

class cTkFilesystem
{
  public:
    struct CachedFile
    {
        TkSTD::File *lpFile;
        const char *lsFilename;
    };

    void Construct();
    void Destruct();

    inline cTkFileHandle CreateHandle(uint32_t luiIncrement)
    {
        cTkFileHandle lHandle;
        lHandle.mID.IsCached     = true;
        lHandle.mID.IsCompressed = false;
        lHandle.mID.IsReadOnly   = false;
        lHandle.mID.muiLookup    = luiIncrement;
        return lHandle;
    }

    cTkFileHandle Open(const char *lpacFilename, const char *lpacMode);
    void Close(cTkFileHandle lFileHandle);

    TkSTD::UnorderedMap<int, TkSTD::File *> maFiles;
    TkSTD::UnorderedMap<const char *, int> maCachedFilenames;
};