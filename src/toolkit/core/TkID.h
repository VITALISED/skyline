#pragma once

#include <toolkit/core/TkString.h>
#include <toolkit/maths/hash/TkHash.h>

class cTkID
{
  public:
    cTkID(const char *lpacID) { this->macName = new cTkFixedString<64, char>(lpacID); }
    ~cTkID() { delete this->macName; }

    uint64_t CalculateHash() const { return cTkHash::FNV1A(macName->macBuffer, macName->Length()); }

    class Hash
    {
      public:
        uint64_t operator()(const cTkID &lID) const { return lID.CalculateHash(); }
    };

    cTkFixedString<64, char> *macName;
};