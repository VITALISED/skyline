#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/memory/allocators/TkSTLAllocator.h>

#include <vector>

template <typename T, class Allocator = TkSTLAllocator<T>>
class cTkVector : protected std::vector<T, Allocator>
{
  public:
#pragma region Re-Exports
    using std::vector<T, Allocator>::vector;
    using std::vector<T, Allocator>::operator=;
    using std::vector<T, Allocator>::operator[];

    using std::vector<T, Allocator>::begin;
    using std::vector<T, Allocator>::end;
#pragma endregion

    constexpr void PushBack(const T &lValue) { return this->push_back(lValue); }
    constexpr void PushBack(T &&lValue) { return this->push_back(lValue); }
};

// TODO: Macro this later for other STL containers, or just simplify
template <class _Ty, class _Alloc>
constexpr decltype((std::_Synth_three_way{}(std::declval<_Ty &>(), std::declval<_Ty &>()))) operator<=>(
    const cTkVector<_Ty, _Alloc> &_Left, const cTkVector<_Ty, _Alloc> &_Right)
{
    return std::operator<=>(
        reinterpret_cast<const std::vector<_Ty, _Alloc> &>(_Left),
        reinterpret_cast<const std::vector<_Ty, _Alloc> &>(_Right));
}
