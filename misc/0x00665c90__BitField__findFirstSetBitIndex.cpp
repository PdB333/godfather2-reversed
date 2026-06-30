// FUNC_NAME: BitField::findFirstSetBitIndex
// Function at 0x00665c90: finds the index of the first set bit in a bitmap stored as 28-bit words.
// The bitmap is an array of uint32 values at offset +0x0C.
// The first field (+0x00) is the number of words.
// Returns the linear bit index = wordIndex * 28 + bitPosition
int BitField::findFirstSetBitIndex(void)
{
    int wordCount = *(int*)this;            // +0x00
    if (wordCount == 0) {
        return 0;
    }

    uint32* words = *(uint32**)((int)this + 0x0C); // +0x0C pointer to word array

    int wordIndex = 0;
    if (0 < wordCount) {
        do {
            if (words[wordIndex] != 0) break;
            wordIndex++;
        } while (wordIndex < wordCount);
    }

    // wordIndex now points to the first non-zero word
    int result = wordIndex * 0x1c;           // 28 bits per word
    uint32 wordVal = words[wordIndex];
    while ((wordVal & 1) == 0) {
        result++;
        wordVal >>= 1;
    }
    return result;
}