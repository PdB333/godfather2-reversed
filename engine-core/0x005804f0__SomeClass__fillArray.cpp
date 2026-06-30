// FUNC_NAME: SomeClass::fillArray
void SomeClass::fillArray(void)
{
    // Global fill value (e.g., 0 or a sentinel)
    uint32_t fillValue = DAT_00e2b1a4;
    // Number of elements (each element is 16 bytes)
    int32_t elementCount = *(int32_t *)(this + 0x0C);
    // Pointer to the start of the element array (offset +0x10)
    uint32_t *buffer = (uint32_t *)(this + 0x10);
    // Process in blocks of 8 elements (128 bytes = 32 dwords)
    int32_t fullBlocks = elementCount >> 3;
    if (fullBlocks > 0) {
        do {
            buffer[0]  = fillValue;
            buffer[1]  = fillValue;
            buffer[2]  = fillValue;
            buffer[3]  = fillValue;
            buffer[4]  = fillValue;
            buffer[5]  = fillValue;
            buffer[6]  = fillValue;
            buffer[7]  = fillValue;
            buffer[8]  = fillValue;
            buffer[9]  = fillValue;
            buffer[10] = fillValue;
            buffer[11] = fillValue;
            buffer[12] = fillValue;
            buffer[13] = fillValue;
            buffer[14] = fillValue;
            buffer[15] = fillValue;
            buffer[16] = fillValue;
            buffer[17] = fillValue;
            buffer[18] = fillValue;
            buffer[19] = fillValue;
            buffer[20] = fillValue;
            buffer[21] = fillValue;
            buffer[22] = fillValue;
            buffer[23] = fillValue;
            buffer[24] = fillValue;
            buffer[25] = fillValue;
            buffer[26] = fillValue;
            buffer[27] = fillValue;
            buffer[28] = fillValue;
            buffer[29] = fillValue;
            buffer[30] = fillValue;
            buffer[31] = fillValue;
            buffer += 32;
            fullBlocks--;
        } while (fullBlocks > 0);
    }
    // Handle remaining elements (1 element = 4 dwords = 16 bytes)
    int32_t remaining = elementCount & 7;
    if (remaining != 0) {
        do {
            buffer[0] = fillValue;
            buffer[1] = fillValue;
            buffer[2] = fillValue;
            buffer[3] = fillValue;
            buffer += 4;
            remaining--;
        } while (remaining > 0);
    }
}