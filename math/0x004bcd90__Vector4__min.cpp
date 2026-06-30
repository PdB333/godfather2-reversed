// FUNC_NAME: Vector4::min
// Function address: 0x004bcd90
// Role: Computes component-wise minimum of two 4-component float vectors (SSE minps)
// This appears to be a member function of a SIMD vector class (likely Vector4 or SSEVector).
// It takes another vector as input and writes the result to a third vector.
// The 'this' pointer is the first operand (source A), param_1 is source B, param_2 is the destination.

void __thiscall Vector4::min(const Vector4& other, Vector4& result) const
{
    // Use SSE minps instruction: dest = min(src1, src2)
    result.m128 = _mm_min_ps(m128, other.m128);
}