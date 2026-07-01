// FUNC_NAME: SelectionManager::selectFreeEntry
void __thiscall SelectionManager::selectFreeEntry(int thisPtr, int direction) {
    uint totalEntries;          // uVar1
    uint i;                     // uVar4
    uint currentIndex;          // uVar3
    uint entryIndex;            // uVar2
    uint clampedIndex;          // temporary
    ResultStruct selectionResult; // local_c, local_8, local_4

    totalEntries = *(uint *)(thisPtr + 0x6C); // +0x6C: number of entries in selection list
    i = 0;
    if (totalEntries != 0) {
        // Clamp current selection index to zero if negative
        clampedIndex = *(uint *)(thisPtr + 0x7C); // +0x7C: current selection index
        if ((int)clampedIndex < 1) {
            clampedIndex = 0;
        }
        // Compute starting search index based on current index + direction
        currentIndex = totalEntries + ((clampedIndex + direction) % totalEntries);
        do {
            entryIndex = currentIndex % totalEntries;
            // Check if entry at index is free (first field of 3-field struct == 0)
            if ((DAT_00e57508)[entryIndex * 3] == 0) {
                if (entryIndex != 0xFFFFFFFF) {
                    *(uint *)(thisPtr + 0x7C) = entryIndex;
                    // Notify selection update
                    FUN_005a04a0("UpdateSelection", 0, &DAT_00d8f7f8, 0);
                    // Initialize result with default selection data
                    selectionResult = DAT_011302b0;
                    FUN_00408a00(&selectionResult, 0);
                    return;
                }
                break;
            }
            i++;
            // Adjust search direction: +1 if direction >= 0, -1 if direction < 0
            if ((int)direction >= 0) {
                currentIndex = currentIndex + 1;
            } else {
                currentIndex = currentIndex - 1;
            }
        } while (i < totalEntries);
    }
    // No free entry found; use alternative default
    selectionResult = DAT_011301f8;
    FUN_00408a00(&selectionResult, 0);
    return;
}