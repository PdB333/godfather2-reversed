//FUNC_NAME: highestSetBit
// Function address: 0x006367a0
// Role: Returns the position (0-31) of the highest set bit in a 32-bit value, or 0xFFFFFFFF if zero.
// Uses a 256-byte lookup table (msbTable) to find the bit position within each byte.

uint __fastcall highestSetBit(uint value)
{
    // Static lookup table for bit position within a byte (0-7)
    // Defined elsewhere in the binary at 0x00e4218f
    static const uint8 msbTable[256] = { /* ... */ };

    if (value > 0xFFFF)
    {
        if (value > 0xFFFFFF)
        {
            // Highest byte is bits 24-31
            return msbTable[value >> 24] + 24;
        }
        // Highest two bytes, but top byte is zero; bits 16-23
        return msbTable[(value >> 16) & 0xFF] + 16;
    }
    if (value > 0xFF)
    {
        // Highest byte is bits 8-15
        return msbTable[(value >> 8) & 0xFF] + 8;
    }
    if (value != 0)
    {
        // Value fits in one byte, bits 0-7
        return msbTable[value & 0xFF];
    }
    return 0xFFFFFFFF; // No bits set
}