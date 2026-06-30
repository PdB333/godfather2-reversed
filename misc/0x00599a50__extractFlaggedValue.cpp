// FUNC_NAME: extractFlaggedValue
// Address: 0x00599a50
// Reads a 32-bit flags value from the given pointer, extracts the high 24 bits (bits 8-31) and returns them shifted left by 8.
// If bit 0 is set and bit 4 is clear, the low byte of the result is set to 1; otherwise it is zero.
// Likely used for packet or state flag processing in the EARS networking layer.

int __fastcall extractFlaggedValue(uint* flagsPtr)
{
    uint flags = *flagsPtr;
    uint high24 = flags >> 8; // Bits 8-31 (24-bit value)

    // Condition: bit 0 set (0x01) and bit 4 clear (0x10)
    if ((flags & 0x10) == 0 && (flags & 1) != 0)
    {
        // Return high24 shifted left by 8 with low byte set to 1
        return (high24 << 8) | 1;
    }
    // Default: return high24 shifted left by 8 (low byte zero)
    return high24 << 8;
}