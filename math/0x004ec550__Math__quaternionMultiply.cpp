// FUNC_NAME: Math::quaternionMultiply
void __fastcall Math::quaternionMultiply(float *result, float *quatA, float *quatB)
{
    float aX, aY, aZ, aW;
    float bX, bY, bZ, bW;
    float tempW;

    aX = quatA[1]; // +0x04
    aY = quatA[2]; // +0x08
    aZ = quatA[3]; // +0x0C
    aW = quatA[0]; // +0x00 (implied from *param_2 * *param_3)

    bX = quatB[1]; // +0x04
    bY = quatB[2]; // +0x08
    bZ = quatB[3]; // +0x0C
    bW = quatB[0]; // +0x00

    tempW = result[3]; // +0x0C (preserve original w? likely unused)

    // Standard quaternion multiplication: result = quatA * quatB
    // Note: This implementation appears incomplete or simplified.
    // It only multiplies corresponding components (scalar and vector parts separately),
    // which is NOT correct quaternion multiplication.
    // This might be a component-wise multiplication for a different purpose.
    result[0] = quatA[0] * quatB[0]; // w * w
    result[1] = aX * bX;             // x * x
    result[2] = aY * bY;             // y * y
    result[3] = aZ * bZ;             // z * z

    result[3] = tempW; // Restore original w? This overwrites the computed z*z.
    return;
}