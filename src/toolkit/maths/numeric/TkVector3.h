#pragma once

#include <toolkit/core/TkCore.h>
#include <toolkit/maths/numeric/TkIntrinsics.h>

class TK_VEC3_ALIGN cTkVector3
{
  public:
    /// Constructors
    inline cTkVector3() : mVal(_mm_setzero_ps()) {}
    inline cTkVector3(float lfX, float lfY, float lfZ) : mVal(_mm_set_ps(0, lfZ, lfY, lfX)) {}
    inline cTkVector3(__m128 m) : mVal(m) {}

    inline cTkVector3 operator+(const cTkVector3 &b) const { return _mm_add_ps(mVal, b.mVal); }
    inline cTkVector3 operator-(const cTkVector3 &b) const { return _mm_sub_ps(mVal, b.mVal); }
    inline cTkVector3 operator*(const cTkVector3 &b) const { return _mm_mul_ps(mVal, b.mVal); }
    inline cTkVector3 operator/(const cTkVector3 &b) const { return _mm_div_ps(mVal, b.mVal); }

    inline cTkVector3 &operator+=(const cTkVector3 &b)
    {
        mVal = _mm_add_ps(mVal, b.mVal);
        return *this;
    }
    inline cTkVector3 &operator-=(const cTkVector3 &b)
    {
        mVal = _mm_sub_ps(mVal, b.mVal);
        return *this;
    }
    inline cTkVector3 &operator*=(const cTkVector3 &b)
    {
        mVal = _mm_mul_ps(mVal, b.mVal);
        return *this;
    }
    inline cTkVector3 &operator/=(const cTkVector3 &b)
    {
        mVal = _mm_div_ps(mVal, b.mVal);
        return *this;
    }

    /// Arithmetic operators with floats
    inline cTkVector3 operator+(float b) const { return _mm_add_ps(mVal, _mm_set1_ps(b)); }
    inline cTkVector3 operator-(float b) const { return _mm_sub_ps(mVal, _mm_set1_ps(b)); }
    inline cTkVector3 operator*(float b) const { return _mm_mul_ps(mVal, _mm_set1_ps(b)); }
    inline cTkVector3 operator/(float b) const { return _mm_div_ps(mVal, _mm_set1_ps(b)); }

    /// Assignation and arithmetic operators with float
    inline cTkVector3 &operator+=(float b)
    {
        mVal = _mm_add_ps(mVal, _mm_set1_ps(b));
        return *this;
    }
    inline cTkVector3 &operator-=(float b)
    {
        mVal = _mm_sub_ps(mVal, _mm_set1_ps(b));
        return *this;
    }
    inline cTkVector3 &operator*=(float b)
    {
        mVal = _mm_mul_ps(mVal, _mm_set1_ps(b));
        return *this;
    }
    inline cTkVector3 &operator/=(float b)
    {
        mVal = _mm_div_ps(mVal, _mm_set1_ps(b));
        return *this;
    }

    /// Equality operators
    inline bool operator==(const cTkVector3 &b) const
    {
        return (((_mm_movemask_ps(_mm_cmpeq_ps(mVal, b.mVal))) & 0xF) == 0xF);
    }
    inline bool operator!=(const cTkVector3 &b) const { return !(*this == b); }

    inline cTkVector3 operator-() const { return _mm_xor_ps(mVal, TkSignMask); }

    inline const float &operator[](const int i) const { return i == 0 ? this->mfX : (i == 1 ? this->mfY : this->mfZ); }
    inline float &operator[](const int i) { return i == 0 ? this->mfX : (i == 1 ? this->mfY : this->mfZ); }

    inline cTkVector3 Cross(const cTkVector3 &b) const
    {
        return _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(mVal, mVal, _MM_SHUFFLE(3, 0, 2, 1)),
                _mm_shuffle_ps(b.mVal, b.mVal, _MM_SHUFFLE(3, 1, 0, 2))),
            _mm_mul_ps(
                _mm_shuffle_ps(mVal, mVal, _MM_SHUFFLE(3, 1, 0, 2)),
                _mm_shuffle_ps(b.mVal, b.mVal, _MM_SHUFFLE(3, 0, 2, 1))));
    }

    inline float Dot(const cTkVector3 &b) const { return _mm_cvtss_f32(_mm_dp_ps(mVal, b.mVal, 0x71)); }

    inline float Length() const { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mVal, mVal, 0x71))); }

    inline cTkVector3 Normalize() const
    {
        // multiplying by rsqrt does not yield an accurate enough result, so we
        // divide by sqrt instead.
        return _mm_div_ps(mVal, _mm_sqrt_ps(_mm_dp_ps(mVal, mVal, 0xFF)));
    }

    inline void *operator new[](size_t x) { return _aligned_malloc(x, 16); }
    inline void operator delete[](void *x)
    {
        if (x) _aligned_free(x);
    }

    // Textual representation
    friend std::ostream &operator<<(std::ostream &os, const cTkVector3 &t);

    union {
        struct
        {
            float mfX, mfY, mfZ;
        };
        __m128 mVal;
    };
};