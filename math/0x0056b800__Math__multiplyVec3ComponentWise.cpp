// FUNC_NAME: Math::multiplyVec3ComponentWise
// Address: 0x0056b800
// Description: Component-wise multiplication of two 3D vectors (w component preserved).
// Note: The decompiled code shows a redundant computation for dest[3] which is immediately overwritten;
// this is likely a compiler artifact. The actual effect is only on first three components.

void __fastcall Math::multiplyVec3ComponentWise(float* dest, const float* a, const float* b)
{
    float originalW = dest[3]; // +0x0C: save original w component

    dest[0] = a[0] * b[0];       // x
    dest[1] = a[1] * b[1];       // y
    dest[2] = a[2] * b[2];       // z
    // dest[3] = a[3] * b[3];    // computed but then overwritten, so effectively ignored
    dest[3] = originalW;         // preserve original w
}