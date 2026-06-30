// FUNC_NAME: MathUtils::normalizeQuaternionArray
void __fastcall normalizeQuaternionArray(float* output, const float* input)
{
    // Global constants: minimum length threshold (0x00e2cbe0) and target length (0x00e2b1a4)
    static const float kMinLengthThreshold = 0.0f;  // placeholder – actual value from DAT_00e2cbe0
    static const float kTargetLength = 1.0f;        // placeholder – actual value from DAT_00e2b1a4

    float lengthSq;
    float scale;

    // Normalize quaternion 0 (elements 0-3)
    lengthSq = input[0]*input[0] + input[1]*input[1] + input[2]*input[2] + input[3]*input[3];
    if (lengthSq <= kMinLengthThreshold) {
        scale = 0.0f;
    } else {
        scale = kTargetLength / __sqrtf(lengthSq);
    }
    output[0] = input[0] * scale;
    output[1] = input[1] * scale;
    output[2] = input[2] * scale;
    output[3] = input[3] * scale;

    // Normalize quaternion 1 (elements 4-7)
    lengthSq = input[4]*input[4] + input[5]*input[5] + input[6]*input[6] + input[7]*input[7];
    if (lengthSq <= kMinLengthThreshold) {
        scale = 0.0f;
    } else {
        scale = kTargetLength / __sqrtf(lengthSq);
    }
    output[4] = input[4] * scale;
    output[5] = input[5] * scale;
    output[6] = input[6] * scale;
    output[7] = input[7] * scale;

    // Normalize quaternion 2 (elements 8-11)
    lengthSq = input[8]*input[8] + input[9]*input[9] + input[10]*input[10] + input[11]*input[11];
    if (lengthSq <= kMinLengthThreshold) {
        scale = 0.0f;
    } else {
        scale = kTargetLength / __sqrtf(lengthSq);
    }
    output[8]  = input[8]  * scale;
    output[9]  = input[9]  * scale;
    output[10] = input[10] * scale;
    output[11] = input[11] * scale;
}