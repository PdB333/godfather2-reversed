// FUNC_NAME: clamp_vector
// Function address: 0x005c4780
// Clamps a 4-float vector between lower and upper bounds using SSE minps/maxps.
// Parameters are passed via EAX (value) and two stack pointers (max, min).
// Reconstructed as in/out __m128 with explicit parameters.

#include <xmmintrin.h> // for _mm_min_ps, _mm_max_ps

void __thiscall clamp_vector(__m128& inOutValue, const __m128& maxVal, const __m128& minVal)
{
    // minps: elementwise minimum of inOutValue and maxVal (upper bound)
    // maxps: elementwise maximum of that result with minVal (lower bound)
    // Result is clamp(inOutValue, minVal, maxVal) where minVal <= maxVal
    __m128 temp = _mm_min_ps(inOutValue, maxVal);
    temp = _mm_max_ps(temp, minVal);
    inOutValue = temp;
}