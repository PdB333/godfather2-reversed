// FUNC_NAME: addVector3PreserveW
// Function at 0x005742e0: Adds two 3D vectors (with w component) but preserves the w of the destination.
// __fastcall: dest (ecx), srcA (edx), srcB (stack)
void __fastcall addVector3PreserveW(float* dest, const float* srcA, const float* srcB)
{
    float origW = dest[3];                   // preserve original w
    dest[0] = srcA[0] + srcB[0];             // x
    dest[1] = srcA[1] + srcB[1];             // y
    dest[2] = srcA[2] + srcB[2];             // z
    dest[3] = srcA[3] + srcB[3];             // w (temporary, will be overwritten)
    dest[3] = origW;                         // restore original w
}