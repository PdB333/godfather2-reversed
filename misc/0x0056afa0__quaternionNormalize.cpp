// FUNC_NAME: quaternionNormalize
// Function at 0x0056afa0: Normalizes a 4-component vector (quaternion) and returns its original length.
// If the squared length is zero (or below epsilon), the output is set to zero and length 0 is returned.
// The global constants are: gNormEpsilon (DAT_00e2cbe0) and gNormScale (DAT_00e2b1a4, typically 1.0f).

// Declare global constants (these are actually located at fixed addresses in the original binary)
extern const float gNormEpsilon;   // 0x00e2cbe0
extern const float gNormScale;     // 0x00e2b1a4

float quaternionNormalize(const float* inQuat, float* outQuat)
{
    // Compute squared length of the quaternion (w,x,y,z assumed)
    float lenSq = inQuat[0] * inQuat[0] + inQuat[1] * inQuat[1] +
                 inQuat[2] * inQuat[2] + inQuat[3] * inQuat[3];

    float len;
    float invLen;

    if (lenSq <= gNormEpsilon)
    {
        // Zero-length quaternion: output zero, return 0
        invLen = 0.0f;
        len = 0.0f;
    }
    else
    {
        len = sqrtf(lenSq);
        invLen = gNormScale / len;   // Typically 1.0f / len
    }

    // Write normalized components
    outQuat[0] = inQuat[0] * invLen;
    outQuat[1] = inQuat[1] * invLen;
    outQuat[2] = inQuat[2] * invLen;
    outQuat[3] = inQuat[3] * invLen;

    return len;
}