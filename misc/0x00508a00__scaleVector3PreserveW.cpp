// FUNC_NAME: scaleVector3PreserveW
// Address: 0x00508a00
// Function: Scales a 3-element vector (stored in a 4-float array) by a scalar,
//           preserving the fourth (W) component unchanged.
// Calling Convention: __fastcall (ECX = dest, EDX = src, stack = scale)
// Transforms: dest[0]=scale*src[0], dest[1]=scale*src[1], dest[2]=scale*src[2]; dest[3] unchanged.
void __fastcall scaleVector3PreserveW(float* dest, float* src, float scale)
{
    // Save original W component of destination
    float savedW = dest[3];

    // Scale the first three components using source vector and scalar
    dest[0] = scale * src[0];
    dest[1] = scale * src[1];
    dest[2] = scale * src[2];

    // Preserve original W component (overwrites the scaled W)
    dest[3] = savedW;
}