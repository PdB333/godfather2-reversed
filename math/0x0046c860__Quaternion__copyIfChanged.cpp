// FUNC_NAME: Quaternion::copyIfChanged
#include <xmmintrin.h>

// Returns true if the original destination quaternion differed from the source.
bool __fastcall Quaternion::copyIfChanged(float *dst, float *src) {
    // Load original destination values.
    float origDst0 = dst[0];
    float origDst1 = dst[1];
    float origDst2 = dst[2];
    float origDst3 = dst[3];

    // Copy source into destination.
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];

    // Compare each component: generate 0xFFFFFFFF if equal, 0 if not.
    __m128 cmp0 = _mm_cmpeq_ps(_mm_set_ps(origDst3, origDst2, origDst1, origDst0),
                               _mm_set_ps(src[3], src[2], src[1], src[0]));
    // Extract sign bits (most significant bit) of each component.
    int mask = _mm_movemask_ps(cmp0);
    // Return true if not all components were equal (mask != 0xF).
    return mask != 0xF;
}