// FUNC_NAME: ProcessSlotArray
void ProcessSlotArray(void)
{
    // Iterates over a global array of 0x38-byte structures (4095 entries) at DAT_011a0f60.
    // Only processes entries that are active (first byte non-zero) and not flagged (bit 7 of offset 0xC clear).
    char *pEntry;          // pcVar1 - pointer to current struct
    int index;             // uVar3 - 1-based index
    int remaining;         // iVar2 - loop counter (0xFFF iterations)
    char *pArray;          // puVar4 - base of array
    
    index = 1;
    pArray = (char *)&DAT_011a0f60;
    remaining = 0xFFF;
    do {
        // pEntry always equals pArray because condition (index < 0x1000) is always true for 1..4095
        pEntry = pArray;
        // Check: active (first byte non-null) and not flagged (byte at +0xC bit7==0)
        if ((*pEntry != '\0') && ((pEntry[0xC] & 0x80U) == 0)) {
            // Process this entry with its index and a zero flag
            FUN_006065a0(index, 0);
        }
        index++;
        pArray += 0x38;   // stride to next struct
        remaining--;
    } while (remaining != 0);
}