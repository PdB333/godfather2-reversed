// FUNC_NAME: CharKeyStringTable::addOrGetString
// 0x00604c10: Adds or retrieves a string entry indexed by a character key.
// The table holds up to 16 entries, each consisting of a char key and a 256-byte string buffer.
// Returns pointer to the string buffer; if table is full, returns nullptr.

#include <cstring>

struct CharKeyStringEntry {
    char key;       // +0: Character key
    char text[256]; // +1: String buffer (255 chars + null terminator)
};

struct CharKeyStringTable {
    int count;                         // +0: Number of entries (0-16)
    CharKeyStringEntry entries[16];    // +4: Fixed-size array of entries (257 bytes each)
};

char* __thiscall CharKeyStringTable::addOrGetString(char key, const char* str) {
    int i;
    // Search for existing key
    for (i = 0; i < this->count; i++) {
        if (this->entries[i].key == key) {
            break;
        }
    }
    
    if (i < this->count) {
        // Existing entry found
        if (i > 15) {
            return nullptr; // Sanity check: should not happen
        }
        return this->entries[i].text;
    } else {
        // Key not found – add new entry if space available
        if (this->count >= 16) {
            return nullptr; // Table is full
        }
        int newIndex = this->count;
        this->count++;
        this->entries[newIndex].key = key;
        strncpy(this->entries[newIndex].text, str, 255);
        return this->entries[newIndex].text;
    }
}