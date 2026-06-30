// FUNC_NAME: StringTable::addEntry
// Address: 0x00605340
// Role: Adds a new entry to a string table. Each entry consists of three 31-character strings and a boolean flag.
// The entry buffer is an array of 0x61-byte slots. The counter at +0xA4 tracks the number of entries.
// Returns the index of the newly added entry.

int __thiscall StringTable::addEntry(const char* str1, const char* str2, const char* str3, const char* flagStr)
{
    int entryIndex = this->entryCount;          // +0xA4
    char* entry = this->entryBuffer + entryIndex * 0x61; // +0xAC is base pointer
    this->entryCount = entryIndex + 1;

    int offset = 0;
    if (str1 != nullptr && *str1 != '\0') {
        _strncpy(entry, str1, 0x1F);           // Copy up to 31 chars
        offset = 0x1F;
    }
    entry[offset] = '\0';                      // Null-terminate first string

    offset = 0;
    if (str2 != nullptr && *str2 != '\0') {
        _strncpy(entry + 0x20, str2, 0x1F);    // Second string at +0x20
        offset = 0x1F;
    }
    entry[0x20 + offset] = '\0';               // Null-terminate second string

    offset = 0;
    if (str3 != nullptr && *str3 != '\0') {
        _strncpy(entry + 0x40, str3, 0x1F);    // Third string at +0x40
        offset = 0x1F;
    }
    entry[0x40 + offset] = '\0';               // Null-terminate third string

    if (flagStr != nullptr) {
        entry[0x60] = (__stricmp(flagStr, "0") != 0) ? 1 : 0; // Boolean flag at +0x60
    } else {
        entry[0x60] = 1;                       // Default to true if no flag string
    }

    return entryIndex;
}