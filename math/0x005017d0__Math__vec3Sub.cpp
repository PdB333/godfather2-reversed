// FUNC_NAME: Math::vec3Sub
// Function at 0x005017d0: Vector subtraction for 3-component (x,y,z) preserving w.
// Parameters: ECX=dest pointer, EDX=source A pointer, stack=source B pointer.
// Operation: dest[0]=A[0]-B[0], dest[1]=A[1]-B[1], dest[2]=A[2]-B[2]; dest[3] unchanged.

#include <cstdint>

// Reconstructed __fastcall function for EARS engine math library
// Preserves the fourth component (w) of the destination vector
void __fastcall Math::vec3Sub(float *dest, const float *a, const float *b)
{
    // Save dest[3] before overwriting first three components
    float w = dest[3];

    // Vector subtraction: x, y, z only
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];

    // Restore w component
    dest[3] = w;
}