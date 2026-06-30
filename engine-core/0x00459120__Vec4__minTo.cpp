// FUNC_NAME: Vec4::minTo
// Function at 0x00459120: Computes component-wise minimum of two float4 vectors and stores result to output pointer.
// Uses SIMD minps instruction. This is likely an inlined utility for EA EARS engine math.
void __thiscall Vec4::minTo(const Vec4& other, Vec4* out) const
{
    // Component-wise minimum of this vector (passed in ECX, but decompiler sees EAX) and other (param_1).
    // Stores the result to the pointer param_2.
    // Offsets: Vec4 is 16 bytes (4 floats, 0x00 to 0x0F).
    __m128 temp = _mm_min_ps(this->m128, other.m128);
    out->m128 = temp;
}