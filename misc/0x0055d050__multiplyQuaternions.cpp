// FUNC_NAME: multiplyQuaternions
// Function at 0x0055d050: Multiplies two quaternions (param2 * param3) and stores result in param1.
// Quaternion layout: [x, y, z, w] (w scalar). Constants unknown (likely 1.0, 0.5, etc.)
void __thiscall multiplyQuaternions(float *outQuat, float *quatA, float *quatB)
{
    float wA = quatA[3]; // +0x0C: scalar part of first quaternion
    float wSqMinus1 = wA * wA - DAT_00e2cd54; // wA^2 - unknown constant (possibly 1.0)

    // Dot product of vector parts
    float dot = quatA[2] * quatB[2] + quatA[1] * quatB[1] + quatA[0] * quatB[0];

    // Cross product components and final result
    float tempY = ((quatB[0] * quatA[2] - quatA[0] * quatB[2]) * wA +
                   quatA[1] * dot + quatB[1] * wSqMinus1) * DAT_00e2b04c;

    float tempZ = ((quatA[0] * quatB[1] - quatB[0] * quatA[1]) * wA +
                   quatA[2] * dot + quatB[2] * wSqMinus1) * DAT_00e2b04c;

    float tempW = (wA * DAT_00e2b05c + wA * dot + quatB[3] * wSqMinus1) * DAT_00e2b04c;

    outQuat[0] = ((quatB[2] * quatA[1] - quatB[1] * quatA[2]) * wA +
                   quatA[0] * dot + quatB[0] * wSqMinus1) * DAT_00e2b04c;
    outQuat[1] = tempY;
    outQuat[2] = tempZ;
    outQuat[3] = tempW;
}