// FUNC_NAME: projectVectorOntoPlane
// Projects a vector onto a plane defined by a normal vector.
// Returns 1 if projection succeeded (non-degenerate plane), 0 if plane normal is too small.
// Global epsilon and mask are used for fast zero-length detection via bitwise float manipulation.
// 0x004a07f0
int projectVectorOntoPlane(float* outProjection, const float* inVector, const float* planeNormal)
{
    float fLengthSq;
    fLengthSq = planeNormal[0] * planeNormal[0] + planeNormal[1] * planeNormal[1] + planeNormal[2] * planeNormal[2];

    // Fast check for denormal/zero: compare bitwise representation of squared length against a mask.
    // DAT_00e44598 and DAT_00e44680 are global constants defined elsewhere.
    union { float f; uint32_t u; } uLengthSq;
    uLengthSq.f = fLengthSq;
    if (s_projectEpsilon < (float)(uLengthSq.u & s_projectMask))
    {
        float fDot;
        fDot = (inVector[1] * planeNormal[1] + inVector[0] * planeNormal[0] + inVector[2] * planeNormal[2]) / fLengthSq;
        outProjection[0] = inVector[0] - planeNormal[0] * fDot;
        outProjection[1] = inVector[1] - planeNormal[1] * fDot;
        outProjection[2] = inVector[2] - planeNormal[2] * fDot;
        return 1;
    }
    outProjection[0] = 0.0f;
    outProjection[1] = 0.0f;
    outProjection[2] = 0.0f;
    return 0;
}