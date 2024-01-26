#pragma once

#include <toolkit/core/TkSTD.h>

template <uint32_t Size, typename CharSet>
class cTkFixedString
{
  public:
    cTkFixedString() = default;
    cTkFixedString(const char *lpacBuffer) { this->Copy(lpacBuffer); }
    void Copy(const char *lpacBuffer) { strcpy_s(macBuffer, Size, lpacBuffer); }

    CharSet macBuffer[Size];
};