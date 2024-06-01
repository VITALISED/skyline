#pragma once

#include <toolkit/core/TkCore.h>

enum eTkFileSeek : uint8_t
{
    ETkFileSeek_Set = SEEK_SET,
    ETkFileSeek_Cur = SEEK_CUR,
    ETkFileSeek_End = SEEK_END
};

enum eTkFileMode : uint8_t
{
    ETkFileMode_Default,
    ETkFileMode_Read,
    ETkFileMode_Write,
    ETkFileMode_Append,
    ETkFileMode_ReadExt,
    ETkFileMode_AppendExt,
    ETkFileMode_WriteExt,
};

using TkRawFile = std::FILE;

class cTkFile
{
  public:
    cTkFile(const cTkString &lsFilename, eTkFileMode leFileMode) { this->Open(lsFilename, leFileMode); };
    ~cTkFile() { this->Close(); };

    void Seek(TkSizeType lOffset, eTkFileSeek leFileSeek) { fseek(mpFile, lOffset, leFileSeek); }

    TkSizeType Tell() const { return ftell(mpFile); }

    TkSizeType Size()
    {
        TkSizeType lCurrentPos = this->Tell();
        this->Seek(0, ETkFileSeek_End);
        TkSizeType lSize = this->Tell();
        this->Seek(lCurrentPos, ETkFileSeek_Set);
        return lSize;
    }

    TkSizeType Read(void *lpBuffer, TkSizeType lSize, int liNumElements)
    {
        return fread(lpBuffer, lSize, liNumElements, mpFile);
    }

    static bool Exists(const cTkString &lsFilename)
    {
        return std::filesystem::exists(std::filesystem::path(lsFilename.c_str()));
    }

    cTkString ReadText(TkSizeType liLength);

    auto operator<=>(const cTkFile &) const = default;

  private:
    void Open(const cTkString &lsFilename, eTkFileMode leFileMode);
    void Close();
    static const cTkString ConvertMode(eTkFileMode leFileMode)
    {
        cTkString lsBuiltFileMode;

        switch (leFileMode)
        {
        case ETkFileMode_Read: lsBuiltFileMode = "r"; break;
        case ETkFileMode_Write: lsBuiltFileMode = "w"; break;
        case ETkFileMode_Append: lsBuiltFileMode = "a"; break;
        case ETkFileMode_ReadExt: lsBuiltFileMode = "r+"; break;
        case ETkFileMode_AppendExt: lsBuiltFileMode = "a+"; break;
        case ETkFileMode_WriteExt: lsBuiltFileMode = "w+"; break;
        case ETkFileMode_Default:
        default: lsBuiltFileMode = "r"; break;
        }

        return lsBuiltFileMode;
    }

    TkRawFile *mpFile;
};