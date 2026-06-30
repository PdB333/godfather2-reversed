// FUNC_NAME: EntityDataManager::findIndexByHash
uint __thiscall EntityDataManager::findIndexByHash(uint identifier) {
    // Compute hash from the given identifier
    int hashedKey = FUN_004dafd0(identifier);
    
    // this+4: pointer to a container header structure
    // header+0x10: number of elements in the array
    uint elementCount = *(uint*)(*(int*)(this + 4) + 0x10);
    if (elementCount != 0) {
        // this+8: pointer to the start of the element array
        // Each element is 12 bytes (3 ints), first int is the key
        int* entries = *(int**)(this + 8);
        for (uint i = 0; i < elementCount; ++i) {
            if (*entries == hashedKey) {
                return i;
            }
            entries += 3; // advance to next element (12 bytes)
        }
    }
    return 0xFFFFFFFF; // not found
}