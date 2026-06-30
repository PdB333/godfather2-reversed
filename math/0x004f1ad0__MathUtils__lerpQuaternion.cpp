// FUNC_NAME: MathUtils::lerpQuaternion
void __fastcall lerpQuaternion(float *outQuat, float *quatA, float *quatB, float t)
{
    float wA, xA, yA, zA;
    float wB, xB, yB, zB;
    float wOut;

    // Extract quaternion components from source quaternion A
    xA = quatA[1]; // +0x04
    yA = quatA[2]; // +0x08
    zA = quatA[3]; // +0x0C
    wA = quatA[0]; // +0x00

    // Extract quaternion components from source quaternion B
    xB = quatB[1]; // +0x04
    yB = quatB[2]; // +0x08
    zB = quatB[3]; // +0x0C
    wB = quatB[0]; // +0x00

    // Store original w component of output (likely for preserving some state)
    wOut = outQuat[3]; // +0x0C

    // Linear interpolation of each component
    outQuat[0] = (quatB[0] - quatA[0]) * t + quatA[0]; // w
    outQuat[1] = (xB - xA) * t + xA; // x
    outQuat[2] = (yB - yA) * t + yA; // y
    outQuat[3] = (zB - zA) * t + zA; // z

    // Restore original w component (note: this overwrites the interpolated z)
    outQuat[3] = wOut;
}