// FUNC_NAME: math::clampVector4
// Address: 0x00508cc0
// Clamps a 4-component vector (in EAX) between min and max bounds using SSE instructions

void __thiscall math::clampVector4(float* __restrict pOut, const float* pMin, const float* pMax)
{
    // Load vector from pOut (EAX) as 4 floats
    __m128 vec = _mm_load_ps(pOut);
    // Clamp to min: maxps(vec, pMin)
    __m128 minVec = _mm_load_ps(pMin);
    vec = _mm_max_ps(vec, minVec);
    // Clamp to max: minps(vec, pMax)
    __m128 maxVec = _mm_load_ps(pMax);
    vec = _mm_min_ps(vec, maxVec);
    // Store result back to pOut
    _mm_store_ps(pOut, vec);
}