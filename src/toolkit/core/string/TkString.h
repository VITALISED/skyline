#pragma once

#include <toolkit/core/string/TkBasicString.h>

#include <format>

#pragma region String

using cTkString = cTkBasicString<char>;

TK_STL_HASH(cTkString, (const cTkString &val) const noexcept { return val.Hash(); });

inline cTkString operator""_s(const char *_Str, size_t _Len)
{
    return cTkString{_Str, _Len};
}

#pragma endregion

#pragma region String View

using cTkStringView = ashvardanian::stringzilla::basic_string_slice<char const>;

constexpr cTkStringView operator""_sv(char const *str, TkSizeType length) noexcept
{
    return cTkStringView{str, length};
}

#pragma endregion

template <>
struct std::formatter<cTkString>
{
    auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
    auto format(const cTkString &lString, std::format_context &ctx)
    {
        return std::format_to(ctx.out(), "{}", lString.c_str());
    }
};