// FUNC_NAME: Entity::testFlagBit15
// Address: 0x005cd5a0
// Reads a 32-bit flags field at offset +0x24, right-shifts by 13, then duplicates to form a 64-bit mask.
// Returns a 64-bit value with bit 2 set if original bit 15 was set, else 0.

ulonglong __thiscall Entity::testFlagBit15(void)
{
    // Read flags at +0x24
    uint shiftedFlags = *(uint *)(this + 0x24) >> 0xD; // shift right 13 bits
    // Duplicate shifted value into 64-bit and mask with 0x200000004
    // Result: low32 bit2 = shiftedFlags bit2 (original bit15), high32 bit29 = shiftedFlags bit29 (always 0)
    return CONCAT44(shiftedFlags, shiftedFlags) & 0x200000004;
}