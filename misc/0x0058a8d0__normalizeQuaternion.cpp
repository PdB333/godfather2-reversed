// FUNC_NAME: normalizeQuaternion
void __fastcall normalizeQuaternion(float* quat)
{
    float fVar1;
    float fVar2;

    fVar1 = *quat;
    // Compute squared length of quaternion (w, x, y, z)
    fVar2 = fVar1 * fVar1 + quat[1] * quat[1] + quat[2] * quat[2] + quat[3] * quat[3];

    // Threshold to avoid division by zero (possibly ~1e-10f)
    if (fVar2 <= 0.0f) { // DAT_00e2cbe0 is likely 0.0f or epsilon
        fVar2 = 0.0f;
    }
    else {
        // Scale factor to normalize to length 1.0 (DAT_00e2b1a4 is probably 1.0f)
        fVar2 = 1.0f / sqrtf(fVar2); // DAT_00e2b1a4 / SQRT(fVar2) where DAT ~1.0
    }

    *quat = fVar1 * fVar2;
    quat[1] = quat[1] * fVar2;
    quat[2] = quat[2] * fVar2;
    quat[3] = quat[3] * fVar2;
}