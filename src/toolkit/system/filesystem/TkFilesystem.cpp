#include <toolkit/system/filesystem/TkFilesystem.h>

void cTkFilesystem::Construct() {}

void cTkFilesystem::Destruct() {}

cTkFileHandle cTkFilesystem::Open(const char *lpacFilename, const char *lpacMode)
{
    return cTkFileHandle();
}

void cTkFilesystem::Close(cTkFile *lpFile) {}

cTkFile *cTkFilesystem::GetFile(const TkFileLookup &lacLookup)
{
    return TK_NULL;
}

void cTkFilesystem::SetWorkingDirectory(const char *lpacDirectory)
{
#ifdef D_MSVC
    int liResult = _chdir(lpacDirectory);
#else
    int liResult = chdir(lpacDirectory);
#endif

    TK_ASSERT(liResult == 0, TkSTD::Format("Could not change working directory: {}", strerror(liResult)));
}