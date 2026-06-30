// FUNC_NAME: Vector4::max
// Address: 0x005144c0
// Computes component-wise maximum of two 4-float vectors (this and vecB) and stores result in output.
void __thiscall Vector4::max(const float* vecB, float* result)
{
    // Load this vector from the object's first 16 bytes (4 floats)
    __m128 a = _mm_load_ps(reinterpret_cast<const float*>(this));
    __m128 b = _mm_load_ps(vecB);
    __m128 res = _mm_max_ps(a, b);
    _mm_store_ps(result, res);
}