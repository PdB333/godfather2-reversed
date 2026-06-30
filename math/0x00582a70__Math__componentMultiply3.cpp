// FUNC_NAME: Math::componentMultiply3
// Address: 0x00582a70
// Multiplies first three components of two 4-float vectors (or quaternions) element-wise.
// The fourth component of the destination is preserved unchanged.
// Parameters: out = destination (EAX), a = first input (EDX), b = second input (stack)
void __fastcall Math::componentMultiply3(float* out, float* a, float* b)
{
    // Read all components of both inputs
    float a0 = a[0];
    float a1 = a[1];
    float a2 = a[2];
    float a3 = a[3];

    float b0 = b[0];
    float b1 = b[1];
    float b2 = b[2];
    float b3 = b[3];

    // Save original fourth component of destination
    float origOut3 = out[3];

    // Multiply first three components
    out[0] = a0 * b0;
    out[1] = a1 * b1;
    out[2] = a2 * b2;

    // Fourth component is not multiplied; restore original value
    out[3] = origOut3;
}