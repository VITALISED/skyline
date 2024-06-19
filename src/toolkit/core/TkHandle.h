#pragma once

#include <toolkit/core/TkTypes.h>

template <typename InnerType>
class ITkHandle
{
  public:
    virtual InnerType *Get()        = 0;
    virtual u64 Value()             = 0;
    virtual bool IsValid() const    = 0;
    virtual void Invalidate()       = 0;
    virtual TkSizeType Hash() const = 0;

    InnerType &operator*() { return *this->Get(); }
    InnerType *operator->() { return this->Get(); }
};