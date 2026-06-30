// FUNC_NAME: SlotManager::isSlotActive
int __thiscall SlotManager::isSlotActive(int this, int index) {
    int *entry;
    int checkResult;
    
    if (index < 1) {
        // Invalid index - use a fallback from some allocator or default
        entry = (int *)FUN_00625430(); // Possibly getDefaultEntry()
    } else {
        // Compute pointer to the 8-byte entry at given index
        // Array base is stored as offset -8 from the first element at this+0xC
        entry = (int *)(*(int *)(this + 0xC) + -8 + index * 8); // +0xC: arrayBaseMinus8
        // If entry >= array end pointer (this+0x8), index out of bounds
        if (*(int **)(this + 0x8) <= entry) { // +0x8: arrayEnd
            return 0;
        }
    }
    
    if (entry != (int *)0x0) {
        // First int of the entry: type flag (3 = always active, 4 = conditionally active)
        if (*entry == 3) {
            return 1;
        }
        if ((*entry == 4) && (checkResult = FUN_00636850(&index), checkResult != 0)) {
            // Additional condition using a global/static check (maybe checkType4Condition)
            return 1;
        }
    }
    return 0;
}