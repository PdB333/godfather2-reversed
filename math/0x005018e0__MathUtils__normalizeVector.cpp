// FUNC_NAME: MathUtils::normalizeVector
// 0x005018e0 - Normalizes a 3D vector with a dead zone threshold, optionally scaling to a given magnitude.
// Input vector passed via EAX (custom calling convention), output vector via stack parameter.
void __fastcall MathUtils::normalizeVector(const float *inVec, float *outVec)
{
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];

    // Compute squared length
    float lengthSq = x * x + y * y + z * z;

    // DAT_00e2cbe0 = epsilon threshold (likely ~0.0f, e.g., 1e-8f)
    // DAT_00e2b1a4 = scale factor for normalization (1.0f for unit length)
    float invLength;
    if (lengthSq <= *reinterpret_cast<const float*>(0x00e2cbe0)) {
        invLength = 0.0f;
    } else {
        invLength = *reinterpret_cast<const float*>(0x00e2b1a4) / sqrtf(lengthSq);
    }

    outVec[0] = x * invLength;
    outVec[1] = y * invLength;
    outVec[2] = z * invLength;
}