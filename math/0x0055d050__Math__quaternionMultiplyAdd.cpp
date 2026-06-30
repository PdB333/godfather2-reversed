// FUNC_NAME: Math::quaternionMultiplyAdd
void __thiscall Math::quaternionMultiplyAdd(float *result, float *quatA, float *quatB)
{
    // Quaternion multiplication with scaling: result = quatA * quatB * scale
    // Each quaternion is [x, y, z, w]
    float wA = quatA[3]; // +0x0C
    float wA_sq_minus = wA * wA - DAT_00e2cd54; // wA^2 - 1.0 (probably)
    
    float xB = quatB[0]; // +0x00
    // Dot product of vector parts: quatA.xyz · quatB.xyz
    float dotVec = quatA[0] * quatB[0] + quatA[1] * quatB[1] + quatA[2] * quatB[2];
    
    // Cross product components scaled by wA
    // x-component of cross: quatA.y * quatB.z - quatA.z * quatB.y
    float crossX = quatA[1] * quatB[2] - quatA[2] * quatB[1];
    float crossY = quatA[2] * quatB[0] - quatA[0] * quatB[2];
    float crossZ = quatA[0] * quatB[1] - quatA[1] * quatB[0];
    
    // Result x: crossX * wA + quatA.x * dotVec + quatB.x * (wA^2 - 1)
    float tempX = crossX * wA + quatA[0] * dotVec + quatB[0] * wA_sq_minus;
    float tempY = crossY * wA + quatA[1] * dotVec + quatB[1] * wA_sq_minus;
    float tempZ = crossZ * wA + quatA[2] * dotVec + quatB[2] * wA_sq_minus;
    float tempW = wA * DAT_00e2b05c + wA * dotVec + quatB[3] * wA_sq_minus; // DAT_00e2b05c might be 1.0
    
    float scale = DAT_00e2b04c; // Scaling factor
    
    result[0] = tempX * scale;
    result[1] = tempY * scale;
    result[2] = tempZ * scale;
    result[3] = tempW * scale;
}