// FUNC_NAME: MathUtils::scaleVector3IgnoreW
// Function address: 0x00508a00
// Role: Scales the first three components of a 4-element vector (src) by a scalar, preserving the fourth component (w).
// Note: In assembly, the destination pointer is passed in EAX, source in EDX, scale on stack.
void __fastcall scaleVector3IgnoreW(float* dest, const float* src, float scale)
{
    // Save original w component from dest
    float originalW = dest[3];

    // Scale each component
    dest[0] = scale * src[0];
    dest[1] = scale * src[1];
    dest[2] = scale * src[2];
    dest[3] = scale * src[3]; // Temporarily set w, then restore

    // Restore w – only x, y, z are scaled
    dest[3] = originalW;
}