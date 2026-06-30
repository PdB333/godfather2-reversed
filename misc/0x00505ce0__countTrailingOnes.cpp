// FUNC_NAME: countTrailingOnes
// 0x00505ce0: Counts consecutive trailing 1 bits across a 64-bit span (low 32 bits = value, high 32 bits = nextValue). Used in bitstream unpacking.
int countTrailingOnes(uint32_t value, uint32_t nextValue) {
    int count = 0; // +0x00: accumulator for number of trailing ones

    // If the low word is entirely 1s, we have 32 trailing ones so far,
    // then continue counting into the high word.
    if (value == 0xffffffff) {
        value = nextValue;
        count = 32;
    }

    // Check low 16 bits: all ones?
    if ((short)value == -1) {
        value >>= 16;
        count += 16;
    }

    // Check low 8 bits: all ones?
    if ((char)value == -1) {
        value >>= 8;
        count += 8;
    }

    // Check low 4 bits: all ones?
    if ((value & 0xf) == 0xf) {
        value >>= 4;
        count += 4;
    }

    // Check low 2 bits: all ones?
    if ((value & 3) == 3) {
        value >>= 2;
        count += 2;
    }

    // Check the last remaining bit.
    if ((value & 1) != 0) {
        count += 1;
    }

    return count;
}