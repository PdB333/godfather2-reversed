// FUNC_NAME: UnknownClass::getMappedId
int __thiscall UnknownClass::getMappedId(int inputId) {
    // this +0x70: pointer to a table container
    // this +0x74: short index into that container's sub-table
    if (this == nullptr || *(int*)((char*)this + 0x70) == nullptr) {
        return -1;
    }

    // +0x1c: pointer to base of array
    int* basePtr = **(int***)((char*)this + 0x70);
    int* table = *(int**)((char*)basePtr + 0x1c);
    short tableIndex = *(short*)((char*)this + 0x74);

    // Each entry at table[0x14 + index * 0x18] is a pointer to a sub-table
    int* subTable = *(int**)((char*)table + 0x14 + tableIndex * 0x18);

    // Look up a sub-index using inputId and the sub-table
    int lookupResult = FUN_004dafd0(inputId, subTable);
    int subIndex = FUN_005828a0(lookupResult);

    if (subIndex == -1) {
        return -1;
    }

    // At offset 0x10 into sub-table, there is an array of 0x14-byte entries
    int mappedId = *(int*)((char*)subTable + 0x10 + subIndex * 0x14);
    if (mappedId == -1) {
        return -1;
    }
    return mappedId;
}