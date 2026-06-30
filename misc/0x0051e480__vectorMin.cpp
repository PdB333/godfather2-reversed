// FUNC_NAME: vectorMin
// Address: 0x0051e480
// Role: Component-wise minimum of two 16-byte floating-point vectors (4 floats) using SSE minps instruction.
// Note: The function uses a custom calling convention where the first source vector pointer is passed in EAX,
// the second source vector pointer is the first stack parameter, and the destination pointer is the second stack parameter.
// This reconstructed version uses a standard __thiscall signature for clarity (the 'this' pointer is not really used).
#include <xmmintrin.h>

void __thiscall vectorMin(__m128* src1, __m128* src2, __m128* dest)
{
    // Compute component-wise minimum of src1 and src2, store result in dest
    *dest = _mm_min_ps(*src1, *src2);
}