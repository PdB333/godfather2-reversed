// FUNC_NAME: MathUtils::vectorMax
void __thiscall MathUtils::vectorMax(float (*a) [4], float (*b) [4], float (*out) [4])
{
  // Per-element maximum of two 4-component vectors using SSE maxps
  // a and b are 16-byte aligned float[4] arrays
  // out receives the component-wise maximum
  __m128 result = _mm_max_ps(*(__m128*)a, *(__m128*)b);
  *(__m128*)out = result;
}