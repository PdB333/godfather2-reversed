// FUNC_NAME: Vector4::clamp
void __thiscall Vector4::clamp(const Vector4& minVec, const Vector4& maxVec)
{
    // Component-wise clamp of this vector to [minVec, maxVec] using SSE minps/maxps
    // Equivalent to: this->x = clamp(this->x, minVec.x, maxVec.x) for each component
    // in_EAX: this pointer (16-byte aligned float4)
    // param_1: min vector (16-byte aligned)
    // param_2: max vector (16-byte aligned)

    __m128 v = *reinterpret_cast<const __m128*>(this);
    __m128 min = *reinterpret_cast<const __m128*>(&minVec);
    __m128 max = *reinterpret_cast<const __m128*>(&maxVec);

    v = _mm_min_ps(v, min);  // minps(*this, minVec)
    v = _mm_max_ps(v, max);  // maxps(auVar1, maxVec)

    *reinterpret_cast<__m128*>(this) = v;  // *in_EAX = auVar1
}