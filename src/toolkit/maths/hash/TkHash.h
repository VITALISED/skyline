#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/core/string/TkString.h>

#define FNV_PRIME  0x100000001b3
#define FNV_OFFEST 0xcbf29ce484222325

class cTkHash
{
  public:
    template <typename T>
    constexpr static TkSizeType FNV1A(const T &lData) noexcept
    {
        TK_STATIC_ASSERT(TkIsSameV<T, cTkStringView> || TkIsIntegralV<T>);

        TkSizeType result = FNV_OFFEST;

        if constexpr (TkIsIntegralV<T>)
        {
            const u8 *lPtr = reinterpret_cast<const u8 *>(&lData);
            for (TkSizeType i = 0; i < sizeof(T); ++i)
            {
                result ^= static_cast<u64>(lPtr[i]);
                result *= FNV_PRIME;
            }
            return result;
        }
        else if constexpr (TkIsSameV<T, cTkStringView>)
        {
            for (char lChar : lData)
            {
                result ^= static_cast<u64>(lChar);
                result *= FNV_PRIME;
            }
            return result;
        }
    }
};