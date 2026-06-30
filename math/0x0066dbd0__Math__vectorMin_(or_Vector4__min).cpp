// FUNC_NAME: Math::vectorMin (or Vector4::min)
// Function address: 0x0066dbd0
// Role: Computes element-wise minimum of two 4-float vectors (SSE minps) and stores result.
// Uses __thiscall but actually takes three pointers: result, a, b (with a passed in EAX).
// This is likely a helper for vector math operations in the EARS engine.

#include <xmmintrin.h> // For __m128 and _mm_min_ps

// Assuming a vector type used in the engine (e.g., EARS::Math::Vector4)
struct Vector4 {
    __m128 data;
};

// Reconstructed function: void __thiscall vectorMin(Vector4* result, const Vector4* a, const Vector4* b)
// Note: The decompiler shows in_EAX as the first argument (a), param_1 as b, param_2 as result.
// The calling convention is unusual; we treat it as a static helper with three pointers.
void __thiscall vectorMin(Vector4* result, const Vector4* a, const Vector4* b) {
    // Compute element-wise minimum of a and b using SSE minps
    __m128 minVal = _mm_min_ps(a->data, b->data);
    // Store the result
    result->data = minVal;
}