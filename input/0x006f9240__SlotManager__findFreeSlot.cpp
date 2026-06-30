// FUNC_NAME: SlotManager::findFreeSlot
int __thiscall SlotManager::findFreeSlot() {
    int* array = *(int**)(this + 0x10);    // +0x10: pointer to array of slot handles
    int count = *(int*)(this + 0x14);      // +0x14: number of elements in array

    // Early exit if the array is empty
    if (count == 0) {
        return 0;
    }

    // Iterate through each slot
    for (int* current = array; current < array + count; ++current) {
        // Check if the slot at offset +0x10 is free (FUN_004d4b20 returns 0)
        if (isSlotAvailable(*current + 0x10) == 0) {
            return *current;  // Return the handle of the free slot
        }
    }

    return 0;  // No free slot found
}