#pragma once

#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <chrono>

template <typename T>
class TkSTLAllocator : public std::allocator<T>
{
  public:
    TkSTLAllocator() noexcept : std::allocator<T>() {}
    TkSTLAllocator(const TkSTLAllocator &other) noexcept : std::allocator<T>(other) {}
    TkSTLAllocator(TkSTLAllocator &&other) noexcept : std::allocator<T>(std::move(other)) {}
    template <typename U>
    TkSTLAllocator(const TkSTLAllocator<U> &other) noexcept : std::allocator<T>(other)
    {}

    constexpr TkSTLAllocator<T> &operator=(const TkSTLAllocator<T> &other)
    {
        std::allocator<T>::operator=(other);
        return *this;
    }

    template <typename U>
    struct rebind
    {
        using other = TkSTLAllocator<U>;
    };

    using std::allocator<T>::allocator;
};

namespace TkSTD
{

using String = std::basic_string<char, std::char_traits<char>, TkSTLAllocator<char>>;

template <typename T>
using Vector         = std::vector<T, TkSTLAllocator<T>>;
using OStream        = std::ostream;
namespace Chrono     = std::chrono;
inline auto ToString = [](auto &&lArg) { return std::to_string(std::forward<decltype(lArg)>(lArg)); };
template <typename T>
using Function = std::function<T>;

template <typename T>
using Vector = std::vector<T, TkSTLAllocator<T>>;

template <typename... Args>
auto Format(std::_Fmt_string<Args...> format, Args &&...args)
{
    return std::format(format, std::forward<Args>(args)...);
}

} // namespace TkSTD

template <>
struct std::formatter<TkSTD::String, char>
{
    template <class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext &ctx)
    {
        return std::formatter<std::string, char>::parse(ctx);
    }

    template <class FmtContext>
    FmtContext::iterator format(const TkSTD::String &str, FmtContext &ctx) const
    {
        std::string stdStr(str.begin(), str.end());
        return std::formatter<std::string, char>::format(stdStr, ctx);
    }
};