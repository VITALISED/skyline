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

    constexpr TkSTLAllocator<T> &operator=(const TkSTLAllocator<T> &other) { std::allocator<T>::operator=(other); }

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
} // namespace TkSTD