#include <toolkit/system/TkSystem.h>

TkSTD::File *cTkFile::Open()
{
    const char *lpacMode = this->mxFlags.ConvertMode();

    if (this->mxFlags.mbPak)
    {
        TK_ERROR("Loading from a pak file is not supported yet.");
        return TK_NULL;
    }

    TkSTD::File *lpFile = fopen(this->mpacFileName->macBuffer, lpacMode);
    if (!lpFile)
    {
        TK_ERROR(TkSTD::Format("Failed to open file: {}", this->mpacFileName->macBuffer));
        return TK_NULL;
    }

    fseek(lpFile, 0, SEEK_END);
    this->miSize = ftell(lpFile);
    fseek(lpFile, 0, SEEK_SET);

    TK_DEBUG(TkSTD::Format("Opened file: {} ({} bytes)", this->mpacFileName->macBuffer, this->miSize));

    return lpFile;
}

void cTkFile::Read(void *lpData, TkSizeType liSize, int liCount)
{
    if (this->mxFlags.mbPak)
    {
        TK_ERROR("Loading from a pak file is not supported yet.");
        return;
    }

    int liResult = fread(lpData, liSize, liCount, mpFile);
    TK_DEBUG(TkSTD::Format("Read {} bytes from file.", liResult));
}

void cTkFile::Write(const void *lpData, TkSizeType liSize, int liCount)
{
    if (this->mxFlags.mbPak)
    {
        TK_ERROR("Cannot write to a pak file.");
        return;
    }

    int liResult = fwrite(lpData, liSize, liCount, mpFile);
    TK_DEBUG(TkSTD::Format("Wrote {} bytes to file.", liResult));
}

void cTkFile::Close()
{
    if (this->mpFile)
    {
        fclose(this->mpFile);
        this->mpFile = TK_NULL;
    }
}