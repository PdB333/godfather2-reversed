// FUNC_NAME: normalizeThreeVec4

// Normalizes three consecutive 4-element vectors (quaternions) to a target length.
// used in animation bone processing to ensure consistent quaternion magnitudes.
extern const float DAT_00e2cbe0; // epsilon threshold
extern const float DAT_00e2b1a4; // desired length (typically 1.0f for unit quaternions)

void __fastcall normalizeThreeVec4(const float* input, float* output)
{
    float lenSq;
    float scale;

    // First quaternion (indices 0..3)
    lenSq = input[0] * input[0] + input[1] * input[1] + input[2] * input[2] + input[3] * input[3];
    if (lenSq <= DAT_00e2cbe0)
    {
        scale = 0.0f;
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(lenSq);
    }
    output[0] = input[0] * scale;
    output[1] = input[1] * scale;
    output[2] = input[2] * scale;
    output[3] = input[3] * scale;

    // Second quaternion (indices 4..7)
    lenSq = input[4] * input[4] + input[5] * input[5] + input[6] * input[6] + input[7] * input[7];
    if (lenSq <= DAT_00e2cbe0)
    {
        scale = 0.0f;
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(lenSq);
    }
    output[4] = input[4] * scale;
    output[5] = input[5] * scale;
    output[6] = input[6] * scale;
    output[7] = input[7] * scale;

    // Third quaternion (indices 8..11)
    lenSq = input[8] * input[8] + input[9] * input[9] + input[10] * input[10] + input[11] * input[11];
    if (lenSq <= DAT_00e2cbe0)
    {
        scale = 0.0f;
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(lenSq);
    }
    output[8] = input[8] * scale;
    output[9] = input[9] * scale;
    output[10] = input[10] * scale;
    output[11] = input[11] * scale;
}