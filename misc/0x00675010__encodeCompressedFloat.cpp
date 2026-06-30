// FUNC_NAME: encodeCompressedFloat
void encodeCompressedFloat(uint floatBits, uint halfBase, void* outputBuffer)
{
    uint combinedBits;
    uint normalizedFloat;
    uint trailingZeroCount;
    int tempExponent;
    uint constantFromHelper;

    // Combine input float bits with halfBase (shifted left 6) and normalize by shifting right until LSB is 1
    combinedBits = floatBits & 1;
    tempExponent = halfBase << 6;
    while (combinedBits == 0) {
        combinedBits = (int)(floatBits | tempExponent) >> 1 & 1;
        tempExponent = (int)tempExponent >> 1;
        floatBits = (int)floatBits >> 1;
    }

    // Store initial flag and get a constant (likely infinity or max exponent value)
    *(uint16_t*)((uint8_t*)outputBuffer + 16) = 2;
    constantFromHelper = FUN_00676090(); // returns e.g., 0x7c00
    *(uint32_t*)((uint8_t*)outputBuffer + 12) = constantFromHelper;

    if (tempExponent + 0x7fff < 0xffff) { // check that exponent is not too large
        // Store the normalized exponent (halfExponent)
        *(uint16_t*)outputBuffer = (uint16_t)tempExponent;

        // Count trailing zeros of the normalized float bits
        trailingZeroCount = 0;
        normalizedFloat = floatBits;
        while ((normalizedFloat & 1) == 0) {
            trailingZeroCount++;
            normalizedFloat = (int)floatBits >> (trailingZeroCount & 0x1f);
        }
        *(uint16_t*)((uint8_t*)outputBuffer + 2) = trailingZeroCount;

        // Store the original normalized float bits and a half-shifted version
        *(uint32_t*)((uint8_t*)outputBuffer + 4) = floatBits;
        *(int32_t*)((uint8_t*)outputBuffer + 8) = (int)floatBits >> 1;

        // Set flag indicating whether mantissa after removing zeros equals 1
        *(uint16_t*)((uint8_t*)outputBuffer + 16) = (uint16_t)(((int)floatBits >> (trailingZeroCount & 0x1f)) != 1);
    }
}