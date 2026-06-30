// FUNC_NAME: Vector4::clamp
// Address: 0x0061c750
// Clamps the vector components to be within [low, high] using SSE minps/maxps.
// Note: Parameter order is high then low (clamp(this, high, low)).
void __thiscall Vector4::clamp(const Vector4& high, const Vector4& low)
{
    // Load vectors as SSE registers
    __m128 thisVec = *reinterpret_cast<const __m128*>(this);
    __m128 highVec = *reinterpret_cast<const __m128*>(&high);
    __m128 lowVec  = *reinterpret_cast<const __m128*>(&low);

    // minps gives component-wise minimum, so min(this, high) enforces upper bound
    __m128 clamped = _mm_min_ps(thisVec, highVec);
    // maxps gives component-wise maximum, so max(..., low) enforces lower bound
    clamped = _mm_max_ps(clamped, lowVec);

    // Store result back to this
    *reinterpret_cast<__m128*>(this) = clamped;
}