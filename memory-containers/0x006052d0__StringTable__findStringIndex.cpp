// FUNC_NAME: StringTable::findStringIndex
uint __thiscall StringTable::findStringIndex(int this, char *str) {
    uint index = 0;
    char *currentStr = *(char **)(this + 0xac); // Array of fixed-size strings (0x61 bytes each)
    uint count = *(uint *)(this + 0xa4);        // Number of strings in the array

    if (count == 0) {
        return 0xffffffff;
    }

    do {
        // Compare strings case-insensitively; handle null pointers
        if (currentStr == (char *)0x0 || str == (char *)0x0) {
            if (currentStr <= str) {
                if (currentStr < str) {
                    // Not equal
                } else {
                    // Equal (both null or same pointer)
                    return index;
                }
            }
        } else {
            if (__stricmp(currentStr, str) == 0) {
                return index;
            }
        }

        index++;
        currentStr += 0x61; // Move to next string buffer
    } while (index < count);

    return 0xffffffff;
}