// FUNC_NAME: scaleVector4DAndSetW
// Address: 0x00582e40
// Scales a 4-component vector (x,y,z,w) by a scalar, then sets the w component to a global constant.
// Likely used for quaternion or vector math (e.g., set w to 1.0 or 0.0 after scaling).

extern float g_constantW; // from DAT_00e2b1a4

void __fastcall scaleVector4DAndSetW(float* outVec, const float* inVec, float scale)
{
    float x = inVec[0]; // +0x00
    float y = inVec[1]; // +0x04
    float z = inVec[2]; // +0x08
    float w = inVec[3]; // +0x0C (unused after overwrite)

    outVec[0] = scale * x; // +0x00
    outVec[1] = scale * y; // +0x04
    outVec[2] = scale * z; // +0x08
    outVec[3] = g_constantW; // +0x0C: override w with constant
}