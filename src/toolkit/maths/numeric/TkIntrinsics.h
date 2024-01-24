#pragma once

#include <toolkit/core/TkCore.h>
#include <xmmintrin.h>

#define TK_VEC3_ALIGN _MM_ALIGN16
constexpr __m128 TkSignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));