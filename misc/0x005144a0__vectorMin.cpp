// FUNC_NAME: vectorMin
// Address: 0x005144a0
// Role: Computes component-wise minimum of two 4-float vectors using SSE minps instruction.
// Note: Decompiler indicated __thiscall, but this appears to be a free utility function.
void __cdecl vectorMin(const __m128* a, const __m128* b, __m128* out)
{
    *out = _mm_min_ps(*a, *b);
}