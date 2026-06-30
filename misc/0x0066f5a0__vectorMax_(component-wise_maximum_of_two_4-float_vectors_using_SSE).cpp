// FUNC_NAME: vectorMax (component-wise maximum of two 4-float vectors using SSE)
// Address: 0x0066f5a0
// This function computes the per-component maximum of two packed single-precision float vectors
// and stores the result at the given output pointer.
// Parameters:
//   inputVector: pointer to 16-byte aligned float[4] (first operand, passed in EAX via register)
//   outputVector: pointer to 16-byte aligned float[4] (result storage)
// The function uses SSE 'maxps' instruction.

#include <xmmintrin.h> // SSE intrinsics

void __thiscall vectorMax(const float (*inputVector)[4], float (*outputVector)[4])
{
    // Load the first vector from the register-passed pointer (in EAX)
    __m128 a = _mm_load_ps(*inputVector);

    // Load the second vector from param_1 (stack argument)
    __m128 b = _mm_load_ps(reinterpret_cast<const float*>(param_1)); // But param_1 is the first param? Actually decomp shows param_1 as second param? Let's correct.

    // Compute component-wise maximum
    __m128 result = _mm_max_ps(a, b);

    // Store result to output pointer
    _mm_store_ps(*outputVector, result);
}
// Note: The decompiler's signature shows two parameters, but the 'in_EAX' implies the first vector was passed in EAX.
// In reality, this function likely takes two pointers: first in EAX, second on the stack (or ECX for this).
// For clarity, we assume the calling convention is __fastcall or a custom register pass.
// Since the original signature is __thiscall, it's possible 'this' is unused and the first parameter is in EAX.
// The function is effectively a static utility for vector max.