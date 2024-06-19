#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/maths/hash/TkHash.h>
#include <toolkit/system/filesystem/TkFile.h>

class cTkFileHandle : public ITkHandle<cTkFile>
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

    virtual InnerType *Get() final;
    virtual u64 Value() final { return this->muiHandle; };
    virtual bool IsValid() const final { return this->muiHandle != TK_NULL; };
    virtual void Invalidate() final { this->muiHandle = TK_NULL; };
    virtual TkSizeType Hash() const final { return cTkHash::FNV1A(this->muiHandle); };

    bool IsBinary() { return this->mbBinary; }
    bool IsPak() { return this->mbPak; }
    u32 GetIncrementor() { return this->muiIndex; }
    eTkFileMode GetFileMode() { return this->meFileMode; }

    TkStrongOrdering operator<=>(const cTkFileHandle &) const = default;
    bool operator==(const cTkFileHandle &lOther) const { return this->muiHandle == lOther.muiHandle; }

  private:
    union {
        u64 muiHandle;
        struct
        {
            bool mbBinary : 1;
            bool mbPak : 1;
            bool mbCompressed : 1;
            u32 _muiReserved : 29;
            eTkFileMode meFileMode : 4;
            u32 muiIndex : 32;
        };
    };
};

TK_STL_HASH(cTkFileHandle, (const cTkFileHandle &val) const noexcept { return val.Hash(); });