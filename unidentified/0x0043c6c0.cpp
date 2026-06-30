// FUN_0043c6c0: GameBitField::testFlagAndGetValue
int __thiscall GameBitField::testFlagAndGetValue(int bitIndex)
{
    // Compute 64-bit mask by shifting 1 left by bitIndex.
    uint64_t mask = 1ULL << bitIndex;

    // Two 32-bit flag words at +0x148 and +0x14c form an effective 64-bit field.
    uint32_t lowFlags  = *(uint32_t*)((uint8_t*)this + 0x148); // +0x148
    uint32_t highFlags = *(uint32_t*)((uint8_t*)this + 0x14c); // +0x14c

    uint32_t lowMask  = (uint32_t)mask;
    uint32_t highMask = (uint32_t)(mask >> 32);

    // Combine both halves – bits from high half are OR'd into the lower 32 bits.
    uint32_t combined = (lowMask & lowFlags) | (highMask & highFlags);

    // Shift combined right by 8, then truncate to 24 bits.
    uint32_t value = (combined >> 8) & 0xFFFFFF;

    // Return: low byte = 1 if any mask bit matched, else 0; high 24 bits = value.
    if (combined != 0) {
        return value | 0x01;
    }
    return value << 8; // effectively 0 when combined == 0
}