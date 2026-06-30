// FUNC_NAME: MathUtil::lerpQuaternion
void __fastcall MathUtil::lerpQuaternion(float *outQuat, float *fromQuat, float *toQuat, float t)
{
    // Interpolate the first three components (vector part) linearly
    outQuat[0] = (toQuat[0] - fromQuat[0]) * t + fromQuat[0]; // +0x00: x
    outQuat[1] = (toQuat[1] - fromQuat[1]) * t + fromQuat[1]; // +0x04: y
    outQuat[2] = (toQuat[2] - fromQuat[2]) * t + fromQuat[2]; // +0x08: z

    // Preserve the original scalar component (w) from the output quaternion
    // This is likely a bug or intentional for specific use (e.g., only interpolating vector part)
    outQuat[3] = outQuat[3]; // +0x0C: w (unchanged)
}