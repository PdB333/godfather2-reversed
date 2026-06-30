// FUNC_NAME: vectorComponentMulKeepW
// Function at 0x004f5930: Component-wise multiplication of two 4D vectors, preserving the fourth component of the destination.
// Calling convention: __fastcall with first parameter (ECX) unused; destination pointer in EAX, source pointers in EDX and stack.
void __fastcall vectorComponentMulKeepW(float* out, const float* a, const float* b)
{
    // Save original fourth component of output
    float origW = out[3];

    // Multiply first three components
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];

    // Temporarily multiply fourth component
    out[3] = a[3] * b[3];

    // Restore original fourth component – only xyz are updated
    out[3] = origW;
}