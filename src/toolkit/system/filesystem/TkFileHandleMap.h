#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/system/filesystem/TkFileHandle.h>

class cTkFileHandleMap
{
  public:
    using Iterator      = TkSTD::UnorderedMap<TkFileLookup, cTkFile *, cTkFileHandle::Hash>::iterator;
    using ConstIterator = TkSTD::UnorderedMap<TkFileLookup, cTkFile *, cTkFileHandle::Hash>::const_iterator;

    void Add(const TkFileLookup &lacLookup, cTkFile *lpFile);
    void Remove(const TkFileLookup &lacLookup);
    cTkFile *Find(const TkFileLookup &lacLookup);

    Iterator begin() { return mpaMap->begin(); }
    Iterator end() { return mpaMap->end(); }
    ConstIterator begin() const { return mpaMap->begin(); }
    ConstIterator end() const { return mpaMap->end(); }

  private:
    TkSTD::UnorderedMap<TkFileLookup, cTkFile *, cTkFileHandle::Hash> *mpaMap;
};