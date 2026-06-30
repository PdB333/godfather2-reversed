// FUNC_NAME: AudioMixer::computeOutputSample
int AudioMixer::computeOutputSample(float* inputData) // inputData passed in EAX
{
    float sumA = (inputData[3] + inputData[0]) * 0.5f; // DAT_00e2cd54 = 0.5? (common half)
    float sumB = (inputData[4] + inputData[1]) * 0.5f;
    float sumC = (inputData[5] + inputData[2]) * 0.5f;

    // Get thread-local game pointer, then some global offset
    int* fsBase = (int*)(__readfsdword(0x2c));
    int globalPtr = **(int**)(fsBase); // typical EARS pattern
    int someObject = *(int*)(globalPtr + 0x24);

    // Read 3x4 rotation/scale matrix (stored column-major?) from object + 0x80
    float* mat = (float*)(someObject + 0x80); // +0x80: first row, +0x84: second, +0x88: third, +0x8c: fourth?

    // Combine with inputData[7..0x16] (16 floats) and constants
    float dot1 = (sumB * inputData[12] + sumA * inputData[8] + sumC * inputData[16] + 0.0f * inputData[20]); // DAT_00e2b1a4 likely 0
    float dot2 = (sumB * inputData[13] + sumA * inputData[9] + sumC * inputData[17] + 0.0f * inputData[21]);
    float dot3 = (sumB * inputData[14] + sumA * inputData[10] + sumC * inputData[18] + 0.0f * inputData[22]);
    float dot4 = (sumB * inputData[11] + sumA * inputData[7] + sumC * inputData[15] + 0.0f * inputData[19]);

    float value = ( DAT_00e44564 - 
                    (mat[1] * dot1 + mat[2] * dot2 + mat[3] * dot3 + mat[0] * dot4) // mat[0] is at +0x80
                  + DAT_00e44628 ) * DAT_00e445d0;

    // Clamp to [0, DAT_00e44624]
    if (value < 0.0f)
        value = 0.0f;
    else if (value > 1.0f) // DAT_00e44624 likely 1.0
        value = 1.0f;

    int result = (int)(value * 256.0f + 0.5f); // ROUND and left shift 8
    return result << 8; // Equivalent to * 256, but keeping original shift logic
}