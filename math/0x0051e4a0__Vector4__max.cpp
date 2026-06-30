// FUNC_NAME: Vector4::max
// Function address: 0x0051e4a0
// Computes element-wise maximum of two 4-float vectors using SSE maxps.
// this: source vector (x, y, z, w)
// param_1: other vector
// param_2: output vector

void __thiscall Vector4::max(const Vector4* other, Vector4* out) const
{
    // Load both vectors into SSE registers
    __m128 a = _mm_load_ps(&x);   // +0x00: float x, +0x04: float y, +0x08: float z, +0x0C: float w
    __m128 b = _mm_load_ps(&other->x);
    // Element-wise max
    __m128 result = _mm_max_ps(a, b);
    // Store result to output
    _mm_store_ps(&out->x, result);
}