// FUNC_NAME: TripleKeyListenerMap::registerListener
void __thiscall TripleKeyListenerMap::registerListener(int thisPtr, int key1, int key2, int valueParam, int key3)
{
    int result;
    int *entryPtr;
    uint index;

    index = 0;
    // Check if an entry with matching key triple (key1, key2, key3) already exists
    if (*(uint *)(thisPtr + 0x14) != 0) {
        entryPtr = *(int **)(thisPtr + 0x10);
        do {
            if (((*entryPtr == key1) && (entryPtr[1] == key2)) && (entryPtr[3] == key3)) {
                // Duplicate found; no need to add
                return;
            }
            index = index + 1;
            entryPtr = entryPtr + 4; // each entry is 4 ints (0x10 bytes)
        } while (index < *(uint *)(thisPtr + 0x14));
    }

    // Resolve the object associated with key3 (probably a handle or ID)
    result = FUN_00405af0(key3);
    if (result != 0) {
        // Attach a listener/reference of type 8 to this map
        FUN_004035c0(result, 8, thisPtr);
    }

    // Check if array capacity is exhausted; if so, grow it (double)
    if (*(int *)(thisPtr + 0x18) == *(int *)(thisPtr + 0x14)) {
        int newCapacity = *(int *)(thisPtr + 0x18);
        if (newCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = newCapacity * 2;
        }
        FUN_00812790(newCapacity); // resize the array
    }

    // Append the new entry at the end of the array
    entryPtr = (int *)(*(int *)(thisPtr + 0x10) + *(int *)(thisPtr + 0x14) * 0x10);
    *(int *)(thisPtr + 0x14) = *(int *)(thisPtr + 0x14) + 1; // increment count
    if (entryPtr != (int *)0x0) {
        *entryPtr = key1;           // entry[0] = key1
        entryPtr[1] = key2;         // entry[1] = key2
        entryPtr[2] = valueParam;   // entry[2] = value (e.g., callback ID or data)
        entryPtr[3] = key3;         // entry[3] = key3 (handle/ID)
    }
    return;
}