// FUNC_NAME: clearBitArray
void clearBitArray(unsigned int* buffer, int numBits)
{
    // Compute number of 32-bit dwords needed to store numBits
    int numDwords = (numBits + 31) >> 5;

    // Only zero if there is at least one dword
    if (buffer < buffer + numDwords) {
        int count = numDwords;
        do {
            *buffer = 0;
            ++buffer;
            --count;
        } while (count != 0);
    }
}