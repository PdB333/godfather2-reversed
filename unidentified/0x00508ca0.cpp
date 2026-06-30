// FUN_00508ca0: MathUtils::multiplyVector3Componentwise
void __fastcall MathUtils::multiplyVector3Componentwise(
    void* unusedThis,          // param_1 in ECX - unused, likely for alignment
    float* a,                  // param_2 in EDX - first input vector (4 floats)
    float* b                   // param_3 on stack - second input vector (4 floats)
) {
    // EAX register holds output vector pointer (implicit)
    float* out; // replaces in_EAX from decompiled code

    // Save original fourth component of output
    float wSaved = out[3];

    // Componentwise multiplication of first three components
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];

    // Multiply fourth component but then restore original (preserves w)
    out[3] = a[3] * b[3];
    out[3] = wSaved;
}