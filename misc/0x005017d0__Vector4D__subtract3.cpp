// FUNC_NAME: Vector4D::subtract3
// Function address: 0x005017d0
// Performs component-wise subtraction of the first 3 components of two vectors,
// preserving the 4th component of the output vector.

void __fastcall Vector4D::subtract3(float* out, const float* a, const float* b)
{
    // Save original w component of output
    float w = out[3];

    // Subtract x, y, z components
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];

    // Restore w component
    out[3] = w;
}