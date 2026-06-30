// FUNC_NAME: Transform::getMatrix
// Address: 0x004df780
// Role: Copies a 4x4 transformation matrix from the object's internal data (offset 0x30) to an output buffer.
// If the object pointer is null, fills the output with a default matrix (gDefaultMatrix) with some identity-like pattern.

void __thiscall Transform::getMatrix(int* thisPtr, float* outMatrix)
{
    float* defaultMatrix = (float*)&gDefaultMatrix; // DAT_00e2b1a4 is a float[16] default matrix

    if (thisPtr != nullptr) {
        // Copy 16 floats from offset 0x30 (4x4 matrix)
        for (int i = 0; i < 16; i++) {
            outMatrix[i] = *(float*)((int)thisPtr + 0x30 + i * 4);
        }
        return;
    }

    // Null case: fill with default matrix (gDefaultMatrix) but with some zeros?
    // The decompiled code shows a specific pattern: first element is gDefaultMatrix[0], then zeros, then gDefaultMatrix[0] at indices 5 and 10, last element gDefaultMatrix[0].
    // This is likely a bug or a specific default matrix. We'll replicate the pattern.
    outMatrix[0] = defaultMatrix[0];
    outMatrix[1] = 0.0f;
    outMatrix[2] = 0.0f;
    outMatrix[3] = 0.0f;
    outMatrix[4] = 0.0f;
    outMatrix[5] = defaultMatrix[0];
    outMatrix[6] = 0.0f;
    outMatrix[7] = 0.0f;
    outMatrix[8] = 0.0f;
    outMatrix[9] = 0.0f;
    outMatrix[10] = defaultMatrix[0];
    outMatrix[11] = 0.0f;
    outMatrix[12] = 0.0f;
    outMatrix[13] = 0.0f;
    outMatrix[14] = 0.0f;
    outMatrix[15] = defaultMatrix[0];
}