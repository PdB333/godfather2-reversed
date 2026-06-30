// FUNC_NAME: VectorMath::addPreservingW
void __fastcall addPreservingW(float * __restrict dest, const float * __restrict a, const float * __restrict b)
{
    // Add x,y,z components; preserve w component of destination.
    float oldW = dest[3];
    dest[0] = a[0] + b[0]; // +0x00 x
    dest[1] = a[1] + b[1]; // +0x04 y
    dest[2] = a[2] + b[2]; // +0x08 z
    dest[3] = oldW;        // +0x0C w unchanged
}