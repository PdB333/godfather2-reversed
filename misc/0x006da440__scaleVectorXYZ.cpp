// FUNC_NAME: scaleVectorXYZ
// Function at 0x006da440: Scales the xyz components of a 4-element vector (src) by a scalar, preserving the w component of the destination.
// Parameters: dest (ECX - output), src (EDX - input), scale (stack - scalar).
void __fastcall scaleVectorXYZ(float* dest, const float* src, float scale)
{
    // Load src components
    float srcY = src[1];
    float srcZ = src[2];
    float srcW = src[3];                 // Loaded but unused (original behavior)
    float destW = dest[3];               // Preserve destination's w component

    // Scale and store x, y, z
    dest[0] = scale * src[0];
    dest[1] = scale * srcY;
    dest[2] = scale * srcZ;
    dest[3] = destW;                     // Restore original w (scaled srcW is discarded)
}