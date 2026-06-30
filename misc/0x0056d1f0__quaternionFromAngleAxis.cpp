// FUNC_NAME: quaternionFromAngleAxis
// Function address: 0x0056d1f0
// Converts an angle-axis vector (axis stored in first 3 components, angle implied by length? Actually uses param_1[3] too) to a quaternion.
// The computation uses a global epsilon, 0.5 factor, and a mysterious FUN_00b99e20 (likely sin/cos).

void quaternionFromAngleAxis(float* inVec, float* outQuat)
{
    // Constants (likely)
    // DAT_00e2e210: small epsilon (e.g., 1e-6)
    // DAT_00e2b1a4: 1.0f (identity quaternion w)
    // DAT_00e2cd54: 0.5f (half angle factor)

    float axisLen = sqrt(inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2]);

    if (axisLen < DAT_00e2e210) {
        outQuat[0] = 0.0f;
        outQuat[1] = 0.0f;
        outQuat[2] = 0.0f;
        outQuat[3] = DAT_00e2b1a4; // identity quaternion (0,0,0,1)
        return;
    }

    double halfAngle = (double)(axisLen * DAT_00e2cd54); // half of the rotation angle
    FUN_00b99e20(); // Likely computes sin and cos of halfAngle (missing arguments? Possibly modifies global state)
    float sinHalf = (float)halfAngle; // In the original code, this is assigned to fVar6 from dVar7

    outQuat[3] = sinHalf; // set w to sin of half angle? (but later overwritten)

    float y = inVec[1];
    float z = inVec[2];
    float wInput = inVec[3]; // Used? overwritten later.

    // Compute scaleFactor = cos(halfAngle) / axisLen? Actually sqrt(1 - sinHalf^2) = cos(halfAngle) if sinHalf were sin, but it's just the angle.
    float cosHalfOverLen = sqrt(DAT_00e2b1a4 - sinHalf * sinHalf) / axisLen; // cosHalfApprox / len

    outQuat[0] = cosHalfOverLen * inVec[0];
    outQuat[1] = cosHalfOverLen * y;
    outQuat[2] = cosHalfOverLen * z;
    outQuat[3] = cosHalfOverLen * wInput; // temporarily set, then overwritten below
    outQuat[3] = sinHalf; // restore w to sinHalf (the original half angle value)
}