// FUNC_NAME: BitField::markAllWithFlag

void __thiscall BitField::markAllWithFlag(int thisPtr, uint flagBit)
{
    uint idx;
    uint *entryPtr;
    int baseOffset;
    uint count;

    count = 0;
    if (*(int *)(thisPtr + 0xc) != 0) {
        baseOffset = 0;
        do {
            entryPtr = (uint *)(*(int *)(thisPtr + 4) + baseOffset);
            // Check if entry has the flag bit set AND not already marked (bit 1 of entry[2] is 0)
            if (((*entryPtr & flagBit) != 0) && ((entryPtr[2] >> 1 & 1) == 0)) {
                // Set the "marked" bit (bit 1) in entry[2]
                entryPtr[2] = entryPtr[2] | 2;
                // Increment the count of marked entries (stored at +0x10)
                *(int *)(thisPtr + 0x10) = *(int *)(thisPtr + 0x10) + 1;
            }
            count = count + 1;
            baseOffset = baseOffset + 0x10;
        } while (count < *(uint *)(thisPtr + 0xc));
    }
    FUN_008963c0(); // likely a post-process or notification callback
    return;
}