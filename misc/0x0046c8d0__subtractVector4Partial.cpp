// FUNC_NAME: subtractVector4Partial
// Subtracts x, y, z of two 4-float vectors; w component of output is preserved.
// Internally uses __fastcall: output pointer in EAX, input A in EDX, input B on stack.
// The function reads a[0..3], b[0..3], writes to out[0..2] and restores out[3] from saved value.
void subtractVector4Partial(float* out, const float* a, const float* b) {
    // Save original w component (offset 12 bytes)
    float savedW = out[3];

    // Subtract first three components
    out[0] = a[0] - b[0];  // offset 0
    out[1] = a[1] - b[1];  // offset 4
    out[2] = a[2] - b[2];  // offset 8

    // Restore the w component (offset 12)
    out[3] = savedW;
}