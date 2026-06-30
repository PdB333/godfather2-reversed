// FUNC_NAME: validateFlagCombination
uint __thiscall validateFlagCombination(int thisPtr, uint mask)
{
    uint temp;

    // Check if all bits set in field_0x14 are also set in mask
    if ((*(uint*)(thisPtr + 0x14) & mask) != *(uint*)(thisPtr + 0x14)) {
        // If not, return mask with lowest byte cleared (failure indicator)
        return mask & 0xFFFFFF00;
    }

    // Compute bits present in field_0x18 but not in mask
    temp = ~mask & *(uint*)(thisPtr + 0x18);

    // Return combined result: high 24 bits from temp (with low byte zeroed)
    // plus a flag (1 if temp equals field_0x18, else 0) in the low byte
    return (temp & 0xFFFFFF00) | (uint)(temp == *(uint*)(thisPtr + 0x18));
}