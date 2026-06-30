// FUNC_NAME: MathUtils::quaternionRotateVector
static void quaternionRotateVector(const float* quat, const float* inVec, float* outVec)
{
    // DAT_00e44564 is a global constant, likely 0.0f. Negate first three components for conjugate.
    // The quaternion is assumed to be [x, y, z, w] (w last).
    float negQuat[4];
    negQuat[0] = -quat[0];   // -x
    negQuat[1] = -quat[1];   // -y
    negQuat[2] = -quat[2];   // -z
    negQuat[3] =  quat[3];   //  w (unchanged)

    // Temporary buffer for intermediate product (size unknown, assume 28 bytes = 7 floats)
    // Possibly stores a quaternion or matrix result.
    char temp[28];  // placeholder size

    // First multiply: quat * inVec (or some representation of the vector)
    // FUN_0056cba0 is likely a quaternion multiplication or vector transformation.
    FUN_0056cba0(quat, inVec, temp);

    // Second multiply: (temp) * conj(quat) to get final rotated vector
    FUN_0056cba0(temp, &negQuat[0], outVec);
}