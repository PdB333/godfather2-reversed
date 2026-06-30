// FUNC_NAME: Math::Vector4Max
#include <xmmintrin.h> // SSE intrinsics

/**
 * Computes component-wise maximum of two 4-component vectors.
 * @param vecA  First vector (passed in EAX via fastcall convention, but represented as first param)
 * @param vecB  Second vector
 * @param outResult  Output vector (must be 16-byte aligned)
 */
void __thiscall Math::Vector4Max(const float* vecA, const float* vecB, float* outResult)
{
    // Load both vectors and take element-wise maximum using SSE instruction maxps
    __m128 a = _mm_load_ps(vecA);
    __m128 b = _mm_load_ps(vecB);
    __m128 max = _mm_max_ps(a, b);
    _mm_store_ps(outResult, max);
}