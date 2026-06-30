// FUNC_NAME: MathHelper::componentMin
// Address: 0x00459160
// Role: Component-wise minimum of two 4-float vectors using SSE minps.
// Observed calling convention: first vector pointer in EAX, second in param_1, result stored in param_2.
// This is a static-like helper; the __thiscall indicates it may be a member function but uses EAX instead of ECX.
// Likely a custom fastcall variant or decompiler artifact. For clarity, treat as a free function.

void __thiscall MathHelper::componentMin(const float* vecA, const float* vecB, float* outVec) {
    // vecA is passed via EAX (custom calling), vecB via ECX? Actually param_1 is first explicit param.
    // The decompiler shows in_EAX and param_1 as sources, param_2 as destination.
    __m128 a = _mm_load_ps(vecA);       // Load first vector (from EAX)
    __m128 b = _mm_load_ps(vecB);       // Load second vector (from param_1)
    __m128 result = _mm_min_ps(a, b);   // SSE minps: component-wise minimum
    _mm_store_ps(outVec, result);       // Store result to param_2
}