#pragma once

#include <toolkit/TkPch.h>

using TkSizeType = size_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

constexpr int guh = sizeof(double);

template <typename T>
class TkOptional
{
  public:
    TkOptional() : mbHasValue(false) {}
    TkOptional(const T &lValue) : mbHasValue(true), mValue(lValue) {}

    TkOptional &operator=(const T &lValue)
    {
        mValue     = lValue;
        mbHasValue = true;
        return *this;
    }

    bool HasValue() const { return mbHasValue; }

    T &Value() { return mValue; }
    const T &Value() const { return mValue; }

    auto operator<=>(const TkOptional &) const = default;

  private:
    bool mbHasValue;
    T mValue;
};