// FUNC_NAME: EntityDataManager::getDataByLookup
uint32_t __thiscall EntityDataManager::getDataByLookup(int thisPtr, uint32_t lookupId)
{
    // Make a copy for primary hash lookup (hash function may modify the value)
    uint32_t idCopy = lookupId;
    int index = primaryHashFind(&idCopy); // 0x006afa90 - returns index or -1
    if (index >= 0) {
        // Access primary hash table: this+0x28 points to an array of 8-byte entries
        // Each entry: first 4 bytes = pointer to object, next 4 bytes = ? (maybe key)
        int** entryPtr = (int**)(*(int*)(thisPtr + 0x28) + 4 + index * 8);
        if (entryPtr != 0) {
            int* objectPtr = *entryPtr; // dereference to get object pointer
            if (objectPtr != 0) {
                return *(uint32_t*)(objectPtr + 0x180); // return value at +0x180
            }
        }
    }
    // Secondary lookup in a different hash table
    index = secondaryHashFind(&lookupId); // 0x006b0150
    if (index >= 0) {
        // Secondary hash table: this+0x34 points to array of 8-byte entries
        // Each entry: first 4 bytes = direct value (pointer or data)
        uint32_t** valuePtr = (uint32_t**)(*(int*)(thisPtr + 0x34) + 4 + index * 8);
        if (valuePtr != 0) {
            return **valuePtr; // return the stored value directly
        }
    }
    return 0;
}