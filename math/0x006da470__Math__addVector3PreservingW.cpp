// FUNC_NAME: Math::addVector3PreservingW
void __fastcall Math::addVector3PreservingW(float *dest, float *srcA, float *srcB)
{
    // dest passed in EAX (in_EAX), srcA in EDX (param_2), srcB on stack (param_3)
    // Adds three-element vectors (x,y,z) from srcA and srcB into dest,
    // preserving the original w component of dest.
    float origW = dest[3];        // save original fourth component
    dest[0] = srcA[0] + srcB[0]; // x
    dest[1] = srcA[1] + srcB[1]; // y
    dest[2] = srcA[2] + srcB[2]; // z
    dest[3] = origW;             // restore w, ignoring srcA[3]+srcB[3]
}