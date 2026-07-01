// FUNC_NAME: MathUtils::lerpQuaternion
void __fastcall lerpQuaternion(float *outQuat, float *fromQuat, float *toQuat, float t)
{
    // Linear interpolation of quaternion components (x, y, z, w)
    // Note: This is a simple lerp, not slerp, and the w component is overwritten
    // at the end with the original w value from outQuat (likely a bug or intentional
    // for specific use case where w is preserved)
    float fromX = fromQuat[0];
    float fromY = fromQuat[1];
    float fromZ = fromQuat[2];
    float fromW = fromQuat[3];
    float toX = toQuat[0];
    float toY = toQuat[1];
    float toZ = toQuat[2];
    float toW = toQuat[3];
    float originalOutW = outQuat[3];

    outQuat[0] = (toX - fromX) * t + fromX;
    outQuat[1] = (toY - fromY) * t + fromY;
    outQuat[2] = (toZ - fromZ) * t + fromZ;
    outQuat[3] = (toW - fromW) * t + fromW;
    outQuat[3] = originalOutW; // Preserve original w component
}