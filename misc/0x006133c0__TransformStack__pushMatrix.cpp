// FUNC_NAME: TransformStack::pushMatrix

void __fastcall TransformStack::pushMatrix(const uint32_t* sourceMatrix, int* stackCount, uint32_t* stackBuffer)
{
    // Copy a 4x4 matrix (16 uint32s = 64 bytes) into a stack buffer with capacity 8.
    if (*stackCount < 8) {
        // Calculate destination offset: 64 bytes per slot
        uint32_t* dest = &stackBuffer[*stackCount * 0x10]; // 0x40 bytes / 4 = 0x10 uint32s
        // Copy source matrix to destination (16 uint32s)
        dest[0] = sourceMatrix[0];
        dest[1] = sourceMatrix[1];
        dest[2] = sourceMatrix[2];
        dest[3] = sourceMatrix[3];
        dest[4] = sourceMatrix[4];
        dest[5] = sourceMatrix[5];
        dest[6] = sourceMatrix[6];
        dest[7] = sourceMatrix[7];
        dest[8] = sourceMatrix[8];
        dest[9] = sourceMatrix[9];
        dest[10] = sourceMatrix[10];
        dest[11] = sourceMatrix[11];
        dest[12] = sourceMatrix[12];
        dest[13] = sourceMatrix[13];
        dest[14] = sourceMatrix[14];
        dest[15] = sourceMatrix[15];
        // Increment the stack count
        (*stackCount)++;
    }
    // If stack is full (>=8), silently ignore.
}