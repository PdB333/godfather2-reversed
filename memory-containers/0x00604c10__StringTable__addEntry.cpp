// FUNC_NAME: StringTable::addEntry
// Function address: 0x00604c10
// Role: Insert or retrieve a key-value pair in a fixed-size string table (max 16 entries).
// Each entry is 0x101 bytes: 1 byte key + 256 byte null-terminated string.
// Returns pointer to the value string, or NULL if table full and key not found.

class StringTable {
public:
    int count; // +0x00: number of entries currently stored
    // Entries start at offset 0x04, each 0x101 bytes:
    //   char key;   // +0x00 of entry
    //   char value[256]; // +0x01 of entry

    // __thiscall
    char* addEntry(char key, const char* value) {
        int currentCount = this->count;
        int index = 0;
        int isNewEntry = 1; // flag: 1 if key not found, 0 if found

        // Search for existing key
        if (currentCount > 0) {
            char* entryPtr = reinterpret_cast<char*>(this) + 4; // first entry's key
            do {
                if (*entryPtr == key) {
                    isNewEntry = 0; // key found
                    break;
                }
                index++;
                entryPtr += 0x101; // move to next entry
            } while (index < currentCount);

            // If key not found and table is full (index >= 16), return NULL
            if (index >= 16) {
                return nullptr;
            }
        }

        // If key is new, increment count
        this->count = currentCount + isNewEntry;

        // Calculate pointer to the value string for this entry
        char* dest = reinterpret_cast<char*>(this) + index * 0x101 + 5; // +5: skip count (4) + key (1)
        // Store the key
        *(reinterpret_cast<char*>(this) + index * 0x101 + 4) = key;
        // Copy the value string (max 255 chars + null)
        _strncpy(dest, value, 0xff);
        return dest;
    }
};