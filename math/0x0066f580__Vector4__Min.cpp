// FUNC_NAME: Vector4::Min
void __thiscall Vector4::Min(const Vector4* other, Vector4* out)
{
    // Element-wise packed single-precision minimum (SSE minps)
    // this->m128 corresponds to the first operand (typically passed in EAX)
    __m128 result = _mm_min_ps(this->m128, other->m128);
    out->m128 = result;
}