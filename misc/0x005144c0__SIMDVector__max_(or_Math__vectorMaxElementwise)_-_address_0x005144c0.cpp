// FUNC_NAME: SIMDVector::max (or Math::vectorMaxElementwise) - address 0x005144c0
// Computes element-wise maximum of two SSE vectors (this and other) and stores result in out.
// Uses SSE maxps intrinsic.

#include <xmmintrin.h>  // for _mm_max_ps

void __thiscall SIMDVector::max(const SIMDVector& other, SIMDVector& out) const
{
    // this pointer (in ECX) points to the first vector
    // param_1 (on stack) is "other"
    // param_2 (on stack) is "out" (reference to write result)
    __m128 result = _mm_max_ps(*(const __m128*)this, *(const __m128*)&other);
    *(__m128*)&out = result;
}