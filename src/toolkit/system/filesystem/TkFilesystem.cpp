#include <toolkit/system/filesystem/TkFilesystem.h>

void cTkFilesystem::Construct()
{
    this->maFiles           = TkSTD::UnorderedMap<int, TkSTD::File *>();
    this->maCachedFilenames = TkSTD::UnorderedMap<const char *, int>();
}

void cTkFilesystem::Destruct()
{
    for (auto &lFile : this->maFiles) { fclose(lFile.second); }
}

cTkFileHandle cTkFilesystem::Open(const char *lpacFilename, const char *lpacMode)
{
    int liIncrement = 0;

    if (this->maCachedFilenames.find(lpacFilename) != this->maCachedFilenames.end())
    {
        liIncrement = this->maCachedFilenames[lpacFilename];
    }

    if (liIncrement) { return this->CreateHandle(liIncrement); }

    liIncrement = this->maFiles.size() + 1;

    TkSTD::File *lFile = fopen(lpacFilename, lpacMode);

#ifdef D_DEBUG
    TkSTD::String lAssertMessage = TkSTD::Format("File could not be opened. (Is the path correct?) {}", lpacFilename);
    TK_ASSERT(lFile != NULL, lAssertMessage);
#endif

    this->maFiles.insert({liIncrement, lFile});
    this->maCachedFilenames.insert({lpacFilename, liIncrement});

    return this->CreateHandle(liIncrement);
}

void cTkFilesystem::Close(cTkFileHandle lFileHandle)
{
    TK_ASSERT(this->maFiles[lFileHandle.mID.muiLookup] != NULL, "File handle is invalid.");

    fclose(this->maFiles[lFileHandle.mID.muiLookup]);
    this->maFiles.erase(lFileHandle.mID.muiLookup);

    for (auto &lFile : this->maCachedFilenames)
    {
        if (lFile.second == lFileHandle.mID.muiLookup)
        {
            this->maCachedFilenames.erase(lFile.first);
            break;
        }
    }
}