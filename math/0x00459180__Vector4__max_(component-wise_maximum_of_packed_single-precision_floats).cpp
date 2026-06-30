// FUNC_NAME: Vector4::max (component-wise maximum of packed single-precision floats)
// Address: 0x00459180
// Role: Computes the component-wise maximum of two 4-float vectors using SSE maxps instruction.
// The function takes this pointer (first vector) in EAX, a pointer to the second vector in param_1,
// and a pointer to the output vector in param_2.

#include <xmmintrin.h>

class Vector4 {
public:
    union {
        __m128 m;           // +0x00: SSE register
        float f[4];         // +0x00: float components
    };

    // __thiscall: this in ECX (decompiler shows EAX, likely an artifact)
    void __fastcall max(const Vector4& other, Vector4& out) {
        // Component-wise maximum of this->m and other.m
        out.m = _mm_max_ps(this->m, other.m); // maxps instruction
    }
};