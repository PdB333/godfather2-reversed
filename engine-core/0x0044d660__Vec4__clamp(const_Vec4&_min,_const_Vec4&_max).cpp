// FUNC_NAME: Vec4::clamp(const Vec4& min, const Vec4& max)

void __thiscall Vec4::clamp(const Vec4& min, const Vec4& max) {
    // SSE clamp: result = max(min(value, min), max)
    __m128 value = *reinterpret_cast<const __m128*>(this);
    __m128 clamped = _mm_min_ps(value, *reinterpret_cast<const __m128*>(&min));
    clamped = _mm_max_ps(clamped, *reinterpret_cast<const __m128*>(&max));
    *reinterpret_cast<__m128*>(this) = clamped;
}