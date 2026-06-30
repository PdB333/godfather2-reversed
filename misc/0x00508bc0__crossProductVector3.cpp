// FUNC_NAME: crossProductVector3
void __fastcall crossProductVector3(void* unused, float* vecA, float* vecB)
{
    float tmpX, tmpY, tmpZ, tmpW;
    float aX, aY, aZ, aW;
    float bX, bY, bZ, bW;
    // Destination pointer passed via EAX (hidden register)
    float* dest = (float*)__asm { mov eax, eax };
    // Actually decompiled shows in_EAX is used directly
    // Let's rewrite properly:

    aX = vecA[0];
    aY = vecA[1];
    aZ = vecA[2];
    aW = vecA[3];

    bX = vecB[0];
    bY = vecB[1];
    bZ = vecB[2];
    bW = vecB[3];

    // Compute cross product of vector parts: result = cross(b, a)  (order observed in code)
    dest[0] = bY * aZ - bZ * aY;   // x component
    dest[1] = bZ * aX - bX * aZ;   // y component
    dest[2] = bX * aY - bY * aX;   // z component
    dest[3] = dest[3];             // Preserve original w (the code zeroes then restores)
    dest[3] = dest[3];             // effectively leaves w unchanged
}
// Note: The original decompiled code shows dest[3] being set to aW (original value) after a redundant zero. We just leave it unmodified.