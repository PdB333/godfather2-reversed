// FUNC_NAME: computeProjectedAngleCosine
float computeProjectedAngleCosine(const float* vectorA, const float* vectorB, const float* planeNormal)
{
    // Global constants from the game executable (likely 1.0f, -1.0f, 0.0f)
    const float kOne = 1.0f;               // DAT_00e2b1a4
    const float kMinusOne = -1.0f;         // DAT_00e2eff4 (used both as projection factor and clamp lower bound)
    const float kZero = 0.0f;              // DAT_00e2b05c

    // Project vector B onto the plane orthogonal to planeNormal: v' = v + (-1)*(v·n)*n
    float dotBN = vectorB[0] * planeNormal[0] + vectorB[1] * planeNormal[1] + vectorB[2] * planeNormal[2];
    float projBX = planeNormal[0] * dotBN * kMinusOne + vectorB[0]; // equivalent to v - (v·n)*n
    float projBY = planeNormal[1] * dotBN * kMinusOne + vectorB[1];
    float projBZ = planeNormal[2] * dotBN * kMinusOne + vectorB[2];

    // Project vector A onto the same plane
    float dotAN = vectorA[0] * planeNormal[0] + vectorA[1] * planeNormal[1] + vectorA[2] * planeNormal[2];
    float projAX = planeNormal[0] * dotAN * kMinusOne + vectorA[0];
    float projAY = planeNormal[1] * dotAN * kMinusOne + vectorA[1];
    float projAZ = planeNormal[2] * dotAN * kMinusOne + vectorA[2];

    // Compute magnitudes and dot product of the projected vectors
    float magB = sqrt(projBX * projBX + projBY * projBY + projBZ * projBZ);
    float magA = sqrt(projAX * projAX + projAY * projAY + projAZ * projAZ);
    float magProduct = magA * magB;

    // Default return value if degeneracy (one vector is zero or parallel to normal)
    float cosine = kOne;
    if (magProduct != kZero)
    {
        cosine = (projAX * projBX + projAY * projBY + projAZ * projBZ) / magProduct;
        // Clamp cosine to valid range [-1, 1]
        if (kOne < cosine)
        {
            return kOne;
        }
        if (cosine < kMinusOne)
        {
            cosine = kMinusOne;
        }
    }
    return cosine;
}