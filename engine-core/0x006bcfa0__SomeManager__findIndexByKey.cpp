// FUNC_NAME: SomeManager::findIndexByKey
// Function address: 0x006bcfa0
// Searches a table of pairs (pointer, ?) for an entry whose derived key matches param_2.
// The key is computed as (pointer - 0x48) if pointer is non-null, else 0.
// Returns the index of the matching entry, or 0xFFFFFFFF if not found.

uint __thiscall SomeManager::findIndexByKey(int thisPtr, int key) {
    uint count = *(uint *)(thisPtr + 0x78); // Number of entries in the table
    uint index = 0xFFFFFFFF;

    if (count != 0) {
        int *table = *(int **)(thisPtr + 0x74); // Pointer to array of 8-byte entries (pairs)
        index = 0;
        while (true) {
            int entryPointer = *table; // First 4 bytes of entry: a pointer (or null)
            int derivedKey;
            if (entryPointer == 0) {
                derivedKey = 0;
            } else {
                derivedKey = entryPointer - 0x48; // Subtract offset 0x48 from pointer
            }
            if (derivedKey == key) {
                break;
            }
            index++;
            table += 2; // Move to next entry (8 bytes)
            if (index >= count) {
                return 0xFFFFFFFF;
            }
        }
    }
    return index;
}