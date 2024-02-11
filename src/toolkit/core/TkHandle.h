#pragma once

#include <toolkit/core/TkSTD.h>

template <typename T, typename R>
class cTkHandle
{
  public:
    using HandleIDType = T;
    using InnerType    = R;

    InnerType &Get();
    void Set(InnerType &lFile);
    bool IsValid() const { return reinterpret_cast<uint64_t>(this->mID) != TK_NULL; }

    InnerType &operator*() { return this->Get(); }
    InnerType *operator->() { return &this->Get(); }

    HandleIDType mID;
};