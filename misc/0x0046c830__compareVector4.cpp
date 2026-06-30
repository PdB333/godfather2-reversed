// FUNC_NAME: compareVector4

#include <xmmintrin.h>

bool __fastcall compareVector4(const float* a, const float* b)
{
    // Load both 4-float vectors into SSE registers
    __m128 va = _mm_loadu_ps(a);
    __m128 vb = _mm_loadu_ps(b);

    // Compare components: result is 0xFFFFFFFF for equal, 0 for not equal
    __m128 cmp = _mm_cmpeq_ps(va, vb);

    // Extract 4-bit mask (high bit of each float)
    int mask = _mm_movemask_ps(cmp);

    // All four components equal => mask == 0xF (all bits 1)
    return mask == 0xF;
}