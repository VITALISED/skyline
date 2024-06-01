#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/maths/hash/TkHash.h>
#include <toolkit/system/filesystem/TkFile.h>

class cTkFileHandle
{
  public:
    using InnerType = cTkFile;

    cTkFileHandle() = default;
    cTkFileHandle(uint32_t muiIncrementor, eTkFileMode leFileMode, bool lbBinary, bool lbPak, bool lbCompressed)
    {
        this->muiIndex     = muiIncrementor;
        this->mbBinary     = lbBinary;
        this->mbPak        = lbPak;
        this->mbCompressed = lbCompressed;
        this->meFileMode   = leFileMode;
    }
    cTkFileHandle(const cTkFileHandle &lFileHandle) { this->muiHandle = lFileHandle.muiHandle; }

    InnerType *Get();
    bool IsValid() const { return this->muiHandle != 0; }
    void Invalidate() { this->muiHandle = 0; }

    InnerType &operator*() { return *this->Get(); }
    InnerType *operator->() { return this->Get(); }

    friend bool operator!=(const cTkFileHandle &lHandle, const cTkFileHandle &lOther)
    {
        return lHandle.muiHandle != lOther.muiHandle;
    }

    friend bool operator==(const cTkFileHandle &lHandle, const cTkFileHandle &lOther)
    {
        return lHandle.muiHandle == lOther.muiHandle;
    }

    auto operator<=>(const cTkFileHandle &) const = default;

    uint64_t CalculateHash() const { return cTkHash::FNV1A(&muiHandle, sizeof(muiHandle)); }

    union {
        uint64_t muiHandle;
        struct
        {
            bool mbBinary : 1;
            bool mbPak : 1;
            bool mbCompressed : 1;
            uint32_t _muiReserved : 29;
            eTkFileMode meFileMode : 4;
            uint32_t muiIndex : 32;
        };
    };
};
