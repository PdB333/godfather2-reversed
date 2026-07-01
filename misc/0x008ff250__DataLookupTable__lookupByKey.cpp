// FUNC_NAME: DataLookupTable::lookupByKey

int __thiscall DataLookupTable::lookupByKey(int thisPtr, int key)
{
    uint index;
    int currentKey;

    index = 0;
    // If no entries, return 0 (not found)
    if (*(int *)(thisPtr + 0x14) == 0) {
        return 0;
    }
    do {
        // Get the key at current index (function likely returns some stored key)
        currentKey = FUN_008fdfd0(); // Note: This function signature may be incomplete; possibly uses thisPtr internally
        if (currentKey == key) {
            // Return the value stored in the array at offset +0x10
            return *(int *)(*(int *)(thisPtr + 0x10) + index * 4);
        }
        index++;
    } while (index < *(uint *)(thisPtr + 0x14));
    return 0;
}