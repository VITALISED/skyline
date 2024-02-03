#pragma once

#include <toolkit/core/TkSTD.h>

struct TkNodeID
{
    uint32_t miValue;
};

struct TkFileID
{

    union {
        struct
        {
            bool IsCompressed : 1;
            bool IsCached : 1;
            bool IsReadOnly : 1;
            bool _Reserved : 5;
            uint32_t muiLookup : 24;
        };
        uint32_t muiValue;
    };
};

struct TkResourceID
{
    uint32_t miValue;
};

template <typename T>
class cTkHandle
{
  public:
    using HandleType = T;
    HandleType mID;
};