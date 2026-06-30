// FUNC_NAME: HashTable::getHashValue(unsigned int)
unsigned int __thiscall HashTable::getHashValue(unsigned int this, unsigned int hashOrId) {
    unsigned int localHash = hashOrId;
    int primaryIndex;
    int *primaryPtr;
    int *secondaryPtr;
    unsigned int result;

    // Try primary lookup table at this+0x28
    primaryIndex = FUN_006afa90(&localHash);  // returns index in primary table, -1 if not found
    if ((primaryIndex >= 0) &&
        (primaryPtr = *(int **)(this + 0x28) + 1 + primaryIndex * 2, // +4 offset: skip count? 8 bytes per entry: pointer and value
         primaryPtr != (int *)0x0) &&
        (result = *primaryPtr, result != 0)) {
        // Found in primary table: return value at offset 0x180 from the pointer
        return *(unsigned int *)(result + 0x180);
    }

    // Fallback to secondary lookup table at this+0x34
    int secondaryIndex = FUN_006b0150(&hashOrId);
    if ((secondaryIndex >= 0) &&
        (secondaryPtr = *(unsigned int **)(this + 0x34) + 1 + secondaryIndex * 2,
         secondaryPtr != (unsigned int *)0x0)) {
        return *secondaryPtr;
    }

    return 0; // Not found
}