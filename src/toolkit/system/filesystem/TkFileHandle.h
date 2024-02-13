#pragma once

#include <toolkit/core/TkHandle.h>

#define TK_NULLFH cTkFileHandle();

class cTkFile;

typedef uint32_t TkFileLookup;

enum eTkFileMode : uint8_t
{
    ETkFileMode_Default,
    ETkFileMode_Read,
    ETkFileMode_Write,
    ETkFileMode_Append,
    ETkFileMode_ReadWrite  = (ETkFileMode_Read << ETkFileMode_Write),
    ETkFileMode_ReadAppend = (ETkFileMode_Read << ETkFileMode_Append),
};

class TkFileID
{
  public:
    const char *ConvertMode()
    {
        switch (this->meFileOpenMode)
        {
        case ETkFileMode_Read: return "r";
        case ETkFileMode_Write: TK_ASSERT(!this->mbPak, "Cannot open pakfile for writing."); return "w+";
        case ETkFileMode_Append: TK_ASSERT(!this->mbPak, "Cannot open pakfile for writing."); return "a+";
        case ETkFileMode_ReadWrite: TK_ASSERT(!this->mbPak, "Cannot open pakfile for writing."); return "w+";
        case ETkFileMode_ReadAppend: TK_ASSERT(!this->mbPak, "Cannot open pakfile for writing."); return "a+";
        default: return "r";
        }
    }

    union {
        struct
        {
            bool mbValid : 1;
            bool mbPak : 1;
            bool mbBinary : 1;
            bool __muiReserved : 1;
            eTkFileMode meFileOpenMode : 4;
            TkFileLookup muiLookup : 24;
        };
        uint32_t muiValue;
    };
};

typedef cTkHandle<TkFileID, cTkFile> cTkFileHandle;