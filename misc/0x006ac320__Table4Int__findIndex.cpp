// FUNC_NAME: Table4Int::findIndex
// Function at 0x006ac320 - Searches for a 4-int key in a table stored at offset 0x18.
// The table has entries of 16 bytes (4 ints) spaced 48 bytes apart (0x30).
// The loop checks 5 entries per iteration, advancing the base pointer by 60 bytes (0x3c).
// Returns the index of the matching entry, or the next available slot index if not found.

int __thiscall Table4Int::findIndex(int thisPtr, int *key)
{
    int iVar1 = key[0];
    int iVar2 = 0;                     // index accumulator
    int *basePtr = (int *)(thisPtr + 0x18);  // +0x18: start of table

    for (;;) {
        // Check 5 entries in this block
        // Entry 0: basePtr[-2], basePtr[-1], basePtr[0], basePtr[1]
        if ((((basePtr[-2] == iVar1) && (basePtr[-1] == key[1])) && (basePtr[0] == key[2])) &&
            (basePtr[1] == key[3])) {
            return iVar2;              // found at index iVar2
        }
        // Entry 1: basePtr[10], basePtr[11], basePtr[12], basePtr[13]
        if (((basePtr[10] == iVar1) && (basePtr[0xb] == key[1])) &&
            ((basePtr[0xc] == key[2] && (basePtr[0xd] == key[3])))) {
            return iVar2 + 1;
        }
        // Entry 2: basePtr[22], basePtr[23], basePtr[24], basePtr[25]
        if (((basePtr[0x16] == iVar1) && (basePtr[0x17] == key[1])) &&
            ((basePtr[0x18] == key[2] && (basePtr[0x19] == key[3])))) {
            return iVar2 + 2;
        }
        // Entry 3: basePtr[34], basePtr[35], basePtr[36], basePtr[37]
        if ((((basePtr[0x22] == iVar1) && (basePtr[0x23] == key[1])) && (basePtr[0x24] == key[2])) &&
            (basePtr[0x25] == key[3])) {
            return iVar2 + 3;
        }
        // Entry 4: basePtr[46], basePtr[47], basePtr[48], basePtr[49]
        if (((basePtr[0x2e] == iVar1) && (basePtr[0x2f] == key[1])) &&
            ((basePtr[0x30] == key[2] && (basePtr[0x31] == key[3])))) {
            return iVar2 + 4;
        }

        // Advance to next block of 5 entries
        iVar2 += 5;
        basePtr += 0x3c / 4;          // +0x3c = 60 bytes forward
        if (0x13 < iVar2) {           // maximum index 19 (0..19)
            break;
        }
    }
    return iVar2;                     // not found, return next slot index
}