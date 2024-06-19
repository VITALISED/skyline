#include <toolkit/system/filesystem/TkFile.h>

void cTkFile::Open(const cTkString &lsFilename, eTkFileMode leFileMode)
{
    this->msFileName = lsFilename;

    bool lbExists = cTkFile::Exists(this->msFileName);

    TK_ASSERT(lbExists, "File does not exist, or might be a directory: {}", this->msFileName);

    if (lbExists)
    {
        const cTkString lsBuiltFileMode = cTkFile::ConvertMode(leFileMode);

        this->mpFile = fopen(this->msFileName.c_str(), lsBuiltFileMode.c_str());

        TK_DEBUG("Opened file: {} which was 0x{:X} bytes", this->msFileName, this->Size());
    }
}

void cTkFile::Close()
{
    if (this->mpFile) fclose(this->mpFile);
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