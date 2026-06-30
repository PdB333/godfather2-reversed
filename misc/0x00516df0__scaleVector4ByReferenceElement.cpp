// FUNC_NAME: scaleVector4ByReferenceElement
// Address: 0x00516df0
// Scales the first four floats of the struct by (g_scaleConstant / element[8]).
// This appears to be a member function of an unknown class, taking 'this' in EAX.
// The struct layout assumed: +0x00: 4 floats (x,y,z,w), +0x20: reference float (denominator)

extern float g_scaleConstant; // DAT_00e2b1a4

void __thiscall scaleVector4ByReferenceElement(float *thisPtr)
{
    float scaleFactor;

    scaleFactor = g_scaleConstant / thisPtr[8]; // +0x20: reference float
    thisPtr[0] *= scaleFactor; // +0x00
    thisPtr[1] *= scaleFactor; // +0x04
    thisPtr[2] *= scaleFactor; // +0x08
    thisPtr[3] *= scaleFactor; // +0x0C
}