// FUNC_NAME: StringTable::addEntry
// Function address: 0x00605520
// Role: Adds a triple-string entry (name, description, value) into a dynamic string table.
// The table stores entries as fixed-size records of 0x60 bytes each (three 32-byte strings).
// Returns the index of the newly added entry.

struct StringTableEntry {
    char name[32];       // +0x00
    char description[32];// +0x20
    char value[32];      // +0x40
};

class StringTable {
public:
    int entryCount;      // +0xa8
    StringTableEntry* entries; // +0xb0 (pointer to dynamic array)

    // Adds a new entry. If defaultValue is NULL or "(none)", the value field is left empty.
    int addEntry(const char* name, const char* description, const char* defaultValue);
};

int __thiscall StringTable::addEntry(const char* name, const char* description, const char* defaultValue) {
    int index = this->entryCount;
    StringTableEntry* dest = &this->entries[index];

    // Increment count for next addition
    this->entryCount = index + 1;

    int pos = 0;

    // Copy name (max 31 chars + null)
    if (name != nullptr && *name != '\0') {
        strncpy(dest->name, name, 0x1f);
        pos = 0x1f;
    }
    dest->name[pos] = '\0';

    // Copy description (max 31 chars + null)
    pos = 0;
    if (description != nullptr && *description != '\0') {
        strncpy(dest->description, description, 0x1f);
        pos = 0x1f;
    }
    dest->description[pos] = '\0';

    // Determine if value field should be filled
    bool skipValue = false;
    if (defaultValue == nullptr) {
        skipValue = true;
    } else {
        skipValue = (stricmp(defaultValue, "(none)") == 0);
    }

    if (skipValue) {
        dest->value[0] = '\0';
        return index;
    }

    // Copy value (max 31 chars + null)
    pos = 0;
    if (defaultValue != nullptr && *defaultValue != '\0') {
        strncpy(dest->value, defaultValue, 0x1f);
        pos = 0x1f;
    }
    dest->value[pos] = '\0';

    return index;
}