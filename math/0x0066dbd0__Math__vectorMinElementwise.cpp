// FUNC_NAME: Math::vectorMinElementwise
// Address: 0x0066dbd0
// This function computes the component-wise minimum of two 4-float vectors using SSE minps.
// The first input vector is expected to be pointed to by the EAX register (non‑standard calling convention),
// the second input vector is passed as a stack parameter, and the output vector is written to a third pointer.
void __thiscall Math::vectorMinElementwise(const float* vecA, const float* vecB, float* outVec)
{
    // Load the two 128‑bit packed single‑precision vectors (4 floats each)
    __m128 a = *reinterpret_cast<const __m128*>(vecA);
    __m128 b = *reinterpret_cast<const __m128*>(vecB);

    // Element‑wise minimum
    __m128 result = _mm_min_ps(a, b);

    // Store the result to the output buffer
    *reinterpret_cast<__m128*>(outVec) = result;
}