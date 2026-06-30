// FUNC_NAME: scaleVector4
// Address: 0x0052a000
// Role: Scales a 4-component vector (likely quaternion or 4D vector) by a global scale factor.
// The four components are stored as separate globals (gVecX, gVecY, gVecZ, gVecW) and multiplied by gScaleFactor.

extern float gScaleFactor;       // DAT_00e2b05c
extern float gVecX;              // DAT_01125230
extern float gVecY;              // DAT_01125234
extern float gVecZ;              // DAT_01125238
extern float gVecW;              // DAT_0112523c

void scaleVector4(void)
{
    gVecX *= gScaleFactor;
    gVecY *= gScaleFactor;
    gVecZ *= gScaleFactor;
    gVecW *= gScaleFactor;
}