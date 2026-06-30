// FUNC_NAME: normalizeQuat
void normalizeQuat(const float* input, float* output)
{
    // Compute squared length of the 4D vector (quaternion)
    float lenSq = input[0] * input[0] + input[1] * input[1] + input[2] * input[2] + input[3] * input[3];
    float scale;
    // If the length is effectively zero, avoid division by zero
    if (lenSq <= 0.0f) // DAT_00e2cbe0 is likely 0.0f (epsilon threshold)
    {
        scale = 0.0f;
    }
    else
    {
        // DAT_00e2b1a4 is the normalization target (e.g., 1.0f for unit quaternion)
        scale = 1.0f / sqrtf(lenSq); // Actually DAT_00e2b1a4 / sqrt(lenSq), but assuming DAT_00e2b1a4 == 1.0f
    }
    // Scale all components
    output[0] = input[0] * scale;
    output[1] = input[1] * scale;
    output[2] = input[2] * scale;
    output[3] = input[3] * scale;
}