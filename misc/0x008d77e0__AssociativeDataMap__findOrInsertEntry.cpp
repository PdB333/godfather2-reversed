// FUNC_NAME: AssociativeDataMap::findOrInsertEntry
uint * __thiscall AssociativeDataMap::findOrInsertEntry(uint *param_2) {
    // param_1 is 'this', with layout:
    // +0x00: pointer to array of entries (each 6 uint32s)
    // +0x04: count of entries
    // Each entry: [key (uint32), value0 (uint32), value1 (uint32), value2 (uint32), value3 (uint32), value4 (uint32)]

    uint *entryArray = (uint *)this[0];  // +0x00
    int entryCount = (int)this[1];       // +0x04
    int i = 0;

    // Search for existing key
    if (0 < entryCount) {
        uint *currentEntry = entryArray;
        do {
            if (*param_2 == *currentEntry) {
                // Key already exists, return null
                return (uint *)0x0;
            }
            if (*param_2 < *currentEntry) {
                // Insert point found before this entry
                break;
            }
            i++;
            currentEntry += 6;  // Advance to next entry (6 uints per entry)
        } while (i < entryCount);
    }

    // Allocate space and insert new entry at position i
    uint *newEntry = (uint *)FUN_008d7220(i);  // Likely a memory allocation/insert function
    *newEntry = *param_2;   // Set key
    return newEntry + 1;    // Return pointer to the value area (first value after key)
}