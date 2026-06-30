// FUNC_NAME: SmoothInterpolator::updateSmoothState
void SmoothInterpolator::updateSmoothState(float blendFactor)
{
    // Global interpolated state (7 floats, e.g., quaternion + translation)
    extern float gInterpolated[7]; // DAT_01206700..DAT_01206718

    // Target state stored in some object (likely this->targetData)
    // Offsets relative to this: 0x10, 0x14, 0x18, 0x1c (quaternion) and 0x20, 0x24, 0x28 (position)
    float* targetQuat = (float*)((char*)this + 0x10); // w, x, y, z? Or x,y,z,w?
    float* targetPos  = (float*)((char*)this + 0x20); // x, y, z

    // Interpolate quaternion (4 floats)
    gInterpolated[0] = (targetQuat[0] - gInterpolated[0]) * blendFactor + gInterpolated[0];
    gInterpolated[1] = (targetQuat[1] - gInterpolated[1]) * blendFactor + gInterpolated[1];
    gInterpolated[2] = (targetQuat[2] - gInterpolated[2]) * blendFactor + gInterpolated[2];
    gInterpolated[3] = (targetQuat[3] - gInterpolated[3]) * blendFactor + gInterpolated[3];

    // Interpolate position (3 floats)
    static const float ONE = 1.0f; // DAT_00e2b1a4
    float oneMinusBlend = ONE - blendFactor;
    gInterpolated[4] = targetPos[0] * blendFactor + oneMinusBlend * gInterpolated[4];
    gInterpolated[5] = targetPos[1] * blendFactor + oneMinusBlend * gInterpolated[5];
    gInterpolated[6] = targetPos[2] * blendFactor + oneMinusBlend * gInterpolated[6];
}