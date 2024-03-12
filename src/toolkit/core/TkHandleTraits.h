#pragma once

template <typename T>
class cTkHandleHash
{
  public:
    using HandleType = T;
    uint64_t operator()(const HandleType &lHandle) const { return lHandle.CalculateHash(); }
};