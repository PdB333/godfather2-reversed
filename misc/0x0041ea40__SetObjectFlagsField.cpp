// FUNC_NAME: SetObjectFlagsField
// Sets the first 32-bit field (offset 0) of a structure at index param_1 in a global array.
// The structure size is 0x84 bytes. The lower 5 bits of the value are cleared (mask 0xFFFFFFE0),
// possibly to align to 32-byte boundaries or to preserve flags in the lower bits.
void SetObjectFlagsField(int index, uint value)
{
    // Global array of structures, each 0x84 bytes. Access via base pointer + index * stride.
    // DAT_01163848 is the base address of the array.
    // Write the value with lower 5 bits cleared to the first field.
    ((uint*)(&DAT_01163848))[index * 0x84 / sizeof(uint)] = value & 0xFFFFFGE0;
}