// FUNC_NAME: OrderedUIntTable::insert
// Function at 0x006b1230: Insert a new key-value pair into a sorted table of uint pairs.
// The table is stored as a dynamic array of uint pairs (key, value), sorted by key.
// Returns pointer to the value slot for the new entry, or nullptr if key already exists.
uint* __thiscall OrderedUIntTable::insert(uint* keyPtr) {
    // this points to structure with:
    // +0x00: pointer to array of uint32 pairs (key, value) – uint* pArray
    // +0x04: count of entries – int count
    int count = param_1[1];          // +0x04
    uint* array = (uint*)*param_1;   // +0x00

    int i = 0;
    if (count > 0) {
        uint* currentPair = array;
        do {
            if (*keyPtr == *currentPair) {
                // Key already exists, insertion fails
                return nullptr;
            }
            if (*keyPtr < *currentPair) {
                // Insertion point found (key less than current key)
                break;
            }
            i++;
            currentPair += 2; // Move to next pair (8 bytes per entry)
        } while (i < count);
    }

    // Insert new entry at index i (before existing entry if found)
    uint* newEntry = (uint*)insertHelper(i); // FUN_006b0dc0 returns pointer to new 8-byte block
    *newEntry = *keyPtr;
    // Return pointer to the value slot (offset +4 bytes)
    return newEntry + 1;
}