// FUNC_NAME: memset_bitfield
void memset_bitfield(uint32_t* bitfield, int bitCount)
{
    int numWords;
    int i;

    // Calculate number of 32-bit words needed to cover bitCount bits
    numWords = (bitCount + 31) >> 5;

    // Clear each word in the bitfield
    for (i = 0; i < numWords; i++) {
        bitfield[i] = 0;
    }
}