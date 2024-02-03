#pragma once

#include <deque>
#include <fstream>
#include <functional>
#include <memory>
#include <span>
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
using SizeType                          = std::size_t;
constexpr inline SizeType DynamicExtent = std::dynamic_extent;

using String = std::basic_string<char, std::char_traits<char>, TkSTLAllocator<char>>;
template <typename T>
using Vector = std::vector<T, TkSTLAllocator<T>>;
template <typename T>
using Deque          = std::deque<T, TkSTLAllocator<T>>;
using OStream        = std::ostream;
namespace Chrono     = std::chrono;
inline auto ToString = [](auto &&lArg) { return std::to_string(std::forward<decltype(lArg)>(lArg)); };
template <typename T>
using Function = std::function<T>;

template <typename T>
using Vector = std::vector<T, TkSTLAllocator<T>>;
template <typename T>
using Hash = std::hash<T>;

template <typename T>
using EqualTo = std::equal_to<T>;

template <typename T1, typename T2>
using Pair = std::pair<T1, T2>;

template <
    class Key, class T, class Hash = Hash<Key>, class KeyEqual = EqualTo<Key>,
    class Allocator = TkSTLAllocator<Pair<const Key, T>>>
using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

using File = std::FILE;

template <class T, SizeType Extent = DynamicExtent>
using Span = std::span<T, Extent>;

template <typename... Args>
TkSTD::String Format(std::_Fmt_string<Args...> format, Args &&...args)
{
    return TkSTD::String(std::format(format, std::forward<Args>(args)...).c_str());
}

} // namespace TkSTD