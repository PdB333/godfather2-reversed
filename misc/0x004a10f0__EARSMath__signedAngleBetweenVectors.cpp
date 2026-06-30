// FUNC_NAME: EARSMath::signedAngleBetweenVectors
float EARSMath::signedAngleBetweenVectors(const float* from, const float* to, const float* normal)
{
    // Compute the component of 'to' perpendicular to 'normal'
    float dotToNormal = to[0] * normal[0] + to[1] * normal[1] + to[2] * normal[2];
    float vX = to[0] - dotToNormal * normal[0];
    float vY = to[1] - dotToNormal * normal[1];
    float vZ = to[2] - dotToNormal * normal[2];

    // Compute the component of 'from' perpendicular to 'normal'
    float dotFromNormal = from[0] * normal[0] + from[1] * normal[1] + from[2] * normal[2];
    float wX = from[0] - dotFromNormal * normal[0];
    float wY = from[1] - dotFromNormal * normal[1];
    float wZ = from[2] - dotFromNormal * normal[2];

    // Product of magnitudes of v and w
    float magV = sqrtf(vX * vX + vY * vY + vZ * vZ);
    float magW = sqrtf(wX * wX + wY * wY + wZ * wZ);
    float magProd = magV * magW;

    float angle = 0.0f;
    if (magProd != 0.0f)
    {
        // Cosine of the angle between v and w
        float cosAngle = (vX * wX + vY * wY + vZ * wZ) / magProd;

        // Clamp to [-1, 1] to avoid acos domain errors
        float clampedCos = cosAngle;
        if (cosAngle <= -1.0f)
            clampedCos = -1.0f;
        else if (cosAngle >= 1.0f)
            clampedCos = 1.0f;

        angle = acosf(clampedCos); // FUN_00b9b988 is acos

        // Determine sign: use scalar triple product (cross(v, w) dot normal)
        float crossX = vY * wZ - vZ * wY;
        float crossY = vZ * wX - vX * wZ;
        float crossZ = vX * wY - vY * wX;
        float sign = crossX * normal[0] + crossY * normal[1] + crossZ * normal[2];
        if (sign < 0.0f)
            angle = -angle;
    }
    return angle;
}