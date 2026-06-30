// FUNC_NAME: findIndexById
uint __thiscall findIndexById(int thisPtr, int id)
{
    uint index;
    int *entryPtr;

    // Return 0xFFFFFFFF for invalid (-1) ID
    if (id == -1) {
        return 0xFFFFFFFF;
    }

    // The array of entries is stored at offset +4 of this object.
    // Each entry is 7 ints (28 bytes). The first int is the ID key.
    entryPtr = *(int **)(thisPtr + 4);
    index = 0;
    while (*entryPtr != id) {
        index++;
        entryPtr += 7; // move to next entry (28 bytes)
        if (index > 0x3F) { // max 64 entries (0x3F = 63, but we check > 0x3F -> fail when index reaches 64)
            return 0xFFFFFFFF; // not found
        }
    }
    return index; // return the index of the matching entry
}