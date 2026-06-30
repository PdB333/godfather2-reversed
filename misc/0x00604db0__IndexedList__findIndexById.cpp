// FUNC_NAME: IndexedList::findIndexById
// Address: 0x00604db0
// Role: Linear search for an entry matching a given key in an array of 12-byte structures.
// Returns the index (0-based) or 0xFFFFFFFF if not found.

uint __thiscall IndexedList::findIndexById(undefined4 param_2) {
    // Convert the input parameter to the internal key ID
    int id = convertKeyToId(param_2);  // FUN_004dafd0

    // Count of entries is stored in a sub-structure at this+0x4, offset +0x10
    uint entryCount = *(uint *)(*(int *)(this + 0x4) + 0x10);
    if (entryCount == 0) {
        return 0xFFFFFFFF;
    }

    // Array of 3 ints per entry (key, data1, data2) at this+0x8
    int *array = *(int **)(this + 0x8);
    for (uint i = 0; i < entryCount; i++) {
        if (array[i * 3] == id) {
            return i;
        }
    }

    return 0xFFFFFFFF;
}