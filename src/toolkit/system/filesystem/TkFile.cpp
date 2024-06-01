#include <toolkit/system/filesystem/TkFile.h>

void cTkFile::Open(const cTkString &lsFilename, eTkFileMode leFileMode)
{
    bool lbExists = cTkFile::Exists(lsFilename);

    TK_ASSERT(lbExists, "File does not exist, or might be a directory: {}", lsFilename);

    if (lbExists)
    {
        const cTkString lsBuiltFileMode = cTkFile::ConvertMode(leFileMode);

        this->mpFile = fopen(lsFilename.c_str(), lsBuiltFileMode.c_str());

        TK_INFO("Opened file: {} which was 0x{:X} bytes", lsFilename, this->Size());
    }
}

void cTkFile::Close()
{
    if (this->mpFile) { fclose(this->mpFile); }
}

cTkString cTkFile::ReadText(TkSizeType liLength)
{
    char *lpacBuffer        = new char[liLength + 1];
    TkSizeType liBytesRead  = Read(lpacBuffer, 1, liLength);
    lpacBuffer[liBytesRead] = '\0';
    cTkString result(lpacBuffer);
    delete[] lpacBuffer;
    return result;
}