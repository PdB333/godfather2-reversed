// FUNC_NAME: Math::vectorMin
void __thiscall Math::vectorMin(float *out, float *a, float *b)
{
    // Performs component-wise minimum of two 4-component vectors (SSE minps)
    // out = min(a, b) for each component
    __m128 result = _mm_min_ps(*(__m128*)a, *(__m128*)b);
    *(__m128*)out = result;
}