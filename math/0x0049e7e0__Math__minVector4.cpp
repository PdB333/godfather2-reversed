// FUNC_NAME: Math::minVector4
// Address: 0x0049e7e0
// Role: Computes element-wise minimum of two packed single-precision vectors (SSE minps)
// The first vector is passed in EAX, the second and third via stack (this is a regparm-like convention).
// The output vector is stored through the third pointer.

void __thiscall Math::minVector4(const float* a, const float* b, float* out)
{
    // SSE packed single-precision minimum: result[i] = min(a[i], b[i])
    __m128 va = _mm_load_ps(a);
    __m128 vb = _mm_load_ps(b);
    __m128 result = _mm_min_ps(va, vb);
    _mm_store_ps(out, result);
}