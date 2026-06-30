// FUNC_NAME: Math::maxVector
void __thiscall Math::maxVector(const __m128* a, const __m128* b, __m128* out)
{
    // Compute element-wise maximum of two 4-float vectors using SSE maxps
    *out = _mm_max_ps(*a, *b);
}