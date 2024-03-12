#pragma once

#include <toolkit/core/TkID.h>
#include <toolkit/core/containers/TkUnorderedMap.h>

template <typename T>
class cTkIDMap : public std::unordered_map<cTkID, T, cTkID::Hash>
{
  public:
    cTkIDMap()  = default;
    ~cTkIDMap() = default;

    void Insert(const cTkID &id, const T &value) { (*this)[id] = value; }
    void Remove(const cTkID &id) { this->erase(id); }
    bool Contains(const cTkID &id) const { return this->find(id) != this->end(); }
    T &GetValue(const cTkID &id) { return (*this)[id]; }
    size_t Size() const { return this->size(); }
    bool IsEmpty() const { return this->empty(); }
};