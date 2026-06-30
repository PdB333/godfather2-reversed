// FUNC_NAME: componentwiseMultiply3D
// Function at 0x0049e7c0: Componentwise multiply of first 3 components of two 4-float vectors, preserving w (index 3).
// __fastcall: out in ECX, a in EDX, b on stack.
void __fastcall componentwiseMultiply3D(float* out, float* a, float* b)
{
    // Save original w component of output
    float w = out[3];

    // Multiply x, y, z components
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];

    // Restore w (unchanged)
    out[3] = w;
}