// FUNC_NAME: vector3SubPreserveW
// Address: 0x005fd4e0
// Role: Performs 3-component vector subtraction (a - b) while preserving the 4th component (e.g., w) of the output vector.
// Used for homogeneous vector operations where the w component is kept unchanged.

void __fastcall vec3SubPreserveW(float* out, const float* a, const float* b)
{
    // Save w component of output before modification
    float savedW = out[3];

    // Subtract x, y, z components from a and b
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];

    // Restore the w component (unchanged)
    out[3] = savedW;
}