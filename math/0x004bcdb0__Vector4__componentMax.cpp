// FUNC_NAME: Vector4::componentMax
void __thiscall Vector4::componentMax(const Vector4& other, Vector4& out) const
{
    // Compute component-wise maximum of this vector and other, store in out
    // Vector4 layout: 4 floats (x, y, z, w) at offsets 0x00, 0x04, 0x08, 0x0C
    __m128 a = _mm_load_ps(&x);
    __m128 b = _mm_load_ps(&other.x);
    __m128 result = _mm_max_ps(a, b);
    _mm_store_ps(&out.x, result);
}