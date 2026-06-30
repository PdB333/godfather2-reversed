// FUNC_NAME: subtractVectorPreserveW
// Address: 0x0044d470
// Role: 3D vector subtraction with preserved fourth (w) component.
// This function subtracts two 4‑element float vectors (a and b) for the first three components,
// but leaves the output's fourth component untouched. The output pointer is passed in EAX
// (hidden first parameter) per compiler optimization; parameters from the caller:
//   param1 (ECX) = unused / ignored
//   param2 (EDX) = a (first input vector)
//   param3 (stack) = b (second input vector)
// The actual C++ signature is likely:
//   void subtractVectorDelta(float* out, const float* a, const float* b)
// with 'out' passed in EAX.
void __fastcall subtractVectorDelta(float* out, const float* a, const float* b)
{
    float originalW;   // Saved w component of the output (in_EAX[3])
    float a1, a2, a3;  // Components of a[1..3]
    float b1, b2, b3;  // Components of b[1..3]

    // Load second, third, fourth components of input vectors
    a1 = a[1];
    a2 = a[2];
    a3 = a[3];
    b1 = b[1];
    b2 = b[2];
    b3 = b[3];

    // Preserve the original fourth component of the output before modifying it
    originalW = out[3];

    // Compute the difference for the first three components, store in output
    out[0] = a[0] - b[0];
    out[1] = a1 - b1;
    out[2] = a2 - b2;

    // Restore the fourth component (w) – it remains unchanged
    out[3] = originalW;

    return;
}