// FUNC_NAME: findKeyInFlagTable
// Function address: 0x004430c0
// Searches a key-value pair table for a given key (passed in EDI register).
// Returns 1 (lower byte) with index in upper bits if found, else 0.
// The table structure has entries array at +0x18 and count at +0x1c.
// Each pair: first element = key (int), second element = flag (bool, stored as int).

// Note: The key to search for is expected in the EDI register before the call.
// This is a fastcall function; first param (ecx) is unused.

#include <cstdint>

// Table structure
struct KeyFlagEntry {
    int key;    // +0x00
    int flag;   // +0x04 (treated as bool, non-zero = true)
};

struct KeyFlagTable {
    struct KeyFlagEntry* entries;  // +0x18
    int count;                     // +0x1c
};

uint32_t __fastcall findKeyInFlagTable(void* unused, struct KeyFlagTable* table, bool* outFlag)
{
    int searchKey; // assumed to be in EDI register prior to call
    // In the original code, EDI (unaff_EDI) holds the key to find.
    // For reconstruction we treat it as an implicit parameter.

    // If table has no entries, return failure.
    if (table->count == 0) {
        return 0;  // failure, lower byte zero
    }

    // Linear search through the entries array.
    for (int i = 0; i < table->count; i++) {
        if (table->entries[i].key == searchKey) {
            // Found: output the flag value from the pair.
            *outFlag = (table->entries[i].flag != 0);
            // Return success (1) in low byte, index in upper bits.
            return (static_cast<uint32_t>(i) << 8) | 1;
        }
    }

    // Key not found.
    return 0;
}