// FUNC_NAME: scaleVector4
// Address: 0x00526070
// Scales a global 4-component vector (likely a quaternion or 4D vector) by a factor.
void scaleVector4(float scale)
{
    // Global 4-float vector at 0x01125200
    extern float gScaleTarget[4];
    gScaleTarget[0] *= scale;
    gScaleTarget[1] *= scale;
    gScaleTarget[2] *= scale;
    gScaleTarget[3] *= scale;
}