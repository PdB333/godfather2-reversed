// FUNC_NAME: resolveDataPointer
// Function at 0x0043ab90 - Resolves a data pointer in a structure.
// Checks for a known type ID at offset 0x06 and either returns an offset pointer or a base+offset.
int* __fastcall resolveDataPointer(int* pStruct)
{
    // Check type identifier at offset 0x06 (short)
    if (*(short*)((char*)pStruct + 6) != 0x25E3)
    {
        // Not the expected type, return pointer to next entry (skip 2 ints)
        return pStruct + 2;
    }

    // Expected type: check if first field (offset 0) is non-zero
    if (*pStruct != 0)
    {
        // Return pointer at offset 8 (param_1[2]) plus the value at offset 0
        return (int*)(pStruct[2] + *pStruct);
    }

    // If first field is zero, return a fixed address (sentinel/fallback)
    return (int*)0x00E2A89B;
}