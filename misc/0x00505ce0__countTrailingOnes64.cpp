// FUNC_NAME: countTrailingOnes64
// Function at 0x00505ce0: Counts the number of trailing consecutive 1 bits in a 64-bit value.
// Input: uHigh32 (high 32 bits), uLow32 (low 32 bits)
// Returns: count of trailing ones (0-64)
int countTrailingOnes64(uint uHigh32, uint uLow32)
{
    int trailingOnes = 0;

    // If all high 32 bits are 1, they contribute 32 trailing ones,
    // and we continue counting from the low 32 bits.
    if (uHigh32 == 0xffffffff) {
        uHigh32 = uLow32;
        trailingOnes = 0x20;
    }

    uint value = uHigh32; // now the relevant 32 bits

    // Check if lower 16 bits are all ones (0xFFFF)
    if ((short)value == -1) {
        value >>= 0x10;
        trailingOnes += 0x10;
    }
    // Check if lower 8 bits are all ones (0xFF)
    if ((char)value == -1) {
        value >>= 8;
        trailingOnes += 8;
    }
    // Check if lower 4 bits are all ones (0xF)
    if ((value & 0xf) == 0xf) {
        value >>= 4;
        trailingOnes += 4;
    }
    // Check if lower 2 bits are all ones (0x3)
    if ((value & 3) == 3) {
        value >>= 2;
        trailingOnes += 2;
    }
    // Check if the lowest bit is 1
    if ((value & 1) != 0) {
        trailingOnes += 1;
    }

    return trailingOnes;
}