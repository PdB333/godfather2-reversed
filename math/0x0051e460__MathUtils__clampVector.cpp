// FUNC_NAME: MathUtils::clampVector
void __thiscall MathUtils::clampVector(float *outResult, float *minValues, float *maxValues)
{
    // Performs component-wise clamp on a 4-component vector (SSE minps/maxps)
    // outResult = clamp(outResult, minValues, maxValues)
    __m128 result = _mm_load_ps(outResult);
    __m128 min = _mm_load_ps(minValues);
    __m128 max = _mm_load_ps(maxValues);
    
    result = _mm_min_ps(result, min);  // minps - component-wise minimum
    result = _mm_max_ps(result, max);  // maxps - component-wise maximum
    
    _mm_store_ps(outResult, result);
}