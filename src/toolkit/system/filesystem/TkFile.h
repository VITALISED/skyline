#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/system/filesystem/TkFileHandle.h>

class cTkFile
{
  public:
    cTkFile(const char *lpacFileName, TkFileID lxFlags, const char *lpacMode)
    {
        this->mxFlags      = lxFlags;
        this->mpFile       = this->Open();
        this->mpacFileName = new cTkFixedString<64, char>(lpacFileName);
    }

    ~cTkFile()
    {
        if (this->mpFile) { this->Close(); }

        delete mpacFileName;
    }

    TkSTD::File *Open();
    void Read(void *lpData, TkSizeType liSize, int liCount);
    void Write(const void *lpData, TkSizeType liSize, int liCount);
    void Seek(TkSizeType liOffset, int liOrigin) { fseek(this->mpFile, liOffset, liOrigin); }
    void Close();

    static cTkFileHandle HandleFactory();

    TkSTD::File *mpFile;
    TkFileID mxFlags;
    TkSizeType miSize;
    cTkFixedString<64, char> *mpacFileName;
};
