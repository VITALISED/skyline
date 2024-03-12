#pragma once

#include <stringzilla/stringzilla.hpp>
#include <toolkit/core/TkSTD.h>
#include <toolkit/core/TkTypes.h>

class cTkString : public ashvardanian::stringzilla::basic_string<char, TkSTLAllocator<char>>
{
  public:
    using BaseType = ashvardanian::stringzilla::basic_string<char, TkSTLAllocator<char>>;

    cTkString() : BaseType() {}
    cTkString(const char *value) : BaseType(value) {}
    cTkString(const cTkString &other) : BaseType(other) {}
    cTkString(cTkString &&other) noexcept : BaseType(other) {}
    ~cTkString() = default;

    template <typename... T>
    cTkString &Append(const T &...args)
    {
        return static_cast<cTkString &>(static_cast<BaseType &>(*this).append(args...));
    }

    bool Empty() { return static_cast<BaseType &>(*this).empty(); }

    template <typename T>
    static cTkString ToString(T lValue)
    {
        return cTkString(std::to_string(lValue).c_str());
    }

    template <typename... Args>
    static cTkString Format(cTkString &lFormat, Args... lArgs)
    {
        std::string_view lTempString = std::string_view(lFormat.c_str());
        std::format_args lFmtArgs    = std::make_format_args(lArgs...);
        std::string lFmtResult       = std::vformat(lTempString, lFmtArgs);
        return cTkString(lFmtResult.c_str());
    }

    bool operator==(const cTkString &other) const { return static_cast<const BaseType &>(*this) == other; }
    bool operator!=(const cTkString &other) const { return static_cast<const BaseType &>(*this) != other; }
    bool operator<(const cTkString &other) const { return static_cast<const BaseType &>(*this) < other; }
    bool operator>(const cTkString &other) const { return static_cast<const BaseType &>(*this) > other; }
    bool operator<=(const cTkString &other) const { return static_cast<const BaseType &>(*this) <= other; }
    bool operator>=(const cTkString &other) const { return static_cast<const BaseType &>(*this) >= other; }

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

template <>
struct std::formatter<cTkString>
{
    auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
    auto format(const cTkString &lString, std::format_context &ctx)
    {
        return std::format_to(ctx.out(), "{}", lString.c_str());
    }
};