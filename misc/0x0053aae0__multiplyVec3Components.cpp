// FUNC_NAME: multiplyVec3Components
// Address: 0x0053aae0
// Role: Performs component-wise multiplication of two 3D vectors (stored as float[4]) on the first three components,
// leaving the fourth (often w) untouched. Used for scaling or element-wise operations.

void __fastcall multiplyVec3Components(float* out, const float* a, const float* b)
{
    float savedW = out[3];                // Preserve the fourth component of output
    out[0] = a[0] * b[0];                 // X component
    out[1] = a[1] * b[1];                 // Y component
    out[2] = a[2] * b[2];                 // Z component
    out[3] = a[3] * b[3];                 // Product of W components (discarded)
    out[3] = savedW;                      // Restore original W
}