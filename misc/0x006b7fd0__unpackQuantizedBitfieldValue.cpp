// FUNC_NAME: unpackQuantizedBitfieldValue
int __thiscall unpackQuantizedBitfieldValue(uint* packedWord, int isValidFlag)
{
    // Extract bits 10–31 (24-bit value) from the packed word
    uint3 extracted24Bit = (uint3)(*packedWord >> 10);

    // Condition: bit 2 of packedWord must be set AND the external validity flag must be nonzero
    if (((*packedWord >> 2 & 1) != 0) && (isValidFlag != 0))
    {
        // Return extracted value in the high 24 bits, low byte zero
        return (uint)extracted24Bit << 8;
    }
    else
    {
        // Return extracted value in the high 24 bits, low byte set to 1 (invalid/dirty flag?)
        return ((uint)extracted24Bit << 8) | 1;
    }
}