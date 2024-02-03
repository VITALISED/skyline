#pragma once
#include <toolkit/core/TkCore.h>

class cTkVPAK
{
  public:
    void Construct();
    void Destruct();

    struct Header
    {
        cTkFixedString<4, char> macMagic = {"VPAK"};
        uint8_t muiVersion;
        cTkFixedString<256, char> macFolderPath;
        cTkFixedString<256, char> macFileName;
        uint32_t muiFileCount;
    };

    struct FileEntry
    {
        cTkFixedString<256, char> macFileName;
        uint32_t muiFileOffset;
        uint32_t muiFileSize;
    };
};