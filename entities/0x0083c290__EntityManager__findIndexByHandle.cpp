// FUNC_NAME: EntityManager::findIndexByHandle
uint32 __thiscall EntityManager::findIndexByHandle(int this, int handle) {
    uint32 count = *(uint32 *)(this + 0x98);
    if (count == 0) {
        return 0xFFFFFFFF;
    }

    // Array of pairs: each entry is 8 bytes, first int is handle+0x48 or 0 for empty
    int *handles = *(int **)(this + 0x94);
    for (uint32 i = 0; i < count; i++) {
        int stored = handles[i * 2]; // first element of the pair
        int adjusted;
        if (stored == 0) {
            adjusted = 0; // empty slot
        } else {
            adjusted = stored - 0x48; // handle == ID + 0x48
        }
        if (adjusted == handle) {
            return i;
        }
    }
    return 0xFFFFFFFF;
}