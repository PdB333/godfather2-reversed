// FUNC_NAME: EntryManager::findAndProcessEntry
// Address: 0x0043c740

#include <stdint.h>

// Internal structure: 7 ints = 28 bytes
struct Entry {
    int32_t id;          // +0x00: Unique identifier
    int32_t field_1;     // +0x04
    int32_t field_2;     // +0x08
    int32_t field_3;     // +0x0C
    int32_t field_4;     // +0x10
    int32_t field_5;     // +0x14
    int32_t field_6;     // +0x18
};

class EntryManager {
public:
    // Offset +0x04: pointer to array of Entry structs
    Entry* m_pEntries;

    // Forward declaration of the internal handler
    bool processEntry(uint32_t index, uint32_t param2, uint32_t param3);

    // Searches entries by ID, calls processEntry if found
    bool findAndProcessEntry(int32_t entryId, uint32_t param2, uint32_t param3);
};

bool EntryManager::findAndProcessEntry(int32_t entryId, uint32_t param2, uint32_t param3) {
    // Return 0 if entryId is invalid
    if (entryId == -1) {
        return false;
    }

    // Get the base pointer to the entries array
    Entry* entries = m_pEntries; // dereference offset +0x04

    // Linear search through up to 64 entries (0x3F)
    for (uint32_t i = 0; i < 64; i++) {
        if (entries[i].id == entryId) {
            // Found matching entry, call the handler with index and parameters
            if (i != 0xFFFFFFFF) { // safety check for negative index (though i is unsigned)
                processEntry(i, param2, param3);
                return true;
            }
            break;
        }
    }

    return false;
}