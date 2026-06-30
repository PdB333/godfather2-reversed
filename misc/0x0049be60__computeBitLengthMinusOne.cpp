// FUNC_NAME: computeBitLengthMinusOne
short computeBitLengthMinusOne(unsigned short x) {
    short result = 0;
    unsigned short m = x - 1;
    short shift = 0xF; // start at 15 (highest bit index for 16-bit)

    // If m is nonzero, find the index of the most significant set bit
    if (m != 0) {
        while ((m >> shift) == 0) {
            shift--;
        }
    }

    // If m was nonzero, result = highest bit index + 1 = bit length of m
    if (m != 0) {
        result = shift + 1;
    }

    return result;
}