//FUNC_NAME: EntityDataManager::findIDInRange
// Function address: 0x00579220
// Role: Checks if any entity ID (stored in a hash table) falls within a given range [param_1, param_2).
// Returns a packed value: high byte = 1 if found, else 0; lower 24 bits = (found ID >> 8) or some computed value.

uint __thiscall EntityDataManager::findIDInRange(uint rangeStart, uint rangeEnd)
{
    // +0x60: own entity ID (or current ID)
    uint ownID = *(uint *)(this + 0x60);
    if (rangeStart <= ownID && ownID < rangeEnd) {
        // Found: return (ownID >> 8) with high byte set to 1
        return (ownID >> 8) | 0x01000000;
    }

    // Get count of hash table entries (from some global or member function)
    uint entryCount = FUN_00579170(); // likely returns number of active entries
    int i = 0;
    uint result = entryCount; // default return if no entries

    if ((int)entryCount > 0) {
        // +0x2e4: hash table size (number of slots)
        int tableSize = *(int *)(this + 0x2e4);
        // +0x2e8: some offset or starting index
        int startOffset = *(int *)(this + 0x2e8);
        // +0x2ec: pointer to array of hash table entries (each 0xE0 bytes)
        int* hashTable = *(int **)(this + 0x2ec);

        // Compute initial probe index: (startOffset + tableSize) / tableSize gives a starting slot
        int probeValue = startOffset + tableSize;
        do {
            // Current slot index = probeValue % tableSize
            int slotIndex = probeValue % tableSize;
            // Read ID from the slot at offset +0x60 within the 0xE0-byte structure
            uint slotID = *(uint *)((int)hashTable + slotIndex * 0xE0 + 0x60);
            if (rangeStart <= slotID && slotID < rangeEnd) {
                // Found: return (slotID >> 8) with high byte set to 1
                return (slotID >> 8) | 0x01000000;
            }
            i++;
            probeValue--;
        } while (i < (int)entryCount);

        // After loop, result is the last computed probeValue / tableSize (from the last iteration)
        // Actually the loop overwrites result each iteration; final result is from last iteration
        result = probeValue / tableSize; // but probeValue has been decremented, so this is the last computed slot index
    }

    // Not found: return result with low byte cleared (high byte remains 0)
    return result & 0xffffff00;
}