// FUNC_NAME: scaleVector3PreserveW
void __fastcall scaleVector3PreserveW(float* dest, const float* src, float scalar)
{
    // Save original w component of dest (index 3)
    float w = dest[3];
    // Scale x, y, z from src by scalar
    dest[0] = scalar * src[0];
    dest[1] = scalar * src[1];
    dest[2] = scalar * src[2];
    // Restore w component unchanged (preserves 4D vector w)
    dest[3] = w;
}