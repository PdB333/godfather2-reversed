// FUNC_NAME: SlotManager::getSlotData
// Function at 0x00625a70: Retrieves a pointer to slot data at a given index.
// param_1: pointer to SlotManager instance
// param_2: slot index (1‑based; <1 returns default slot)
// Returns: pointer to data (offset 0x10 from slot's object pointer) if valid, else 0
int SlotManager::getSlotData(int param_1, int param_2)
{
    int *slotPtr; // pointer to the 8-byte slot structure

    if (param_2 < 1) {
        // Use default slot
        slotPtr = (int *)FUN_00625430(); // Returns pointer to default slot
    }
    else {
        // Compute slot pointer: array base + (param_2 - 1) * 8
        int *arrayBase = *(int **)(param_1 + 0xC); // +0x0C: pointer to start of slot array
        slotPtr = (int *)((int)arrayBase - 8 + param_2 * 8);
        // Check if slot is beyond the end pointer
        int *endPtr = *(int **)(param_1 + 0x8); // +0x08: pointer to one past the last valid slot
        if (endPtr <= slotPtr) {
            return 0; // Out of range
        }
    }

    if (slotPtr == (int *)0x0) {
        return 0; // Null slot
    }

    // Check slot type
    if (*slotPtr == 4) {
        // Type 4: valid; return object data at offset 0x10
        return slotPtr[1] + 0x10;
    }

    // For non-type-4 slots, perform additional validation via FUN_00633990
    int validationResult = FUN_00633990(param_1);
    if (validationResult != 0) {
        return slotPtr[1] + 0x10;
    }

    // Validation failed; perform a debug check
    // +0x10: pointer to a related state structure (e.g., manager state)
    int *statePtr = *(int **)(param_1 + 0x10);
    uint countA = *(uint *)(statePtr + 0x20); // +0x20: some counter
    uint countB = *(uint *)(statePtr + 0x24); // +0x24: another counter
    if (countA <= countB) {
        FUN_00627360(); // Possibly debug assertion or maintenance
    }

    return 0;
}