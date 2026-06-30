// FUNC_NAME: MathUtils::quaternionNormalizeSafe
// Address: 0x004176a0
// Normalizes a quaternion (4 floats) with an epsilon check to avoid division by zero.
// Constants: DAT_00e2cbe0 = small epsilon (e.g., 1e-6), DAT_00e2b1a4 = 1.0f (normalization factor).

void __fastcall MathUtils::quaternionNormalizeSafe(float* quat) // quat in ECX (source/dest same pointer)
{
    float lenSq; // fVar2

    // Compute squared length
    lenSq = quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] + quat[3] * quat[3];

    // If below epsilon, result becomes zero (safe guard)
    if (lenSq <= DAT_00e2cbe0) // epsilon threshold
    {
        lenSq = 0.0f;
    }
    else
    {
        // fVar2 = 1.0f / sqrt(lenSq) (normalization factor)
        lenSq = DAT_00e2b1a4 / sqrtf(lenSq);
    }

    // Multiply each component by the scale factor
    quat[0] *= lenSq;
    quat[1] *= lenSq;
    quat[2] *= lenSq;
    quat[3] *= lenSq;
}