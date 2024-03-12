#pragma once

#include <toolkit/core/TkSTD.h>
#include <toolkit/core/TkTypes.h>

#include <unordered_map>
#include <utility>

template <
    class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>,
    class Allocator = TkSTLAllocator<std::pair<const Key, T>>>
class cTkUnorderedMap : public std::unordered_map<Key, T, Hash, KeyEqual, Allocator>
{
  public:
    cTkUnorderedMap() : std::unordered_map<Key, T, Hash, KeyEqual, Allocator>() {}
    cTkUnorderedMap(const cTkUnorderedMap &lOther) : std::unordered_map<Key, T, Hash, KeyEqual, Allocator>(lOther) {}
    cTkUnorderedMap(cTkUnorderedMap &&lOther) : std::unordered_map<Key, T, Hash, KeyEqual, Allocator>(std::move(lOther))
    {}

    cTkUnorderedMap &operator=(const cTkUnorderedMap &lOther)
    {
        std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::operator=(lOther);
        return *this;
    }

    void Insert(const Key &lKey, const T &lValue) { this->insert(std::make_pair(lKey, lValue)); }
    void Remove(const Key &lKey) { this->erase(lKey); }
    TkSizeType Size() const { return this->size(); }
    const Key &Find(const T &lValue)
    {
        for (auto &lPair : *this)
        {
            if (lPair.second == lValue) { return lPair.first; }
        }
        return TK_NULL;
    }
};