// FUNC_NAME: Vector4::max
// Function address: 0x00459140
// Computes component-wise maximum of two Vector4 (16-byte SIMD floats) and stores result in output.
// Uses SSE maxps instruction.
void Vector4::max(const Vector4& other, Vector4& out) const {
    // Load this vector and other vector into SSE registers (16-byte aligned assumed)
    __m128 a = _mm_load_ps(reinterpret_cast<const float*>(this));
    __m128 b = _mm_load_ps(reinterpret_cast<const float*>(&other));
    // Compute component-wise maximum
    __m128 result = _mm_max_ps(a, b);
    // Store result to output vector
    _mm_store_ps(reinterpret_cast<float*>(&out), result);
}