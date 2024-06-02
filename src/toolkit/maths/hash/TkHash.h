#pragma once

#define FNV_PRIME  0x100000001b3
#define FNV_OFFSET 0xcbf29ce484222325

class cTkHash
{
  public:
    static u64 FNV1A(const void *lpData, u64 luiSize)
    {
        u64 lHash = FNV_OFFSET;
        for (u64 i = 0; i < luiSize; i++)
        {
            lHash ^= static_cast<const u8 *>(lpData)[i];
            lHash *= FNV_PRIME;
        }
        return lHash;
    }
};