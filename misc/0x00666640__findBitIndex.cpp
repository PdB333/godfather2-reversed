// FUNC_NAME: findBitIndex
// Function at 0x00666640: Utility to find the index (1-based, bits 1-27) of a single set bit in a mask.
// Input mask in EAX (passed implicitly), output index written to pIndex.
// Returns 1 if mask is a power of two in range [2^1, 2^27], 0 otherwise.
int findBitIndex(int mask /* from EAX */, int* pIndex)
{
    int i = 1;
    do {
        if (mask == (1 << (i & 0x1f))) {
            *pIndex = i;
            return 1;
        }
        i = i + 1;
    } while (i < 0x1c); // 28
    return 0;
}