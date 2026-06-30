// FUNC_NAME: StringArray::findStringIndex
// Address: 0x00605b80
// Role: Searches an internal array of strings for a case-insensitive match, returns the index if found.

int __thiscall StringArray::findStringIndex(const char *searchStr, uint *outIndex) {
    uint count = *(uint *)((char *)this + 0x14); // +0x14: number of strings in array
    if (count == 0) {
        return 0;
    }

    char **stringArray = *(char ***)((char *)this + 0x18); // +0x18: pointer to array of char*
    for (uint i = 0; i < count; ++i) {
        char *storedStr = stringArray[i];
        // Both null: treat as match (pointer equality check from decompiled logic)
        if (storedStr == nullptr && searchStr == nullptr) {
            *outIndex = i;
            return 1;
        }
        // If one is null but not both, no match for this entry
        if (storedStr == nullptr || searchStr == nullptr) {
            continue;
        }
        // Case-insensitive comparison for non-null strings
        if (__stricmp(storedStr, searchStr) == 0) {
            *outIndex = i;
            return 1;
        }
    }
    return 0;
}