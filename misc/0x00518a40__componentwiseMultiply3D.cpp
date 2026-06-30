// FUNC_NAME: componentwiseMultiply3D
void __fastcall componentwiseMultiply3D(float *out, float *a, float *b)
{
    // Preserve the fourth (w) component of the output vector
    float originalW = out[3];

    // Element-wise multiply the first three components (x, y, z)
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];

    // Restore w – leaves it unchanged (typical for 3D vectors with homogenous coordinate)
    out[3] = originalW;
}