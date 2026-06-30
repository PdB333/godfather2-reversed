// FUNC_NAME: scaleVector3
void __fastcall scaleVector3(float* dest, const float* src, float scalar)
{
    // Save the 4th component of dest (often homogeneous w or quaternion scalar)
    float savedW = dest[3];

    // Scale the first three components from src
    dest[0] = scalar * src[0];
    dest[1] = scalar * src[1];
    dest[2] = scalar * src[2];

    // Restore the original 4th component (not affected by scaling)
    dest[3] = savedW;
}