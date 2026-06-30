// FUNC_NAME: Vector3Add
// Function address: 0x00519f20
// Purpose: Adds two 3-element vectors (XYZ) while preserving the 4th component of the destination.
// Calling convention: __fastcall with destination pointer in EAX, source pointers in ECX and EDX (inferred from decompilation).
// Arguments:
//   out  - pointer to destination float[4] (4th element unchanged)
//   a    - pointer to first source float[4] (only first 3 used)
//   b    - pointer to second source float[4] (only first 3 used)
void __fastcall Vector3Add(float *out, const float *a, const float *b)
{
    // Save the original 4th element of the destination (likely padding or w-component)
    float savedW = out[3];

    // Add the first three components (x, y, z) from a and b
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];

    // Restore the 4th component of the destination unchanged
    out[3] = savedW;
}