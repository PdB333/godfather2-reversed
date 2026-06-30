// FUNC_NAME: Vector4::min
// Function address: 0x0051e480
// Role: Component-wise minimum of two 4-float vectors, storing result into an output vector.
// This is likely a member function of a Vector4 class within the EARS engine.
// __thiscall: "this" pointer holds the first operand (first source in EAX/ECX).
// The second operand is passed as a reference (param_1), and the output is passed as a reference (param_2).
// Uses SSE minps intrinsic (_mm_min_ps) for packed single-precision floats.

#include <xmmintrin.h> // For __m128 and _mm_min_ps

struct Vector4 {
    __m128 v; // +0x00: 16 bytes of packed floats (x, y, z, w)

    // Compute component-wise minimum of this vector and 'other', store into 'result'.
    void __thiscall min(const Vector4& other, Vector4& result) const {
        result.v = _mm_min_ps(v, other.v); // minps: element-wise min
    }
};