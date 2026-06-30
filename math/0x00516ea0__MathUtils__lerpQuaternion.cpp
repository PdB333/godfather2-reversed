// FUNC_NAME: MathUtils::lerpQuaternion
void __thiscall MathUtils::lerpQuaternion(float *fromQuat, float t, float *toQuat, float *outQuat)
{
    // Linear interpolation between two quaternions (x, y, z, w)
    // fromQuat[0..3] = source quaternion
    // t = interpolation factor (0.0 = from, 1.0 = to)
    // toQuat[0..3] = target quaternion
    // outQuat[0..3] = result quaternion

    float fromX = fromQuat[0]; // +0x00
    float fromY = fromQuat[1]; // +0x04
    float fromZ = fromQuat[2]; // +0x08
    float fromW = fromQuat[3]; // +0x0C

    float toX = toQuat[0]; // +0x00
    float toY = toQuat[1]; // +0x04
    float toZ = toQuat[2]; // +0x08
    float toW = toQuat[3]; // +0x0C

    // outQuat = fromQuat + t * (toQuat - fromQuat)
    outQuat[0] = (toX - fromX) * t + fromX;
    outQuat[1] = (toY - fromY) * t + fromY;
    outQuat[2] = (toZ - fromZ) * t + fromZ;
    outQuat[3] = (toW - fromW) * t + fromW;
}