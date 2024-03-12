#pragma once

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