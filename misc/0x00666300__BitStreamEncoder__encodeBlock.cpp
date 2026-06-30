// FUNC_NAME: BitStreamEncoder::encodeBlock
int __cdecl BitStreamEncoder::encodeBlock(int unused, int numBits, int* streamState, int64_t* outputInfo)
{
    uint32_t *currentWord;
    int result;
    void *allocPtr;
    uint8_t bitCount;
    uint32_t carry;
    uint32_t newCarry;
    int64_t temp;

    if (numBits < 1) {
        result = initBitStream();  // FUN_00665ce0
        if (outputInfo != (int64_t*)0x0) {
            *(int32_t*)(outputInfo + 1) = 0; // outputInfo->field4
            *(int32_t*)outputInfo = 0;       // outputInfo->field0
            memset(*(void**)((int32_t)outputInfo + 0xc), 0, *(int32_t*)((int32_t)outputInfo + 4) * 4);
        }
        return result;
    }

    allocPtr = calloc(4, 0x40); // 4 * 64 = 256 bytes, or maybe 4 * 0x40 = 4 * 64 = 256? Actually calloc(4,0x40) -> 4 elements of size 64? But calloc(num,size) typically num*size. So 4*64=256.
    if (allocPtr == (void*)0x0) {
        return -2;
    }
    temp = (int64_t)(uint64_t)(intptr_t)allocPtr << 32; // store pointer in upper 32 bits of 64-bit value

    if (((outputInfo == (int64_t*)0x0) || (result = acquireBuffer(numBits), result == 0)) &&
        (result = initBitStream(), result == 0)) {
        if (0x1b < numBits) {
            adjustBlockSize(numBits / 0x1c); // FUN_0066a4d0
        }
        if (numBits % 0x1c != 0) {
            // Bit packing: shift each word right by (numBits % 28) and propagate the low bits to the next word
            bitCount = (uint8_t)(numBits % 0x1c);
            carry = 0;
            // streamState[0] = number of words to process
            // streamState[3] = pointer to the word array
            currentWord = (uint32_t*)(streamState[3] - 4 + (*streamState) * 4); // pointer to last word
            int wordsRemaining = *streamState;
            while (wordsRemaining = wordsRemaining - 1, -1 < wordsRemaining) {
                newCarry = carry << (0x1c - bitCount);
                carry = *currentWord & ((1 << bitCount) - 1);
                *currentWord = (*currentWord >> bitCount) | newCarry;
                currentWord = currentWord - 1;
            }
        }
        commitBuffer(); // FUN_00665b10
        if (outputInfo != (int64_t*)0x0) {
            *outputInfo = 0x4000000000LL; // magic constant
            outputInfo[1] = temp; // packed pointer
        }
        finalizeStream(); // FUN_00665b40
        return 0;
    }
    finalizeStream(); // FUN_00665b40
    return result;
}