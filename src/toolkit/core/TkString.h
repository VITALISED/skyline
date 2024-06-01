#pragma once

#include <stringzilla/stringzilla.hpp>
#include <toolkit/core/TkSTD.h>
#include <toolkit/core/TkTypes.h>

template <typename Charset_, typename Allocator = TkSTLAllocator<Charset_>>
class cTkBasicString;

using cTkString     = cTkBasicString<char>;
using cTkWString    = cTkBasicString<wchar_t>;
using cTkStringView = ashvardanian::stringzilla::basic_string_slice<const char>;

template <typename Charset_, typename Allocator>
class cTkBasicString : public ashvardanian::stringzilla::basic_string<Charset_, Allocator>
{
  public:
    using Charset       = Charset_;
    using cTkStringView = ashvardanian::stringzilla::basic_string_slice<typename std::add_const<Charset>::type>;
    using BaseType      = ashvardanian::stringzilla::basic_string<Charset_, Allocator>;
    using ConstPointer  = Charset const *;
    static const TkSizeType NPos = BaseType::npos;

    constexpr cTkBasicString() : BaseType() {}
    cTkBasicString(const char *value) : BaseType(value) {}
    cTkBasicString(const cTkBasicString &other) : BaseType(other) {}
    cTkBasicString(cTkBasicString &&other) noexcept : BaseType(other) {}
    cTkBasicString(const BaseType &other) : BaseType(other) {}
    cTkBasicString(const std::string &other) : BaseType(other) {}
    ~cTkBasicString() = default;

    template <typename... T>
    cTkBasicString &Append(const T &...args)
    {
        return static_cast<cTkBasicString &>(static_cast<BaseType &>(*this).append(args...));
    }

    cTkBasicString &operator+=(cTkStringView other) noexcept(false) { return this->Append(other); }
    cTkBasicString &operator+=(std::initializer_list<Charset> other) noexcept(false) { return this->Append(other); }
    cTkBasicString &operator+=(Charset character) noexcept(false) { return operator+=(cTkStringView(&character, 1)); }
    cTkBasicString &operator+=(ConstPointer other) noexcept(false)
    {
        return operator+=(ashvardanian::stringzilla::string_view(other));
    }

    cTkBasicString operator+(Charset character) const noexcept(false)
    {
        return operator+(ashvardanian::stringzilla::string_view(&character, 1));
    }
    cTkBasicString operator+(ConstPointer other) const noexcept(false) { return operator+(string_view(other)); }
    cTkBasicString operator+(cTkStringView other) const noexcept(false)
    {
        return static_cast<cTkBasicString>(static_cast<BaseType>(*this).operator+(other));
    }
    cTkBasicString operator+(std::initializer_list<Charset> other) const noexcept(false)
    {
        return static_cast<cTkBasicString>(static_cast<BaseType>(*this).operator+(other));
    }

    bool Empty() const { return static_cast<const BaseType &>(*this).empty(); }

    TkSizeType Find(const cTkString &lString) const { return static_cast<const BaseType &>(*this).find(lString); }
    TkSizeType FindLastOf(const cTkString &lString) const
    {
        return static_cast<const BaseType &>(*this).find_last_of(lString);
    }

    cTkString SubStr(TkSizeType lStart, TkSizeType lCount = NPos) const
    {
        return static_cast<BaseType>(*this).substr(lStart, lCount).c_str();
    }

    template <typename T>
    static cTkString ToString(T lValue)
    {
        return std::to_string(lValue);
    }

    template <typename... Args>
    static cTkString Format(const cTkString lFormat, Args... lArgs)
    {
        std::string_view lTempString = std::string_view(lFormat.c_str());
        std::format_args lFmtArgs    = std::make_format_args(lArgs...);
        std::string lFmtResult       = std::vformat(lTempString, lFmtArgs);
        return cTkString(lFmtResult.c_str());
    }

    cTkString &operator=(const cTkString &other)
    {
        static_cast<BaseType &>(*this) = other;
        return *this;
    }

    class Hash
    {
      public:
        TkSizeType operator()(const cTkString &lString) const { return static_cast<const BaseType &>(lString).hash(); }
    };
};

constexpr cTkStringView operator""_sz(char const *str, TkSizeType length) noexcept
{
    return {str, length};
}

template <>
struct std::formatter<cTkString>
{
    auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
    auto format(const cTkString &lString, std::format_context &ctx)
    {
        return std::format_to(ctx.out(), "{}", lString.c_str());
    }
};