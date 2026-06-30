// FUNC_NAME: PackedHandle::getValue
// Function address: 0x006b7fd0
// Role: Extracts a 22-bit value from bits 10-31 of a packed uint, and returns it shifted left by 8 with a low byte set to 0 or 1 based on a flag (bit 2) and a parameter.
// The packed uint layout: bit 2 = some flag, bits 10-31 = value (22 bits).
// If bit 2 is set AND param2 is non-zero, low byte of result is 0; otherwise low byte is 1.

int __thiscall PackedHandle::getValue(uint* thisPtr, int param2)
{
    // Extract bits 10-31 (22 bits) from the packed uint
    unsigned int extracted = (*thisPtr >> 10) & 0x3FFFFF; // 22-bit mask

    // Check bit 2 of the packed uint
    bool flagSet = ((*thisPtr >> 2) & 1) != 0;

    if (flagSet && (param2 != 0)) {
        // Return value shifted left by 8, low byte 0
        return (int)(extracted << 8);
    } else {
        // Return value shifted left by 8, low byte 1
        return (int)((extracted << 8) | 1);
    }
}