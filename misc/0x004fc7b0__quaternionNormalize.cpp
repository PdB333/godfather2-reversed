// FUNC_NAME: quaternionNormalize
// Function address: 0x004fc7b0
// Role: Normalize a 4-component quaternion (or 4D vector) with zero-length protection.
// Input: pointer to source quaternion (4 floats) in ECX (in_EAX)
// Output: pointer to destination quaternion (4 floats) in EDX (param_1)
// Constants: DAT_00e2cbe0 = epsilon threshold, DAT_00e2b1a4 = normalization factor (likely 1.0f)

void __fastcall quaternionNormalize(const float* inQuat, float* outQuat)
{
    float sqLen = inQuat[0] * inQuat[0] + inQuat[1] * inQuat[1] + inQuat[2] * inQuat[2] + inQuat[3] * inQuat[3];
    float invLen;

    // Check against epsilon to avoid division by zero
    if (sqLen <= DAT_00e2cbe0) // epsilon threshold (e.g., 1e-10f)
    {
        invLen = 0.0f;
    }
    else
    {
        invLen = DAT_00e2b1a4 / sqrtf(sqLen); // DAT_00e2b1a4 is likely 1.0f
    }

    outQuat[0] = inQuat[0] * invLen;
    outQuat[1] = inQuat[1] * invLen;
    outQuat[2] = inQuat[2] * invLen;
    outQuat[3] = inQuat[3] * invLen;
}