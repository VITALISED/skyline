#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/memory/allocators/TkSTLAllocator.h>

#include <unordered_map>

template <
    class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>,
    class Allocator = TkSTLAllocator<std::pair<const Key, T>>>
class cTkUnorderedMap : public std::unordered_map<Key, T, Hash, KeyEqual, Allocator>
{
  public:
#pragma region Re-Exports
    using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::unordered_map;

    using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::operator=;
    using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::operator[];

    using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::begin;
    using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::end;
    using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::cbegin;
    using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::cend;
#pragma endregion

    void Insert(const Key &lKey, const T &lValue) { this->insert(std::make_pair(lKey, lValue)); }
    void Remove(const Key &lKey) { this->erase(lKey); }
    TkSizeType Size() const { return this->size(); }
    bool Contains(const Key &lKey) { return this->contains(lKey); }
    TkOptional<T> Find(const Key &lKey)
    {
        TkOptional<T> result = TkOptional<T>();

        auto search = this->find(lKey);

        if (search != this->end()) result = TkOptional<T>(search->first);

        return result;
    }
};