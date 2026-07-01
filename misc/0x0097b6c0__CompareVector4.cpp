// FUNC_NAME: CompareVector4
bool __fastcall CompareVector4(float* vectorA, float* vectorB)
{
    // Compare four 32-bit float components using SSE
    __m128 a = _mm_loadu_ps(vectorA);
    __m128 b = _mm_loadu_ps(vectorB);
    __m128 cmp = _mm_cmpeq_ps(a, b);       // All bits set if equal
    int mask = _mm_movemask_ps(cmp);       // Extract sign bits (bit 31) of each component
    return mask == 0xF;                    // True if all 4 components equal
}