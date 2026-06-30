// FUNC_NAME: MathUtils::vectorMax
void __thiscall MathUtils::vectorMax(float (*inVec)[4], float (*otherVec)[4], float (*outVec)[4])
{
    // Per-element maximum of two 4-component vectors (SSE maxps instruction)
    // Used for clamping or component-wise max operations on float4 data
    // +0x00: x component
    // +0x04: y component
    // +0x08: z component
    // +0x0C: w component
    __m128 result = _mm_max_ps(*(__m128*)*inVec, *(__m128*)*otherVec);
    *(__m128*)*outVec = result;
}