#pragma once

#include <toolkit/core/TkCore.h>

#define TK_NULLFH cTkFileHandle();

struct TkFileID
{
    union {
        struct
        {
            bool mbCompressed : 1;
            bool mbCached : 1;
            bool mbReadOnly : 1;
            bool mbValid : 1;
            bool mbPak : 1;
            uint32_t _Reserved : 3;
            uint32_t muiLookup : 24;
        };
        uint32_t muiValue;
    };
};

class cTkFile
{
  public:
    void Read(void *lpData, TkSizeType liSize, int liCount);
    void Write(const void *lpData, TkSizeType liSize, int liCount);
    void Seek(TkSizeType liOffset, int liOrigin);

    TkSTD::File *mpFile;
    TkFileID mxFlags;
    TkSizeType miSize;
};

typedef cTkHandle<TkFileID, cTkFile> cTkFileHandle;