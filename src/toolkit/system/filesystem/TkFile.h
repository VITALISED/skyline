#pragma once

#include <toolkit/core/TkCore.h>

enum eTkFileSeek : uint8_t
{
    TkFileSeek_Set = SEEK_SET,
    TkFileSeek_Cur = SEEK_CUR,
    TkFileSeek_End = SEEK_END
};

enum eTkFileMode : uint8_t
{
    ETkFileMode_Default,
    ETkFileMode_Read,
    ETkFileMode_Write,
    ETkFileMode_Append,
    ETkFileMode_ReadWrite  = (ETkFileMode_Read << ETkFileMode_Write),
    ETkFileMode_ReadAppend = (ETkFileMode_Read << ETkFileMode_Append),
};

using TkRawFile = std::FILE;

class cTkFile
{
  public:
    cTkFile(cTkString &lsFilename, eTkFileMode leFileMode) { this->Open(lsFilename, leFileMode); };
    ~cTkFile() { this->Close(); };

    void Seek(TkSizeType lOffset, eTkFileSeek leFileSeek) { fseek(mFile, lOffset, leFileSeek); }

    TkSizeType Tell() const { return ftell(mFile); }

    TkSizeType Size()
    {
        this->Seek(0, TkFileSeek_End);
        TkSizeType lSize = this->Tell();
        this->Seek(0, TkFileSeek_Set);
        return lSize;
    }

    TkSizeType Read(void *lpBuffer, TkSizeType lSize, int liNumElements = 1)
    {
        return fread(lpBuffer, lSize, liNumElements, mFile);
    }

    auto operator<=>(const cTkFile &) const = default;

  private:
    void Open(cTkString &lsFilename, eTkFileMode leFileMode);
    void Close();

    TkRawFile *mFile;
};