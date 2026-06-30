// FUNC_NAME: vec3Sub
// Address: 0x004270f0
// Role: Subtract two 3D vectors (stored as 4-component arrays), preserving the fourth (W) component.
// Calling convention: __fastcall with destination in EAX, source A in EDX, source B on stack. The first parameter (ECX) is unused.

void __fastcall vec3Sub(float *out, const float *a, const float *b)
{
    float a1 = a[1];
    float a2 = a[2];
    float a3 = a[3];
    float b1 = b[1];
    float b2 = b[2];
    float b3 = b[3];
    float originalW = out[3];

    // Subtract the first three components
    out[0] = a[0] - b[0];
    out[1] = a1 - b1;
    out[2] = a2 - b2;
    out[3] = a3 - b3;        // temporary full 4D subtraction

    // Restore the original fourth component (keeps W unchanged)
    out[3] = originalW;
}