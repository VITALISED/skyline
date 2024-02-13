#pragma once

#define FNV_PRIME  0x100000001b3
#define FNV_OFFSET 0xcbf29ce484222325

class cTkHash
{
  public:
    static uint64_t FNV1A(const void *lpData, uint64_t luiSize)
    {
        uint64_t lHash = FNV_OFFSET;
        for (size_t i = 0; i < luiSize; i++)
        {
            lHash ^= static_cast<const uint8_t *>(lpData)[i];
            lHash *= FNV_PRIME;
        }
        return lHash;
    }
};