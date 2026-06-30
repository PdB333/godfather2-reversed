// FUNC_NAME: StringTable::FindStringCaseInsensitive
int StringTable::FindStringCaseInsensitive(const char* searchString, uint* outIndex) {
    uint count = *(uint*)((int)this + 0x14); // +0x14: number of string entries
    uint index = 0;
    if (count != 0) {
        do {
            char* currentStr = *(char**)(*(int*)((int)this + 0x18) + index * 4); // +0x18: array of string pointers
            if (currentStr == nullptr || searchString == nullptr) {
                // If either is null, compare pointers directly (likely no match)
                if (currentStr <= searchString) {
                    uint cmp = (uint)(currentStr < searchString);
                    goto checkResult;
                }
            } else {
                uint cmp = __stricmp(currentStr, searchString); // case-insensitive comparison
checkResult:
                if (cmp == 0) {
                    *outIndex = index;
                    return 1; // found
                }
            }
            index++;
        } while (index < count);
    }
    return 0; // not found
}