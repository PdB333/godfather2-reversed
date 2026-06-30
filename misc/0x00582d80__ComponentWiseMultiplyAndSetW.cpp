// FUNC_NAME: ComponentWiseMultiplyAndSetW
void __fastcall ComponentWiseMultiplyAndSetW(float *out, float *a, float *b)
{
    float a1 = a[1];
    float a2 = a[2];
    float a3 = a[3];
    float b1 = b[1];
    float b2 = b[2];
    float b3 = b[3];

    // Component-wise multiplication for first three components
    out[0] = a[0] * b[0];
    out[1] = a1 * b1;
    out[2] = a2 * b2;
    out[3] = a3 * b3;

    // Override fourth component with a global constant
    out[3] = DAT_00e2b1a4; // +0x00e2b1a4: float constant (likely alpha/scale)
}