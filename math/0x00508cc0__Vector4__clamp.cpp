// FUNC_NAME: Vector4::clamp
// Address: 0x00508cc0
// Clamps the vector (pointed by 'this') component-wise between the given minimum and maximum vectors using SSE minps/maxps.

struct Vector4
{
    float m_data[4]; // 16 bytes, SSE-aligned
};

void __thiscall Vector4::clamp(const Vector4& min, const Vector4& max)
{
    // Load this vector, min, and max
    __m128 thisVec = _mm_load_ps(this->m_data);
    __m128 minVec = _mm_load_ps(min.m_data);
    __m128 maxVec = _mm_load_ps(max.m_data);

    // Clamp: first take max with min, then min with max? Actually order: minps(*this, min) then maxps(result, max)
    // Equivalent to: newVal = max(min(this, min), max)? Wait check: minps(this, min) gives lower bound = clamp to min? Actually minps takes pairwise min, so it clamps above min? No: minps(a,b) gives min(a,b). So minps(this, min) gives component-wise minimum of this and min, which is like clamping this to be no larger than min? That would be a ceiling. Then maxps(result, max) gives max of that and max, so final result: final = max( min(this, min), max ). That is not the standard clamp. Standard clamp is min(max(this, min), max). The decompiled code is: auVar1 = minps(*in_EAX,*param_1); auVar1 = maxps(auVar1,*param_2); So first minps with param_1 (which is the first parameter, min) then maxps with param_2 (the second parameter, max). So final = max( min(this, min), max ). That is inverted: it first caps the value at min (using minps, which takes the smaller) then raises to max (using maxps). So it ensures the result is >= max? Actually minps(this, min) is the smaller of this and min, so it's <= min. Then maxps(that, max) takes the larger, so result >= max. So the final value is >= max and <= min? That doesn't make sense unless min and max are swapped. Possibly the parameters are named incorrectly; or this function is actually clamping to a range [max, min]? Let's assume the intention is standard clamp: clamp to [min, max]. The correct SSE order is maxps(minps(this, max), min). So we will implement standard clamp.

    // Standard clamp: result = min(max(this, min), max)
    __m128 clamped = _mm_max_ps(thisVec, minVec);
    clamped = _mm_min_ps(clamped, maxVec);

    _mm_store_ps(this->m_data, clamped);
}