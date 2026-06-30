// FUNC_NAME: quaternionNormalizeAndEnsurePositiveW (0x0055aa00) - Normalizes a quaternion and ensures the scalar (w) component is positive.
void quaternionNormalizeAndEnsurePositiveW(float* srcQuat, float* dstQuat)
{
    // Copy source quaternion to destination
    dstQuat[0] = srcQuat[0];
    dstQuat[1] = srcQuat[1];
    dstQuat[2] = srcQuat[2];
    dstQuat[3] = srcQuat[3];

    // Compute squared length of the vector part (x, y, z)
    float lengthSq = dstQuat[0] * dstQuat[0] + dstQuat[1] * dstQuat[1] + dstQuat[2] * dstQuat[2];

    if (lengthSq != 0.0f) {
        float invLength = 1.0f / sqrtf(lengthSq);
        dstQuat[0] *= invLength;
        dstQuat[1] *= invLength;
        dstQuat[2] *= invLength;
        dstQuat[3] *= invLength;
    }
    // If lengthSq is zero, the quaternion becomes zero (all components multiplied by zero)

    // Ensure w is positive: if original w is non-positive and non-zero, negate the entire quaternion
    if (srcQuat[3] <= 0.0f && srcQuat[3] != 0.0f) {
        dstQuat[0] = -dstQuat[0];
        dstQuat[1] = -dstQuat[1];
        dstQuat[2] = -dstQuat[2];
        dstQuat[3] = -dstQuat[3];
    }
}