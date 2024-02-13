#pragma once

#include <toolkit/core/TkSTD.h>
#include <toolkit/maths/hash/TkHash.h>

template <typename T, typename R>
class cTkHandle
{
  public:
    using HandleIDType = T;
    using InnerType    = R;

    InnerType *Get();
    void Set(InnerType &lFile);
    bool IsValid() const { return reinterpret_cast<uint64_t>(this->mID) != TK_NULL; }

    uint64_t CalculateHash() const { return cTkHash::FNV1A(mID, sizeof(mID)); }

    InnerType &operator*() { return *this->Get(); }
    InnerType *operator->() { return this->Get(); }

    template <typename... Args>
    static cTkHandle FactoryFunc(Args &&...args);

    class Hash
    {
      public:
        uint64_t operator()(const cTkHandle &lHandle) const { return lHandle.CalculateHash(); }
    };

    HandleIDType mID;
};