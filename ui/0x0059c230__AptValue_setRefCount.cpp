// Xbox PDB: AptValue::setRefCount
// FUNC_NAME: AptValue::setHighWord
void AptValue::setHighWord(uint16 high)
{
    // Assertion: high must fit in 16 bits (n < 65536)
    if (high >= 0x10000)
    {
        // Trigger assertion from _AptValue.h line 0x9c (debug builds)
        // In release builds, may be omitted or handled differently
        // The actual assertion mechanism (FS segment, DAT_01128f0b, swi) is omitted for clarity
    }

    // Clear the upper 16 bits of the 32-bit value at this
    *((uint16*)this + 1) = 0;

    // Set the upper 16 bits to the given value (shifted left 16)
    *(uint32*)this |= ((uint32)high) << 16;
}