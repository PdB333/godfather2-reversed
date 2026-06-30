// FUNC_NAME: DataManager::findEntryByKey
// Address: 0x006bb1a0
// Role: Searches a linear array of 6-int entries (24 bytes each) for a matching 4-int key.
// Array at this+0xa0, count at this+0xa4. Entry structure: [type (int), unknown (int), key[4] (int)].
// Returns 1 if found, sets *outIndex to index, *outValue to result of global function.
// If not found, returns 0.

int __thiscall DataManager::findEntryByKey(int this, int *key, uint *outIndex, int *outValue)
{
    int result = 0;
    uint index = 0;

    if (*(uint *)(this + 0xa4) != 0) {
        int *entryPtr = *(int **)(this + 0xa0);
        int *keyPtr = entryPtr + 4; // Points to entry[4] (start of key part? Actually used for comparison)

        while (true) {
            // Check if entry is empty (type == 0) or special type (0x48), or key doesn't match
            if ((*entryPtr != 0 && *entryPtr != 0x48) &&
                (entryPtr[2] == key[0] && entryPtr[3] == key[1] && entryPtr[4] == key[2] && entryPtr[5] == key[3])) {
                break; // Found matching entry
            }
            index++;
            entryPtr += 6; // Move to next entry (6 ints = 24 bytes)
            keyPtr += 6;
            if (*(uint *)(this + 0xa4) <= index) {
                return result; // Not found, return 0
            }
        }

        *outIndex = index;
        // Even though *entryPtr is guaranteed non-zero here, the decompiler shows both branches
        if (*entryPtr != 0) {
            result = FUN_007914e0(); // Global function returning a handle/value
            *outValue = result;
            return 1;
        }
        // Dead code: *entryPtr is never 0 at this point
        result = FUN_007914e0();
        *outValue = result;
        return 1;
    }
    return result;
}