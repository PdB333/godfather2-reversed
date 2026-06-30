// FUNC_NAME: Math::maxVector4
void __thiscall Math::maxVector4(__m128* outResult, __m128 a, __m128 b)
{
    // SSE packed single-precision max: outResult = max(a, b) component-wise
    *outResult = _mm_max_ps(a, b);
}